// Final202106.cpp
//

//#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include<stack>
#include<queue>
#include "BinarySearchTree.h"
#include "HashedDictionary.h" 

using namespace std;

void displayWordCount(BinaryNode<string>&  entry)
{
	cout << entry.getItem() << "(" << entry.getCount() << ")  ";
}

void displayWordCount(HashedEntry<string, string>&  entryPtr)
{
	cout << entryPtr.getItem() << "(" << entryPtr.getCount() << ")  ";
}

void input(string sMessage, string &sInputString)
{
	do {
		cout << sMessage << endl;
		cin >> sInputString;
	} while (cin.fail());
}

void input(string sMessage, int &inputNum)
{
	do {
		cout << sMessage << endl;
		cin >> inputNum;
	} while (cin.fail());
}

void stringToTokens(queue<string>& aQueue, string aString)
{
	string token, theDelimters = ".,!?;: ";
	int end = 0;
	int start = aString.find_first_not_of(theDelimters, end);

	while (start != string::npos) {
		end = aString.find_first_of(theDelimters, start);
		token = aString.substr(start, end - start);
		aQueue.push(token);
		start = aString.find_first_not_of(theDelimters, end);
	}
}

// ================ Q1 Begins Here ==================
#define PQSIZE	10

void pqArrayInsert(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == PQSIZE)
		cout << "ARRAY Priority queue full!" << endl;
	bool success = false;
	for (int i = 0; i < size; i++)
	{
		if (pqArray[i].getItem() == word)
		{
			pqArray[i].countUp();
			success = true;
			break;
		}
	}
	if (success == false)
	{
		pqArray[size] = word;
		size++;
	}
	
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < size; k++)
			{	
				if ((pqArray[i].getItem().size()>pqArray[k].getItem().size())||(pqArray[i].getCount() > pqArray[k].getCount())||(pqArray[i].getItem()>pqArray[k].getItem()))
				{
					BinaryNode<string>temp = pqArray[i];
					pqArray[i] = pqArray[k];
					pqArray[k] = temp;
					
					
				}
			}
		}
	
	// add your code here


	//pqArray[size] = word;
	//pqArray[size].countUp();
	//size++;

}

int pqArrayDelete(BinaryNode<string>* pqArray, int& size, const string word)
{
	if (size == 0) {
		cout << "ARRAY Priority queue empty!" << endl;
		return -1;
	}
	int count = -1;

	// add your code here
	for (int i = 0; i < size; i++)
	{
		if (pqArray[i].getItem() == word)
		{
			if (pqArray[i].getCount() > 1)
			{
				pqArray[i].countDown();
				count = pqArray[i].getCount();
			}
			else
			{
				for (int k =i; k <size; k++)
				{
					pqArray[k] = pqArray[k+1];
				}
				count = 0;
				size--;
			}
		}
	}
	
		for (int i = 0; i < size; i++)
		{
			for (int k = 0; k < size; k++)
			{

				if ((pqArray[i].getItem().size() > pqArray[k].getItem().size()) || (pqArray[i].getCount() > pqArray[k].getCount()) || (pqArray[i].getItem() > pqArray[k].getItem()))
				{
					BinaryNode<string>temp = pqArray[i];
					pqArray[i] = pqArray[k];
					pqArray[k] = temp;
				}
			}
		}
	//pqArray[size].countDown();
	//size--;
	if (count == -1)
	{
		return -1;
	}
	else
	{
		return count;
	}
}

void doQ1()
{
	BinaryNode<string> pqItems[PQSIZE];
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	int i, size = 0;

	while (1) {
		input("\nEnter A to Add words, R to Remove a word, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				pqArrayInsert(pqItems, size, aWord);
			}

			for (i = 0; i < size; i++)
				displayWordCount(pqItems[i]);

			cout << endl;
		}
		else if (sInput == "R" || sInput == "r") {
			if (size == 0)
				cout << "PQ is empty!" << endl;
			else {
				input("Enter word: ", aWord);

				if (pqArrayDelete(pqItems, size, aWord) < 0)
					cout << "Not exist in PQ!" << endl;
				else if (size == 0)
					cout << "Last word deleted!" << endl;
				else {
					for (i = 0; i < size; i++)
						displayWordCount(pqItems[i]);

					cout << endl;
				}
			}
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// ================ Q2 Begins Here ==================
void showAdjMatrix(int** matrixGraph, int numVertices)
{
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			if (matrixGraph[i][j] == INT_MAX)
				cout << " - ";
			else
				cout << ' ' << matrixGraph[i][j];
		}
		cout << '\n';
	}
}

int countEdges(int** matrixGraph, int numVertices)
{
	int count = 0;
	// add your code here
	for (int i = 0; i < numVertices-1; i++)
	{
		for (int k = i; k < numVertices; k++)
		{
			if (matrixGraph[i][k] < INT_MAX && i != k)
			{
				count++;
			}
		}
	}
	return count;
}

int countWeights(int** matrixGraph, int numVertices)
{
	int n[100] = {INT_MAX};
	int count = 0;
	// add your code here
	for (int k = 0; k < numVertices - 1; k++)
	{
		for (int i = 0; i < numVertices; i++)
		{
			if (matrixGraph[k][i] < INT_MAX && i!=k)
			{
				bool success = true;
				for (int h = 0; h < count; h++)
				{
					if (n[h] == matrixGraph[k][i])
					{
						success = false;
					}
				}
				if (success == true)
				{
					n[count] = matrixGraph[k][i];
					count++;
				}
			}
		}
	}
	return count;
}

int findMaxWeight(int** matrixGraph, int numVertices)
{

	// add your code here
	int max = INT_MIN;
	for (int i = 0; i < numVertices-1; i++)
	{
		for (int k = i; k < numVertices; k++)
		{
			if (matrixGraph[i][k] < INT_MAX && i != k&&max<matrixGraph[i][k])
			{
				max = matrixGraph[i][k];
			}
		}
	}
	return max;
}

bool peekPath(int** matrixGraph, int numVertices, int startVertex, int endVertex)
{
	/*
	 q = a new empty queue
	
	 for ( each vertex v adjacent to startVertex )
	   	q.enqeue(v)


	 while (!q.isEmpty()) 
	 {
		q.dequeue(w)

		if ( w is equal to endVertex ) 
			return true;

		for ( each vertex u that is larger than w and adjacent to w )
				q.enqueue(u)
	 }
	 
	 return false;
	*/

	queue<int> myQueue;
	myQueue.push(startVertex);
	int count = 0;
	int c = startVertex;
	while (1)
	{
		if (startVertex == endVertex)
		{
			return true;
		}
		for (int i = 0; i < numVertices; i++)
		{
			if (matrixGraph[startVertex][i] < INT_MAX && i != startVertex)
			{
				myQueue.push(i);
			}
		}
		if (!myQueue.empty())
		{
			startVertex = myQueue.front();
			myQueue.pop();
		}
		if (count > numVertices && startVertex == c)
		{
			break;
		}
		count++;
	}

	// add your code here


	return false;
}


void doQ2()
{
	string sInput;
	int numVertices, u, v, weight;

	ifstream inFile("C:\\Users\\¼Bªv¦ö\\Desktop\\I2B21¼Bªv¦ö\\graph.txt");

	if (!inFile) {
		cerr << "Error: Failed to open " << "graph.txt" << " for input! \n";
		return;
	}

	if (inFile.peek() == EOF) {
		cerr << "Error: Empty input file! \n";
		return;
	}

	inFile >> numVertices;

	int **matrixGraph = new int*[numVertices];

	for (int i = 0; i < numVertices; i++) {
		matrixGraph[i] = new int[numVertices];

		for (int j = 0; j < numVertices; j++)
			matrixGraph[i][j] = INT_MAX;

		matrixGraph[i][i] = 0;
	}

	while (inFile.peek() != EOF) {
		inFile >> u >> v >> weight;

		if (inFile.fail())
			break;

		if (u < numVertices && v < numVertices)
			matrixGraph[u][v] = matrixGraph[v][u] = weight;
	}

	cout << "\nThe adjacency matrix:\n";
	showAdjMatrix(matrixGraph, numVertices);
	/*
	0 1 - - - - - -
	1 0 - 3 4 - - -
	- - 0 - - 5 6 -
	- 3 - 0 - - - 7
	- 4 - - 0 - - -
	- - 5 - - 0 - -
	- - 6 - - - 0 -
	- - - 7 - - - 0
	*/

	cout << "\nThere are " << countEdges(matrixGraph, numVertices) << " edges and " << countWeights(matrixGraph, numVertices) << " different weights\n";

	cout << "\nThe max. edge weight is ";
	cout << findMaxWeight(matrixGraph, numVertices) << "\n";

	cout << "\nThere are paths between\n\n";
	for (int i = 0; i < numVertices - 1; i++)
		for (int j = i + 1; j < numVertices; j++)
			if (peekPath(matrixGraph, numVertices, i, j))
				cout << i << " <===> " << j << endl;
	/*
	0 <===> 1
	0 <===> 3
	0 <===> 4
	0 <===> 7
	1 <===> 3
	1 <===> 4
	1 <===> 7
	2 <===> 5
	2 <===> 6
	3 <===> 4
	3 <===> 7
	4 <===> 7
	5 <===> 6
	*/

	return;
}

// ================ Q3 Begins Here ==================
void display(BinaryNode<string>& aNode)
{
	cout << aNode.getItem() << "  ";
}

void doQ3()
{
	string sInput, aString, aLine;
	BinarySearchTree<string> myBST;

	while (1) {
		input("\nEnter command: A to Add, N to Count, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);

			string token, theDelimters = ".,!?;: ";
			int end = 0;
			int start = aLine.find_first_not_of(theDelimters, end);

			while (start != string::npos) {
				end = aLine.find_first_of(theDelimters, start);
				token = aLine.substr(start, end - start);
				myBST.add(token);
				start = aLine.find_first_not_of(theDelimters, end);
			}

			cout << endl << "The inoder traversal of the BST is " << endl;
			myBST.inorderTraverse(display);
			cout << endl << "The mirrored and reverse levelorder traversal of the BST are " << endl;
			myBST.levelorderTraverse(display);
			cout << endl;
		}
		else if (sInput == "N" || sInput == "n") {
			cout << endl << "The iterative non leaf count of the BST is " << myBST.countNonLeaves("i");
			cout << endl << "The recursive non leaf count of the BST is " << myBST.countNonLeaves("r") << endl;
		}
		else if (sInput == "C" || sInput == "c") {
			myBST.clear();
			cout << endl << "BST is empty." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}

	return;

}

// ================ Q4 Begins Here ==================
void doQ4()
{
	queue<string> myTokenQueue;
	string sInput, aLine, aWord;
	HashedEntry<string, string>* itemPtr;
	HashedDictionary<string, string> myHashTable(11);

	while (1) {
		input("\nEnter A to Add, R to Remove, Q to Query, D to Display, C to Clear, or X to Exit", sInput);

		if (sInput == "A" || sInput == "a") {
			cin.ignore();
			cout << "Enter a line of text: ";
			getline(cin, aLine);
			stringToTokens(myTokenQueue, aLine);

			while (!myTokenQueue.empty()) {
				aWord = myTokenQueue.front();
				myTokenQueue.pop();
				myHashTable.add(aWord, aWord);
			}
		}
		else if (sInput == "R" || sInput == "r") {
			input("Enter word: ", aWord);

			if (myHashTable.remove(aWord))
				cout << aWord << " is removed." << endl;
			else
				cout << "Word not found!" << endl;
		}
		else if (sInput == "Q" || sInput == "q") {
			input("Enter word: ", aWord);
			itemPtr = myHashTable.getEntry(aWord);

			if (itemPtr == nullptr)
				cout << "Word not found!" << endl;
			else {
				cout << "Retireved word is: ";
				displayWordCount(*itemPtr);
				cout << endl;
			}
		}
		else if (sInput == "D" || sInput == "d") {
			cout << "Words in buckets are: " << endl;

			int i, len = myHashTable.getTableSize();

			for (i = 0; i < len; i++) {
				cout << i << ": ";
				myHashTable.traverse(i, displayWordCount);
				cout << endl;
			}
		}
		else if (sInput == "C" || sInput == "c") {
			myHashTable.clear();
			cout << "Words in buckets are cleared." << endl;
		}
		else  if (sInput == "X" || sInput == "x")
			return;
		else
			cout << "Unknown command!\r" << endl;
	}
}

// =============== Main Begins Here =================

int main()
{
	string sCommand, sName, sNum, sMessage;

	while (1) {
		cout << endl;
		cout << "1. Priroity queue operations" << endl;
		cout << "2. Graph operations" << endl;
		cout << "3. Binary search tree operations" << endl;
		cout << "4. Hash table operations" << endl;

		input("Enter Question Number( 1 ~ 4 ) or 0 to Exit:", sNum);

		switch (sNum[0] - '0') {
		case 0:
			return 0;
		case 1:
			doQ1();
			break;
		case 2:
			doQ2();
			break;
		case 3:
			doQ3();
			break;
		case 4:
			doQ4();
			break;
		}
	}
}
// ============== Main Program Ends Here ================

