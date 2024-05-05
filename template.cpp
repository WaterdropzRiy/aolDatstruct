#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int size = 26;

struct Node {
    char alphabet;
    char desc[500];
    int data_end;
    Node *child[size];
};

Node *createNode(char alphabet){ 
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->alphabet = alphabet;
    for(int i = 0; i < size; i++)
        newNode->child[i] = NULL;
    newNode->data_end = 0; 

    return newNode;
}

void insertNode(Node **root, const char *key) {
    if (*root == NULL) *root = createNode('-');

    Node* curr = *root;
    while (*key) {
        int index = *key - 'a';
        if (!curr->child[index])
            curr->child[index] = createNode(*key);
        curr = curr->child[index];
        key++;
    }
    curr->data_end = 1;
}

void printNode(Node *root, char *slang, int height){
    if(!root){
        puts("There are no words yet");
        return;
    }

    slang[height] = root->alphabet;
    if(root->data_end){
        slang[height+1] = '\0';
        printf("%s\n", slang+1);
    }

    for(int i = 0; i < size; i++){
        if(root->child[i])
            printNode(root->child[i], slang, ++height);
    }
}

int exists(Node* root, const char* word) {
    Node* curr = root;
    while (*word) {
        int index = *word - 'a';
        if (!curr || !curr->child[index]) 
           return 0;
        curr = curr->child[index];
        word++;
    }
    return curr != NULL && curr->data_end;
}

void searchPrefix(Node* root, const char* prefix) {
    char buffer[100];
    int height = 0;
    buffer[height++] = *prefix;
    Node* curr = root;
    while (*prefix) {
        if (curr == NULL) return;
        int index = *prefix - 'a';
        curr = curr->child[index];
        buffer[height++] = *prefix++;
    }

    if (curr && curr->data_end) {
        buffer[height] = '\0';
        printf("%s\n", buffer); 
    }

    for (int i = 0; i < 26; i++) { 
        if (curr->child[i] != NULL) {
            printNode(curr->child[i], buffer, height);
        }
    }
}

int main(){
    Node *root = NULL;
    insertNode(&root,"apple");
    insertNode(&root,"banana");

    searchPrefix(root, "");

    // printf("%d\n", exists(root, "apple"));


    return 0;
}