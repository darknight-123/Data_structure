// HW4.cpp : 定義主控台應用程式的進入點。
//

#include <iostream>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

typedef struct linkedTerm {
	int coef;
	int expo;
	linkedTerm *nextTermPtr;
} linkedPolynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void clear(linkedPolynomialTerm *&polynomialTermPtr) 
{
	linkedPolynomialTerm *tmpPtr;

	while ( polynomialTermPtr != nullptr ) {
		tmpPtr = polynomialTermPtr;
		polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		delete tmpPtr;
	}
}

void inputTerms(polynomialTerm terms[], int coef, int expo)
{
	
	// add your code here
	for (int i = 0;i < MAX_TERMS;i++)
	{
		if (expo == terms[i].expo)
		{
			terms[i].coef = coef;
			break;
		}
		else if (expo > terms[i].expo)
		{
			for (int k = MAX_TERMS - 1;k > i;k--)
			{
				terms[k] = terms[k - 1];
			}
			terms[i].coef = coef;
			terms[i].expo = expo;
			break;
		}
	}
	for (int i = 0;i < MAX_TERMS;i++)
	{
		if (terms[i].coef == 0)
		{
			for (int k = i;k<MAX_TERMS-1;k++)
			{
				terms[k] = terms[k+1];
			}
		}
	}
	return;
}

void inputLinkTerms(linkedPolynomialTerm *&polyPtr, int coef, int expo)
{
	linkedPolynomialTerm *tmpPtr,*first=polyPtr,*h;
	h = nullptr;
	tmpPtr = new linkedPolynomialTerm;
	tmpPtr->coef = coef ;
	tmpPtr->expo = expo;
	tmpPtr->nextTermPtr = nullptr;
	// add your code here 
		if (polyPtr == nullptr&&tmpPtr->coef!=0)
		{
			polyPtr = tmpPtr;
		}
		else if(polyPtr!=nullptr)
		{
			while (1)
			{
				if (tmpPtr->expo > polyPtr->expo&&tmpPtr->coef!=0)
				{
					tmpPtr->nextTermPtr = polyPtr;
					polyPtr = tmpPtr;
					break;
				}
				else if (first->expo == tmpPtr->expo)
				{
					if (polyPtr->expo==tmpPtr->expo&&tmpPtr->coef==0)
					{
						if (polyPtr->nextTermPtr == nullptr)
						{
							polyPtr = nullptr;
						}
						else
						{
							polyPtr = polyPtr->nextTermPtr;
						}
					}
					else if (tmpPtr->coef == 0)
					{
						if (first->nextTermPtr == nullptr)
						{
							h->nextTermPtr = nullptr;
						}
						else
						{
							h->nextTermPtr = first->nextTermPtr;
						}
					}
					else if (coef != 0)
					{
						first->coef = coef;
					}
					break;
				}
				else if (tmpPtr->expo > first->expo && tmpPtr->coef != 0)
				{
					tmpPtr->nextTermPtr = first;
					h->nextTermPtr = tmpPtr;
					break;
				}
				else if (first->nextTermPtr == nullptr && tmpPtr->coef != 0)
				{
					first->nextTermPtr = tmpPtr;
					break;
				}
					h = first;
					first = first->nextTermPtr;
					if (first == nullptr)
					{
						break;
					}
			}
		}
	
	return;
}


void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	int k = 0, o = 0, h;

	for (int i = 0;i < MAX_TERMS;i++)
	{

		if (a[k].expo == b[o].expo)
		{
			d[i] = a[k];
			d[i].coef = d[i].coef + b[o].coef;
			k++;
			o++;

		}
		else if (a[k].expo > b[o].expo)
		{
			d[i] = a[k];
			k++;

		}
		else if (a[k].expo < b[o].expo)
		{
			d[i] = b[o];
			o++;
		}
		if (d[i - 1].coef == 0 && i != 0)
		{
			for (h = i;h < MAX_TERMS;h++)
			{
				d[h - 1] = d[h];
			}
			d[h].expo = 0;
			d[h].coef = 0;
			i--;
		}
		if (a[k].coef == 0 && b[o].coef == 0)
		{
			break;
		}
	}
	// add your code here

	return;
}

linkedPolynomialTerm* addLinkBasedPoly(linkedPolynomialTerm* aPtr, linkedPolynomialTerm* bPtr)
{
	int count = 0;
	linkedPolynomialTerm* dPtr, * first, * k;
	dPtr = new linkedPolynomialTerm;
	dPtr = nullptr;
	k = dPtr;
	while (1)
	{
		if (aPtr == nullptr || bPtr == nullptr)
		{
			break;
		}
		first = new linkedPolynomialTerm;
		first->nextTermPtr = nullptr;
		if (aPtr->expo == bPtr->expo)
		{
			first->expo = aPtr->expo;
			first->coef = aPtr->coef+bPtr->coef;
			aPtr = aPtr->nextTermPtr;
			bPtr=bPtr->nextTermPtr;
		}
		else if (aPtr->expo > bPtr->expo)
		{
			first->expo = aPtr->expo;
			first->coef = aPtr->coef;
			aPtr = aPtr->nextTermPtr;
		}
		else if (aPtr->expo < bPtr->expo )
		{
			first->expo = bPtr->expo;
			first->coef = bPtr->coef;
			bPtr = bPtr->nextTermPtr;
		}
		if (first->coef != 0)
		{
			if (dPtr == nullptr)
			{
				dPtr = first;
				k = dPtr;
			}
			else
			{
				k->nextTermPtr = first;
				k = first;
				k->nextTermPtr = nullptr;
			}
		}	
	}
	if (aPtr == nullptr && bPtr != nullptr)
	{
		
			while (bPtr != nullptr)
			{
				first = new linkedPolynomialTerm;
				first->coef = bPtr->coef;
				first->expo = bPtr->expo;
				first->nextTermPtr = nullptr;
				if (k != nullptr)
				{
					k->nextTermPtr = first;
				}
				else
				{
					dPtr = first;
				}
				k = first;
				bPtr = bPtr->nextTermPtr;
			}
		
		
	}
	else if (bPtr == nullptr && aPtr != nullptr)
	{
		
			while (aPtr != nullptr)
			{
				first = new linkedPolynomialTerm;
				first->coef = aPtr->coef;
				first->expo = aPtr->expo;
				first->nextTermPtr = nullptr;
				if (k != nullptr)
				{
					k->nextTermPtr = first;
				}
				else
				{
					dPtr = first;
				}
				k = first;
				aPtr = aPtr->nextTermPtr;
			}
		
	}
	return dPtr;
}

void printArrayBasedPoly(polynomialTerm terms[])
{
	if ( terms[0].coef == 0 ) 
		return;

	if ( terms[0].expo == 0 )
		cout << terms[0].coef;
	else
		cout << terms[0].coef << "X^" << terms[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( terms[i].coef == 0 ) 
			return;

		if ( terms[i].expo == 0 )
			cout << " + " << terms[i].coef;
		else
			cout << " + "<< terms[i].coef  << "X^" << terms[i].expo;
	}
}

void printLinkBasedPoly(linkedPolynomialTerm *polyPtr)
{
	linkedPolynomialTerm *termPtr =  polyPtr;

	if ( termPtr  == nullptr )
			return;

	if ( termPtr->expo == 0 )
		cout << termPtr->coef;
	else
		cout << termPtr->coef << "X^" << termPtr->expo;

	termPtr  = termPtr->nextTermPtr;
	
	while ( termPtr  != nullptr ) {
		if ( termPtr->coef == 0 ) 
			return;

		if ( termPtr->expo == 0 )
			cout << " + " << termPtr->coef;
		else
			cout << " + "<< termPtr->coef  << "X^" << termPtr->expo;

		termPtr = termPtr->nextTermPtr;
	}
}

int main()
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	linkedPolynomialTerm *aPtr, *bPtr, *dPtr;

	int coef, expo;

	aPtr = bPtr = dPtr = nullptr;

	while (1) {
		clear( a ); clear( b ); clear( d );
		clear( aPtr ); clear( bPtr ); clear( dPtr );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( a, coef, expo );
			inputLinkTerms( aPtr, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\na = ";
		printLinkBasedPoly( aPtr );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerms( b, coef, expo );
			inputLinkTerms( bPtr, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );

		cout << "\nb = ";
		printLinkBasedPoly( bPtr );

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		
		dPtr = addLinkBasedPoly( aPtr, bPtr );
		cout << "\na + b = ";
		printLinkBasedPoly( dPtr );

		cout << "\n";
	}
	return 0;
}
 