/**
 * @file TripleNetwork.cpp
 * @date 13.05.2009
 * @author gerd
 */

#include "TripleNetwork.h"

namespace lnet
{

TripleNetwork::TripleNetwork() :
	TripleMultiNetwork()
{
}

TripleNetwork::TripleNetwork(const id_size_t nNodes, const id_size_t nLinks,
		const id_size_t nNodeStates, const id_size_t nLinkStates,
		const id_size_t nTripleStates, LinkStateCalculator* lsCalc,
		TripleStateCalculator* tsCalc) :
	TripleMultiNetwork(nNodes, nLinks, nNodeStates, nLinkStates, nTripleStates,
			lsCalc, tsCalc)
{
}

TripleNetwork::~TripleNetwork()
{
}

link_id_t TripleNetwork::addLink(const node_id_t source, const node_id_t target)
{
	std::pair<bool, link_id_t> linkExists = isLink(source, target);
	link_id_t l;
	if (!linkExists.first)
	{
		l = TripleMultiNetwork::addLink(source, target);
	}
	else
	{
		l = linkExists.second;
	}
	return l;
}

bool TripleNetwork::changeLink(const link_id_t l, const node_id_t source,
		const node_id_t target)
{
	if (isLink(source, target).first)
		return false;

	return TripleMultiNetwork::changeLink(l, source, target);
}

}