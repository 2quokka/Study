#ifndef LIST_GRAPH
#define LIST_GRAPH

#include "linkedlist.h"

#define LINKED_GRAPH_TYPE_DIRECT         0
#define LINKED_GRAPH_TYPE_UNDIRECT       1

typedef struct LinkedGraphType
{
    int graphType;    
    int nodeCount;          // ��� ����
    LinkedList** ppAdjEdge;	// ���� ������ ���� ���� ����Ʈ (������)�� �迭
}  LinkedGraph;

LinkedGraph* createLinkedGraph(int graphType, int nodeCount);
int checkVertexValid(LinkedGraph* pGraph, int node);
int addEdgeInternalLG( LinkedGraph* pGraph, int fromNode, int toNode);
int addEdgeLG( LinkedGraph* pGraph, int fromNode, int toNode);
int removeEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode);
int removeEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode);
int getEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode);
void displayGraphLG( LinkedGraph* pGraph);
void deleteGraphLG( LinkedGraph* pGraph);
#endif
