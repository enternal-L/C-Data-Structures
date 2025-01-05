#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int value;
    StackNode * next;
} StackNode;

typedef struct{
    StackNode * top;
    // would we need a bottom?
    // How do we know if its empty: top is null
    // How do we know size of a stack -> O(n) looping -> O(1) if we keep track of variable
    unsigned int size;
} Stack;

// Definitions
StackNode * StackNode_ctor(int val);
Stack * Stack_ctor();
int push(Stack * stack, int val); //returns true if suceeds, 0 if fails
int pop(Stack * stack);
int top(Stack * stack); //assumes that stack is a valid pointer
int empty(Stack * stack);
void StackNode_dtor(StackNode * del);
void Stack_dtor(Stack * del);


StackNode * StackNode_ctor(int val){
    StackNode * stackNode = (StackNode *)malloc(sizeof(StackNode));
    stackNode->next = NULL;
    stackNode->value = val;

    return stackNode;
}

Stack * Stack_ctor(){
    Stack * stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

int push(Stack * stack, int val){
    if(stack == NULL) return 0;

    // update the size, and update the top
    StackNode * node = StackNode_ctor(val); //created the node

    // point new node to current top
    node->next = stack->top;

    //update top
    stack->top = node;

    //update size
    stack->size++;

    return 1;
}

int pop(Stack * stack){
    if(stack == NULL) return 0;
    // decrement size and remove top

    // store top's value to return
    int res = stack->top->value;

    // have temporary del variable
    StackNode * del = stack->top;

    // repoint the top
    stack->top = del->next;

    StackNode_dtor(del);
    
    stack->size--;
    
    return res;
}

void StackNode_dtor(StackNode * del){
    // free the node
    free(del);
}

void Stack_dtor(Stack * del){
    // we keep popping until the size is 0
    while(del->size > 0){
        pop(del);
    }
}

int top(Stack * stack){
    return stack->top;
}

int empty(Stack * stack){
    return stack->top == NULL;
    // or you could size == 0
}
