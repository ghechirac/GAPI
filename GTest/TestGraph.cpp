#include "TestGraph.h"
#include "../GAPI/GGraph.h"
#include "../GAPI/GNode.h"
#include <chrono>
#include <ctime>
#include <algorithm>
#include <string>

TestGraph::TestGraph(void)
{
}

TestGraph::~TestGraph(void)
{
}


void TestGraph::run()
{
    RUN_TEST(testConstruct);
    RUN_TEST(testAddNode);
    RUN_TEST(testRemoveNode);
 	RUN_TEST(testNodeAccess);
    RUN_TEST(testSaveLoad);
}

//
//
//
int TestGraph::setUp(const std::string& iTestName)
{
    return 0;
}

//
//
//
void TestGraph::tearDown(const std::string& iTestName)
{
}

//
//
//
void TestGraph::testConstruct()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), 0);
}

//
//
//
void TestGraph::testAddNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_NOT_EQUALS(pGraph, NULL);
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->addNode(""), NULL);

    GNode *pNode_na = pGraph->addNode("na");
    ASSERT_NOT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
    pNode_na = NULL;

    pNode_na = pGraph->addNode("na");
    ASSERT_EQUALS(pNode_na, NULL);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes + 1);
}

//
//
//
void TestGraph::testRemoveNode()
{
    GGraph *pGraph = new GGraph("ga");
    ASSERT_EQUALS(pGraph->removeNode(""), RC_ParameterError);
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
    
    pGraph->addNode("na");
    int numNodes = pGraph->getNumNodes();
    
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_OK);
    ASSERT_EQUALS(pGraph->getNumNodes(), numNodes - 1);
    ASSERT_EQUALS(pGraph->removeNode("na"), RC_ValueError);
}


void TestGraph::testNodeAccess()
{
	GGraph *pGraph = new GGraph("ga");
	ASSERT_EQUALS(pGraph->getNode("na"), NULL);
	GNode *pNode = pGraph->addNode("na");
	ASSERT_EQUALS(pGraph->getNode("na") ,pGraph->getNode(pNode->getName()));
}

void TestGraph::testSaveLoad()
{
	GGraph *pGraph = new GGraph("graph_1");

	GNode *pNode_1 = pGraph->addNode("node_1");
	GNode *pNode_2 = pGraph->addNode("node_2");
	GNode *pNode_3 = pGraph->addNode("node_3");
	GNode *pNode_4 = pGraph->addNode("node_4");
	GNode *pNode_5 = pGraph->addNode("node_5");
	
	//pGraph->getNode(pNode_2->getName())
	pGraph->getNode(pNode_1->getName())->connect(pGraph->getNode(pNode_2->getName()));
	pGraph->getNode(pNode_1->getName())->connect(pGraph->getNode(pNode_3->getName()));
	pGraph->getNode(pNode_1->getName())->connect(pGraph->getNode(pNode_4->getName()));
	pGraph->getNode(pNode_1->getName())->connect(pGraph->getNode(pNode_5->getName()));
	//pGraph->getNode(pNode_1->getName())
	pGraph->getNode(pNode_2->getName())->connect(pGraph->getNode(pNode_1->getName()));
	pGraph->getNode(pNode_2->getName())->connect(pGraph->getNode(pNode_3->getName()));
	pGraph->getNode(pNode_2->getName())->connect(pGraph->getNode(pNode_4->getName()));
	pGraph->getNode(pNode_2->getName())->connect(pGraph->getNode(pNode_5->getName()));

	pGraph->getNode(pNode_3->getName())->connect(pGraph->getNode(pNode_2->getName()));
	pGraph->getNode(pNode_3->getName())->connect(pGraph->getNode(pNode_1->getName()));
	pGraph->getNode(pNode_3->getName())->connect(pGraph->getNode(pNode_4->getName()));
	pGraph->getNode(pNode_3->getName())->connect(pGraph->getNode(pNode_5->getName()));

	pGraph->getNode(pNode_4->getName())->connect(pGraph->getNode(pNode_2->getName()));
	pGraph->getNode(pNode_4->getName())->connect(pGraph->getNode(pNode_3->getName()));
	pGraph->getNode(pNode_4->getName())->connect(pGraph->getNode(pNode_1->getName()));
	pGraph->getNode(pNode_4->getName())->connect(pGraph->getNode(pNode_5->getName()));

	pGraph->getNode(pNode_5->getName())->connect(pGraph->getNode(pNode_1->getName()));
	pGraph->getNode(pNode_5->getName())->connect(pGraph->getNode(pNode_2->getName()));
	pGraph->getNode(pNode_5->getName())->connect(pGraph->getNode(pNode_3->getName()));
	pGraph->getNode(pNode_5->getName())->connect(pGraph->getNode(pNode_4->getName()));

	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::time_point::clock().now());

	std::string filename = std::ctime(&t);
	filename = filename.substr(0, filename.size() - 1);
	std::replace(filename.begin(), filename.end(), ':', '_');
	filename = filename + ".txt";

	ASSERT_EQUALS(pGraph->save(filename) , RC_OK);
	
	GGraph *loadedGraph = pGraph->load(filename);

	ASSERT_EQUALS(true,pGraph->CompareGraph(loadedGraph));

	GGraph *loadedGraph_wrong = pGraph->load("nokGraph.txt");
	ASSERT_EQUALS(false, pGraph->CompareGraph(loadedGraph_wrong));

}
