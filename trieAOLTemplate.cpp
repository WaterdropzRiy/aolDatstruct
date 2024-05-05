#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct trieNode {
    char ch;
    int isWord;
    struct trieNode* children[128];
} TrieNode;

TrieNode* createNode(char ch) {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->ch = ch;
    node->isWord = 0;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

void insertWord(TrieNode** root, const char* word) {
    if (*root == NULL) *root = createNode('*');
    //abc
    TrieNode* current = *root;
    while (*word) {
        if (current->children[*word] == NULL) {
            current->children[*word] = createNode(*word);
        }
        current = current->children[*word];
        word++;
    }
    current->isWord = 1;
}

void printTrieContents(TrieNode* node, char* temp, int height) {
    if (node == NULL) return;
    //abc
    temp[height] = node->ch;
    if (node->isWord == 1) {
        temp[height + 1] = '\0';
        printf("%s\n", temp + 1);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != NULL) {
            printTrieContents(node->children[i], temp, height + 1);
        }
    }
}

void searchPrefix(TrieNode* root, const char* prefix) {
    char buffer[100];
    int depth = 0;
    buffer[depth++]=*prefix;
    TrieNode* current = root;
    //a
    while (*prefix) {
        if (current == NULL) return;
        current = current->children[*prefix];
        buffer[depth++] = *prefix++;
    }

    if (current != NULL && current->isWord) {
        buffer[depth] = '\0';
        printf("%s\n", buffer); 
    }

    for (int i = 0; i < 128; i++) {
        if (current->children[i] != NULL) {
            printTrieContents(current->children[i], buffer, depth);
        }
    }
}

int exists(TrieNode* root, const char* word) {
    TrieNode* current = root;
    while (*word) {
        if (current == NULL || current->children[*word] == NULL) return 0;
        current = current->children[*word];
        word++;
    }
    return current != NULL && current->isWord;
}

int main() {
    TrieNode* root = NULL;

    insertWord(&root, "shan");
    insertWord(&root, "test");
    insertWord(&root, "abc");

    // Uncomment to test the existence of a word
    // printf("Exists 'shan': %d\n", exists(root, "shan"));

    // Show all words starting with 'a'
    puts("Print all without prefix");
    searchPrefix(root, "");

    puts("Print all with prefix 'a'");
    searchPrefix(root, "a");


    return 0;
}
