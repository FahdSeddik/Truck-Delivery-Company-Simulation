#pragma once
#include "Node.h"

template <typename ItemType>
class Linked_List {
private:
	Node<ItemType>* Head;
public:
	Linked_List() {
		Head = nullptr;
	}
	~Linked_List() {
		Node<ItemType>* ptr = Head;
		while (ptr) {
			Head = Head->getNext();
			delete ptr;
			ptr= Head;
		}
		Head = nullptr;
	}
	bool add(ItemType& newEntry) {
		Node<ItemType>* ptr = Head;
		Head = new Node<ItemType>(newEntry);
		Head->setNext(ptr);
		return true;
	}
	
	bool GetofIndex(ItemType& Entry,int i) {
		int count = 0;
		if (!Head)
			return false;
		Node<ItemType>* ptr = Head;
		while (ptr) {
			if (count == i) {
				Entry = ptr->getItem();
				return true;
			}
			count++;
			ptr = ptr->getNext();
		}
		return false;
	}

	bool remove(ItemType& Entry) {
		Node<ItemType>* ptr = Head;
		Node<ItemType>* prev = Head;
		if (!Head)
			return false;
		if (Head->getItem() == Entry) {
			Head = Head->getNext();
			delete ptr;
			return true;
		}
		ptr = ptr->getNext();
		while (ptr) {
			if (ptr->getItem() == Entry) {
				prev->setNext(ptr->getNext());
				delete ptr;
				return true;
			}
			prev = ptr;
			ptr = ptr->getNext();
		}
		return false;
	}

};