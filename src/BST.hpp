#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
   protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data> *root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

   public:
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    // TODO
    virtual ~BST() {
    	deleteAll(root);//call deleteAll function to delete entire BST
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO
    virtual bool insert(const Data &item) {
	//check if BST is empty
	if(empty()){
		BSTNode<Data>* newNode = new BSTNode<Data>(item);
		root = newNode;
		isize += 1;//increment the size
		iheight = 1;
		return true;
	}
	unsigned int newHeight = 1;
	BSTNode<Data> * node = this->root;// make a pointer to root to find element

	while(true){//using while loop to insert
		if(item < node->data){//check if item < node->data
			if(node->left)//check if there is a left node for this node
				node = node->left;
			else{
				//create a new node object
				BSTNode<Data>* newNode = new BSTNode<Data>(item);
				newNode->parent = node;//let new node's parent points to node
				node->left = newNode;
				isize += 1;
				newHeight += 1;
				if(newHeight > iheight)
					iheight = newHeight;
				
				return true;
			}
		} else if (node->data < item){
			if(node->right)//check if there is a right node for this node
				node = node->right;
			else{
				//create a new node object
				BSTNode<Data>* newNode = new BSTNode<Data>(item);
				newNode->parent = node;//let new node's parent points to node
				node->right = newNode;
				isize += 1;
				newHeight += 1;
				if(newHeight > iheight)
					iheight = newHeight;

				return true;
			}
		} else {
			return false;//there is already same element in this BST
		}
		newHeight += 1;
	}
    }

    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    // TODO
    virtual iterator find(const Data &item) const {
	if(empty()) // check if there is no element in the BST
		return iterator(first(root));
	BSTNode<Data> * node = root;// make a pointer to root to find element

	while(true){
		if(item < node->data){
			if(node->left)
				node = node->left;
			else
				return iterator(node);
		} else if (node->data < item){
			if(node->right)
				node = node->right;
			else
				return iterator(node);
		} else {
			return iterator(node);
		}
	}
		
	
	

    }

    /** Return the number of items currently in the BST.
     */
    // TODO
    unsigned int size() const {
	return isize;
    }

    /** Return the height of the BST.
     */
    // TODO
    unsigned int height() const {
	
    	return iheight;
    }

    /** Return true if the BST is empty, else false.
     */
    // TODO
    bool empty() const {
    	if(!isize)
		return true;
	else
		return false;
    }

    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    // TODO
    iterator begin() const {
	return BSTIterator<Data>( first(root)); 
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const { inorder(root); }

   private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    // TODO
    void inorder(BSTNode<Data> *n) const {
        /* Pseudo Code:
          if current node is null: return;
          recursively traverse left sub-tree
          print current node data
          recursively traverse right sub-tree
        */
	//if current node is null pointer, return
	if(n == nullptr)
		return;
	inorder(n->left);//go to left node of current node
	std::cout << n->data << endl;//print current data
	inorder(n->right);//go to right node
	
	
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data> *first(BSTNode<Data> *curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    // TODO
    static void deleteAll(BSTNode<Data> *n) {
        /* Pseudo Code:
          if current node is null: return;
          recursively delete left sub-tree
          recursively delete right sub-tree
          delete current node
        */
	if(n == 0)// check if current node if null
		return;
	deleteAll(n -> left);//recursively delete left sub-tree
	deleteAll(n -> right);//recursively delete right sub-tree
	delete n;
    }
};

#endif  // BST_HPP
