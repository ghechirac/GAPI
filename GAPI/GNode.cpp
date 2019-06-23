#include "GNode.h"


GNode::GNode(const std::string &iName)
{
	this->m_name = iName;
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
	if (ipNode->m_connected == true && ipNode->getName() == this->getName())
	{
		rc = RC_ValueError;
	}
	else
	{
		ipNode->m_connected = true;
		m_conn_Nodes.push_back(*ipNode);
		rc = RC_OK;
		this->m_conn_Nodes = m_conn_Nodes;
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
			m_conn_Nodes.remove(*ipNode);
			ipNode->m_connected = false;
		rc = RC_OK;
	}
    return rc;
}

bool GNode::operator==(const GNode &other) const
{
	return (m_name == other.m_name && m_connected == other.m_connected && m_conn_Nodes == other.m_conn_Nodes);
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