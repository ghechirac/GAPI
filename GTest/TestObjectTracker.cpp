#include "TestObjectTracker.h"

#include "../GAPI/GNode.h"
#include "../GAPI/GGraph.h"
#include "../GAPI/GraphCounter.cpp"

TestObjectTracker::TestObjectTracker(void)
{
}

TestObjectTracker::~TestObjectTracker(void)
{
    tearDown("");
}


void TestObjectTracker::run()
{
    RUN_TEST(testNode);
    //RUN_TEST(testGraph);
    //RUN_TEST(testNodeWithConnection);
    //RUN_TEST(testGraphWithNodes);
}

int TestObjectTracker::setUp(const std::string& iTestName)
{
    return 0;
}

void TestObjectTracker::tearDown(const std::string& iTestName)
{
}

void TestObjectTracker::testNode()
{
	const std::string rootNode = "root_node";
	GGraph *pGraph = new GGraph("graph_1");

	GNode *pNode_1 = pGraph->addNode(rootNode);
	GNode *pNode_2 = pGraph->addNode("node_2");
	GNode *pNode_3 = pGraph->addNode("node_3");
	GNode *pNode_4 = pGraph->addNode("node_4");
	GNode *pNode_5 = pGraph->addNode("node_5");

	pGraph->getNode(pNode_1->getName())->connect(pNode_2);
	pGraph->getNode(pNode_1->getName())->connect(pNode_3);
	pGraph->getNode(pNode_1->getName())->connect(pNode_4);
	pGraph->getNode(pNode_1->getName())->connect(pNode_5);

	ASSERT_EQUALS(pGraph->getNumNodes(), 5);
	ASSERT_EQUALS(pGraph->getNode(rootNode)->getNumConnectedTo(), 4);
	
	pGraph->getNode(rootNode)->disconnect(pNode_2);

	ASSERT_EQUALS(pGraph->getNumNodes(), 5);
	ASSERT_EQUALS(pGraph->getNode(rootNode)->getNumConnectedTo(), 3);
}

void TestObjectTracker::testGraph()
{
	//int graphCounter = GraphCounter::getNumGraph();

	//GGraph *graph_1 = new GGraph("graph_1");
	//GGraph *graph_2 = new GGraph("graph_2");

	//int graphCounterAfterCreation = GraphCounter::getNumGraph();
	//ASSERT_EQUALS(graphCounterAfterCreation,graphCounter+2);

}

void TestObjectTracker::testNodeWithConnection()
{
	const std::string rootNode = "root_node";
	//GGraph *pGraph = new GGraph("graph_1");

	GNode *pNode_1 = new GNode(rootNode);
	GNode *pNode_2 = new GNode("node_2");
	GNode *pNode_3 = new GNode("node_3");
	GNode *pNode_4 = new GNode("node_4");
	GNode *pNode_5 = new GNode("node_5");

	pNode_1->connect(pNode_2);
	pNode_1->connect(pNode_3);
	pNode_1->connect(pNode_4);
	pNode_1->connect(pNode_5);
	int connNodes = pNode_1->getNumConnectedTo();
	ASSERT_EQUALS(connNodes, 4);
	//create a node tracker object, append all node when they are created.
	// at delete time, if node is not connected, RC_OK, if node is connected RC_Error

	
	

}

void TestObjectTracker::testGraphWithNodes()
{
    //TO BE IMPLEMENTED
}
