#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//Headers das auxiliares
void Transplant(BinTree*, TNo*, TNo*);

BinTree* BinTree_create(){
    BinTree *tree = malloc(sizeof(BinTree));
    if(tree){
        tree->root = NULL;
    }return tree;
}

TNo* TNo_createNFill(int key){
    TNo* node = malloc(sizeof(TNo));
    if(node){
        node->p = NULL;
        node->left = NULL;
        node->right = NULL;
        node->key = key;
    }return node;
}

_Bool BinTree_insert(BinTree* T, int key){
    TNo* z = TNo_createNFill(key);
    if(z == NULL) return false;
    TNo* y = NULL;
    TNo* x = T->root;

    while(x){
        y = x;
        if(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;
    if(y == NULL)
        T->root = z;
    else
        if(z->key < y->key)
            y->left = z;
        else
            y->right = z;
    
    return true;
}

_Bool BinTree_insert_r(TNo** root, TNo* z){
    int k = z->key;
    if((*root) == NULL){
        *root = z;
        return true;
    }

    z->p = *root;
    if(k < (*root)->key)
        return BinTree_insert_r(&(*root)->left, z);
    else
        return BinTree_insert_r(&(*root)->right, z);
}

void BinTree_preorder(TNo* root){
    if(root){
        printf("%d, ", root->key);
        BinTree_preorder(root->left);
        BinTree_preorder(root->right);
    }
}

void BinTree_inorder(TNo* root){
    if(root){
        BinTree_inorder(root->left);
        printf("%d, ", root->key);
        BinTree_inorder(root->right);
    }
}

void BinTree_posorder(TNo* root){
    if(root){
        BinTree_posorder(root->left);
        BinTree_posorder(root->right);
        printf("%d, ", root->key);
    }
}

void PrintTree(BinTree* tree){
    printf("Preorder: ");
    BinTree_preorder(tree->root);
    printf("\nInorder: ");
    BinTree_inorder(tree->root);
    putchar('\n');
}

TNo* BinTree_search_i(BinTree* T, int k){
    TNo* x = T->root;
    while(x != NULL && k != x->key)
        x = (k < x->key) ? x->left : x->right;
    return x;
}

TNo* BinTree_search_r(TNo* x, int k){
    if(x == NULL || k == x->key) return x;
    return BinTree_search_r((k < x->key) ? x->left : x->right, k);
}

TNo* BinTree_minimum(TNo* x){
    while(x->left)
        x = x->left;
    return x;
}

void Transplant(BinTree* T, TNo* u, TNo* v){
    if(u->p == NULL)
        T->root = v;
    else
        if(u == u->p->left)
            u->p->left = v;
        else
            u->p->right = v;
    if(v)
        v->p = u->p;
}

_Bool BinTree_delete(BinTree* T, TNo* z){
    if(T == NULL || T->root == NULL) return false;
    if(z->left == NULL)
        Transplant(T, z, z->right);
    else if(z->right == NULL)
        Transplant(T, z, z->left);
    else{
        TNo* y = BinTree_minimum(z->right);
        if(y->p != z){
            Transplant(T, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        Transplant(T, z, y);
        y->left = z->left;
        y->left->p = y;
    }
    free(z);
    return true;
}

void return_brackets(char* s, char* v){
    char *bracket;
    int i = 0, j = 0;

    bracket = strchr(s, '(');
    while(s[i] != '\0'){
        if(*(bracket+i) == '(' || *(bracket+i) == ')'){
            v[j] = *(bracket+i);
            j++;
        }
        i++;
    }
}

void return_int(char* s, int *v){
    char *pt = strtok(s, "()");
    int i = 0;
    while(pt){
        v[i] = atoi(pt);
        pt = strtok(NULL, "()");
        i++;
    }
}

TNo* str_to_tree(char* s, int i, int* v, int j){
    TNo* root = NULL;
    if(s[i] == ')')
        return root;
    else if(s[i] == '('){
        root = TNo_createNFill(v[j]);
        if(s[i+1] == ')')
            return root;
        else if(s[i+1] == '('){
            if(root->left == NULL)
                root->left = str_to_tree(s, i+1, v, j+1);
            if(root->right == NULL)
                root->right = str_to_tree(s, i+2, v, j+2);
        }
    }
    return root;
}
