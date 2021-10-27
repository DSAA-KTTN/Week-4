#include "jrb.h"
#include "jval.h"
#include "jval.c"
#include "jrb.c"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    JRB a;
    JRB book = make_jrb();
   
    int choice;
    long phone;
    char name[50];
    FILE *fi,*fo;

    while(1){
    printf("1.Load phone book\n");
    printf("2.Add\n");
    printf("3.Delete\n");
    printf("4.Modify phone number\n");
    printf("5.Print\n");
    printf("6.Print file\n");
    printf("7.Exit\n");
    printf("Your choice is: ");
    scanf("%d",&choice);

    switch(choice){
        case 1: //// LOAD PHONE BOOK ////
            fi=fopen("input.txt","r");
             while(1){
                if(feof(fi)) break;
                fscanf(fi,"%s %d",name,&phone);

                jrb_insert_str(book,strdup(name),new_jval_l(phone));
            }
            fclose(fi);
         break;
        case 2://// ADD ////
            printf("Name: ");
            while(getchar()!='\n');
            scanf("%[^\n]%*c",name);
            printf("Phone Number: ");
            scanf("%d",&phone);
            a=jrb_find_str(book,name);
            if(a==NULL){
                jrb_insert_str(book,strdup(name),new_jval_l(phone));
            } else a->val.l=phone;
         break;

        case 3://// DELETE ////
            printf("Name: ");
            while(getchar()!='\n');
            scanf("%[^\n]%*c",name);
            a=jrb_find_str(book,name);
            if(a==NULL) {
                printf("Name not exist!");
                break;
            }
            jrb_delete_node(a);
         break;

        case 4://// MODIFY PHONE NUMBER ////
            printf("Name: ");
            while(getchar()!='\n');
            scanf("%[^\n]%*c",name);
            a=jrb_find_str(book,name);
            if(a==NULL) {
                printf("Name not exist!");
                break;
                }
            printf("New number: ");
            scanf("%d",&phone);            
            a->val.l=phone;
         break;

        case 5://// PRINT ////
            jrb_traverse(a,book){
                printf("%s %d\n",a->key.s,a->val.l);
            }
         break;

        case 6://// PRINT FILE ////
            fo=fopen("output.txt","w");

            jrb_traverse(a,book){
                fprintf(fo,"%s %d\n",a->key.s,a->val.l);
            }
            fclose(fo);
         break;
 
        case 7: //// EXIT ////
            jrb_free_tree(book);
        return 0;
    }

    printf("\n");
    }

return 0;
}
