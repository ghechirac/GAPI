#pragma once

#include "GAPI.h"
#include "GNode.h"
#include <string>
#include <list>

class GNode;

/**
 * GGraph class represents a graph object which is used to group a number of nodes.
 */
 class GAPI_API GraphCounter
{
	
	 static int counter;
	public:
	
	GraphCounter(void);
	virtual ~GraphCounter(void);
	static int GetCounter(void);
	static void SetCounter(const int &iNumber);
	
	
 };
class GAPI_API GGraph
{
public:
    GGraph(const std::string &iName);
    ~GGraph(void);

	bool GGraph::operator==(const GGraph &other) const;
    //
    //Create a new node object and store it in graph for future access
    //Created object is returned to the caller as well
    //
    GNode *addNode(const std::string &iName);

    //
    //Remove the node given by its name.
    //
    ReturnCode removeNode(const std::string &iName);
    
    //
    //Return the node object identified by iName
    //
    GNode* getNode(const std::string& iName);
    
    //
    //Return number of nodes attached to this graph
    //
    int getNumNodes();

    //
    //Dump the current state of the graph to given file
    //
    ReturnCode save(const std::string& iFileName);
    
    //
    //Update the current state of the graph from given file
    //
    GGraph* load(const std::string& iFileName);
	void DelGraph(GGraph *iGraph);
	bool CompareGraph(GGraph *diskGraph);
private:
	std::list<GNode> m_graphNodes;
	bool nodeNameInGraph(std::string name);
	std::string m_name;
};
