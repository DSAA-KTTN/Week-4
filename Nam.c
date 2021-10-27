#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"jrb.h"
void jrb_print_db(JRB tree){
    JRB tmp;
    jrb_traverse(tmp,tree){
      printf("Name: %s - Phone number: %ld\n",jval_s(tmp->key),(tmp->val).l);
    }
  }
JRB jrb_find_key(JRB tree, Jval value){
  JRB tmp;
  jrb_traverse(tmp,tree){
    if((tmp->val).l==(value).l){
      return tmp;
    }
  }
  return NULL;
}

int main(){
  JRB phonebook, node;
  FILE *fp;
  int choice,num,i;
  long val;
  char key[50];
  do{
    printf("\n____________________MENU____________________\n");
    printf(" 1. Import Phonebook data from file!\n");
    printf(" 2. Add new contact!\n");
    printf(" 3. Remove a contact!\n");
    printf(" 4. Update the Phonebook file!\n");
    printf(" 5. Printf phonebook data!\n");
    printf(" 6. Modify phone number!\n");
    printf(" 7. Quit!\n");
    printf("-> Your choice: ");
    scanf("%d%*c",&choice);
    switch(choice){
    case 1:
      phonebook=make_jrb();
      fp=fopen("Phonebook.txt","r");
      if(fp==NULL){
	printf("No files were found!\n");
	return 0;
      }
      fseek(fp,0,SEEK_SET);
 while(!feof(fp)){
   fscanf(fp,"%s %ld\n",key,&val); 
   printf("%s %ld\n",key,val);
   jrb_insert_str(phonebook,key,new_jval_l(val));
  }
      fclose(fp);
      printf("Imported successfully!\n");
      break;
    case 2:
      printf("Enter number of contacts: ");
      scanf("%d%*c",&num);
      for(i=0;i<num;i++){
	printf("%d.\n",i+1);
	printf("Enter name: ");
	gets(key);
	printf("Enter phone number: ");
	scanf("%ld%*c",&val);
	jrb_insert_str(phonebook,key,new_jval_l(val));
      }
      printf("Added successfully!\n");
      break;
    case 3:
      printf("Enter name of contact: ");
      gets(key);
      node=jrb_find_str(phonebook,key);
      if(node !=NULL){
	jrb_delete_node(node);}
      printf("Removed successfully!\n");
      break;
    case 4:
      fp=fopen("Phonebook.txt","w");
      if(phonebook==NULL){
    printf("No data.\n");
  }else{
    jrb_traverse(node,phonebook){
    fprintf(fp,"%s %ld\n",jval_s(node->key),jval_l(node->val));
  }
    printf("Successful!\n");
}
      fclose(fp);
      break;
    case 5:
      jrb_print_db(phonebook);
      break;
    case 6:
       printf("Enter name of contact: ");
      gets(key);
      node=jrb_find_str(phonebook,key);
      if(node==NULL){
	printf("No contact satisfy the name!\n");
      }else{
	printf("Enter new phone number: ");
	scanf("%ld%*c",&val);
	node->val=new_jval_l(val);
	printf("Modified successfully!\n");
      }
      break;
    case 7:
      jrb_free_tree(phonebook);
      break;
    default:
      break;
    }
  }while(choice!=7);
  return 0;
}
