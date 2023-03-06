 //  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

/** @file  HashedDictionary.cpp */

// Separate chaining resolves collisions

// PARTIALLY COMPLETE
#include <string>
#include "HashedEntry.h"

template<class KeyType, class ItemType>
class HashedDictionary 
{
private:
	HashedEntry<KeyType, ItemType> ** hashTable;
	static const int DEFAULT_SIZE = 1;
	HashedEntry<KeyType, ItemType>* nextPtr;
	int hashTableSize;
   
public:
   HashedDictionary();
   HashedDictionary(int size);
   void add(const KeyType& searchKey, const ItemType& newItem);
   bool remove(const KeyType& searchKey);
   HashedEntry<KeyType, ItemType>* getEntry(const KeyType& searchKey);
   void traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const;
   void clear();
   bool isEmpty();
   int getTableSize();

protected:
	int getHashIndex(const KeyType& searchKey);
}; // end HashedDictionary

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary()
{
	hashTableSize = DEFAULT_SIZE;
	hashTable = new HashedEntry<KeyType, ItemType>*[hashTableSize];
	
	for ( int i = 0; i < hashTableSize; i++ )
		hashTable[ i ] = nullptr;
}

template <class KeyType, class ItemType>
HashedDictionary<KeyType, ItemType>::HashedDictionary(int size)
{
	hashTableSize = size;
	hashTable = new HashedEntry<KeyType, ItemType>*[hashTableSize];

	for ( int i = 0; i < hashTableSize; i++ )
		hashTable[ i ] = nullptr;
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::traverse(int itemHashIndex, void visit(HashedEntry<KeyType, ItemType>&)) const
{
	HashedEntry<KeyType, ItemType> *itemPtr = hashTable[ itemHashIndex ];

	while ( itemPtr != nullptr ) {
		visit( *itemPtr );
		itemPtr = itemPtr->getNext();
	}
}

template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::clear()
{
	HashedEntry<KeyType, ItemType> *nextPtr, *curPtr;

   for ( int i = 0; i < hashTableSize; i++ ) {
	   curPtr = hashTable[ i ];

	   while (curPtr != nullptr) {
		   nextPtr = curPtr->getNext();
           delete curPtr;
		   curPtr = nextPtr;
	   } // end while

	   hashTable[ i ] = nullptr;
   } // end if
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getTableSize()
{
	return hashTableSize ;
}

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::isEmpty()
{
	for (int i = 0; i < hashTableSize; i++) {
		if ( hashTable[i] != nullptr )
			return false;
	}

	return true;
}

template <class KeyType, class ItemType>
int HashedDictionary<KeyType, ItemType>::getHashIndex(const KeyType& searchKey)
{
	int strLen =  searchKey.length();

	if ( strLen == 0 )
		return 0;

	return  ( (unsigned char) searchKey[0] ) % hashTableSize;
}


template <class KeyType, class ItemType>
void HashedDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	HashedEntry<string, string>* itemPtr = getEntry(searchKey);
	int num = getHashIndex(searchKey);
	
	HashedEntry<KeyType, ItemType>* newnode = new HashedEntry<KeyType, ItemType>(searchKey, newItem);
	newnode->setNext(nullptr);
	HashedEntry<KeyType, ItemType>* item = hashTable[num];
	int size = 0;
	// Compute the hashed index into the array
	if (itemPtr == nullptr)
	{
		if (hashTable[num] == nullptr)
		{
			hashTable[num] = newnode;
			
		}
		else
		{
			newnode->setNext(hashTable[num]);
			hashTable[num] = newnode;
		}
	}
	else
	{
		while (1)
		{
			if (item->getKey() == searchKey)
			{
				item->countUp();
				break;
			}
			item = itemPtr->getNext();
		}
	}
	HashedEntry<KeyType, ItemType>* headPtr = hashTable[num];
	while (headPtr!=nullptr)
	{
		size++;
		headPtr = headPtr->getNext();
	}
	HashedEntry<KeyType, ItemType>* prevPtr = hashTable[num];
	// add your code here
	/*for (int i = 0; i < size - 1; i++)
	{
		HashedEntry<KeyType, ItemType>* curPtr = prevPtr->getNext();
		for (int k = 0; k < size-1; k++)
		{

			if ((curPtr->getKey().size() > prevPtr->getKey().size()) || (curPtr->getCount() > prevPtr->getCount()) || (curPtr->getItem() > prevPtr->getItem()))
			{
				HashedEntry<KeyType, ItemType>*temp=prevPtr;
				prevPtr = curPtr;
				curPtr = temp;
			}
			curPtr = curPtr->getNext();
		}
		prevPtr = prevPtr->getNext();
	}*/

} // end add

template <class KeyType, class ItemType>
bool HashedDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
	bool itemFound = false;
	HashedEntry<string, string>* itemPtr = getEntry(searchKey);
	// Compute the hashed index into the array
	int num = getHashIndex(searchKey);
	HashedEntry<KeyType, ItemType>* curPtr = hashTable[num]->getNext();
	HashedEntry<KeyType, ItemType>* prevPtr = hashTable[num];
	if (itemPtr != nullptr)
	{
		if (hashTable[num]->getKey() == searchKey)
		{
			itemFound = true;
			if (hashTable[num]->getCount() > 1)
			{
				hashTable[num]->countDown();
			}
			else
			{
				hashTable[num] = hashTable[num]->getNext();
			}
		}
		else
		{
			while (1)
			{
				if (curPtr->getKey() == searchKey)
				{
					if (curPtr->getCount() > 1)
					{
						curPtr->countDown();
					}
					else
					{
						prevPtr->setNext(curPtr->getNext());
					}
					itemFound = true;
					break;
				}
			}
		}
	}
	// add yor code here


	return itemFound;
} // end remove

template <class KeyType, class ItemType>
HashedEntry<KeyType, ItemType>* HashedDictionary<KeyType, ItemType>::getEntry(const KeyType& searchKey)
{
	bool itemFound = false;
	// Compute the hashed index into the array
	int num = getHashIndex(searchKey);
	HashedEntry<KeyType, ItemType>* itemPtr = hashTable[num];
	while (itemPtr != nullptr)
	{
		if (itemPtr->getKey() == searchKey)
		{
			itemFound = true;
			return itemPtr;
		}
		itemPtr=itemPtr->getNext();
	}
	// add your code here


	return nullptr;
}

