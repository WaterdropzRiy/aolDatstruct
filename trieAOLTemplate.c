#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct trieNode {
    char ch;
    int isWord;
    struct trieNode* children[128];
} TrieNode;

TrieNode* createNode(char ch) {
    TrieNode* node = malloc(sizeof(TrieNode));
    node->ch = ch;
    node->isWord = 0;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

void insertWord(TrieNode** root, const char* word) {
    if (*root == NULL) *root = createNode('*');

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

void printTrieContents(TrieNode* node, char* buffer, int depth) {
    if (node == NULL) return;

    buffer[depth] = node->ch;
    if (node->isWord) {
        buffer[depth + 1] = '\0';
        printf("%s\n", buffer + 1);
    }

    for (int i = 0; i < 128; i++) {
        if (node->children[i] != NULL) {
            printTrieContents(node->children[i], buffer, depth + 1);
        }
    }
}

void searchPrefix(TrieNode* root, const char* prefix) {
    char buffer[100];
    int depth = 0;
    buffer[depth++]=*prefix;
    TrieNode* current = root;
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
