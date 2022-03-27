#pragma once

//Node class
template <class ItemType>
class Node {
private:
	ItemType item;
	Node<ItemType>* next;
public:
	//Constructor takes item and next pointer
	Node<ItemType>(ItemType& ITEM, Node<ItemType>* NEXT = nullptr) {
		item = ITEM;
		next = NEXT;
	}
	
	//SETTERS
	void setItem(ItemType& ITEM) {
		item = ITEM;
	}
	void setNext(Node<ItemType>* NEXT) {
		next = NEXT;
	}

	//GETTERS
	ItemType& getItem() {
		return item;
	}
	Node<ItemType>* getNext() const {
		return next;
	}

	~Node<ItemType>() {
		next = nullptr;
	}
};