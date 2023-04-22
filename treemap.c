#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap*)malloc(sizeof(TreeMap));
    if (map == NULL) return NULL;
    map->root = NULL;
    map->current= NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  tree->current=tree->root;
  TreeNode *aux = tree->current;
  TreeNode *node= createTreeNode(key, value);
  while(tree->current!=NULL){
    if(is_equal(tree, tree->current->pair->key, key)==1){
      return;
    }
    aux=tree->current;
    if(tree->lower_than(tree->current->pair->key, key)==0){
      tree->current = tree->current->left;
    }
    else{
      tree->current = tree->current->right;
    }
  }
  if(tree->lower_than(aux->pair->key, key)==0){
    aux->left= node; 
    node->parent=aux;
  }
  else{
    aux->right= node;
    node->parent=aux;
  }
  tree->current=node;
}

TreeNode * minimum(TreeNode * x){
  while(x->left!=NULL){
    x=x->left;
  }
  return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node->left == NULL && node->right == NULL){ //compruebo si el nodo no tiene hijos
    if(node->parent== NULL){
      tree->root = NULL;
    }
    if(node==node->parent->right){
      node->parent->right=NULL;
    }
    else{
      node->parent->left=NULL;
    }
  }
  else if(node->right == NULL){ // si tiene un hijo a la derecha
    if(node->parent == NULL){
      tree->root = node->left;
    }
    else if(node==node->parent->right){
      node->parent->right=node->left;
    }
    else{
      node->parent->left=node->left;
    }
    node->left->parent = node->parent;
    free(node->pair);
    free(node);
  }else if(node->left == NULL){ // si tiene un hijo a la izquierda
    if(node->parent == NULL){
      tree->root = node->right;
    }
    else if(node==node->parent->right){
      node->parent->right=node->right;
    }
    else{
      node->parent->left=node->right;
    }
    node->right->parent = node->parent;
    free(node->pair);
    free(node);
  }
  else{
    TreeNode* minimo = minimum(node->left);
    node->pair->key= minimo->pair->key;
    node->pair->value= minimo->pair->value;
    return removeNode(tree,minimo);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current=tree->root;
  while(tree->current != NULL){
    if(is_equal(tree,tree->current->pair->key, key)==1){
      return tree->current->pair;
    }
    else if(tree->lower_than(tree->current->pair->key, key)==0){
      tree->current = tree->current->left;
    }
    else{
      tree->current = tree->current->right;
    }
  }
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode *a
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode *node= minimum(tree->root);
    return node->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree->current->right != NULL) {
        tree->current = tree->current->right;
        while (tree->current->left != NULL) {
            tree->current = tree->current->left;
        }
  }else {
    TreeNode* parent = tree->current->parent;
        while (parent != NULL && tree->current == parent->right) {
            tree->current = parent;
            parent = parent->parent;
        }
        tree->current = parent;
    }
  if(tree->current == NULL){
    return NULL;
  }
    return tree->current->pair;
}
