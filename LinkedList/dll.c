#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Goals: implement a doubly linked list - open practice problem from crafting interpreters! requirements we all self made
- insert
- delete
- append_left
- append_right
- pop_left
- pop_right
- find
*/ 

typedef struct Node{
    char * str;
    Node * next;
    Node * prev;
} Node;

typedef struct LinkedList{
    Node * first;
    Node * last;
    int size;
} DLL;

// Definitions
int append_left(DLL * list, Node * ins); //O(1)
int append_right(DLL * list, Node * ins); //O(n)
int insert_before(DLL * list, Node * ins, int index); //O(n)
int pop_left(DLL * list); //O(n)
int pop_right(DLL * list); //O(n)
char * get_first(DLL * list); 
char * get_last(DLL * list);
Node * find_node(DLL * list, char * search);
int size(DLL * list);

// Interfaces
// return 1 for success, -1 for no success
Node * Node_Ctor(char * input_str){
    Node * new_node = (Node *)malloc(sizeof(Node));
    new_node->next = NULL;
    new_node->prev = NULL;
    
    // innit string, strlen() doesn't include null terminator
    new_node->str = (char *)malloc(strlen(input_str) + 1);
    strncpy(new_node->str, input_str, strlen(input_str) + 1);

    return new_node;
}

void Node_Dtor(Node * target){
    free(target->str);
    free(target);
}

DLL * DLL_Ctor(){
    DLL * new_list = (DLL *)malloc(sizeof(DLL));

    new_list->first = NULL;
    new_list->last = NULL;
    new_list->size = 0;

    return new_list;
}

void DLL_Dtor(DLL * target){
    Node * next = target->first;
    Node * del = next;

    while(next != NULL){
        next = next->next;

        Node_Dtor(del);
        del = next;
    }
}

int append_left(DLL * list, Node * ins){
    if(!list){
        list->first = ins;
        list->last = ins;
    }// if empty

    else{
        list->first->prev = ins;
        ins->next = list->first;
        list->first = ins;
    }// if not empty

    list->size++;

    return 1;
}

int append_right(DLL * list, Node * ins){
    if(!list){
        list->first = ins;
        list->last = ins;
    }// if empty

    else{
        list->last->next = ins;
        ins->prev = list->last;
        list->last = ins;
    }// if not empty

    list->size++;

    return 1;
}

int insert_before(DLL * list, Node * ins, int index){
    if(index > size){
        printf("index %d exceeds size of %d in list", index, list->size);
        return 0;
    }//too large to insert

    // assume it is 0 indexed
    if(index == 0){
        append_left(list, ins);
    }//insert to the front

    else if(index == size){
        append_right(list, ins);
    }//insert at the back

    else{
        Node * target = list->first;

        for(int i = 0; i < index; ++i){
            target = target->next;
        }

        // we are at the target
        Node * previous = target->prev;

        ins->prev = previous;
        ins->next = target;

        previous->next = ins;
        target->prev = ins;
    }

    list->size++;

    return 1;
}

int pop_left(DLL * list){
    if(list->size == 0){
        printf("List size is 0, cannot pop anything");
        return 0;
    }

    else{

        Node * target = list->first;

        if(list->size == 1){
            list->first = NULL;
            list->last = NULL;
        }

        else{
            list->first = target->next;
            target->next->prev = NULL;
        }

        Node_Dtor(target);
        list->size--;
    }

    return 1;
}

int pop_right(DLL * list){
    if(list->size == 0){
        printf("List size is 0, cannot pop anything");
        return 0;
    }

    else{
        Node * target = list->last;

        if(list->size == 1){
            list->first = NULL;
            list->last = NULL;
        }

        else{
            list->last = target->prev;
            target->prev->next = NULL;
        }

        Node_Dtor(target);
        list->size--;
    }

    return 1;
}

char * get_first(DLL * list){
    if(list == NULL || list->size == 0){
        printf("Linked List is null or is empty");
        return NULL;
    }

    return list->first->str;
}

char * get_last(DLL * list){
    if(list == NULL || list->size == 0){
        printf("Linked List is null or is empty");
        return NULL;
    }

    return list->last->str;
}

Node * find_node(DLL * list, char * search){
    if(list){
        Node * current = list->first;

        for(int i = 0; i < list->size; ++i){
            if(strcmp(current->str, search)){
                return current;
            }

            current = current->next;
        }
    }//if it is a valid list

    //node not found
    return NULL;
}

int size(DLL * list){
    if(list == NULL){
        return -1;
    }

    return list->size;
}

int main() {

    return 0;
}


