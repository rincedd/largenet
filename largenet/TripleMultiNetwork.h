/**
 * This work is licensed under the Creative Commons
 * Attribution-NonCommercial 3.0 Unported License. To view a copy of this
 * license, visit http://creativecommons.org/licenses/by-nc/3.0/ or send a
 * letter to Creative Commons, 444 Castro Street, Suite 900, Mountain View,
 * California, 94041, USA.
 */
/**
 * @file TripleMultiNetwork.h
 * @date 12.05.2009
 * @author gerd
 */

#ifndef TRIPLEMULTINETWORK_H_
#define TRIPLEMULTINETWORK_H_

#include <largenet/base/types.h>
#include <largenet/base/Node.h>
#include <largenet/base/TLink.h>
#include <largenet/base/Triple.h>
#include <largenet/base/TypedNetwork.h>
#include <largenet/base/repo/CategorizedRepository.h>
#include <cassert>

namespace lnet
{

class TripleMultiNetwork: public TypedNetwork<Node, TLink>
{
protected:
	// member types
	typedef repo::CategorizedRepository<Triple> TripleRepo;
public:
	typedef Triple TripleType;
	typedef TripleRepo::IndexIterator TripleIterator;
	typedef TripleRepo::CategoryIterator TripleStateIterator;
	typedef TripleRepo::IndexIteratorRange TripleIteratorRange;
	typedef TripleRepo::CategoryIteratorRange TripleStateIteratorRange;

	typedef TLink::TripleIDIterator NeighborTripleIterator;
	typedef TLink::TripleIDIteratorRange NeighborTripleIteratorRange;

	typedef count_triples_tag triple_counting_category;

public:
	/**
	 * Default constructor.
	 */
	TripleMultiNetwork();
	TripleMultiNetwork(id_size_t nNodes, id_size_t nLinks,
			node_state_size_t nNodeStates, LinkStateCalculator* lsCalc = 0,
			TripleStateCalculator* tsCalc = 0);
	TripleMultiNetwork(const TripleMultiNetwork& net);
	virtual ~TripleMultiNetwork();

	triple_state_size_t numberOfTripleStates() const;
	id_size_t numberOfTriples() const;
	id_size_t numberOfTriples(triple_state_t s) const;

	void setTripleStateCalculator(TripleStateCalculator* tsCalc);
	const TripleStateCalculator& getTripleStateCalculator() const;

	link_id_t left(triple_id_t t) const;
	link_id_t right(triple_id_t t) const;

	node_id_t leftNode(triple_id_t t) const;
	node_id_t centerNode(triple_id_t t) const;
	node_id_t rightNode(triple_id_t t) const;

	TripleIteratorRange triples() const;
	TripleStateIteratorRange triples(triple_state_t s) const;

	NeighborTripleIteratorRange neighborTriples(link_id_t l) const;

	std::pair<bool, triple_id_t> randomTriple() const;
	std::pair<bool, triple_id_t> randomTriple(triple_state_t s) const;

protected:
	/**
	 * Create a link between two nodes, given by their unique IDs. The link
	 * state is determined using the internal link state calculator.
	 * @param source Unique ID of the source node
	 * @param target Unique ID of the target node
	 * @return Unique ID of link created
	 */
	virtual link_id_t doAddLink(node_id_t source, node_id_t target);

	/**
	 * Change link to connect the new @p source with the new @p target.
	 * If you need link rewiring, use this instead of removing and
	 * adding a link. Here, the link is not deleted, thus keeping its link ID.
	 * Returns true.
	 * @param l	Unique ID of link to change.
	 * @param source New source node ID.
	 * @param target New target node ID.
	 * @return true
	 */
	virtual bool doChangeLink(link_id_t l, node_id_t source, node_id_t target);

	/**
	 * Remove link with unique ID @p l
	 * @param l ID of link to remove.
	 */
	virtual void doRemoveLink(link_id_t l);

	/**
	 * Remove all links in network.
	 */
	virtual void doRemoveAllLinks();

	/**
	 * Remove node with unique ID @p n.
	 * @param n	ID of node to be removed.
	 */
	virtual void doRemoveNode(node_id_t n);

	virtual void onNodeStateChange(node_id_t n);

	Triple& triple(triple_id_t t) const;
	bool isValidTripleStateCalculator(TripleStateCalculator* tsCalc) const;

	void doReset(id_size_t nNodes, id_size_t nLinks,
			node_state_size_t nNodeStates);

private:
	void addTriple(link_id_t left, link_id_t right);
	void removeTriplesFromLinkEnd(link_id_t l, bool fromSource);

protected:
	TripleRepo* tripleStore_;
	TripleStateCalculator* tsCalc_;
	bool tscOwn_;
};

inline triple_state_size_t TripleMultiNetwork::numberOfTripleStates() const
{
	return tripleStore_->numberOfCategories();
}

inline id_size_t TripleMultiNetwork::numberOfTriples() const
{
	return tripleStore_->size();
}

inline id_size_t TripleMultiNetwork::numberOfTriples(const triple_state_t s) const
{
	return tripleStore_->count(s);
}

inline TripleMultiNetwork::NeighborTripleIteratorRange TripleMultiNetwork::neighborTriples(
		const link_id_t l) const
{
	return link(l).triples();
}

inline TripleMultiNetwork::TripleIteratorRange TripleMultiNetwork::triples() const
{
	return tripleStore_->ids();
}

inline TripleMultiNetwork::TripleStateIteratorRange TripleMultiNetwork::triples(
		const triple_state_t s) const
{
	return tripleStore_->ids(s);
}

inline Triple& TripleMultiNetwork::triple(const triple_id_t t) const
{
	return (*tripleStore_)[t];
}

inline link_id_t TripleMultiNetwork::left(const triple_id_t t) const
{
	return triple(t).left();
}

inline link_id_t TripleMultiNetwork::right(const triple_id_t t) const
{
	return triple(t).right();
}

inline const TripleStateCalculator& TripleMultiNetwork::getTripleStateCalculator() const
{
	return *tsCalc_;
}

}

#endif /* TRIPLEMULTINETWORK_H_ */
