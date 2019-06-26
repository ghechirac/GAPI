#include "GGraph.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <iterator>

	//static int counter;
	GraphCounter::GraphCounter(void)
	{	
		
	}
	
	GraphCounter::~GraphCounter(void)
	{
		
	}
	
	int GraphCounter::GetCounter()
	{
		return counter;
	}

	void GraphCounter::SetCounter(const int &iNumber)
	{
		if(iNumber > 0)
		{
			counter++;
		}
		else if (iNumber < 0)
		{
			counter--;
		}

	}
int GraphCounter::counter;
GGraph::GGraph(const std::string &iName)
{
	this->m_name = iName;
	
	GraphCounter::SetCounter(1);
}

GGraph::~GGraph(void)
{
	
	GraphCounter::SetCounter(-1);
}

GNode* GGraph::addNode(const std::string& iName)
{
	if (iName.empty() || nodeNameInGraph(iName))
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

	if (iName.empty())
	{
		rc = RC_ParameterError;
	}
	else if (!nodeNameInGraph(iName))
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
	std::ofstream myfile;
	try
	{
		myfile.open(iFileName);
		myfile << "*" + this->m_name + "\n";
		for (auto itr = m_graphNodes.begin(); itr != m_graphNodes.end(); itr++)
		{
			myfile << "@" + itr->getName() + "\n";
			std::list<GNode> myList = itr->getConnectedNodes();
			for (auto n_itr = myList.begin(); n_itr != myList.end(); n_itr++)
			{
				myfile << n_itr->getName() + "\n";
			}
		}
		myfile.close();

	}
	catch (int e)
	{
		return RC_ParameterError;
	}
	
	return RC_OK;
}

GGraph* GGraph::load(const std::string& iFileName)
{
	std::string line;
	std::ifstream myfile(iFileName);
	if (myfile.is_open())
	{
		GGraph *pGraph;
		GNode *pParentNode;
		while (getline(myfile, line))
		{
			if (line.at(0) == '*')
			{
				std::string graphName = line.substr(1, line.size());
				pGraph = new GGraph(graphName);
			}
			else if (line.at(0) == '@')
			{
				std::string nodeName = line.substr(1, line.size());
				pParentNode = pGraph->addNode(nodeName);
			}
			else
			{
				GNode *tmpNode = new GNode(line);
				pGraph->getNode(pParentNode->getName())->connect(tmpNode);
			}
		}
		myfile.close();
		return pGraph;
	}
}

int GGraph::getNumNodes()
{
	return m_graphNodes.size();
}

bool GGraph::nodeNameInGraph(std::string name)
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
void GGraph::DelGraph(GGraph *iGraph)
{
	this->~GGraph();
	iGraph = nullptr;
}
bool GGraph::operator==(const GGraph &other) const
{
	return (m_name == other.m_name && m_graphNodes == other.m_graphNodes);
}
bool GGraph::CompareGraph(GGraph *iGraph)
{
	if (*this == *iGraph)
	{
		for (auto itr = this->m_graphNodes.begin(); itr != this->m_graphNodes.end(); itr++)
		{
			GNode* iGraphNode = iGraph->getNode(itr->getName());
			if (iGraphNode != NULL)
			{
				std::list<GNode> childList = itr->getConnectedNodes();
				for (auto itr_1 = childList.begin(); itr_1 != childList.end(); itr_1++)
				{
					if (!iGraphNode->containsNode(itr_1->getName()))
					{
						return false;
					}
				}
			}
		}
		//std::list<GNode>::sort(m_graphNodes);
		/*m_graphNodes.sort();
		iGraph->m_graphNodes.sort();*/
		/*std::list<GNode> res;
		std::set_difference(m_graphNodes.begin(), m_graphNodes.end(), iGraph->m_graphNodes.begin(), iGraph->m_graphNodes.end(),res);*/
	}
	return true;
}


