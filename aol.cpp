//Initializing program
#include <stdio.h> //Included for standard input and output
#include <string.h> //Included to be able to manipulate strings using strcpy, strcmp, and strcat
#include <stdlib.h> //Included to be able to do memory allocation
#include <ctype.h> //Included to be able to use tolower

//Declaring colors for aesthetic purposes
#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[35m"

const int size = 26; //The max size of the tree (26 is the amount of alphabets in English)

/* Declaring a struct for the Trie
    It consists of the alphabets for each Node, description for the leaves of the tree, an integer that indicates if the current Node is a leaf or not, and a pointer to the next Node 
*/
struct Node {
    char alphabet;
    char desc[500];
    int data_end;
    Node *child[size];
};
Node *root = NULL; //root as a global variable

/* 
    Here I declare every function in this program so it can be accessed from everywhere in this file
*/
Node *createNode(char alphabet);
void insertNode(const char *key, const char *desc);
void inputSlang_menu();
char *searchFromTrie(const char *key);
int exists(Node *root, const char *word);
void searchWord_menu();
void searchPrefix(const char *prefix, char *temp, int height);
void searchPrefix_menu();
void showMenu();
void printNode(Node *root, char *temp, int height);
void printAll_menu();

/* 
    Creating a new Node. First we allocate the memory for newNode. Then we "construct" the alphabet and data_end. Alphabet is used to contain every alphabet in the word and data_end is to detect whether the current alphabet is a leaf or not. And like every tree data structure, we first make the child NULL to avoid any clashes
*/
Node *createNode(char alphabet){ 
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->alphabet = alphabet;
    for(int i = 0; i < size; i++)
        newNode->child[i] = NULL;
    newNode->data_end = 0; 

    return newNode;
}

/* =================================================================================================================================================== */
//Logic Part

/*Inserting a new node for the trie. 
    Parameters explanation:
    - key: The string to be inserted into the trie.
    - desc: The description of the word.

    If the trie is still null, we can create the root of the trie with a star. Then we create a temporary string and fill it with a null terminator. Then we create a new Node, curr, to loop it inside the while(*key) statements. The index variable is used to identify which index in the child of the current node, hence why it's subtracted with 'a', assuming the word starts with a lowercase character;

    Now if the word already exists, we only update the description. Otherwise, it'll mark the last node as the end of the word and create a new description for the word.
*/
void insertNode(const char *key, const char *desc) {
    if (root == NULL) root = createNode('*'); 
    char temp[100];
    temp[0] = '\0'; 

    Node *curr = root; 
    while (*key) { 
        int index = *key - 'a'; 
        if (!curr->child[index]) //if the child node doesn't exists, create a new one
            curr->child[index] = createNode(*key);
        curr = curr->child[index];
        temp[0] = '\0'; 
        strncat(temp, key, 1); // Append current character to the temp variable
        key++; 
    }
    
    if (exists(root, temp)) { //Checks if the word alreadt exists or not
        strcpy(curr->desc, desc);
    } else {
        curr->data_end = 1;
        strcpy(curr->desc, desc);
    }
}

/*
    This function is the main function of the first case. It contains inputs from the user that are validated by the program. The validation is as follows:
    - The slang word
*/
void inputSlang_menu() {
    int wordFlag = 0;
    int len;
    char inputSlang[100];
    char inputDesc[500];
    
    /* While the word flag is equals to 1, it'll repeat the input process*/
    do {
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", inputSlang); getchar();
        len = strlen(inputSlang);

        if(len < 2){
            printf(RED "\nInput must be more than 1 character and have no spaces\n" RESET);
            printf("Press enter to continue..."); getchar(); 
            system("cls");
            wordFlag = 1;
            continue;
        }

        for(int i = 0; i < len; i++){
            if(inputSlang[i] == ' '){
                printf(RED "\nInput must be more than 1 character and have no spaces\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
                wordFlag = 1;
                break;
            } else if(islower(inputSlang[i])){
                wordFlag = 1;
                printf(RED "\nInput must be in all lowercase\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
                break;
            } else wordFlag = 0;
        }
    } while(wordFlag);

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
    
    insertNode(inputSlang, inputDesc);
    puts("");
    printf("Press enter to continue..."); getchar();    
}

/* =================================================================================================================================================== */

char *searchFromTrie(const char *key) {
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

int exists(struct Node* root, const char* word) {
    struct Node* curr = root;
    while (*word) {
        int index = *word - 'a';
        if (!curr || !curr->child[index]) 
           return 0;
        curr = curr->child[index];
        word++;
    }
    return curr != NULL && curr->data_end;
}

void searchWord_menu() {
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

    char *description = searchFromTrie(searchSlang);
    if(description) {
        printf("Slang word  : %s\n", searchSlang);
        printf("Description : %s\n", description);
    } else {
        printf("There is no word \"%s\" in the dictionary\n", searchSlang);
    }

    printf("Press enter to continue..."); getchar();   
}

/* =================================================================================================================================================== */

void searchPrefix(const char* prefix, char *temp, int height) {
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
        // printf("%s\n", temp); 
    }
    int found = 0;
    for (int i = 0; i < 26; i++) { 
        if (curr->child[i] != NULL) {
            found = 1;
            printNode(curr->child[i], temp, height);
        }
    }
    if(!found) puts("Word with that prefix doesn't exist");
}

void searchPrefix_menu(){
    char prefix[20];
    printf("Input a prefix to be searched: ");
    scanf("%[^\n]", prefix); getchar();
    char temp[100];
    temp[0] = '\0';
    searchPrefix(prefix, temp, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

/* =================================================================================================================================================== */

void printNode(Node *root, char *temp, int height){
    char local_temp[100];
    if(!root){
        puts("There are no words yet"); return;
    }
    strcpy(local_temp, temp);
    local_temp[height++] = root->alphabet;

    if(root->data_end){
        local_temp[height] = '\0';
        printf("%s\n", local_temp+1);
    }

    for(int i = 0; i < size; i++){
        if(root->child[i])
            printNode(root->child[i], local_temp, height);
    }
}

/* A function to print the contents from the printNode function. temp is used in the printNode function, hence why it's delared here and passed as a parameter*/
void printAll_menu(){
    puts("List of all slang words in the dictionary:");
    char temp[100];
    printNode(root, temp, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

/* =================================================================================================================================================== */
/* 
    A function to show the menu screen. It will clear the terminal before printing the menu to avoid cluttering in the terminal 
*/
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
/*
    The main() function first declare the choice */
int main() {
    int choice = 0;
    do {
        showMenu();
        printf("Your choice: ");
        scanf("%d", &choice); getchar();
        switch(choice) {
            case 1:
                system("cls");
                inputSlang_menu();
                break;
            case 2:
                system("cls");
                searchWord_menu();
                break;
            case 3:
                system("cls");
                searchPrefix_menu();
                break;
            case 4:
                system("cls");
                printAll_menu();
                break;
            case 5:
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
