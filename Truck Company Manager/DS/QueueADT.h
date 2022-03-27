#pragma once

//QUEUE interface
template <class ItemType>
class QueueADT
{
public:
	virtual bool isEmpty() = 0; //if queue is empty
	virtual bool enqueue(ItemType& newEntry) = 0; //add new entry
	virtual bool dequeue(ItemType& Entry) = 0; //remove an item
	virtual bool peekFront(ItemType& Entry)const = 0; //peek front of queue
};

