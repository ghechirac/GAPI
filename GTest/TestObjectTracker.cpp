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
	//TO BE IMPLEMENTED
}

void TestObjectTracker::testGraphWithNodes()
{
    //TO BE IMPLEMENTED
}
