/* Boogle, a dictionary for slang words. Made with tree data structure */

#include <stdio.h> 

#include <string.h>

#include <stdlib.h>



const int size = 26;



struct Node{

    char alphabet;

    char desc[500];

    int data_end;

    Node *next[size];

} *root = NULL;



Node *createNode(){ 

    Node *newNode = (Node*) malloc(sizeof(Node));

    for(int i = 0; i < size; i++)

        newNode->next[i] = NULL;



    newNode->data_end = 0;

    return newNode;

}



void insertNode(const char *key, const char *desc){

    Node *curr = root;

    int len = strlen(key);

    for(int i = 0; i < len; i++){

        int index = key[i] - 'a';

        if(!curr->next[index])

            curr->next[index] = createNode();

        curr = curr->next[i];

    }

    curr->data_end = 1;

    strcpy(curr->desc, desc);

}



int searchFromTrie(Node *root, const char *key){

    Node *curr = root;

    int len = strlen(key);

    for(int i = 0; key[i] < len; i++){

        int index = key[i] - 'a';

        if(!curr->next[index]) return 0;

        curr = curr->next[i];

    }

    return curr->data_end;

}



void searchWord_menu(){

    int len, spaceCount = 0;

    char searchSlang[100];

    do {

        printf("Input a slang word to be searched [Must be more than 1 characters and contains no space]: ");

        scanf("%[^\n]", searchSlang);

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

    } while(len < 2 || spaceCount > 0);



    if(searchFromTrie(root, searchSlang)){

        printf("Slang word  : %s", searchSlang);

        printf("Description : %s", searchFromTrie(root, searchSlang));

    } else{

        printf("There is no word \"%s\" in the dictionary", searchSlang);

    }

}



void inputSlang_menu(){

    int spaceCount = 0;

    int len;

    char inputSlang[100];

    char inputDesc[500];

    

    do {

        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");

        scanf("%[^\n]", inputSlang);

        len = strlen(inputSlang);



        // Clear input buffer

        while (getchar() != '\n');



        // Check if there's more than 1 character and contains no space

        for(int i = 0; i < len; i++){

            if(inputSlang[i] == ' '){

                spaceCount++;

                break;

            }

        }

    } while(len < 2 || spaceCount > 0);

    int isMoreThanTwo = 0;



    do {

        printf("Input a new slang word description [Must be more than 2 words]: ");

        scanf("%[^\n]", inputDesc);

        len = strlen(inputDesc);



        // Check if there's more than 2 words by detecting the space (' ') location and if there's any word after that

        for(int i = 0; i < len; i++){

            if(inputDesc[i] == ' ' && i != len-1){

                isMoreThanTwo = 1;

                break;

            }

        }

    } while(isMoreThanTwo == 0);    

    // Store the slang word in Trie

    insertNode(inputSlang, inputDesc);



    puts("Press enter to continue...");

    getchar();

}



void printAll(){

    struct Node* curr = root;

    

}



void showMenu(){

    puts("\t\tWelcome to Boogle");

    puts("1. Release a new slang word");

    puts("2. Search a slang word");

    puts("3. View all slang words starting with a certain prefix word");

    puts("4. View all slang words");

    puts("5. Exit");

}





int main(){

    int choice = 0;

    do{

        showMenu();

        printf("Your choice: ");

        scanf("%d", &choice);

        switch(choice){

            case 1:

                inputSlang_menu();

                break;

            case 2:

                searchWord_menu();

                puts("");

                break;

            case 3:

                // viewPrefixWords();

                puts("");

                break;

            case 4:

                printAll_menu();

                puts("");

                break;

            default: 

                printf("Invalid option\n");

        }

    } while(choice != 5);



    puts("Thank you.. Have a nice day :)");



    return 0;

}
