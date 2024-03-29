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
   TreeMap *map = malloc(sizeof(TreeMap));
    if (map == NULL) exit(EXIT_FAILURE); 
    map->root = NULL;
    map->current = 0;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  TreeNode * newNode = createTreeNode(key, value);
 
  if (tree->root == NULL){
    tree->root = newNode;
    tree->current = newNode;
  }
  
  TreeNode * current = tree->root;
  TreeNode * parent = NULL;

  while(current != NULL) {
      
    if(is_equal(tree, key, current->pair->key) == 1) {
      return;
    }
    
    parent = current;
    if(tree->lower_than(key,current->pair->key) == 0) {
      current = current->right;
    }else current = current->left;
  }
    
    newNode->parent = parent;
    if (tree->lower_than(key, parent->pair->key) == 0) {
      parent->right = newNode;
    } else {
      parent->left = newNode;
    }
  
  tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){
    while(x->left != NULL) x = x->left;
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node == NULL) return;
  if(node->left == NULL && node->right == NULL){
    if(tree->lower_than(node->pair->key,node->parent->pair->key) == 0) node->parent->right = NULL;
    else node->parent->left = NULL;
    free(node);
    return;
  }

  else if(node->left == NULL || node->right == NULL){
    TreeNode* child = node->left ? node->left : node->right;
    if (node->parent->left == node) node->parent->left = child;
    else node->parent->right = child;
    child->parent = node->parent;
    free(node);
    return;
  }

  else{
    TreeNode *minimo = minimum(node->right);
    node->pair->key = minimo->pair->key;
    node->pair->value = minimo->pair->value;
    removeNode(tree, minimo);
  }
  
  return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


Pair * searchTreeMap(TreeMap * tree, void* key) {
  tree->current = tree->root;  
  
  while(tree->current != NULL){
    if(is_equal(tree,tree->current->pair->key,key) == 1) return tree->current->pair;
     else{
            if(tree->lower_than(tree->current->pair->key,key) == 0) tree->current = tree->current->left;
            else tree->current = tree->current->right;
        }
  }  
  return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    if(tree->root == NULL) return NULL;
    
    tree->current = tree->root;
    TreeNode *ubNode = NULL;

    while( tree->current != NULL ){

      if(is_equal(tree,tree->current->pair->key, key) == 1) return tree->current->pair;
      else if(tree->lower_than(key, tree->current->pair->key) == 1){
        ubNode = tree->current;
        tree->current = tree->current->left;
      }
      else tree->current = tree->current->right;
    }

    if(ubNode != NULL) return ubNode->pair;
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* first = minimum(tree->root);
    return first->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if (tree->current == NULL) return NULL;

  if (tree->current->right != NULL) {
    TreeNode * current = tree->current->right;
      while (current->left != NULL) {
        current = current->left;
      }

      tree->current = current;
      return current->pair;
  }

  TreeNode *aux = tree->current->parent;
  while (aux != NULL && tree->current == aux->right) {
    tree->current = aux;
    aux = aux->parent;
  }
  tree->current = aux;
  
  if(aux==NULL) return NULL;
  return aux->pair;
}
