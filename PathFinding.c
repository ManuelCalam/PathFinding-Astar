#include <stdio.h>
#include <stdlib.h>
#define rows 5
#define columns 5

int** A_start();
int findNeighbors(int currentNode[], int end[], int neighbors[8][4], int **closed, int counter);
int heuristica(int x1, int x2, int y1, int y2);
int lookForLowestF(int neighbors[8][4]);

int map [rows][columns]= {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
    };

void main(){
    int start [2]= {2, 0};
    int end [2] = {2, 4};
    int** path;

    path = A_start(start, end);

    printf("Recorrido:\n");
    for (int i = 0; path[i] != NULL; i++) {
        printf("Nodo %d: [%d, %d]\n", i+1, path[i][0], path[i][1]);
    }


    for (int i = 0; path[i] != NULL; i++) {
        free(path[i]);
    }

    free(path);
}

int** A_start(int start[], int end[]){
    int counter = 1;
    int currentNode[2] = {start[0], start[1]};

    int** closed = malloc(counter * sizeof(int));
    closed[0] = malloc(2 * sizeof(int));

    closed[0][0] = currentNode[0];
    closed[0][1] = currentNode[1];

    printf("%d, ", closed[0][0]);
    printf("%d", closed[0][1]);


    do{
        printf("Nodo actual: [%d, %d]\n\n", currentNode[0], currentNode[1]);
        int neighbors[8][4] = {0};
        int nextNode_id = findNeighbors(currentNode, end, neighbors, closed, counter);


        //Imprimir lo vecinos del nodo actual
        for(int i = 0; i<8; i++){
                for(int j=0; j<4; j++){
                    printf("%d, ", neighbors[i][j]);
                    if(j == 3){
                        printf("\n");
                    }
                }
        }

        //Agregar una fila a la matriz dinamica
        counter++;
        closed = realloc(closed, counter * sizeof(int*));
        closed[counter-1] = malloc(2 * sizeof(int));

        //Cambiar al nodo con menor valor f=g+h
        currentNode[0] = neighbors[nextNode_id][0];
        currentNode[1] = neighbors[nextNode_id][1];

        //Registramos el camino
        closed[counter-1][0] = currentNode[0];
        closed[counter-1][1] = currentNode[1];


        //system("pause");

    }while(currentNode[0] != end[0] || currentNode[1] != end[1]);

    closed = realloc(closed, (counter + 1) * sizeof(int*));
    closed[counter] = NULL;

    return closed;
}

int heuristica(int x1, int x2, int y1, int y2){
    return 10*((abs(x1 - x2) + abs(y1 - y2)));
}

int findNeighbors(int currentNode[], int end[], int neighbors[8][4], int **closed, int counter) {
    int movements[8][2] = {
        {0, -1},  {-1, -1},  {-1, 0},  {-1, 1},
        {0, 1},   {1, 1},    {1, 0},   {1, -1}
    };

    int costs[8] = {10, 14, 10, 14, 10, 14, 10, 14};

    for (int i = 0; i < 8; i++) {
        int newX = currentNode[0] + movements[i][0];
        int newY = currentNode[1] + movements[i][1];
        int alreadyClosed = 0;

        // Verificar si el vecino ya está en `closed`
        for (int j = 0; j < counter; j++) {
            if (closed[j][0] == newX && closed[j][1] == newY) {
                alreadyClosed = 1;
                break;
            }
        }

        if (!alreadyClosed && newX >= 0 && newX < rows && newY >= 0 && newY < columns) {
            if (map[newX][newY] != 1) {
                neighbors[i][0] = newX;
                neighbors[i][1] = newY;
                neighbors[i][2] = costs[i];
                neighbors[i][3] = neighbors[i][2] + heuristica(newX, end[0], newY, end[1]);
            } else {
                neighbors[i][0] = -1;
                neighbors[i][1] = -1;
                neighbors[i][2] = -1;
                neighbors[i][3] = -1;
            }
        } else {
            neighbors[i][0] = -1;
            neighbors[i][1] = -1;
            neighbors[i][2] = -1;
            neighbors[i][3] = -1;
        }
    }

    return lookForLowestF(neighbors);
}


int lookForLowestF(int neighbors[8][4]){
    int lowestF = 99999;
    int lowestF_id = -1;
    for(int i=0; i<8; i++){
        if(neighbors[i][3] != -1 && neighbors[i][3] < lowestF){
            lowestF = neighbors[i][3];
            lowestF_id = i;
        }
    }
    printf("%d es el mejor camino con id %d\n", lowestF, lowestF_id);
    return lowestF_id;
}





