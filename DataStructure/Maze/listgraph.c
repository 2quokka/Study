#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "listgraph.h"

LinkedGraph* createLinkedGraph(int graphType, int nodeCount)
{
    int i = 0;
    LinkedGraph *pReturn = NULL;
    
    if (nodeCount > 0)	{
        pReturn = ( LinkedGraph *)malloc(sizeof( LinkedGraph));
        if (pReturn == NULL) {
            printf("오류, 메모리할당(1), in createLinkedGraph()\n");
            return NULL;
        }
        pReturn->graphType = graphType;
        pReturn->nodeCount = nodeCount;
    }
    else {
        printf("오류, 최대 노드 개수는 0보다 커야합니다\n");
        return NULL;
    }
    
    pReturn->ppAdjEdge = (LinkedList **)malloc(sizeof(LinkedList*) * nodeCount);
    if (pReturn->ppAdjEdge == NULL) {
        printf("오류, 메모리할당(3), in createLinkedGraph()\n");
        if (pReturn != NULL)  free(pReturn);
        return NULL;
    }
    for(i = 0; i < nodeCount; i++) {
        pReturn->ppAdjEdge[i] = createLinkedList();
        if (pReturn->ppAdjEdge[i] == NULL) {
            printf("오류, 메모리할당(4), in createLinkedGraph()\n");
            if (pReturn->ppAdjEdge != NULL)  free(pReturn->ppAdjEdge);
            if (pReturn != NULL)  free(pReturn);
            return NULL;
        }
    }
    
    return pReturn;
}

int checkVertexValid(LinkedGraph* pGraph, int node)
{
    if (pGraph != NULL && node >= 0 && node < pGraph->nodeCount) {
        return 1;
    }
    else {
        return 0;
    }
}

int addEdgeInternalLG( LinkedGraph* pGraph, int fromNode, int toNode)
{
    int ret = 0;
    
    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        addLinkedListData(pGraph->ppAdjEdge[fromNode], 0, toNode);
    }
    else {
        ret = -1;
    }
    
    return ret;
}

int addEdgeLG( LinkedGraph* pGraph, int fromNode, int toNode)
{
    int ret = 0;
    
    ret = addEdgeInternalLG(pGraph, fromNode, toNode);
    if (0 == ret && LINKED_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = addEdgeInternalLG(pGraph, toNode, fromNode);
    }
    
    return ret;
}

int removeEdgeInternalLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
    int ret = -1;
    LinkedList *pList = NULL;
    int i = 0, count = 0;
    
    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);
        for(i = 0; i < count; i++) {
            if (getLinkedListData(pList, i) == toNode) {
                removeLinkedListData(pList, i);
                ret = 0;
                break;
            }
        }
    }
    else {  // 해당되는 간선이 없는 경우 (삭제에 실패한 경우).
        ret = -1;
    }
    
    return ret;
}


int removeEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
    int ret = -1;
    
    ret = removeEdgeInternalLG(pGraph, fromNode, toNode);
    if (0 == ret && LINKED_GRAPH_TYPE_UNDIRECT == pGraph->graphType) {
        ret = removeEdgeInternalLG(pGraph, toNode, fromNode);
    }
    
    return ret;
}

int getEdgeLG(LinkedGraph* pGraph, int fromNode, int toNode)
{
    int ret = 0;
    LinkedList *pList = NULL;
    int i = 0, count = 0;
    
    if (pGraph != NULL
        && checkVertexValid(pGraph, fromNode)
        && checkVertexValid(pGraph, toNode)) {
        pList = pGraph->ppAdjEdge[fromNode];
        count = getLinkedListLength(pList);
        for(i = 0; i < count; i++) {
            if (getLinkedListData(pList, i) == toNode) {
                ret = 1;
                break;
            }
        }
    }
    
    return ret;
}

void displayGraphLG( LinkedGraph* pGraph)
{
    int i = 0, j = 0, count = 0;
    
    if (pGraph != NULL) {
        count = pGraph->nodeCount;
        for(i = 0; i < count; i++)	{
            for(j = 0; j < count; j++) {
                if (getEdgeLG(pGraph, i, j)) {
                    printf("1 ");
                }
                else {
                    printf("0 ");
                }
            }
            printf("\n");
        }
    }
}

void deleteGraphLG( LinkedGraph* pGraph)
{
    int i = 0;
    
    if (pGraph != NULL) {
        for(i = 0; i < pGraph->nodeCount; i++) {
            deleteLinkedList(pGraph->ppAdjEdge[i]);
        }
        if (pGraph->ppAdjEdge != NULL) free(pGraph->ppAdjEdge);
        free(pGraph);
    }
}

