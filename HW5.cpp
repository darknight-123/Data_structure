// HW5.cpp : 定義主控台應用程式的進入點。
//


#include <iostream>
//#include<math.h>
using namespace std;

#define MAX_TERMS 10 /*size of terms array*/

class PolynomialTerm { 
public:                          
	int coef;
	int expo;
};                                                                          /////
                                                                         
class ArrayPolynomial {                                        /////
public:                                                                  /////
	PolynomialTerm terms[MAX_TERMS]; /////

	void clear() /////
	{
		for (int i = 0; i < MAX_TERMS; i++) {
			terms[i].coef = 0;
			terms[i].expo = 0;
		}
		return;
	}

	void inputTerms(int coef, int expo) /////
	{
		
			if (terms[0].coef == 0)
			{
				terms[0].coef = coef;
				terms[0].expo = expo;
			}
			else
			{
				for (int i = 0;i < MAX_TERMS;i++)
				{
					if (expo == terms[i].expo)
					{
						terms[i].coef = coef;
						if (coef == 0)
						{
							for (int k = i;k < MAX_TERMS - 1;k++)
							{
								terms[k] = terms[k + 1];
							}
						}
						break;
					}
					else if (terms[i].expo < expo&& coef != 0)
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
			}
		// add your code here

		return;
	}

	void addArrayBasedPoly(ArrayPolynomial &a, ArrayPolynomial &b) /////
	{
		int count_a = 0, count_b = 0,i=0;
		while(1)
		{
			if (a.terms[count_a].expo == b.terms[count_b].expo)
			{
				if ((b.terms[count_b].coef + a.terms[count_a].coef) != 0)
				{
					terms[i].coef = a.terms[count_a].coef;
					terms[i].coef += b.terms[count_b].coef;
					terms[i].expo = b.terms[count_b].expo;
					i++;
				}
				count_a++;
				count_b++;
			}
			else if (a.terms[count_a].expo > b.terms[count_b].expo)
			{
				terms[i] = a.terms[count_a];
				count_a++;
				i++;
			}
			else if (a.terms[count_a].expo < b.terms[count_b].expo)
			{
				terms[i] = b.terms[count_b];
				count_b++;
				i++;
			}
			if (a.terms[count_a].coef==0&&b.terms[count_b].coef==0)
			{
				break;
			}
		}
		// add your code here

		return;
	}

	void reverseArrayBasedPoly() /////
	{
		int k = 0;
		ArrayPolynomial c;
		for (int i = 0;i < MAX_TERMS;i++)
		{
			if (terms[i].coef != 0)
			{
				k++;
			}
		}
		for (int i = 0;i < k/2;i++)
		{
			c.terms[0] = terms[i];
			terms[i] = terms[k-i-1];
			terms[k-i-1] = c.terms[0];
		}
		// add your code here
		
		return;
	}

	void printArrayBasedPoly() /////
	{
		if (terms[0].coef == 0)
			return;

		if (terms[0].expo == 0)
			std::cout << terms[0].coef;
		else
			std::cout << terms[0].coef << "X^" << terms[0].expo;

		for (int i = 1; i < MAX_TERMS; i++) {
			if (terms[i].coef == 0)
				return;

			if (terms[i].expo == 0)
				std::cout << " + " << terms[i].coef;
			else
				std::cout << " + " << terms[i].coef << "X^" << terms[i].expo;
		}

		return;
	}

	int compute(int x) 
	{                          

		int total = 0;
		for (int i = 0;i < MAX_TERMS;i++)
		{
			total += pow(x,terms[i].expo)*terms[i].coef;
			if (terms[i].coef == 0)
			{
				break;
			}
		}

		// add your code here
	

		return total;    
	}                           
};                                                                

class LinkedPolynomialTerm {                       
public:                                                          
	int coef;
	int expo;
	LinkedPolynomialTerm *nextTermPtr; /////
};                                                                  /////

class LinkPolynomial {                                /////
public:                                                          /////
	LinkedPolynomialTerm *polynomialTermPtr = nullptr; /////

	void clear() /////
	{
		LinkedPolynomialTerm *tmpPtr;                       

		while (polynomialTermPtr != nullptr) {
			tmpPtr = polynomialTermPtr;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
			delete tmpPtr;
		}

		return;
	}

	void inputLinkTerms(int coef, int expo) /////
	{
		LinkedPolynomialTerm *tmpPtr,*now,*last;                                                 

		tmpPtr = new LinkedPolynomialTerm;                                        
		tmpPtr->coef = coef;
		tmpPtr->expo = expo;
		tmpPtr->nextTermPtr = nullptr;
		last = nullptr;
		now = polynomialTermPtr;
		//6 8 5 4 1 0 0 2 0 0
		if (polynomialTermPtr == nullptr&&tmpPtr->coef!=0)
		{
			polynomialTermPtr = tmpPtr;
			now = polynomialTermPtr;
		}
		else if(polynomialTermPtr!=nullptr)
		{
			while (now!=nullptr)
			{
				if (polynomialTermPtr->expo < tmpPtr->expo&&tmpPtr->coef!=0)
				{
					tmpPtr->nextTermPtr = polynomialTermPtr;
					polynomialTermPtr = tmpPtr;
					break;
				}
				else if (polynomialTermPtr->expo == tmpPtr->expo && tmpPtr->coef == 0)
				{
					polynomialTermPtr = polynomialTermPtr->nextTermPtr;
				
					break;
				}
				else if (now->expo == tmpPtr->expo)
				{
					if (tmpPtr->coef != 0)
					{
						now->coef = tmpPtr->coef;
					}
					else
					{
						last = now->nextTermPtr;
					}
					break;
				}
				else if (tmpPtr->expo > now->expo&&tmpPtr->coef!=0)
				{
					tmpPtr->nextTermPtr = now;
					last->nextTermPtr= tmpPtr;
					break;
				}
				else if (now->nextTermPtr == nullptr&&tmpPtr->coef!=0)
				{
					now->nextTermPtr = tmpPtr;
					break;
				}
					last = now;
					now = now->nextTermPtr;
			}
		}
		// add your code here 


		return;
	}

	void addLinkBasedPoly(LinkPolynomial &aPol, LinkPolynomial &bPol) /////
	{
                         /////
		LinkedPolynomialTerm* now,*k;
		now = polynomialTermPtr;
		while (1)
		{
			int p = 0;
			if (aPol.polynomialTermPtr == nullptr || bPol.polynomialTermPtr == nullptr)
			{
				break;
			}
			LinkedPolynomialTerm* k = new LinkedPolynomialTerm;
			k->nextTermPtr = nullptr;
			if (aPol.polynomialTermPtr->expo == bPol.polynomialTermPtr->expo)
			{
				if ((aPol.polynomialTermPtr->coef + bPol.polynomialTermPtr->coef) != 0)
				{
					k->coef= aPol.polynomialTermPtr->coef+bPol.polynomialTermPtr->coef;
					k->expo = aPol.polynomialTermPtr->expo;
					p = 1;
				}
				aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
				bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
			}
			else if (aPol.polynomialTermPtr->expo > bPol.polynomialTermPtr->expo)
			{
				k->coef = aPol.polynomialTermPtr->coef;
				k->expo = aPol.polynomialTermPtr->expo;
				aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
				p = 1;
			}
			else if (aPol.polynomialTermPtr->expo < bPol.polynomialTermPtr->expo)
			{
				k->coef = bPol.polynomialTermPtr->coef;
				k->expo = bPol.polynomialTermPtr->expo;
				bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
				p = 1;
			}
			if (polynomialTermPtr == nullptr&&p==1)
			{
				polynomialTermPtr = k;
				now = polynomialTermPtr;
			}
			else if(p==1)
			{
				now->nextTermPtr = k;
				now = k;
			}
		}
		if (aPol.polynomialTermPtr == nullptr && bPol.polynomialTermPtr != nullptr)
		{
			while (bPol.polynomialTermPtr != nullptr)
			{
				LinkedPolynomialTerm* k = new LinkedPolynomialTerm;
				k->nextTermPtr = nullptr;
				k->coef = bPol.polynomialTermPtr->coef;
				k->expo = bPol.polynomialTermPtr->expo;
				if (polynomialTermPtr == nullptr)
				{
					polynomialTermPtr = k;
				}
				else
				{
					now->nextTermPtr = k;
					
				}
				now = k;
				bPol.polynomialTermPtr = bPol.polynomialTermPtr->nextTermPtr;
			}
		}
		else if (aPol.polynomialTermPtr != nullptr && bPol.polynomialTermPtr == nullptr)
		{
			while (aPol.polynomialTermPtr != nullptr)
			{
				LinkedPolynomialTerm* k = new LinkedPolynomialTerm;
				k->nextTermPtr = nullptr;
				k->coef = aPol.polynomialTermPtr->coef;
				k->expo = aPol.polynomialTermPtr->expo;
				if (polynomialTermPtr == nullptr)
				{
					polynomialTermPtr = k;
				}
				else
				{
					now->nextTermPtr = k;

				}
				now = k;
				aPol.polynomialTermPtr = aPol.polynomialTermPtr->nextTermPtr;
			}
		}
		// add your code here


		return;
	}

	void reverseLinkBasedPoly() /////
	{
		/////
		LinkedPolynomialTerm* change, * now;
		LinkedPolynomialTerm* n = new LinkedPolynomialTerm;
		now = polynomialTermPtr;
		change = polynomialTermPtr;
		int h = 0;
		/*while (1)
		{
			if (now == nullptr)
			{
				break;
			}
			h ++;
			now = now->nextTermPtr;
		}
		now = polynomialTermPtr;
		for (int i = 0;i < h / 2;i++)
		{
			change = polynomialTermPtr;
			for (int k = 0;k < h- i - 1;k++)
			{
				change = change->nextTermPtr;
			}

			n->coef = change->coef;
			n->expo = change->expo;
			change->coef = now->coef;
			change->expo = now->expo;
			now->coef = n->coef;
			now->expo = n->expo;
			now = now->nextTermPtr;
		}*/
		/*int count = 0;*/
		while (polynomialTermPtr != nullptr)
		{
			if (polynomialTermPtr->nextTermPtr == nullptr)
			{
				break;
			}
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		}
		/*for (int i = 0;i < count;i++)*/
		while(now!=polynomialTermPtr)
		{
			now = now->nextTermPtr;
			if (polynomialTermPtr->nextTermPtr == nullptr)
			{
				polynomialTermPtr->nextTermPtr = change;
				change->nextTermPtr = nullptr;
			}
			else
			{
				change->nextTermPtr = polynomialTermPtr->nextTermPtr;
				polynomialTermPtr->nextTermPtr = change;
			}
			change = now;
		}
		// add your code here


		return;
	}

	void printLinkBasedPoly()                                                            /////
	{
		LinkedPolynomialTerm *termPtr = polynomialTermPtr; /////

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

	int compute(int x) 	
	{
		int total = 0;
		while (polynomialTermPtr != nullptr)
		{
			total += pow(x, polynomialTermPtr->expo) * polynomialTermPtr->coef;
			polynomialTermPtr = polynomialTermPtr->nextTermPtr;
		}
		// add your code here


		return total;
	}
}; 

int main()
{
	ArrayPolynomial a, b, d;                                                              /////
	LinkPolynomial aPol, bPol, dPol;                                             /////

	int coef, expo, x;

          // aPtr = bPtr = dPtr = nullptr; /////

	while (1) {
		a.clear(); b.clear(); d.clear();                                    /////
                      // aPtr->clear(aPtr); bPtr->clear(bPtr); dPtr->clear(dPtr); /////


		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			a.inputTerms(coef, expo);             /////
			aPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\na = ";
		a.printArrayBasedPoly();     /////
		cout << "\na = ";
		aPol.printLinkBasedPoly(); /////
		cout << "\n";

		for (int i = 0; i < MAX_TERMS; i++) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if (expo == 0 && coef == 0)
				break;

			b.inputTerms(coef, expo);             /////
			bPol.inputLinkTerms(coef, expo); /////
		}

		cout << "\n\nb = ";
		b.printArrayBasedPoly();      /////

		cout << "\nb = ";
		bPol.printLinkBasedPoly(); /////

		cout << "\n";

		// d =a + b, where a, b, and d are polynomials

		d.addArrayBasedPoly(a, b); /////
		cout << "\na + b = ";
		d.printArrayBasedPoly();     /////

		dPol.addLinkBasedPoly(aPol, bPol); /////
		cout << "\na + b = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		d.reverseArrayBasedPoly(); /////
		cout << "\nreversed d = ";
		d.printArrayBasedPoly();     /////
		
		dPol.reverseLinkBasedPoly(); /////
		cout << "\nreversed d = ";
		dPol.printLinkBasedPoly();               /////

		cout << "\n";

		cout << "\ninput X: ";
		cin >> x;

		cout << "\nd = ";
		cout << d.compute(x);      //////

		cout << "\nd = ";
		cout << dPol.compute(x); //////

		cout << "\n";

		aPol.clear(); bPol.clear(); dPol.clear(); /////
	}

	return 0;
}
