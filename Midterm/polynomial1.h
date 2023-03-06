
#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm {
public:
	int coef;
	int expo;
};

class ArrayPolynomial {
public:
	PolynomialTerm terms[MAX_TERMS];

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}

		return;
	}

	void inputArrayBasedTerms(int coef, int expo)
	{
		// modify the following code and add your code here
		int i = 0;

		for (i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef == 0 && terms[i].expo == 0)
			{
				terms[i].coef = coef;
				terms[i].expo = expo;
				break;
			}
			else if (expo <= terms[i].expo)
			{
				for (int k = MAX_TERMS-1; k >=i; k--)
				{
					terms[k + 1] = terms[k];
				}
				terms[i].coef = coef;
				terms[i].expo = expo;
				break;
			}
		}

		// add your code here 


		return;
	}

	void printArrayBasedPoly()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				cout << " + " << terms[i].coef;
			else
				cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	void printArrayBasedPolyRecursively()
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			cout << terms[0].coef;
		else
			cout << terms[0].coef << "X^" << terms[0].expo;

		printArrayBasedPolyRecursively(1);
	}

	void printArrayBasedPolyRecursively(int i)
	{
		
		if (i < MAX_TERMS&&terms[i].coef!=0&&terms[i].expo!=0)
		{
			if (terms[i].expo == 0)
			{
				if (terms[i].coef >= 0)
				{
					if (i == 0)
					{
						cout << terms[i].coef << " ";
					}
					else
					{
						cout << "+" << terms[i].coef << " ";
					}
				}
				else
				{
					cout << terms[i].coef << " ";
				}
			}
			else
			{
				if(terms[i].coef>=0)
				{
				if (i == 0)
				{
					cout << terms[i].coef<<"X^"<<terms[i].expo<<" ";
				}
				else
				{
					cout << "+" << terms[i].coef << "X^" << terms[i].expo << " ";
				}
			}
				else
				{
				cout << terms[i].coef << "X^" << terms[i].expo << " ";
				}
					}
			printArrayBasedPolyRecursively(i+1);
		}
		// add yor code here

		return;
	}

	void ArrayBasedReverse()
	{
		PolynomialTerm temp;
		int i = 0;
		for (i = 0; i < MAX_TERMS; i++)
		{
			if (terms[i].coef == 0 && terms[i].expo == 0)
			{
				break;
			}
		}
		for (int k = 0; k < i/2; k++)
		{
			temp = terms[k];
			  terms[k]= terms[i - k -1];
			  terms[i - k -1] = temp;
		}
		// add yor code here


	}

	void ArrayBasedIncPower(int expo)
	{


		// add yor code here


	}
};

class LinkedPolynomialTerm {
public:
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr;
};

class LinkedPolynomial {
public:
	LinkedPolynomialTerm *polynomialTermPtr = nullptr;

	void clear()
	{
		LinkedPolynomialTerm *tmpPtr;

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkBasedTerms(int coef, int expo)
	{
		LinkedPolynomialTerm *tmpPtr;
		LinkedPolynomialTerm *curr=polynomialTermPtr,*last=polynomialTermPtr;
		tmpPtr = new LinkedPolynomialTerm;
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;
		if (polynomialTermPtr == nullptr)
		{
			polynomialTermPtr = tmpPtr;
		}
		else
		{ 
			while (curr != nullptr)
			{
				if (tmpPtr->expo <= curr->expo)
				{
					if (tmpPtr->expo <= polynomialTermPtr->expo)
					{
						tmpPtr->nextTermPtr = polynomialTermPtr;
						polynomialTermPtr = tmpPtr;
					}
					else
					{
						last->nextTermPtr = tmpPtr;
						tmpPtr->nextTermPtr = curr;
					}
					break;
				}
				else if (curr->nextTermPtr == nullptr)
				{
					curr->nextTermPtr = tmpPtr;
					break;
				}
				last = curr;
				curr = curr->nextTermPtr;
			}
		}
		//tmpPtr->nextTermPtr = polynomialTermPtr;



		// add your code here 


		return;
	}

	void printLinkBasedPoly()
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr;

		if (termPtr == nullptr)
			return;

		if (termPtr->expo == 0)
			cout << termPtr->coef;
		else
			cout << termPtr->coef << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;

		while (termPtr != nullptr) {
			if (termPtr->coef == 0)
				return;

			if (termPtr->expo == 0)
				cout << " + " << termPtr->coef;
			else
				cout << " + " << termPtr->coef << "X^" << termPtr->expo;

			termPtr = termPtr->nextTermPtr;
		}

		return;
	}

	void printLinkBasedPolyRecursively()
	{
		if (polynomialTermPtr == nullptr)
			return;

		if (polynomialTermPtr->expo == 0)
			cout << polynomialTermPtr->coef;
		else
			cout << polynomialTermPtr->coef << "X^" << polynomialTermPtr->expo;

		printLinkBasedPolyRecursively(polynomialTermPtr->nextTermPtr);
	}

	void printLinkBasedPolyRecursively(LinkedPolynomialTerm *currPtr)
	{
		if (currPtr->expo == 0)
		{
			
				cout << currPtr->coef ;
				if (currPtr->nextTermPtr != nullptr)
				{
					if (currPtr->nextTermPtr->coef >= 0)
					{
						cout << "+ ";
					}
				}
			
		}
		else
		{	
				cout << currPtr->coef << "X^" << currPtr->expo;
				if (currPtr->nextTermPtr != nullptr)
				{
					if (currPtr->nextTermPtr->coef >= 0)
					{
						cout << "+ ";
					}
				}
			
		}
		if (currPtr->nextTermPtr != nullptr)
		{
			printLinkBasedPolyRecursively(currPtr->nextTermPtr);
		}
		// add yor code here

		return;
	}

	void LinkBasedReverse()
	{
		/*LinkedPolynomialTerm *curr = polynomialTermPtr;
		int count=0,count1=0;
		while (curr->nextTermPtr != nullptr)
		{
			curr = curr->nextTermPtr;
			count++;
		}
		while (count < count1)
		{
			if (count1 == 0)
			{
				curr ->nextTermPtr= polynomialTermPtr;
				polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				curr->nextTermPtr->nextTermPtr = nullptr;
			}
			else
			{
				LinkedPolynomialTerm *last ;
				last = polynomialTermPtr;
				polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				last->nextTermPtr=curr->nextTermPtr;
				curr->nextTermPtr = last;
			}
			count1++;
		}
		polynomialTermPtr = curr;*/
		// add yor code here


	}

	void LinkBasedIncPower(int expo)
	{


		// add yor code here


	}
};
