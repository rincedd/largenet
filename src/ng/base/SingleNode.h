/**
 * @file SingleNode.h
 * @date 01.09.2009
 * @author gerd
 */

#ifndef SINGLENODE_H_
#define SINGLENODE_H_

#include "Node.h"

namespace largenet {

class SingleNode: public Node
{
public:
	SingleNode(node_id_t id) : Node(id) {}
	virtual ~SingleNode() {}
	virtual degree_size_t outDegree() const { return outEdges_.size(); }
	virtual degree_size_t inDegree() const { return inEdges_.size(); }
	virtual bool hasInEdge(Edge* e) const { return inEdges_.find(e) != inEdges_.end(); }
	virtual bool hasOutEdge(Edge* e) const { return outEdges_.find(e) != outEdges_.end(); }
	virtual bool hasEdgeTo(const Node* n) const;
	virtual bool hasEdgeFrom(const Node* n) const;
	virtual Edge* edgeTo(const Node* n) const;
	virtual Edge* edgeFrom(const Node* n) const;
	virtual edge_iterator_range outEdges() const { return std::make_pair(outEdges_.begin(), outEdges_.end()); }
	virtual edge_iterator_range inEdges() const { return std::make_pair(inEdges_.begin(), inEdges_.end()); }
	virtual OutNeighborIteratorRange outNeighbors() const { return std::make_pair(OutNeighborIterator(outEdges_.begin()), OutNeighborIterator(outEdges_.end())); }
	virtual InNeighborIteratorRange inNeighbors() const { return std::make_pair(InNeighborIterator(inEdges_.begin()), InNeighborIterator(inEdges_.end())); }

protected:
	virtual void registerEdge(Edge* e);
	virtual void unregisterEdge(Edge* e);

private:
	edge_set outEdges_, inEdges_;
};

}

#endif /* SINGLENODE_H_ */
