// myOrchard2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<iostream>
#include <algorithm>
#include <array>
using namespace std;
template <typename T>
class AVL_Tree
{
	struct node
	{
		int value;
		T* data;
		node* left;
		node* right;
		int height;
	};

	node* root;
	int numberOfNodes = 0;

	void makeEmpty(node* t)
	{
		if (t == NULL)
			return;
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}

	node* insert(int x, T* data, node* t)
	{
		if (t == NULL)
		{
			numberOfNodes++;
			t = new node;
			t->value = x;
			t->data = data;
			t->height = 0;
			t->left = t->right = NULL;
		}

		else if (x < t->value)
		{
			t->left = insert(x, data, t->left);
			if (height(t->left) - height(t->right) == 2)
			{
				if (x < t->left->value)
					t = singleRightRotate(t);
				else
					t = doubleRightRotate(t);
			}
		}
		else if (x > t->value)
		{
			t->right = insert(x, data, t->right);
			if (height(t->right) - height(t->left) == 2)
			{
				if (x > t->right->value)
					t = singleLeftRotate(t);
				else
					t = doubleLeftRotate(t);
			}
		}

		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRightRotate(node* &t)
	{
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), t->height) + 1;
		return u;
	}

	node* singleLeftRotate(node* &t)
	{
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(t->right), t->height) + 1;
		return u;
	}

	node* doubleLeftRotate(node* &t)
	{
		t->right = singleRightRotate(t->right);
		return singleLeftRotate(t);
	}

	node* doubleRightRotate(node* &t)
	{
		t->left = singleLeftRotate(t->left);
		return singleRightRotate(t);
	}

	node* findMin(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->left == NULL)
			return t;
		else
			return findMin(t->left);
	}

	node* findMax(node* t)
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL)
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t)
	{
		node* temp;

		// Element not found
		if (t == NULL)
			return NULL;

		// Searching for element
		else if (x < t->value)
			t->left = remove(x, t->left);
		else if (x > t->value)
			t->right = remove(x, t->right);

		// Element found
		// With 2 children
		else if (t->left && t->right)
		{
			temp = findMin(t->right);
			t->value = temp->value;
			t->right = remove(t->value, t->right);
		}
		// With one or zero child
		else
		{
			temp = t;
			if (t->left == NULL)
				t = t->right;
			else if (t->right == NULL)
				t = t->left;
			delete temp;
			numberOfNodes--;
		}
		if (t == NULL)
			return t;

		t->height = max(height(t->left), height(t->right)) + 1;

		// If node is unbalanced
		// If left node is deleted, right case
		if (height(t->left) - height(t->right) == 2)
		{
			// right right case
			if (height(t->left->left) - height(t->left->right) == 1)
				return singleLeftRotate(t);
			// right left case
			else
				return doubleLeftRotate(t);
		}
		// If right node is deleted, left case
		else if (height(t->right) - height(t->left) == 2)
		{
			// left left case
			if (height(t->right->right) - height(t->right->left) == 1)
				return singleRightRotate(t);
			// left right case
			else
				return doubleRightRotate(t);
		}
		return t;
	}

	int height(node* t)
	{
		return (t == NULL ? -1 : t->height);
	}

	int getBalance(node* t)
	{
		if (t == NULL)
			return 0;
		else
			return height(t->left) - height(t->right);
	}

	void inorder(node* t)
	{
		if (t == NULL)
			return;
		inorder(t->left);
		cout << t->value << " ";
		inorder(t->right);
	}

	void inorderVisit(node* t, T* array[], int &i)
	{
		if (t == NULL)
			return;
		inorderVisit(t->left, array, i);
		array[i] = t->data;
		i += 1;
		inorderVisit(t->right, array, i);
	}
	/*
	*/

public:
	AVL_Tree()
	{
		root = NULL;
	}

	void insert(int x, T* data)
	{
		root = insert(x, data, root);
	}

	void remove(int x)
	{
		root = remove( x, root);
	}

	T** getSortedArray() {
		T** array = new T*[numberOfNodes];
		int counter = 0;
		inorderVisit(root, array, counter);

		for (int i = 0; i < numberOfNodes; i++){
			cout << "{ ripeRate: "<< array[i]->ripeRate << ", id: " << array[i]->id <<" }"<< endl;
		}
		return array;
	}
	void display()
	{
		inorder(root);
		cout << endl;

	}
	
};

class Fruit {
	public:
	int ripeRate;
	int id;
};
/*
	struct fruit
	{
		int ripeRate;
		int id;
	};
*/
int main()
{

	AVL_Tree<Fruit> t;
	Fruit* f1 = new Fruit;
	f1->ripeRate = 20;
	f1->id = 2;
	t.insert(f1->ripeRate, f1);
	Fruit* f2 = new Fruit;
	f2->ripeRate = 15;
	f2->id = 7;
	t.insert(f2->ripeRate, f2);
	Fruit* f3 = new Fruit;
	f3->ripeRate = 15;
	f3->id = 9;
	t.insert(f3->ripeRate, f3);
	//t.remove(20);
	t.getSortedArray();
	t.display();
	std::cout << "Hello World111!\n";
}
