# include <stdio.h>
# include <stdlib.h>
struct node {
struct node * left;
int data;
struct node * right;
};
struct node * root=NULL;
struct node * createNode() {
int data;
struct node * newNode;
newNode=(struct node*)malloc(sizeof(struct node));
printf("Enter the data that you want to insert : ");
scanf("%d",&data);
newNode->left=NULL;
newNode->data=data;
newNode->right=NULL;
return newNode;
}
void insert() {
struct node * current;
current=createNode();
if(root==NULL){
root=current;
printf("Element inserted successfully.\n");
return ;
}
struct node* temp;
temp=root;
while(1){
if(current->data == temp->data ){
printf("Element exist already.\n ");
return ;
}
if(current->data < temp->data){
if(temp->left == NULL){
temp->left = current;
printf("Element inserted successfully.\n");
return ;
}
temp=temp->left;
}else{
if(temp->right == NULL){
temp->right= current;
printf("Element inserted successfully.\n");
return ;
}
temp=temp->right;
}
}
}
void inorder(struct node * ptr) {
if(root==NULL){
printf("Tree is empty.\n");
return ;
}
if(ptr!=NULL){
inorder(ptr->left);
printf("%d ",ptr->data);
inorder(ptr->right);
}
}
void preorder(struct node* ptr) {
if(root==NULL){
printf("\nTree is empty.\n");
return ;
}
if(ptr!=NULL){
printf("%d ",ptr->data);
preorder(ptr->left);
preorder(ptr->right);
}
}
void postorder(struct node* ptr) {
if(root==NULL){
printf("\nTree is empty.\n");
return ;
}
if(ptr!=NULL){
postorder(ptr->left);
postorder(ptr->right);
printf("%d ",ptr->data);
}
}
void clearBST(struct node * ptr) {
if(ptr!=NULL){
clearBST(ptr->left);
clearBST(ptr->right);
free(ptr);
}
}
void search() {
int data;
printf("Enter the data that you want to search : ");
scanf("%d",&data);
struct node* temp;
temp=root;
while(temp!= NULL){
if(data == temp->data){
printf("Element found.\n");
return ;
}
if(data < temp->data){
temp=temp->left;
}else{
temp=temp->right;
}
}
printf("Element is not found.\n");
}
struct node * delete(struct node *root,int data){
if(root==NULL){
return root;
}else if(data < root->data){
root->left=delete(root->left,data);
}else if(data > root->data){
root->right=delete(root->right,data);
}else{
//cases
if(root->left==NULL && root->right==NULL){
free(root);
root=NULL;
}else if(root->left== NULL){
struct node * temp=root;
root= root->right;
free(temp);
}else if(root->right==NULL){
struct node* temp=root;
root = root->left;
free(temp);
}else{
struct node * temp;
temp=root->right;
while(temp->left !=NULL){
temp=temp->left;
}
root->data=temp->data;
root->right=delete(root->right, temp->data);
}
}
return root;
}
int main() {
int choice;
while(1){
printf("\n\n......Binary Search Tree......\n");
printf("1. insert\n");
printf("2. Inorder traversal\n");
printf("3. Preorder traversal \n");
printf("4. Postorder traversal .\n");
printf("5. Clear Binary Search Tree.\n");
printf("6. Search .\n");
printf("7. delete particular node.\n");
printf("8. Exit \n");
printf("\nEnter your choice : ");
scanf("%d",&choice);
switch(choice){
case 1:
{
insert();
break;
}
case 2:
{
inorder(root);
break;
}
case 3:
{
preorder(root);
break;
}
case 4:
{
postorder(root);
break;
}
case 5:
{
if(root == NULL)
printf("\nTree is empty.\n");
else {
clearBST(root);
root = NULL;
printf("\nBinary Search Tree cleared successfully.\n");
}
break;
}
case 6:
{
search();
break;
}
case 7:
{
int data;
printf("Enter element that you want to delete : ");
scanf("%d",&data);
root=delete(root,data);
break;
}
case 8:
{
printf("\nProgram ended.\n");
return 0;
}
default:
printf("\nInvalid choice.\n");
}
}
return 0;
