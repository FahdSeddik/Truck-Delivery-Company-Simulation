#pragma once


//Priority queue node
template <typename ItemType>
class PQNode {
private:
	ItemType item;
	int priority;
	PQNode<ItemType>* next;
public:
	//Constructor takes item and next pointer
	PQNode<ItemType>(ItemType& ITEM,int PRIO ,PQNode<ItemType>* NEXT = nullptr) {
		item = ITEM;
		next = NEXT;
		priority = PRIO;
	}

	//SETTERS
	void setItem(ItemType& ITEM) {
		item = ITEM;
	}
	void setNext(PQNode<ItemType>* NEXT) {
		next = NEXT;
	}
	void setPrio(int PRIO) {
		priority = PRIO;
	}

	//GETTERS
	ItemType& getItem() {
		return item;
	}
	PQNode<ItemType>* getNext() const {
		return next;
	}
	int getPrio() const {
		return priority;
	}


	~PQNode<ItemType>() {
		next = nullptr;
	}

};