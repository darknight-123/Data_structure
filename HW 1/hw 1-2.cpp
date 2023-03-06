#include<iostream>
using namespace std;
struct Node{
	int data;
	Node *ptr;
};
typedef struct Node node;
int main()
{
	char n;
	
	node *first,*now,*last,*first1,*delnode;
	first=new node;
	first->ptr=nullptr;
	int count=0,num;
	while(1)
	{
		printf("\nInput or Delete?");
		cin>>n;
		cin>>num;
		first1=first;
		if(n=='I'||n=='i')
		{
			now=new node;
			now->ptr=nullptr;
			if(count==0)
			{
				now->data=num;
				first1->ptr=now;
			}
			else if(count==1)
			{
				last=first1->ptr;
				if(num<last->data)
				{
					now->data=num;
					first1->ptr=now;
					now->ptr=last;
				}
				else
				{
					now->data=num;
					last->ptr=now;
				}
			}
			else
			{
				if(first1->ptr->data>num)
				{
					now->data=num;
					last=first1->ptr;
					first1->ptr=now;
					now->ptr=last;
				}
				else
				{
				while(1)
				{
				first1=first1->ptr;
				last=first1->ptr;
				if(last->ptr==nullptr&&last->data<=num)
				{
					now->data=num;
					last->ptr=now;
					break;
				}
				else if(first1->data<=num&&last->data>=num)
				{
					now->data=num;
					first1->ptr=now;
					now->ptr=last;
					break;
				}
				}
			}
			}
			count++;
		}
		else if(n=='D'||n=='d')
		{
			while (1)
			{
				first1 = first;
				if (first1->ptr == nullptr)
				{
					break;
				}
				int time = 0, k = 0;
				while (1)
				{
					last = first1;
					first1 = first1->ptr;
					if (first1->data == num)
					{
						k = 1;
						if (first1->ptr == nullptr)
						{
							delnode = first1;
							delete delnode;
							last->ptr = nullptr;
						}
						else
						{
							last->ptr = first1->ptr;
							delnode = first1;
							delete delnode;
						}
						time++;
						break;
					}
					if (k == 0 && first1->ptr == nullptr)
					{
						//printf("no this number\n");
						break;
					}
				}
				if (time == 0)
				{
					break;
				}
				count--;
			}
		}
		first1=first;
		while(1)
		{
			if(first1->ptr==nullptr)
			{
				break;
			}
			printf("%d ",first1->ptr->data);
			first1=first1->ptr;
		}
	}
	system("pause");
	return 0;
}
