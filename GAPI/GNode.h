#pragma once

#include "GAPI.h"

#include <string>
#include <list>
#include <vector>

class GAPI_API NodeCounter
{
	static int counter;
	
	public:
	NodeCounter(void);
	virtual ~NodeCounter(void);
	static int GetCounter(void);
	static void SetCounter(const int &iNumber);
};

/**
 * GNode class represents a node in a given graph. Each node is 
 * identified by a unique name.
 **/
class GAPI_API GNode
{
public:
    GNode(const std::string &iName);
    ~GNode(void);
    
	int getNumConnectedTo();
	std::list<GNode> getConnectedNodes();

    const std::string& getName() {return m_name;}
	bool GNode::operator==(const GNode &other) const;
    
    //
    //Connect this node to given ipNode
    //
    ReturnCode connect(GNode *ipNode);
    
    //
    //Break the connection between this node and given ip node
    //if exists.
    //
    ReturnCode disconnect(GNode *ipNode);
    
    //
    //Disconnect all connections of this node.
    //
    ReturnCode disconnectAll();
	ReturnCode deleteNode(GNode *iNode);
	

    //
    //Get number of nodes which this node connects to
    //
 
bool containsNode(std::string name);

private:
	
    std::string m_name;
	bool m_connected;
	std::list<GNode> m_conn_Nodes;
	GNode* getNode(const std::string& iName);
	
};
