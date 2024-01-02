#pragma once

//Week 6-7 challange
// Implementation of a SparseMatrix class using a quad tree structure 

//============== Required includes ============== 
//#include <iostream>
//#include<vector>

//Uncomment to remove debug
//#define NDEBUG
//#include<cassert>

namespace QuadTree 
{
#include <iostream>

	template <typename T>
	class QuadNode {
	public:
		T value;
		QuadNode* northWest;
		QuadNode* northEast;
		QuadNode* southWest;
		QuadNode* southEast;

		QuadNode(const T& init_Value) : value(init_Value), northWest(nullptr), northEast(nullptr), southWest(nullptr), southEast(nullptr) {}
	};

	template <typename T>
	class SparseMatrix {
	private:
		int numRows;
		int numColumns;
		QuadNode<T>* root;

		//Private helper using recurion to set values in the matrix
		void setValueRec(QuadNode<T>*& node, int rowIndex, int columnIndex, int numRows, int numColumns, const T& new_Value) 
		{
			if (!node)
			{
				//If node is null, create a new QuadNode
				node = new QuadNode<T>(T());
			}
			
			if (numRows == 1 && numColumns == 1)
			{
				node = new QuadNode<T>(new_Value);
			}
			else
			{
				int new_numRows = numRows / 2;
				int new_numColumns = numColumns / 2;

				if (rowIndex < new_numRows && columnIndex < new_numColumns)
					setValueRec(node->northWest, rowIndex, columnIndex, new_numRows, new_numColumns, new_Value);

				else if (rowIndex < new_numRows && columnIndex >= new_numColumns)
					setValueRec(node->northEast, rowIndex, columnIndex - new_numColumns, new_numRows, new_numColumns, new_Value);

				else if (rowIndex >= new_numRows && columnIndex < new_numColumns)
					setValueRec(node->southWest, rowIndex - new_numRows, columnIndex, new_numRows, new_numColumns, new_Value);

				else
					setValueRec(node->southEast, rowIndex - new_numRows, columnIndex - new_numColumns, new_numRows, new_numColumns, new_Value);
			}
		}

		T getValueRec(QuadNode<T>* node, int rowIndex, int columnIndex, int numRows, int numColumns)
		{
			if (!node)
				return T();  // Return default value for non-existent elements

			if (numRows == 1 && numColumns == 1)
				return node->value;

			int new_numRows = numRows / 2;
			int new_numColumns = numColumns / 2;

			if (rowIndex < new_numRows && columnIndex < new_numColumns)
				return getValueRec(node->northWest, rowIndex, columnIndex, new_numRows, new_numColumns);

			else if (rowIndex < new_numRows && columnIndex >= new_numColumns)
				return getValueRec(node->northEast, rowIndex, columnIndex - new_numColumns, new_numRows, new_numColumns);

			else if (rowIndex >= new_numRows && columnIndex < new_numColumns)
				return getValueRec(node->southWest, rowIndex - new_numRows, columnIndex, new_numRows, new_numColumns);

			else
				return getValueRec(node->southEast, rowIndex - new_numRows, columnIndex - new_numColumns, new_numRows, new_numColumns);
		}

	public:
		//Constructor for empty matrix
		SparseMatrix(int init_numRows, int init_numColumns) : numRows(init_numRows), numColumns(init_numColumns), root(new QuadNode<T>(T())) {}

		//Constructor for initialising from 2d vector
		SparseMatrix(std::vector<std::vector<T>> vector) : numRows(vector.size()), numColumns(vector[0].size()), root(new QuadNode<T>(T())) 
		{
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < numColumns; j++)
				{
					setValue(i, j, vector[i][j]);
				}
			}
		}

		//Constructor for initialising from dense matrix
		SparseMatrix(Dense::Matrix<T> matrix) : numRows(matrix.getNumRows()), numColumns(matrix.getNumCols), root(new QuadNode<T>(T()))
		{
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < numColumns; j++)
				{
					setValue(i, j, matrix(i, j));
				}
			}
		}

		void setValue(int rowIndex, int columnIndex, T value)
		{
			assert(("Index out of range", 0 <= rowIndex && rowIndex < numRows && 0 <= columnIndex && columnIndex < numColumns));
			setValueRec(root, rowIndex, columnIndex, numRows, numColumns, value);
		}

		T getValue(int rowIndex, int columnIndex) 
		{
			assert(("Index out of range", 0 <= rowIndex && rowIndex < numRows && 0 <= columnIndex && columnIndex < numColumns));
			return getValueRec(root, rowIndex, columnIndex, numRows, numColumns);
		}

		void printDense()
		{
			for (int i = 0; i < numRows; i++)
			{
				for (int j = 0; j < numColumns; j++)
				{
					std::cout << getValue(i, j) << ", ";
				}
				std::cout << std::endl;
			}
		}
	};
}

