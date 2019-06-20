#include "GGraph.h"
#include <algorithm>

GGraph::GGraph(const std::string &iName)
{
}

GGraph::~GGraph(void)
{
}


GNode* GGraph::addNode(const std::string& iName)
{
	if (iName.empty()  || checkNodeName(iName)) 
	{
		return NULL;
	}

	GNode *currentNode = new GNode(iName);
	m_graphNodes.push_back(*currentNode);
    return currentNode;
}

GNode* GGraph::getNode(const std::string& iName)
{
	for (auto itr = m_graphNodes.begin(); itr != m_graphNodes.end(); itr++)
	{
		if (itr->getName() == iName)
		{
			return &*itr;
		}
	}
	return NULL;
}

ReturnCode GGraph::removeNode(const std::string& iName)
{
	ReturnCode rc;
	//if (!iName.empty() && checkNodeName(iName)) 
	//{


	//}
	if (iName.empty())
	{
		rc = RC_ParameterError;
	}
	else if (!checkNodeName(iName))
	{
		rc = RC_ValueError;
	}
	else
	{
		GNode *tmpNode = getNode(iName);
		if (tmpNode != NULL)
		{
			m_graphNodes.remove(*tmpNode);
			rc = RC_OK;
		}
	}
    return rc;
}

ReturnCode GGraph::save(const std::string& iFileName)
{
    return RC_NotImplemented;
}

ReturnCode GGraph::load(const std::string& iFileName)
{
    return RC_NotImplemented;
}

int GGraph::getNumNodes()
{
    return m_graphNodes.size();
}

bool GGraph::checkNodeName(std::string name)
{
	for (auto itr = m_graphNodes.begin(); itr != m_graphNodes.end(); itr++)
	{
		if (itr->getName() == name)
		{
			return true;
		}
	}
	return false;
}


