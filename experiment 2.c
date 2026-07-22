#include <stdio.h>
#define max 4
int top=-1;
int stack_arr[max];
int isEmpty(){
    if(top==-1){
        return 1;
    }else{
        return 0;
    }
}
int isFull(){
    if(top==max-1){
        return 1;
    }else{
        return 0;
    }
}
void push(int data){
    if(isFull()){
       printf("Stack Overflow \n");
       return;
    }
    top++;
    stack_arr[top]=data;
}
int pop(){
    int value;
    if(isEmpty()){
        printf("Stack Underflow \n");
        return -1;
    }
    value = stack_arr[top];
    top--;
    
}
int peek(){
    if(isEmpty()){
        printf("Stack Underflow \n");
        return -1;
    }
    return stack_arr[top];
}
 void display(){
    if(isEmpty()){
        printf("Stack Underflow \n");
        return ;
    }
    printf("Elements in stack are \n");
    for(int i=top;i>=0;i--){
        printf(" | _%d_ | \n",stack_arr[i]);
    }
 }
 int main(){
    int choice,data;
    while(1){ 
        printf("\n");
        printf("       stack Menu     \n");
        printf("1.push\n");
        printf("2.pop\n");
        printf("3.peek\n");
        printf("4.display\n");
        printf("5.exit\n");
        printf("enter your choice =  ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            printf("Enter the element to be pushed = ");
            scanf("%d",&data);
            push(data);
            break;

            case 2:
            data=pop();
            if(data!=-1){
                printf("Deleted or Poped element : %d\n",data);
            }
            break;

            case 3:
            data=peek();
            if(data!=-1){
                printf("Top most element of stack : %d\n",data);
            }
            break;

            case 4:
            display();
            break;

            case 5:
            printf("Program ended \n");
            return 0;

            default:
            printf("Invalid choice \n");
        }
    }
    return 0;
 }
