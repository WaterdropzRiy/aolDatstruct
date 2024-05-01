#include <stdio.h> //Included for standard input and output
#include <string.h> //Included to be able to manipulate strings using strcpy and strcmp
#include <stdlib.h> //Included to be able to do memory allocation

//Declaring colors for aesthetic purposes
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[35m"

//The max size of the tree (26 is the amount of alphabets in English)
const int size = 26;

/* Declaring a struct for the Trie, consists of the alphabets for each Node, description for the leaves of the tree, an integer that indicates if the current Node is a leaf or not, and a pointer to the next Node */
struct Node {
    char alphabet;
    char desc[500];
    int data_end;
    Node *child[size];
};

/* Declare every function in this program so it can be accessed from everywhere */
Node *createNode(char ch);
void insertNode(Node **root, const char *key, const char *desc);
void inputSlang_menu(Node *root);
char *searchFromTrie(Node *root, const char *key);
int exists(Node* root, const char* word);
void searchWord_menu(Node *root);
void searchPrefix(Node* root, const char* prefix);
void searchPrefix_menu(Node *root);
void showMenu();
void printNode(Node *root, char *slang, int height);
void printAll_menu(Node *root);

/* Creating a new Node */
Node *createNode(char alphabet){ 
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->alphabet = alphabet;
    for(int i = 0; i < size; i++)
        newNode->child[i] = NULL;
    newNode->data_end = 0; 

    return newNode;
}

/*Inserting a new node for the trie. */
void insertNode(Node **root, const char *key, const char *desc) {
    if (*root == NULL) *root = createNode('-');

    Node *curr = *root;
    while (*key) {
        int index = *key - 'a';
        if (!curr->child[index])  
            curr->child[index] = createNode(*key);
        curr = curr->child[index];
        printf("%c", curr->alphabet);
        key++;
    }
    puts("");
    
    if (exists(*root, key)) {
        printf("%d", exists(*root, key));
        strcpy(curr->desc, desc);
    } else {
        printf("%d", exists(*root, key));
        curr->data_end = 1;
        strcpy(curr->desc, desc);
    }
}

void inputSlang_menu(Node *root) {
    int spaceCount = 0;
    int len;
    char inputSlang[100];
    char inputDesc[500];
    
    do {
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", inputSlang); getchar();
        len = strlen(inputSlang);

        for(int i = 0; i < len; i++){
            spaceCount = 0;
            if(inputSlang[i] == ' '){
                printf(RED "\nInput must be more than 1 character and have no spaces\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
                spaceCount++;
                break;
            }
        }
    } while(len < 2 || spaceCount > 0);

    if(exists(root, inputSlang)){
        system("cls");
        int isMoreThanTwo = 0;
        do {
            printf("Update the slang word description [Must be more than 2 words]: ");
            scanf("%[^\n]", inputDesc); getchar();
            len = strlen(inputDesc);

            for(int i = 0; i < len; i++){
                if(inputDesc[i] == ' ' && i != len-1){
                    isMoreThanTwo = 1;
                    break;
                }
            }
            if(!isMoreThanTwo){
                printf(RED "\nThe description must be more than 2 words!\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
            }
        } while(!isMoreThanTwo);
    } 
    else{
        system("cls");
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
            if(!isMoreThanTwo){
                printf(RED "\nThe description must be more than 2 words!\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
            }
        } while(!isMoreThanTwo);
    }
    
    insertNode(&root, inputSlang, inputDesc);
    puts("");
    printf("Press enter to continue..."); getchar();    
}

/* =================================================================================================================================================== */

char *searchFromTrie(Node *root, const char *key) {
    Node *curr = root;
    int len = strlen(key);
    for(int i = 0; i < len; i++) {
        int index = key[i] - 'a';
        if(!curr->child[index])  return NULL;
        curr = curr->child[index];
    }
    if (curr && curr->data_end)  return curr->desc;

    return NULL;
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

void searchWord_menu(Node *root) {
    int len;
    char searchSlang[100];
    int spaceCount = 0;

    do {
        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", searchSlang); getchar();
        len = strlen(searchSlang);

        for(int i = 0; i < len; i++){
            spaceCount = 0;
            if(searchSlang[i] == ' '){
                printf(RED "Input must be more than 1 character and have no spaces" RESET);
                spaceCount++;
                break;
            }
        }
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

/* =================================================================================================================================================== */

void searchPrefix(Node* root, const char* prefix) {
    char temp[100];
    int height = 0;
    temp[height++] = *prefix;
    Node* curr = root;
    while (*prefix) {
        if (curr == NULL) return;
        int index = *prefix - 'a';
        curr = curr->child[index];
        temp[height++] = *prefix++;
    }

    if (curr && curr->data_end) {
        temp[height] = '\0';
        printf("%s\n", temp); 
    }

    for (int i = 0; i < 26; i++) { 
        if (curr->child[i] != NULL) {
            printNode(curr->child[i], temp, height);
        }
    }
}

void searchPrefix_menu(Node *root){
    char prefix[20];
    printf("Input a prefix to be searched: ");
    scanf("%[^\n]", prefix); getchar();
    searchPrefix(root, prefix);
}

/* =================================================================================================================================================== */

void printNode(Node *root, char *temp, int height){
    // printf("%d", exists(root, "da"));
    if(!root){
        puts("There are no words yet");
        return;
    }

    temp[height] = root->alphabet;
    if(root->data_end){
        temp[height+1] = '\0';
        printf("%s\n", temp+1);
    }

    for(int i = 0; i < size; i++){
        if(root->child[i])
            printNode(root->child[i], temp, ++height);
    }
}

void printAll_menu(Node *root){
    puts("List of all slang words in the dictionary:");
    char temp[100];
    printNode(root, temp, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

/* =================================================================================================================================================== */

/* A function to show the menu screen. It will clear the terminal before printing the menu to avoid cluttering in the terminal */
void showMenu() {
    system("cls"); 
    printf(BLUE "\t\tWelcome to Boogle\n\n" RESET);
    printf("1. Release a new slang word\n");
    printf("2. Search a slang word\n");
    printf("3. View all slang words starting with a certain prefix word\n");
    printf("4. View all slang words\n");
    printf("5. Exit\n");
}

/* =================================================================================================================================================== */

int main() {
    int choice = 0;
    Node *root = NULL;
    do {
        showMenu();
        printf("Your choice: ");
        scanf("%d", &choice); getchar();
        switch(choice) {
            case 1:
                system("cls");
                inputSlang_menu(root);
                break;
            case 2:
                system("cls");
                searchWord_menu(root);
                break;
            case 3:
                system("cls");
                searchPrefix_menu(root);
                break;
            case 4:
                system("cls");
                printAll_menu(root);
                break;
            default: 
                system("cls");
                puts(RED "Invalid option\n" RESET);
                printf("Press enter to continue..."); getchar();
        }
    } while(choice != 5);

    puts(BLUE "Thank you.. Have a nice day :)" RESET);

    return 0;
} 
