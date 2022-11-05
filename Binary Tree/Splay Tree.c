#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    unsigned value;
    struct no *right, *left;
} No;

No* findfather(No* root,int value){
  
   if(root!=NULL){
     
      if((root->left && value == (root->left->value) ) || (root->right && value == (root->right->value)))
         return root;

      if(value < root->value)
         return findfather(root->left,value);

      else if(value > root->value)
         return findfather(root->right,value);
   }
   return NULL;
}

No* searching_tree(No *root, int value){
    while(root){
        if(value < root->value)
            root = root->left;
        else if(value > root->value)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

No* leftRotate(No *x){
  
   No *y = x->right;
   No *c = y->left;
   y->left = x;
   x->right = c;
   return y;
}

No* rightRotate(No *x){
  
   No *y = x->left;
   No *c = y->right;
   y->right = x;
   x->left = c;
   return y;
}


int findDepth(No *root, int x){
  
    if (root == NULL)
        return -1;
 
    int dist = -1;
    if ((root->value == x) || (dist = findDepth(root->left, x)) >= 0 || (dist = findDepth(root->right, x)) >= 0)
        return dist + 1;
    return dist;
}

No* Splay_Tree(No *root, int value, int depth){
    //int depth = 0;

    if (value == root->value){
        return root;
    }

    //depth = findDepth(root, value);

    for (int x = 0; x < depth; x++){
      
        No *father = findfather(root, value);
        No *Gfather = findfather(root, father->value); 

        if(Gfather == NULL){
            if (root->value > value){
                root = rightRotate(root);
            }
            else 
                root = leftRotate(root);
        }
        else{
          
            if (father->left != NULL && father->left->value == value){
                if (value < Gfather->value){
                    Gfather->left = rightRotate(father);
                }
                else{
                    Gfather->right = rightRotate(father);
                }
            }
            if (father->right != NULL && father->right->value == value){
                if (value < Gfather->value){
                    Gfather->left = leftRotate(father);
                }
                else{
                    Gfather->right = leftRotate(father);
                }
            }
        }
    }    
    return root;
}

void insert_element(No **raiz, int num){
    if(*raiz == NULL){
        *raiz = malloc(sizeof(No));
        (*raiz)->value = num;
        (*raiz)->left = NULL;
        (*raiz)->right = NULL;
    }
    else{
        if(num < (*raiz)->value)
            insert_element(&((*raiz)->left), num);
        if(num > (*raiz)->value)
            insert_element(&((*raiz)->right), num);
    }
}

void printree(No *root){
    if(root){
        printree(root->left);
        printf("%d ", root->value);
        printree(root->right);
    }
}


No* Delete(No *root, int value)
{ 
  if(root == NULL){
    return NULL;
  }
  else{
    if(value == root->value){
      
      if(root->left == NULL && root->right == NULL){
        free(root);
        return NULL;
      }

      
      if(root->left != NULL && root->right == NULL){
        No *help = root->left;
        free(root);
        return help;
      }

      
      if(root->left == NULL && root->right != NULL){
        No *help = root->right;
        free(root);
        return help;
      }


      if(root->left != NULL && root->right != NULL){
        No *help = root->right;

        while(help->left != NULL){
          help = help->left;
        }

        root->value = help->value;
        help->value = value;

        root->right = Delete(root->right, value);
        return root;
      }
    }
    else{
      if(value < root->value){
        root->left = Delete(root->left, value);
      }

      if(value > root->value){
        root->right = Delete(root->right, value);
      }

      return root;
    }
  }
}

int main(void)
{
    No *tree = NULL;
    char control[4];
    int value;

    while (strcmp(control , "END")){
      
        scanf(" %s", control);

      if(!(strcmp(control, "INS"))){
            
            scanf("%d", &value); 
  
                insert_element(&tree, value);
                int x = findDepth(tree, value); 
                printf("%d\n", x);
                tree = Splay_Tree(tree, value, x); 
            
            
        }
    
      if(!(strcmp(control, "FND"))){
            scanf("%d", &value);
            No *aux = searching_tree(tree, value);
            if (aux){
                int x = findDepth(tree, value);
                printf("%d\n", x);
                tree = Splay_Tree(tree, value, x);
            }
            else{
                insert_element(&tree,value);
                int y = findDepth(tree, value); 
                printf("%d\n", y);
                tree = Delete(tree, value);
            } 
        }    
      
      if(!(strcmp(control, "DEL"))){
            scanf("%d", &value);
        
            No *aux = searching_tree(tree, value);
            if(aux){
              int x = findDepth(tree, value);
              printf("%d\n", x);
              No *FOTD = findfather(tree, value);
               int j = findDepth(tree , FOTD->value);
              tree = Delete(tree , value); 
              tree = Splay_Tree(tree, FOTD->value, j); 
          }
            else{
                insert_element(&tree,value); 
                int y = findDepth(tree, value); 
                printf("%d\n", y);
                tree = Delete(tree, value);
          } 
      }    
  }
  
  return 0;
}