#include <stdio.h>
#include <stdlib.h>
struct node{
    int data;
    struct node *link;
};
struct node * head;

int isEmpty(){
    if(head==NULL){
     return 1;
    }else{
        return 0;
    }
}

struct node *createNode(){
    int value;
    printf(" \nEnter the value of data  : ");
    scanf("%d",&value);
    struct node * nextNode;
    nextNode=(struct node *)malloc(sizeof(struct node *));
     nextNode->data=value;
     nextNode->link=NULL;
    return nextNode;
}

void InsertAtEnd(){
    struct node *current;
    current=createNode();
    if(head==NULL){
        head=current;
    }else{
    struct node * ptr;
    ptr=head;
    while(ptr->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=current;
}
}


void InsertAtBeginning(){
    struct node *current;
    current=createNode();
    if(head==NULL){
        head=current;
    }else{
    current->link=head;
    head=current;
    }
}

int countNode(){
    int count=0;
 struct node *ptr;
    ptr=head;
    while(ptr!=NULL){
        count++;
        ptr=ptr->link;
    }
    return count;
}

void display(){
    
     if(isEmpty()){
        printf("Linked list empty.\n");
        return ;
     }

    struct node *ptr=NULL;
    ptr=head;
    while(ptr!=NULL){
        printf("%d ",ptr->data);
        ptr=ptr->link;
    }
    printf("\n");
    
}

void Insert_At_Position(){
    int pos;
    int num=0;
    int count=countNode();
    
    printf(" \n Enter the position at which you want to enter a node : ");
    scanf("%d",&pos);

        if(pos<1 || pos>count+1){
        printf("Invalid Position .\n");
        return ;
         }
        
          struct node*ptr;
           ptr=head;

        if(pos==1){
            InsertAtBeginning();
        }else if(pos==count+1){
            InsertAtEnd();
        }else{
            struct node *current;
            current=createNode();
        while( ptr!=NULL && num!=pos-2){
            num++;
            ptr=ptr->link;
        }
         current->link=ptr->link;
        ptr->link=current;
    }
}

void deleteFirst(){
     if(head==NULL){
        printf("Linked list is empty .\n");
     }else{
        struct node* ptr;
        ptr=head;
        head=ptr->link;
        free(ptr);
        printf("Elment deleted successfully form first.\n");
     }

}

 void deleteLast(){
    
    if(head==NULL){
        printf("Linked list is empty .\n");
     }else if(head->link==NULL){
        free(head);
        head=NULL;                           
        printf("Element deleted successfully from last.\n");
        return;
    }else{
        struct node *ptr;
        ptr=head;
        struct node *q=NULL;
        while(ptr->link!=NULL){
            q=ptr;
            ptr=ptr->link;
        }
            q->link=NULL;
            free(ptr);
        printf("Elment deleted successfully from last.\n");
    }
     
 }

 void deleteAtPosition(){
    int count=countNode();
    int pos;
    printf("Entet the position in which you have to delete data : ");
    scanf("%d",&pos);
    if(pos<=0 || pos>count){
        printf("Invalid Position .\n");
        return ;
    }

    if(pos==1){
       deleteFirst();
    }else if(pos==count){
       deleteLast();
    }else{
        int num=1;
        struct node *ptr=head;
        struct node *q=NULL;

while(num < pos){
    q=ptr;
    ptr=ptr->link;
    num++;
}

q->link=ptr->link;
free(ptr);
printf("Elment deleted successfully from certain position.\n");
        }
 }
int main(){

    int choice;

    while(1){

        printf("\n\n========== LINKED LIST MENU ==========\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete from Beginning\n");
        printf("5. Delete from End\n");
        printf("6. Delete from Position\n");
        printf("7. Display\n");
        printf("8. Count Nodes\n");
        printf("9. Exit\n");

        printf("Enter your choice : ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                InsertAtBeginning();
                break;

            case 2:
                InsertAtEnd();
                break;

            case 3:
                Insert_At_Position();
                break;

            case 4:
                deleteFirst();
                break;

            case 5:
                deleteLast();
                break;

            case 6:
                deleteAtPosition();
                break;

            case 7:
                display();
                break;

            case 8:
                printf("Number of nodes = %d\n",countNode());
                break;

            case 9:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
