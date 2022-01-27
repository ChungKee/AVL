#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//AVL
typedef struct avl{
        int data;
        int height;
        struct avl *left;
        struct avl*right;
}avl;
int avl_height(avl*left,avl*right);
int avl_balance(avl*temp);
avl*avl_left(avl*tree);
avl*avl_right(avl*tree);
avl*avl_insert(avl*parent,int data);
void avl_search(avl*root,int data);
avl* findleft(avl* node);
avl*avl_delete(avl*root,int data);
void avl_exist(avl*root,int data);
//AVL  end

int main(){
        avl*root=NULL;
        char operation[12];
          do{
            int value=0;
            scanf("%s",operation);
            if(strcmp(operation,"insert")==0){
                scanf("%d",&value);
                root=avl_insert(root,value);
            }else if(strcmp(operation,"search")==0){
                scanf("%d",&value);
                avl_search(root,value);
            }else if(strcmp(operation,"exist")==0){
                scanf("%d",&value);
                avl_exist(root,value);
            }else if(strcmp(operation,"delete")==0){
                scanf("%d",&value);
                root=avl_delete(root,value);
            }
          }while(strcmp(operation,"quit")!=0);

        return 0;
}

int avl_height(avl*left,avl*right)
{
        int h1,h2;
        if(left==NULL){
                h1=0;
        }else{
                h1=left->height;
        }
        if(right==NULL){
                h2=0;
        }else{
                h2=right->height;
        }
        if(h1>h2){ //updata height of parent
                return h1;
        }else{
                return h2;
        }
}

int avl_balance(avl*temp)
{
        int h1,h2;
        if(temp->left==NULL){
                h1=0;
        }else{
                h1=temp->left->height;
        }
        if(temp->right==NULL){
                h2=0;
        }else{
                h2=temp->right->height;
        }
        return h1-h2;
}

avl*avl_left(avl*tree)
{
        avl*temp=tree->left;
        tree->left=temp->right;
        temp->right=tree;
        tree->height=avl_height(tree->left,tree->right)+1;
        temp->height=avl_height(temp->left,temp->right)+1;

        return temp;
}

avl*avl_right(avl*tree)
{
        avl*temp=tree->right;
        tree->right=temp->left;
        temp->left=tree;
        tree->height=avl_height(tree->left,tree->right)+1;
        temp->height=avl_height(temp->left,temp->right)+1;

        return temp;
}

avl*avl_insert(avl*parent,int data)
{
        if(parent==NULL){
                avl*temp=(avl*)malloc(sizeof(avl));
                temp->data=data;
                temp->left=NULL;
                temp->right=NULL;
                temp->height=1;
                return temp;
        }

        if(data<parent->data){ //smaller,go left
                parent->left=avl_insert(parent->left,data);
        }else if(data>parent->data){ //bigger,go right
                parent->right=avl_insert(parent->right,data);
        }else{ //same
                return parent;
        }


        int bf=0;
        bf=avl_balance(parent); //balance factor
        parent->height=avl_height(parent->left,parent->right)+1; //update height
        //left left
        if(bf>1&&data<parent->left->data){
                return avl_left(parent);
        }
        //right right
        if(bf<-1&&data>parent->right->data){
                return avl_right(parent);
        }
        //left right
        if(bf>1&&data>parent->left->data){
                parent->left=avl_right(parent->left);
                return avl_left(parent);
        }
        //right left
        if(bf<-1&&data<parent->right->data){
                parent->right=avl_left(parent->right);
                return avl_right(parent);
        }

        return parent;
}

void avl_search(avl*root,int data)
{
        if(root==NULL){
                printf("Not found\n");
        }else{
        if(root->data==data){
                printf("%d\n",avl_balance(root));
        }
        if(data<root->data){ //smaller,go left
                avl_search(root->left,data);
        }else if(data>root->data){ //bigger,go right
                avl_search(root->right,data);
        }
        }
}

avl* findleft(avl* node){
    avl* current = node;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}

avl*avl_delete(avl*root,int data)
{
        if(root==NULL){
                return root;
        }
        if(data<root->data){ //smaller,go left
                root->left=avl_delete(root->left,data);
        }else if(data>root->data){ //bigger,go right
                root->right=avl_delete(root->right,data);
        }else{ //same
                if(root->left==NULL &&root->right==NULL){ //no child
                        free(root);
                        root=NULL;
                }else if(root->left!=NULL &&root->right==NULL){ //left child only
                        avl*temp=root->left;
                        root=root->left;
                        free(temp);
                }else if(root->left==NULL &&root->right!=NULL){ //right child only
                        avl*temp=root->right;
                        root=root->right;
                        free(temp);
                }else{
                        avl*temp=findleft(root->right);
                        root->data=temp->data;
                        root->right=avl_delete(root->right,temp->data);
                }
        }
        if(root==NULL){
                return root;
        }
        int bf=avl_balance(root); //balance factor
         root->height=avl_height( root->left, root->right)+1; //update height
        //left left
        if(bf>1&&avl_balance(root->left)>=0){
                return avl_left( root);
        }
        //right right
        if(bf<-1&&avl_balance(root->right)<=0){
                return avl_right( root);
        }
        //left right
        if(bf>1&&avl_balance(root->left)<0){
                 root->left=avl_right( root->left);
                return avl_left( root);
        }
        //right left
        if(bf<-1&&avl_balance(root->right)>0){
                 root->right=avl_left( root->right);
                return avl_right( root);
        }
        return root;
}

void avl_exist(avl*root,int data)
{
        if(root==NULL){
                printf("Not exist\n");
        }else{
            if(root->data==data){
                printf("exist\n");
            }
            if(data<root->data){ //smaller,go left
                avl_exist(root->left,data);
            }else if(data>root->data){ //bigger,go right
                avl_exist(root->right,data);
            }
        }
}
