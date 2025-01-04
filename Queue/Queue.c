#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes
QueueNode * createNode(int data);
Queue* createQueue();
void enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
int front(Queue* queue);
int isEmpty(Queue* queue);
void freeQueue(Queue* queue);
void freeNode(QueueNode * del);

int main() {
    // Example usage here
    return 0;
}

// f <- 1 <- 2 <- 3 <- r
Queue* createQueue(){
    Queue * res = (Queue *)malloc(sizeof(Queue));
    res->front = NULL;
    res->rear = NULL;

    return res;
}

QueueNode * createNode(int data){
    QueueNode * res = (QueueNode *)malloc(sizeof(QueueNode));
    res->data = data;
    res->next = NULL;
    
    return res;
}

void freeNode(QueueNode * del){
    free(del);
}

void enqueue(Queue* queue, int data){
    if(queue == NULL) return;

    QueueNode * insert = createNode(data);

    insert->next = queue->rear;
    queue->rear = insert;
}

int dequeue(Queue* queue){
    if(queue == NULL || isEmpty(queue)) return -1;

    QueueNode * del = queue->front;
    int res = queue->front->data;
    QueueNode * current = queue->rear;

    if(current == del){
        queue->front = NULL;
        queue->rear = NULL;
    }//size of 1

    else{
        while(current->next != del){
            current = current->next;
        }

        current->next = NULL;
        queue->front = current;
    }// else

    free(del);
    return res;
}

int front(Queue* queue){
    if(queue == NULL) return -1;

    return queue->front->data;
}

int isEmpty(Queue* queue){
    return queue->front == NULL && queue->rear == NULL;
}

void freeQueue(Queue* queue){
    if(queue == NULL) return;

    while(queue->front != NULL){
        dequeue(queue);
    }
}