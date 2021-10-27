#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>
#include"jrb.h"
#include"jval.h"
// ---------------------------------------------------------------------------------------------
typedef struct data{
    char name[20];
    long num;
} data;
// ---------------------------------------------------------------------------------------------
JRB jrb_search(JRB tree, char *key){
    JRB temp = NULL;
    jrb_traverse(temp, tree){
        if(strcmp(jval_s(temp->key), key) == 0)
            return temp;
    }
    return NULL;
}
// ---------------------------------------------------------------------------------------------
JRB jrb_insert(JRB tree, char *key, Jval value)
{
    JRB temp = NULL;
    temp = jrb_search(tree, key);
    if (temp == NULL)
        temp = jrb_insert_str(tree, key, value);
    else temp->val.l = value.l;
    return tree;
}
// ---------------------------------------------------------------------------------------------
void jrb_print(JRB tree)
{
    JRB temp = NULL;
    jrb_traverse(temp, tree){
        printf("Name: %s\tPhone number: %ld\n", jval_s(temp->key), jval_l(temp->val));
    }
}
// ---------------------------------------------------------------------------------------------
void jrb_delele(JRB tree, char *key)
{
    JRB temp = jrb_search(tree, key);
    if (temp == NULL)
        return;
    else jrb_delete_node(temp);
}
// ---------------------------------------------------------------------------------------------
void menu()
{
    printf("\n==========MENU==========\n");
    printf("1, Read File\n");
    printf("2, Print\n");
    printf("3, Insert\n");
    printf("4, Search\n");
    printf("5, Delete\n");
    printf("6, Release Tree\n");
    printf("7, Exit\n");
    printf("========================\n\n");
}
// ---------------------------------------------------------------------------------------------
int main(){
    JRB book = make_jrb();
    int choice;

    while(1){
        menu();
        printf("Choose a number: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: // Read File
            {
                char path[20];
                printf("Insert a path name: ");
                scanf("%s", path);
                FILE* fi = fopen(path, "r");
                data value[10];
                int index = 0;

                while(1){
                    if (feof(fi)) break;
                    
                    fscanf(fi, "%s", value[index].name);
                    fscanf(fi, " %ld", &value[index].num);

                    book = jrb_insert(book, value[index].name, new_jval_l(value[index].num));
                    index++;
                }
                fclose(fi);

                printf("Completed!\n");
                break;
            }

            case 2: // Print
            {
                printf("Phone Book:\n");
                jrb_print(book);
                printf("Completed!\n");
                break;
            }

            case 3: // Insert, Change number
            {
                char name[20];
                long number;

                printf("Insert a name: ");
                scanf("%s", name);
                printf("Insert a phone number: ");
                scanf(" %ld", &number);

                book = jrb_insert(book, name, new_jval_l(number));
                printf("Completed!\n");
                break;
            }

            case 4: // Search
            {
                char name[20];
                printf("Insert a name: ");
                scanf("%s", name);
                JRB temp = jrb_search(book, name);
                if (temp == NULL)
                    printf("Not in the phone book!\n");
                else {
                    printf("Name: %s\tPhone number: %ld\n", name, jval_l(temp->val));
                }
                printf("Completed!\n");
                break;
            }

            case 5: // Delete node
            {
                char name[20];
                printf("Insert a name: ");
                scanf("%s", name);
                jrb_delele(book, name);
                printf("Completed!\n");
                break;
            }

            case 6: // Delete Tree
            {
                jrb_free_tree(book);
                printf("Completed!\n");
                break;
            }

            case 7: // Exit
                break;
        }
        if (choice == 7) break;
    }
}