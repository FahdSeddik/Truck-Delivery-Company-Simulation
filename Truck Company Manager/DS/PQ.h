#pragma once
#include "PQNode.h"
#include "QueueADT.h"


template <typename ItemType>
class PQ {
private:
	/*
	Head									
	[ n ] --- > [ n ] ---> [ n ] ---> [ n ] 
		
	*/
	PQNode<ItemType>* Head;
	int size;
public:
	PQ<ItemType>() {
		Head = nullptr;
		size = 0;
	}
	~PQ<ItemType>() {
		ItemType x;
		while (dequeue(x));
		
	}

	//size of queue
	int getSize()const {
		return size;
	}

	bool isEmpty() {
		return Head == nullptr;
	} //if queue is empty

	bool enqueue(const ItemType& newEntry, int prio) {
		
		if (!Head) {
			Head = new PQNode<ItemType>(newEntry, prio);
			Head->setNext(nullptr);
			size++;
			return true;
		}
		PQNode<ItemType>* cur = Head;
		PQNode<ItemType>* prev = Head;

		//if highest prio
		if (Head->getPrio() <= prio) {
			Head = new PQNode<ItemType>(newEntry, prio);
			Head->setNext(cur);
			size++;
			return true;
		}
		
		while (cur) {
			if (cur->getPrio() <= prio) {
				prev->setNext(new PQNode<ItemType>(newEntry, prio));
				prev = prev->getNext();
				prev->setNext(cur);
				size++;
				return true;
			}
			prev = cur;
			cur = cur->getNext();
		}

		//in case lowest prio
		prev->setNext(new PQNode<ItemType>(newEntry, prio));
		prev->getNext()->setNext(nullptr);
		size++;
		return true;
		
	} //add new entry

	bool dequeue(ItemType& Entry) {
		if (!Head)
			return false;
		Entry = Head->getItem();
		PQNode<ItemType>* cur = Head;
		Head = Head->getNext();
		delete cur;
		size--;
		return true;
	} //remove an item

	bool peekFront(ItemType& Entry)const {
		if (!Head)
			return false;
		Entry = Head->getItem();
	} //peek front of queue

};