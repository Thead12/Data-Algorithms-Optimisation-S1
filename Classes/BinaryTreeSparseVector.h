#pragma once
//Week 6-7 challange
// Implementation of a SparseVector class using a binary tree structure
// Contains an unbalanced and balanced version, balanced version is based of AVL binary tree
// 
// Both have get and set functions aswell as the ability to convert from dense vectors

//============== Required includes ============== 
#include <iostream>
#include<vector>

//Uncomment to remove debug
//#define NDEBUG
#include<cassert>

namespace BinaryTree
{
	//SparseVector using unbalanced binary tree
	namespace Unbalanced
	{
		template<typename T>
		class TreeNode
		{
		public:
			int index;
			T value;
			TreeNode* left;
			TreeNode* right;

			//================ Constructor ================ 
			TreeNode(int initIndex, const T& initValue) : index(initIndex), value(initValue), left(nullptr), right(nullptr) {}
		};

		template<typename T>
		class SparseVector
		{
		private:
			TreeNode<T>* root;

			//Helper function to insert a node into the tree
			void insert(TreeNode<T>*& node, int index, const T& value) {
				if (!node) {
					node = new TreeNode<T>(index, value);
				}
				else if (index < node->index) {
					insert(node->left, index, value);
				}
				else if (index > node->index) {
					insert(node->right, index, value);
				}
				else {
					// Update existing node if index matches
					node->value = value;
				}
			}

			//Helper function to perform an in-order travesal of the tree
			void inOrderTraversal(TreeNode<T>* node) const
			{
				if (node)
				{
					inOrderTraversal(node->left);
					std::cout << "Left -->  (" << node->index << ", " << node->value << ")" << std::endl;
					inOrderTraversal(node->right);
				}
			}

			T getValueRec(TreeNode<T>* node, int index)
			{
				if (!node) {
					// If the node is null or the index is not found
					//returns a default-constructed value
					return T();
				}

				if (index < node->index) {
					// If the index is less than the current node's index, search in the left subtree
					return getValueRec(node->left, index);
				}
				else if (index > node->index) {
					// If the index is greater than the current node's index, search in the right subtree
					return getValueRec(node->right, index);
				}
				else {
					// If the index matches the current node's index, return the value
					return node->value;
				}
			}

		public:
			//================ Constructor ================ 
			SparseVector() : root(nullptr) {}

			SparseVector(std::vector<T> vector) : root(nullptr)
			{
				for (int i = 0; i < vector.size(); i++) {
					T vectorValue = vector[i];
					if (vectorValue != 0)
					{
						insert(i, vector[i]);
					}
				}
			}

			void insert(int index, const T& value)
			{
				insert(root, index, value);
			}

			//================ Getter ================ 
			T getValue(int index)
			{
				return getValueRec(root, index);
			}

			void print() const
			{
				inOrderTraversal(root);
				std::cout << std::endl;
			}
		};
	}

	//SparseVector implementation using self balancing AVL binary tree
	namespace Balanced
	{
		
		template <typename T>
		struct TreeNode
		{
			int index;
			T value;
			int height;
			TreeNode* left;
			TreeNode* right;

			TreeNode(int idx, const T& val) : index(idx), value(val), height(1), left(nullptr), right(nullptr) {}
		};

		template <typename T>
		class SparseVector
		{
		private:
			TreeNode<T>* root;

			int minimumBalanceFactor = 0;
			int maximumBalanceFactor = 0;

			int getHeight(TreeNode<T>* node)
			{
				return (node ? node->height : 0);
			}

			void updateHeight(TreeNode<T>* node)
			{
				node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
			}

			//Rotation functions to reorder the tree and maintain balance
			TreeNode<T>* rightRotate(TreeNode<T>* y)
			{
				TreeNode<T>* x = y->left;
				TreeNode<T>* T2 = x->right;

				x->right = y;
				y->left = T2;

				updateHeight(y);
				updateHeight(x);

				return x;
			}

			TreeNode<T>* leftRotate(TreeNode<T>* x)
			{
				TreeNode<T>* y = x->right;
				TreeNode<T>* T2 = y->left;

				y->left = x;
				x->right = T2;

				updateHeight(x);
				updateHeight(y);

				return y;
			}

			TreeNode<T>* leftRightRotate(TreeNode<T>* x)
			{
				x->left = leftRotate(x->left);
				return rightRotate(x);
			}

			TreeNode<T>* rightLeftRotate(TreeNode<T>* y)
			{
				y->right = rightRotate(y->right);
				return leftRotate(y);
			}

			//Function to balance the tree, is used when inserting
			TreeNode<T>* balance(TreeNode<T>* node, int index)
			{
				updateHeight(node);

				int balanceFactor = getHeight(node->left) - getHeight(node->right);

				// Perform rotations if needed
				if (balanceFactor > 1) {
					if (index < node->left->index) {
						return rightRotate(node);
					}
					else {
						return leftRightRotate(node);
					}
				}
				else if (balanceFactor < -1) {
					if (index > node->right->index) {
						return leftRotate(node);
					}
					else {
						return rightLeftRotate(node);
					}
				}

				return node;
			}

			//Private insert helper function
			TreeNode<T>* insert(TreeNode<T>* node, int index, const T& value)
			{
				if (!node) {
					return new TreeNode<T>(index, value);
				}

				if (index < node->index) {
					node->left = insert(node->left, index, value);
				}
				else if (index > node->index) {
					node->right = insert(node->right, index, value);
				}
				else {
					node->value = value;
					return node;
				}

				return balance(node, index);
			}

			T getValueRec(TreeNode<T>* node, int index)
			{
				if (!node) {
					// If the node is null or the index is not found
					//returns a default-constructed value
					return T();
				}

				if (index < node->index) {
					// If the index is less than the current node's index, search in the left subtree
					return getValueRec(node->left, index);
				}
				else if (index > node->index) {
					// If the index is greater than the current node's index, search in the right subtree
					return getValueRec(node->right, index);
				}
				else {
					// If the index matches the current node's index, return the value
					return node->value;
				}
			}

			//Private helper function for printing tree in order
			void inOrderTraversal(TreeNode<T>* node)
			{
				if (node) {
					inOrderTraversal(node->left);
					updateHeight(node);  // Update height during traversal for accurate display

					int balanceFactor = calculateBalanceFactor(node);

					if (balanceFactor < minimumBalanceFactor) {
						minimumBalanceFactor = balanceFactor;
					}
					else if (balanceFactor > maximumBalanceFactor) {
						maximumBalanceFactor = balanceFactor;
					}
					std::cout << "[BF: " << balanceFactor << "] -->\t";
					std::cout << "(" << node->index << ", " << node->value << "), " << std::endl;;
					inOrderTraversal(node->right);
				}
			}

			int calculateBalanceFactor(TreeNode<T>* node)
			{
				if (!node) {
					return 0;
				}
				return getHeight(node->left) - getHeight(node->right);
			}

		public:
			//Constructor for empty Vector
			SparseVector() : root(nullptr) {}

			//Constructor for constructing from a standard vector
			SparseVector(std::vector<T> vector) : root(nullptr)
			{
				for (int i = 0; i < vector.size(); i++)
				{
					T vectorValue = vector[i];
					if (vectorValue != 0)
					{
						insert(i, vector[i]);
					}
				}
			}

			void insert(int index, const T& value)
			{
				root = insert(root, index, value);
			}

			T getValue(int index)
			{
				return getValueRec(root, index);
			}

			void print()
			{
				inOrderTraversal(root);
				std::cout << std::endl;
			}

			void printBFRange()
			{
				std::cout << "Balance Factor range: [" << minimumBalanceFactor << ", " << maximumBalanceFactor << "]" << std::endl;
			}
		};

	}
}
