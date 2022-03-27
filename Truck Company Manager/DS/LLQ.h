#pragma once
#include "Node.h"
#include "QueueADT.h"


template <class ItemType>
class LLQ : public QueueADT<ItemType> {
private:
	/*
										tail
	[ n ] --- > [ n ] ---> [ n ] ---> [ n ] ---|
		<-----------------------<-------<------|
	*/
	Node<ItemType>* Tail;
	int size;
public:
	LLQ<ItemType>() {
		Tail = nullptr;
		size = 0;
	}

	//size of queue
	int getSize()const {
		return size;
	}

	bool isEmpty() {
		return Tail == nullptr;
	} //if queue is empty

	bool enqueue(ItemType& newEntry) {
		if (!Tail) { 
			Tail = new Node<ItemType>(newEntry);
			//if first item make tail point to itself
			Tail->setNext(Tail);
			size++;
			return true;
		}
		Node<ItemType>* ptr = Tail->getNext();
		Tail->setNext(new Node<ItemType>(newEntry));
		Tail = Tail->getNext();
		Tail->setNext(ptr);
		size++;
		return true;
		
	} //add new entry

	bool dequeue(ItemType& Entry) {
		if (!Tail)
			return false; //empty q
		//Tail only
		if (Tail->getNext() == Tail) { 
			Entry = Tail->getItem();
			delete Tail;
			Tail = nullptr;
			size--;
			return true;
		}
		Node<ItemType>* ptr = Tail->getNext();
		Tail->setNext(ptr->getNext());
		Entry = ptr->getItem();
		delete ptr;
		size--;
		return true;
	} //remove an item

	

	bool peekFront(ItemType& Entry)const {
		if (!Tail)
			return false;
		Node<ItemType>* ptr = Tail->getNext();
		Entry = ptr->getItem();
		return true;
	}//peek front of queue
};