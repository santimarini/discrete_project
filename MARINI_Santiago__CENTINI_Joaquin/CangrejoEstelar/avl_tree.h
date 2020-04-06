#include "veinteveinte.h"

/*get height*/
u32 height(Node N);

/*get max*/
u32 max(u32 a, u32 b); 

Node new_Node(Vertice vert);
Node right_Rotate(Node y);
Node left_Rotate(Node x);
int get_BalanceFactor(Node N);
Node insert(Node node, Vertice v);
Node min_ValueNode(Node node);
int is_in_Node(u32 key, Node N);
Node delete_Node(Node root, u32 key);
Node get_Node(u32 key, Node root);
Vertice get_Vertice(u32 key, Node root);
void print_PreOrder(Node root);
void tree_Destroy(Node root);