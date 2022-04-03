#pragma once

//Bag Interface
template <class ItemType>
class BagADT {
public:
	virtual int GetCurrentSize() const = 0; //current number of entries in bag
	virtual bool isEmpty() const = 0; //checks if empty
	virtual bool add( ItemType& newEntry) = 0; //adds new entry
	virtual bool remove(ItemType& Entry) = 0; //removes specific entry
	virtual void clear() = 0; //clears bag
	virtual int getFrequencyOf(const ItemType& Entry)const = 0; //frequency of entry
	virtual bool contains(const ItemType& Entry) const= 0; //Tests whether the bag contains a given entry
};
