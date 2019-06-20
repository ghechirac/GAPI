#pragma once

#include "GAPI.h"

#include <string>
#include <list>
#include <vector>

/**
 * GNode class represents a node in a given graph. Each node is 
 * identified by a unique name.
 **/
class GAPI_API GNode
{
public:
    GNode(const std::string &iName);
    ~GNode(void);
    
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

    //
    //Get number of nodes which this node connects to
    //
    int getNumConnectedTo();
private:
    std::string m_name;
	bool m_connected;
	std::list<GNode> m_conn_Nodes;
};