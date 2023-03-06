// HW3.cpp : 定義主控台應用程式的進入點。
#include <iostream>
using namespace std;

#define MAX_TERMS 10

typedef struct{
	int coef;
	int expo;
} polynomialTerm;

void clear(polynomialTerm t[]) 
{
	for ( int i = 0; i < MAX_TERMS; i++ ) {
		t[i].coef = 0;
		t[i].expo = 0;
	}

	return;
}

void printArrayBasedPoly(polynomialTerm t[])
{
	if ( t[0].coef == 0 ) 
		return;

	if ( t[0].expo == 0 )
		cout << t[0].coef;
	else
		cout << t[0].coef << "X^" << t[0].expo;

	for ( int i = 1; i < MAX_TERMS; i++ ) {
		if ( t[i].coef == 0 ) 
			return;

		if ( t[i].expo == 0 )
			cout << " + " << t[i].coef;
		else
			cout << " + "<< t[i].coef  << "X^" << t[i].expo;
	}
}

void inputTerm(polynomialTerm t[], int coef, int expo)
{
	int i ;
		for (i = 0;i < MAX_TERMS;i++)
		{
			if (t[i].expo == expo)
			{
				t[i].coef = coef;
				break;
			}
			else if (expo > t[i].expo)
			{
				for (int k = MAX_TERMS - 1;k >= i + 1;k--)
				{
					t[k] = t[k - 1];
				}
				t[i].coef = coef;
				t[i].expo = expo;
				i--;
				break;
			}
			else if (expo == 0&&t[i].expo==0)
			{
				t[i].coef = coef;
			}
		}
		for (int i = 0;i < MAX_TERMS;i++)
		{
			int h;
			if (t[i].coef == 0)
			{
				for (h = i;h < MAX_TERMS - 1;h++)
				{
					t[h] = t[h + 1];
				}
			}
		}
	// add your code here
}

void addArrayBasedPoly(polynomialTerm a[], polynomialTerm b[], polynomialTerm d[])
{
	int k = 0, o = 0,h;

	for (int i = 0;i < MAX_TERMS;i++)
	{
		
			if (a[k].expo == b[o].expo)
			{
				d[i] = a[k];
				d[i].coef =d[i].coef+b[o].coef;
			//	printf("%d", d[i].coef);
				k++;
				o++;
			
			}
			else if(a[k].expo>b[o].expo)
			{
				d[i] = a[k];
			//	printf("%d", d[i].coef);
				k++;
				
			}
			else if (a[k].expo < b[o].expo)
			{
				d[i] = b[o];
			//	printf("%d", d[i].coef);
				o++;
			}
			if (d[i-1].coef == 0&&i!=0)
			{
				for ( h = i;h<MAX_TERMS;h++)
				{
					d[h-1]= d[h];
				}
				d[h].expo = 0;
				d[h].coef = 0;
				i--;
			}
			if (a[k].coef == 0 && b[o].coef==0)
			{
				break;
			}
	}

	// add your code here


	return;
}

int main(int argc)
{
	polynomialTerm a[MAX_TERMS], b[MAX_TERMS], d[MAX_TERMS];
	int coef, expo;

	while (1) {
		clear( a ); clear( b ); clear( d );

		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput a's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( a, coef, expo );
		}

		cout << "\n\na = ";
		printArrayBasedPoly( a );
		cout << "\n";
		
		for ( int i = 0; i < MAX_TERMS; i++ ) {
			cout << "\ninput b's coefficient and exponent: ";
			cin >> coef >> expo;

			if ( expo == 0 && coef == 0 )
				break;

			inputTerm( b, coef, expo );
		}

		cout << "\n\nb = ";
		printArrayBasedPoly( b );
		cout << "\n";
//	printf("%d\n",d[0].expo);
		// d =a + b, where a, b, and d are polynomials
		addArrayBasedPoly( a, b, d );
		cout << "\na + b = ";
		printArrayBasedPoly( d );
		cout << "\n";
	}

	return 0;
}
