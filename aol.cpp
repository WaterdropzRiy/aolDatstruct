#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <ctype.h>

#define RED "\x1b[31m"
#define RESET "\x1b[0m"
#define BLUE "\x1b[36m"

const int size = 52; 

struct Node {
    char alphabet;
    char desc[500];
    int data_end;
    Node *child[size];
};
Node *root = NULL;

Node *createNode(char alphabet);
void insertNode(const char *key, const char *desc);
void inputSlang_menu();
char *searchFromTrie(const char *key);
int exists(const char *word);
void searchWord_menu();
void searchPrefix(const char *prefix, char *temp, int height);
void searchPrefix_menu();
void showMenu();
void printNode(Node *root, char *temp, int height);
void printAll_menu();

Node *createNode(char alphabet){ 
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->alphabet = alphabet;
    for(int i = 0; i < size; i++)
        newNode->child[i] = NULL;
    newNode->data_end = 0; 

    return newNode;
}

/* =================================================================================================================================================== */
void insertNode(const char *key, const char *desc) {
    if (root == NULL) root = createNode('*'); 
    char temp[100];
    temp[0] = '\0'; 
    int index = 0;

    Node *curr = root; 
    while (*key) { 
        if (islower(*key)) index = *key - 'a';
        else if (isupper(*key)) index = *key - 'A' + 26;

        if (!curr->child[index])
            curr->child[index] = createNode(*key);
        curr = curr->child[index];
        temp[0] = '\0'; 
        strncat(temp, key, 1);
        key++; 
    }
    
    if (exists(temp)) {
        strcpy(curr->desc, desc);
    } else {
        curr->data_end = 1;
        strcpy(curr->desc, desc);
    }
}

void inputSlang_menu() {
    int wordFlag = 0;
    int len;
    char inputSlang[100];
    char inputDesc[500];

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
            } else if(!isalpha(inputSlang[i])){ 
                wordFlag = 1;
                printf(RED "\nInput must be all alphabets without numbers or symbols\n" RESET);
                printf("Press enter to continue..."); getchar(); 
                system("cls");
                break;
            } else wordFlag = 0;
        }
    } while(wordFlag);

    if(exists(inputSlang)){ 
        system("cls");
        int isMoreThanTwo = 0;
        do {
            printf("Update the slang word description [Must be more than 2 words]: ");
            scanf("%[^\n]", inputDesc); getchar();
            len = strlen(inputDesc);

            for(int i = 0; i < len; i++){
                if(inputDesc[i] == ' ' && i != len - 1){ 
                    isMoreThanTwo = 1; break;
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
    int index = 0;
    for(int i = 0; i < len; i++) {
        // index = key[i] - 'a';
        if (islower(key[i]))  index = key[i] - 'a';
        else index = key[i] - 'A' + 26;

        if(!curr->child[index])  return NULL;
        curr = curr->child[index];
    }
    if (curr && curr->data_end)  return curr->desc;

    return NULL;
}

int exists(const char* key) {
    Node* curr = root;
    int index = 0;
    while(*key) {
        if (islower(*key)) {
            index = *key - 'a';
        } else if (isupper(*key)) {
            index = *key - 'A' + 26;
        }
        if (!curr || !curr->child[index]) return 0;
        curr = curr->child[index];
        key++;
    }
    if((curr != NULL) && (curr->data_end)) return 1;
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
        printf("The word doesn't exists\n");
    }

    printf("\nPress enter to continue..."); getchar();   
}

/* =================================================================================================================================================== */
void searchPrefix(const char* prefix, char *temp, int height) {
    temp[height++] = *prefix;
    Node* curr = root;
    int found = 0;
    int index = 0;

    for(int i = 0; i < strlen(prefix); i++) {
        if (curr == NULL) return;
        if (islower(prefix[i]))  index = prefix[i] - 'a';
        else  index = prefix[i] - 'A' + 26;

        curr = curr->child[index];
        temp[height++] = *prefix++;
    }

    if (curr && curr->data_end) 
        temp[height] = '\0';

    for (int i = 0; i < size; i++) { 
        if (curr->child[i] != NULL) {
            found = 1;
            printNode(curr->child[i], temp, height);
        }
    }
}

void searchPrefix_menu(){
    char prefix[20];
    printf("Input a prefix to be searched: ");
    scanf("%[^\n]", prefix); getchar();
    char temp[100];
    temp[0] = '\0';

    // if(exists(prefix)){ 
    //     printf("%s\n", prefix);
    // }
    searchPrefix(prefix, temp, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

/* =================================================================================================================================================== */
void printNode(Node *root, char *temp, int height){
    char localTemp[100];
    if(!root) {
        puts("There are no words yet"); return;
    }

    strcpy(localTemp, temp);
    localTemp[height] = root->alphabet;
    height++;

    if(root->data_end){
        localTemp[height] = '\0';
        printf("%s\n", localTemp+1);
    }

    for(int i = 0; i < size; i++){
        if(root->child[i])  printNode(root->child[i], localTemp, height);
    }
}

void printAll_menu(){
    puts("List of all slang words in the dictionary:");
    char temp[100];
    printNode(root, temp, 0);

    puts("");
    printf("Press enter to continue..."); getchar();
}

/* =================================================================================================================================================== */
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