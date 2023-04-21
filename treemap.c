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
  
  TreeNode * actualNode = tree->root;
 
  while(actualNode){
    if (tree->lower_than(key, actualNode->pair->key)) {
       if (!actualNode->left) {
                    actualNode->left = newNode;
                    newNode->parent = actualNode;
                    tree->current = newNode;
                    break;
                } else {
                    newNode = actualNode->left;
                }
  }else if (tree->lower_than(actualNode->pair->key, key)) {
      if(!actualNode->right){
        actualNode -> right = newNode;
        newNode->parent = actualNode;
        tree->current = newNode;
        break;
      }else {
        newNode = actualNode->right;
      }
    }else {
      actualNode ->pair->value = value;
      free(newNode);
      tree->current = actualNode;
      break;
    }
  }
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
|
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
