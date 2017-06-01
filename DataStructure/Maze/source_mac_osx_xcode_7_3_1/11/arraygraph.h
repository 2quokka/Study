#ifndef ARRAY_GRAPH
#define ARRAY_GRAPH

#define ARRAY_GRAPH_TYPE_DIRECT         0
#define ARRAY_GRAPH_TYPE_UNDIRECT       1

typedef struct ArrayGraphType
{
    int graphType;
    int nodeCount;	// �ִ� ��� ����
    int **ppEdge;	// ���� ������ ���� 2���� �迭
} ArrayGraph;

ArrayGraph* createArrayGraph(int graphType, int nodeCount);
int checkVertexValid(ArrayGraph *pGraph, int node);
int addEdgeInternalAG(ArrayGraph* pGraph, int fromNode, int toNode);
int addEdgeAG(ArrayGraph* pGraph, int fromNode, int toNode);
int removeEdgeInternalAG(ArrayGraph* pGraph, int fromNode, int toNode);
int getEdgeAG(ArrayGraph* pGraph, int fromNode, int toNode);
void displayGraphAG(ArrayGraph* pGraph);
void deleteGraphAG(ArrayGraph* pGraph);
#endif
