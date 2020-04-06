// AVL tree implementation in C

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
#include "avl_tree.h"

u32 height(Node N) {
  if (N == NULL)
    return 0;
    
  return N->height;
} 

u32 max(u32 a, u32 b){
  return (a > b)? a : b;
} 

Node new_Node(Vertice vert) { 
  Node node = (Node) calloc(1, sizeof(struct __node));
  assert(node != NULL);
  node->key = vert->nombre;
  node->vert = vert;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
} 

Node right_Rotate(Node y) {
  Node x = y->left;
  Node T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right))+1;
  x->height = max(height(x->left), height(x->right))+1;

  return x;
} 

Node left_Rotate(Node x) { 
  Node y = x->right; 
  Node T2 = y->left; 

  y->left = x; 
  x->right = T2; 

  x->height = max(height(x->left), height(x->right))+1;
  y->height = max(height(y->left), height(y->right))+1;

  return y; 
} 

int get_BalanceFactor(Node N){
  if (N == NULL)
      return 0;

  return height(N->left) - height(N->right);
} 

Node insert(Node node, Vertice v){
  /* 1.  Perform the normal BST rotation */
  if (node == NULL)
    return(new_Node(v));

  if (v->nombre < node->key)
    node->left  = insert(node->left, v);
  else if (v->nombre > node->key)
    node->right = insert(node->right, v);
  else // Equal keys not allowed 
    return node;

  /* 2. Update height of this ancestor node */
  node->height = 1 + max(height(node->left), 
                         height(node->right));

  /* 3. Get the balance factor of this ancestor 
        node to check whether this node became 
        unbalanced */
  int balance = get_BalanceFactor(node);

  // If this node becomes unbalanced, then there are 4 cases 

  // Left Left Case 
  if (balance > 1 && v->nombre < node->left->key)
    return right_Rotate(node);

  // Right Right Case 
  if (balance < -1 && v->nombre > node->right->key)
    return left_Rotate(node);

  // Left Right Case 
  if (balance > 1 && v->nombre > node->left->key){
    node->left =  left_Rotate(node->left);
    return right_Rotate(node);
  } 
  // Right Left Case 
  if (balance < -1 && v->nombre < node->right->key){
    node->right = right_Rotate(node->right);
    return left_Rotate(node);
  }
  /* return the (unchanged) node pointer */
  return node;
} 

Node min_ValueNode(Node node) {
  Node current = node;

  while (current->left != NULL)
      current = current->left;

  return current; 
} 

Node delete_Node(Node root, u32 key) {
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = delete_Node(root->left, key);

  else if(key > root->key)
    root->right = delete_Node(root->right, key);

  else{
    if((root->left == NULL) || (root->right == NULL)){
      Node temp = root->left ? root->left : root->right;

      if (temp == NULL){
        temp = root;
        root = NULL;
      }else{
        *root = *temp; 
        free(temp); 
      }

      }else{
        Node temp = min_ValueNode(root->right); 
        root->key = temp->key; 
        root->right = delete_Node(root->right, temp->key); 
      }
  } 
  if (root == NULL) 
  return root; 

  root->height = 1 + max(height(root->left), height(root->right));

  int balanceFactor = get_BalanceFactor(root);

  if (balanceFactor > 1){
    if (get_BalanceFactor(root->left) >= 0)
      return right_Rotate(root);
    else{
      root->left = left_Rotate(root->left);
      return right_Rotate(root);
    }
  }

  if (balanceFactor < -1){
    if (get_BalanceFactor(root->right) <= 0)
      return left_Rotate(root);
    else{
      root->right = right_Rotate(root->right);
      return left_Rotate(root);
    }
  }
  return root; 
} 

int is_in_Node(u32 key, Node N){
  if (N == NULL)
    return 0;

  if (key == N->key)
    return 1;
  else if (key < N->key)
    return (is_in_Node(key, N->left));
  else if (key > N->key)
    return (is_in_Node(key, N->right));
  else
    return 0;
}

Vertice get_Vertice(u32 key, Node root){
  
  if (root == NULL)
    return NULL;

  if (key == root->key)
    return root->vert;
  else if (key < root->key)
    return (get_Vertice(key, root->left));
  else if (key > root->key)
    return (get_Vertice(key, root->right));
  else
    return NULL;
}

void print_PreOrder(Node root){
  if(root != NULL){
    /*print data of node*/
    printf("%lu ", root->key);
    /*recursion on left subtree*/
    print_PreOrder(root->left);
    /*recursion on right subtree*/
    print_PreOrder(root->right);
  } 
} 

void tree_Destroy(Node root){
 if (!root)
    return;

  tree_Destroy(root->left);
  tree_Destroy(root->right);

  root = delete_Node(root, root->key);
}
