#include "GNode.h"


GNode::GNode(const std::string &iName)
{
	this->m_name = iName;
	//this->m_conn_Nodes = 
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
	if (ipNode->m_connected == true)
	{
		rc = RC_ValueError;
	}
	else
	{
		ipNode->m_connected = true;
		m_conn_Nodes.push_back(*ipNode);
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
		
		//ipNode->m_connected = false;
		//for(int i=1; i< m_conn_Nodes.size();i++)
		//for (auto itr = m_conn_Nodes.begin();
		//	itr != m_conn_Nodes.end(); itr++) {
		//	//
		//}
	

			m_conn_Nodes.remove(*ipNode);
			ipNode->m_connected = false;
		//m_conn_Nodes.get_allocator();
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

	//for (auto itr = m_conn_Nodes.begin(); itr != m_conn_Nodes.end(); itr++)
	//{
	//	itr->m_connected = false;
	//}
	m_conn_Nodes.clear();

	//for (int i = 1; i < m_conn_Nodes.size(); i++)
	//{
	//	m_conn_Nodes[i]
	//}



	//m_counter = 0;
	//should have a list of connected nodes, of type nodes
	//neighbours, and at the connect time the info should be stored at the dissconect time the info should be deleted
    return RC_OK;
}

int GNode::getNumConnectedTo()
{
    return m_conn_Nodes.size();
}