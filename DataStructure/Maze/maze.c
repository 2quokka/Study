#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "listgraph.h"
#define INT_MAX 999999
#define true 1
#define false 0

//#define DEBUG
void connectPath(LinkedGraph *lg, int **matrix, int row, int column){
    int i, j, node, objNode;
    for(i = 0 ; i < row ; i++){
        for(j = 0 ; j < column ; j++){
            node = matrix[i][j];

            if(node != -1){
                
                if(i > 0) //up
                {
                    objNode = matrix[i-1][j];
                    if(objNode != -1){
                        if(!getEdgeLG(lg, node, objNode))
                        {
                            addEdgeLG(lg, node, objNode);
                        }
                    }
                }

                if( i < row - 1) // down
                {
                    objNode = matrix[i+1][j];
                    if(objNode != -1){
                        if(!getEdgeLG(lg, node, objNode))
                        {
                            addEdgeLG(lg, node, objNode);
                        }
                    }     
                }

                if( j > 0 ) //left
                {
                    objNode = matrix[i][j-1];
                    if(objNode != -1){
                        if(!getEdgeLG(lg, node, objNode))
                        {
                            addEdgeLG(lg, node, objNode);
                        }
                    }
                }

                if(j < column - 1 ) //right
                {
                    objNode = matrix[i][j+1];
                    if(objNode != -1){
                        if(!getEdgeLG(lg, node, objNode))
                        {
                            addEdgeLG(lg, node, objNode);
                        }
                    }
                }
            }
        }
    }
}

int dijkstra(LinkedGraph *lg, int start, int end, int **path){
    int vCount = lg -> nodeCount;
    int *isVisits = malloc(sizeof(int) * vCount);
    int *distance = malloc(sizeof(int) * vCount);
    int *historyPath = malloc(sizeof(int) * vCount);
    int vertex, nextVertex = start;
    int min = 0;
    int i, j, distanceVertex;

    for ( i = 0 ; i < vCount ; i ++ ) {
        isVisits[i] = false;
        distance[i] = INT_MAX;
        historyPath[i] = INT_MAX;
    }
    distance[start] = 0;

    while(true){
        min = INT_MAX;
        for( j = 0 ; j < vCount ; j++ ){
            if (isVisits[j] == false && distance[j] < min) {

                nextVertex = j;
                min = distance[j];
            }
        }
        if (min == INT_MAX)
            break;
        isVisits[nextVertex] = true;

        for ( j = 0 ; j < vCount ; j ++){
            distanceVertex = distance[nextVertex] + (getEdgeLG(lg, nextVertex, j) ? 1 : INT_MAX );
            if (distance[j] > distanceVertex)
            {
                distance[j] = distanceVertex;
                historyPath[j] = nextVertex;
            }
        }
    }

    vertex = end;
    *path = malloc( sizeof(int) * (distance[end] + 1));
    for ( i = distance[end] ; i >= 0 ; i--)
    {
        (*path)[i] = vertex;
        vertex = historyPath[vertex];
    }

    free(isVisits);
    free(distance);
    free(historyPath);

    return distance[end];
}


int main(void){
    int column, row;
    char wall, tmp;
    int **maze_matrix;
    int *path = NULL;
    int i, j, h, nodeNum=0;
    LinkedGraph *lg = NULL;
    int distance, path_flag;
    FILE *fp = NULL;

    fp=fopen("map.txt","r");
    fscanf(fp, "%d %d %c", &row, &column, &wall);

#ifdef DEBUG
    printf("row : %d column : %d wall : %c\n",row, column, wall);
#endif

    row = row * 2 + 1;
    column = column * 2 + 1;

    maze_matrix = (int **)malloc(sizeof(int *) * row);
    if(maze_matrix == NULL){
       return -1;
    }

    for(i = 0 ; i < row; i++){
        maze_matrix[i] = (int *)malloc(sizeof(int) * column);
        if(maze_matrix[i] == NULL){
            return -1;
        }
        memset(maze_matrix[i], -1, sizeof(int) * column);
    }

    for(i=0 ; i < row ; i++){
        for(j=0 ; j < column ; j++){
            
            tmp=fgetc(fp);
            
            if(tmp == '\n')
                tmp=fgetc(fp);

            if(tmp == ' '){
                maze_matrix[i][j] = nodeNum++;
            }
        }
    }

#ifdef DEBUG 
    printf("\n** node map **\n");
    for(i = 0; i < row ; i++){
        for(j = 0 ; j < column ; j++){
            printf("%2d ", maze_matrix[i][j]);
        }
        printf("\n");
    }
    printf("node num : %d \n", nodeNum);
#endif

    lg = createLinkedGraph(LINKED_GRAPH_TYPE_UNDIRECT, nodeNum);

    connectPath(lg, maze_matrix, row, column);
   // displayGraphLG(lg);

    
    distance = dijkstra(lg, 0, lg->nodeCount -1, &path);
#ifdef DEBUG
    printf("distance: %d \n", distance );
#endif


    //maze matrix print

    for ( i = 0 ; i < row ; i++ ){
        for ( j = 0 ; j < column ; j++ ){
            if(maze_matrix[i][j] == -1)
                putchar(wall);
            else
            {
                path_flag = false;
                for( h = 0 ; h < distance+1 ; h++)
                {
                    if(maze_matrix[i][j] == path[h])
                        path_flag = true;
                }

                if(path_flag)
                    printf("[42m [0m");
                else
                    putchar(' ');
            }
        }
        printf("\n");
    }

    free(path);
    
    for(i = 0 ; i < row; i++)
        free(maze_matrix[i]);

    //maze_matrix free!!

    fclose(fp);
    return 0;
}
