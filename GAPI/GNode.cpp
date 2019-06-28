#include "GNode.h"
	
NodeCounter::NodeCounter(void)
{

}

NodeCounter::~NodeCounter(void)
{

}

	int NodeCounter::GetCounter()
	{
		return counter;
	}
	void NodeCounter::SetCounter(const int &iNumber)
	{
		if (iNumber > 0)
		{
			counter++;
		}
		else if (iNumber < 0)
		{
			counter--;
		}
	}
int NodeCounter::counter;
GNode::GNode(const std::string &iName)
{
	this->m_name = iName;
	this->m_connected = false;
	NodeCounter::SetCounter(1);
}

GNode::~GNode(void)
{
	
}

ReturnCode GNode::connect(GNode *ipNode)
{
	ReturnCode rc= RC_ParameterError;

	if (ipNode == NULL) 
	{
		return rc;
	}
	if (ipNode->m_connected == true && containsNode(ipNode->getName()))
	{
		rc = RC_ValueError;
	}
	else
	{
		ipNode->m_connected = true;
		this->m_connected = true;
		m_conn_Nodes.push_back(*ipNode);
		ipNode->m_conn_Nodes.push_back(*this);
		rc = RC_OK;
	}

	return rc;
}

ReturnCode GNode::disconnect(GNode *ipNode)
{
	ReturnCode rc = RC_ParameterError;
	
	if (ipNode == NULL) 
	{
		return rc;
	}
	if (ipNode->m_connected == false || getNumConnectedTo() == 0)
	{
		rc = RC_ValueError;
	}
	else
	{
			m_conn_Nodes.remove(*getNode(ipNode->getName()));
			ipNode->m_connected = false;
			ipNode->m_conn_Nodes.remove(*this);

			if (m_conn_Nodes.size() == 0)
			{
				m_connected = false;
			}
			rc = RC_OK;
	}
    return rc;
}

bool GNode::operator==(const GNode &other) const
{
	return (m_name == other.m_name && m_conn_Nodes == other.m_conn_Nodes);
}

ReturnCode GNode::disconnectAll()
{
	if (getNumConnectedTo() == 0)
	{
		return RC_ValueError;
	}

	m_conn_Nodes.clear();
    return RC_OK;
}

int GNode::getNumConnectedTo()
{
    return m_conn_Nodes.size();
}


std::list<GNode> GNode::getConnectedNodes()
{
	return m_conn_Nodes;
}
bool GNode::containsNode(std::string name)
{
	for (auto itr = m_conn_Nodes.begin(); itr != m_conn_Nodes.end(); itr++)
	{
		if (itr->getName() == name)
		{
			return true;
		}
	}
	return false;
}

ReturnCode GNode::deleteNode(GNode *iNode)
{
	if (iNode != NULL  && iNode->m_connected == false)
	{
		iNode->~GNode();
		iNode = nullptr;
		NodeCounter::SetCounter(-1);
		return RC_OK;
	}
	return RC_ValueError;
}

GNode* GNode::getNode(const std::string& iName) 
{
	for (auto itr = m_conn_Nodes.begin(); itr != m_conn_Nodes.end(); itr++)
	{
		if (itr->getName() == iName)
		{
			return &*itr;
		}
	}
	return NULL;
}