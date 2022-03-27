#pragma once
#include "BagADT.h"
#include "Node.h"


template <class ItemType>
class LLBag : public BagADT<ItemType> {

	Node<ItemType>* Head; //pointer to head
	int numEntries; //number of contents

public:
	LLBag<ItemType>() {
		Head = nullptr;
		numEntries = 0;
	}
	int GetCurrentSize() const {
		return numEntries;
	} //current number of entries in bag

	bool isEmpty() const {
		return Head == nullptr;
	} //checks if empty

	bool add(const ItemType& newEntry) {
		Head = new Node<ItemType>(newEntry, Head);
		return true;
	} //adds new entry

	bool remove(ItemType& Entry) {
		Node<ItemType>* ptr = Head;
		Node<ItemType>* temp = Head;
		if (!Head)
			return false;
		if (Head->getItem() == Entry) {
			delete Head;
			Head = nullptr;
			return true;
		}
		ptr = ptr->getNext();
		while (ptr) {
			if (ptr->getItem() == Entry) {
				temp->setNext(ptr->getNext());
				delete ptr;
				return true;
			}
			temp = ptr;
			ptr = ptr->getNext();
		}
		return false;
	} //removes specific entry

	void clear() {
		Node<ItemType>* ptr = Head;
		while (Head) {
			Head = Head->getNext();
			delete ptr;
			ptr = Head;
		}
		Head = nullptr;
	} //clears bag

	int getFrequencyOf(const ItemType& Entry)const {
		Node<ItemType>* ptr = Head;
		int count = 0;
		while (ptr) {
			if (ptr->getItem() == Entry)
				count++;
			ptr = ptr->getNext();
		}
		return count;
	} //frequency of entry

	bool contains(const ItemType& Entry) const{
		bool found = false;
		Node<ItemType>* ptr = Head;
		while (ptr) {
			if (ptr->getItem() == Entry) {
				found = true;
				break;
			}
			ptr = ptr->getNext();
		}
		return found;
	} //Tests whether the bag contains a given entry

	~LLBag<ItemType>() {
		clear();
	}
};