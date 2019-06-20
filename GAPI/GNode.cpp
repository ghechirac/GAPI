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
	if (ipNode->m_connected == false)
	{
		rc = RC_ValueError;
	}
	else
	{
		
		ipNode->m_connected = false;
		//for(int i=1; i< m_conn_Nodes.size();i++)
		for (auto itr = m_conn_Nodes.begin();
			itr != m_conn_Nodes.end(); itr++) {
			//
		}
		m_conn_Nodes.remove(*ipNode);
		//m_conn_Nodes.get_allocator();
		rc = RC_OK;
	}
    return rc;
}

ReturnCode GNode::disconnectAll()
{
	if (getNumConnectedTo() == 0)
	{
		return RC_ValueError;
	}
	//m_counter = 0;
	//should have a list of connected nodes, of type nodes
	//neighbours, and at the connect time the info should be stored at the dissconect time the info should be deleted
    return RC_OK;
}

int GNode::getNumConnectedTo()
{
    return m_conn_Nodes.size();
}