#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

const int size = 26;

struct Node {
    char alphabet;
    char desc[500];
    int data_end;
    struct Node *child[size];
} *root = NULL;

struct Node *createNode() { 
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    for(int i = 0; i < size; i++)
        newNode->child[i] = NULL;

    newNode->data_end = 0; 
    return newNode;
}

void insertNode(const char *key, const char *desc) {
    struct Node *curr = root;
    int len = strlen(key);
    for(int i = 0; i < len; i++) {
        int index = key[i] - 'a';
        if(!curr->child[index])
            curr->child[index] = createNode();
        curr = curr->child[index];
    }
    curr->data_end = 1;
    strcpy(curr->desc, desc);
}

char *searchFromTrie(struct Node *root, const char *key) {
    struct Node *curr = root;
    int len = strlen(key);
    for(int i = 0; i < len; i++) {
        int index = key[i] - 'a';
        if(!curr->child[index])
            return NULL;
        curr = curr->child[index];
    }
    if (curr && curr->data_end)
        return curr->desc;
    return NULL;
}

void searchWord_menu() {
    int len, spaceCount = 0;
    char searchSlang[100];
    do {
        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", searchSlang); getchar();
        len = strlen(searchSlang);

        // Clear input buffer
        while (getchar() != '\n');

        // Check if there's more than 1 character and contains no space
        for(int i = 0; i < len; i++){
            if(searchSlang[i] == ' '){
                spaceCount++;
                break;
            }
        }
        spaceCount = 0;
    } while(len < 2 || spaceCount > 0);

    char *description = searchFromTrie(root, searchSlang);
    if(description) {
        printf("Slang word  : %s\n", searchSlang);
        printf("Description : %s\n", description);
    } else {
        printf("There is no word \"%s\" in the dictionary\n", searchSlang);
    }

    printf("Press enter to continue..."); getchar();
}

void viewPrefixWords(Node *root, const char *prefix, char *slang, int index){
    if(!root) return;
    int j = 1;
    if(root->data_end){
        slang[index] = '\0';
        printf("%d. %s", j, slang);
        j++;
    }
    for(int i = 0; i < size; i++){
        if(root->child[i]){
            slang[index] = root->child[i]->alphabet;
            viewPrefixWords(root->child[i], prefix, slang, index+1);
        }
    }
}

void inputSlang_menu() {
    int spaceCount = 0;
    int len;
    char inputSlang[100];
    char inputDesc[500];
    
    do {
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", inputSlang); getchar();
        len = strlen(inputSlang);

        // Check if there's more than 1 character and contains no space
        for(int i = 0; i < len; i++){
            spaceCount = 0;
            if(inputSlang[i] == ' '){
                spaceCount++;
                break;
            }
        }
    } while(len < 2 || spaceCount > 0);
    
    int isMoreThanTwo = 0;
    do {
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf("%[^\n]", inputDesc); getchar();
        len = strlen(inputDesc);

        for(int i = 0; i < len; i++){
            if(inputDesc[i] == ' ' && i != len-1){
                isMoreThanTwo = 1;
                break;
            }
        }
    } while(isMoreThanTwo == 0);  
    // Store the slang word in Trie
    insertNode(inputSlang, inputDesc);
    puts("");
    printf("Press enter to continue..."); getchar();
}

void searchPrefix_menu(){
    char prefix[20];
    printf("Input a prefix to be searched: ");
    scanf("%[^\n]", prefix); getchar();
    int len = strlen(prefix);

    Node *curr = root;
    int index = 0;
    for(int i = 0; i < index; i++){
    }
}

void showMenu() {
    puts("\t\tWelcome to Boogle");
    puts("1. Release a new slang word");
    puts("2. Search a slang word");
    puts("3. View all slang words starting with a certain prefix word");
    puts("4. View all slang words");
    puts("5. Exit");
}

void printNode(Node *root, char *slang, int height){
    if(root == NULL){
        puts("There are no words yet");
        return;
    }

    int index = 1;
    if(root->data_end == true){
        slang[height] = '\0';
        printf("%d. %s\n",index++, slang);
    }
    for(int i = 0; i < size; i++){
        if(root->child[i]){
            slang[height] = i + 'a';
            printNode(root->child[i], slang, height+1);
        }
    }
}

void printAll_menu(){
    puts("List of all slang words in the dictionary:");
    char str[100];
    printNode(root, str, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

int main() {
    // Initialize the root node
    // root = createNode();
    int choice = 0;
    do {
        showMenu();
        printf("Your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                inputSlang_menu();
                break;
            case 2:
                searchWord_menu();
                break;
            case 3:
                searchPrefix_menu();
                break;
            case 4:
                printAll_menu();
                break;
            default: 
                puts("Invalid option\n");
                printf("Press enter to continue..."); getchar();
        }
    } while(choice != 5);

    puts("Thank you.. Have a nice day :)");

    return 0;
} 
