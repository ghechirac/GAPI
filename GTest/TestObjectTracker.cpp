#include "TestObjectTracker.h"

#include "../GAPI/GNode.h"
#include "../GAPI/GGraph.h"

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
    RUN_TEST(testGraph);
    RUN_TEST(testNodeWithConnection);
    RUN_TEST(testGraphWithNodes);
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
	pGraph->DelGraph(pGraph);
	
}

void TestObjectTracker::testGraph()
{
	int graphCounter = GraphCounter::GetCounter();

	GGraph *graph_1 = new GGraph("graph_1");
	GGraph *graph_2 = new GGraph("graph_2");

	int graphCounterAfterCreation = GraphCounter::GetCounter();
	ASSERT_EQUALS(graphCounterAfterCreation,graphCounter+2);
	graph_1->DelGraph(graph_1);
	graph_2->DelGraph(graph_2);

	int graphCounterAfterDeletion = GraphCounter::GetCounter();

	ASSERT_EQUALS(graphCounterAfterCreation - 2, graphCounterAfterDeletion);

}

void TestObjectTracker::testNodeWithConnection()
{
	const std::string rootNode = "root_node";
	int nodeCounterInitial = NodeCounter::GetCounter();
	
	GNode *pNode_1 = new GNode(rootNode);
	GNode *pNode_2 = new GNode("node_2");
	GNode *pNode_3 = new GNode("node_3");
	GNode *pNode_4 = new GNode("node_4");
	GNode *pNode_5 = new GNode("node_5");
	GNode *pNode_6 = new GNode("node_6");

	pNode_1->connect(pNode_2);
	pNode_1->connect(pNode_3);
	pNode_1->connect(pNode_4);
	pNode_1->connect(pNode_5);

	int nodeCounterAfterConnection = NodeCounter::GetCounter();
	int connNodes = pNode_1->getNumConnectedTo();

	ASSERT_EQUALS(connNodes, 4);
	ASSERT_EQUALS(nodeCounterInitial + 6, nodeCounterAfterConnection);
	ASSERT_EQUALS(pNode_1->deleteNode(pNode_1), RC_ValueError);
	ASSERT_EQUALS(pNode_2->deleteNode(pNode_2), RC_ValueError);
	ASSERT_EQUALS(pNode_6->deleteNode(pNode_6), RC_OK);

	int nodeCounterAfterDelete = NodeCounter::GetCounter();
	ASSERT_EQUALS(nodeCounterAfterConnection-1, nodeCounterAfterDelete);
}

void TestObjectTracker::testGraphWithNodes()
{
	int graphCounter = GraphCounter::GetCounter();
	int nodeCounterInitial = NodeCounter::GetCounter();

	const std::string rootNode = "root_node";
	GGraph *graph_1 = new GGraph("graph_1");

	GNode *pNode_1 = graph_1->addNode(rootNode);
	GNode *pNode_2 = graph_1->addNode("node_2");
	GNode *pNode_3 = graph_1->addNode("node_3");
	GNode *pNode_4 = graph_1->addNode("node_4");
	GNode *pNode_5 = graph_1->addNode("node_5");

	graph_1->getNode(pNode_1->getName())->connect(pNode_2);
	graph_1->getNode(pNode_1->getName())->connect(pNode_3);
	graph_1->getNode(pNode_1->getName())->connect(pNode_4);
	graph_1->getNode(pNode_1->getName())->connect(pNode_5);

	GGraph *graph_2 = new GGraph("graph_2");
	GNode *pNode_6 = graph_2->addNode("node_6");
	GNode *pNode_7 = graph_2->addNode("node_7");
	GNode *pNode_8 = new GNode("node_8");
	GNode *pNode_9 = new GNode("node_9");
	graph_2->getNode(pNode_6->getName())->connect(pNode_7);

	int graphCounterAfterCreation = GraphCounter::GetCounter();
	ASSERT_EQUALS(graphCounterAfterCreation, graphCounter + 2);

	int nodeCounterAfterCreate = NodeCounter::GetCounter();
	ASSERT_EQUALS(nodeCounterInitial + 9, nodeCounterAfterCreate);

	nodeCounterAfterCreate = NodeCounter::GetCounter();
	graph_1->getNode(rootNode)->disconnect(pNode_2);
	nodeCounterAfterCreate = NodeCounter::GetCounter();

	ASSERT_EQUALS(graph_1->getNumNodes(), 5);
	ASSERT_EQUALS(graph_1->getNode(rootNode)->getNumConnectedTo(), 3);
	ASSERT_EQUALS(pNode_2->deleteNode(pNode_2),RC_OK);

	int nodeCountAfterDelete = NodeCounter::GetCounter();
	ASSERT_EQUALS(nodeCountAfterDelete , nodeCounterAfterCreate-1);

	int nodeCounterBeforeDelete = NodeCounter::GetCounter();
	ASSERT_EQUALS(pNode_8->deleteNode(pNode_8), RC_OK);
	ASSERT_EQUALS(pNode_9->deleteNode(pNode_9), RC_OK);
	graph_2->getNode(pNode_6->getName())->disconnect(pNode_7);
	ASSERT_EQUALS(pNode_7->deleteNode(pNode_7), RC_OK);
	nodeCountAfterDelete = NodeCounter::GetCounter();
	ASSERT_EQUALS(nodeCountAfterDelete,nodeCounterBeforeDelete -3);

}
