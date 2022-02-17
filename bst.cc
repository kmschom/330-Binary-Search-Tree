#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
    key = -100;    // Setting key = NULL still returns as 0, so set key = -100 as no student ID will ever be a negative number
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Constructor
Node::Node(int in) {
    key = in;
    parent = NULL;
    left = NULL;
    right = NULL;
}
// Destructor
Node::~Node() {
}

// Add parent 
void Node::add_parent(Node* in) {
    parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
    left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
    right = in;
}

// Get key
int Node::get_key()
{
    return key;
}
// Get parent node
Node* Node::get_parent()
{
    return parent;
}
// Get left node
Node* Node::get_left()
{
    return left;
}
// Get right node
Node* Node::get_right()
{
    return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------

bool Cleanup = 0;    // Boolean to signify in inorder_walk method whether to delete the node or just print it

// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
    if(in != nullptr){
	inorder_walk(in->get_left(), to);
	if(!Cleanup){
	    in->print_info(to);    // Just printing the node
	}
	inorder_walk(in->get_right(), to);
	if(Cleanup){
	    delete in;    // Deleting each node in the tree in order
	}
    }
}
// Constructor
BST::BST()
{
    root = NULL;
}
// Destructor
BST::~BST()
{
    Cleanup = 1;
    walk(std::cout);
    Cleanup = 0;    // Reset Cleanup otherwise it will start deleting student IDS as it's adding them
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
    Node* y = NULL;
    Node* x = root;
    while(x != NULL){
	y = x;
	if (in->get_key() < x->get_key()){
	    x = x->get_left();
	} else {
	    x = x->get_right();
	}
    }
    in->add_parent(y);
    if(y == NULL){
	root = in;    // Tree was empty
    } else if (in->get_key() < y->get_key()){
        y->add_left(in);
    } else{
        y->add_right(in);
    }
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
    Node* y;
    if(out->get_left() == NULL){
        transplant(out, out->get_right());
    } else if(out->get_right() == NULL){
        transplant(out, out->get_left());
    } else{
	y = get_min(out->get_right());
        if(y->get_parent() != out){
	    transplant(y, y->get_right());
	    y->add_right(out->get_right());
	    y->get_right()->add_parent(y);
	}
	transplant(out, y);
	y->add_left(out->get_left());
	y->get_left()->add_parent(y);
    }
    delete out;
}

// Transplant function to assist delete function. Takes subtree rooted at u and roots it at v instead.
void BST::transplant(Node* u, Node* v)
{
    if(u->get_parent() == NULL){
        root = v;
    } else if (u == u->get_parent()->get_left()){
        u->get_parent()->add_left(v);
    } else {
        u->get_parent()->add_right(v);
    }
    if(v != NULL){
        v->add_parent(u->get_parent());
    }
}

// minimum key in the BST
Node* BST::tree_min()
{
    return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
    return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
    Node* x = in;
    while(x->get_left() != NULL){
        x = x->get_left();
    }
    return x;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
    Node* x = in;
    while(x->get_right() != NULL){
        x = x->get_right();
    }
    return x;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
    if(in->get_right() != NULL){
         return get_min(in->get_right());
    }
    Node* y = in->get_parent();
    while((y != NULL) and (in == y->get_right())){
        in = y;
	y = y->get_parent();
    }
    return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
    if(in->get_left() != NULL){
        return get_max(in->get_left());
    }
    Node* y = in->get_parent();
    while((y != NULL) and (in == y->get_left())){
        in = y;
	y = y->get_parent();
    }
    return y;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
   inorder_walk(root, to); 
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
    Node* x = root;
    while((x != NULL) and (search_key != x->get_key())){
        if(search_key < x->get_key()){
	    x = x->get_left();
	} else {
	    x = x->get_right();
	}
    }
    return x;
}
// ---------------------------------------
