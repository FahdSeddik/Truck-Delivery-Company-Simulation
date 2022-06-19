#pragma once
#include <iostream>
using namespace std;
template <typename T>
class MaxHeap {
private:
	/*
		[0][1][2][3][4][5][6][7][8][9]
		15  10 8
	*/
	T* Arr;
	int free;
	int CurrCap;

	//******************
	//---==Utility==---*
	//******************
	void Swap(int i1, int i2) {
		T temp = Arr[i1];
		Arr[i1] = Arr[i2];
		Arr[i2] = temp;
	}
	int MaxIndex(int i1, int i2)const {
		if (*Arr[i1] > *Arr[i2])return i1;
		else return i2;
	}
	void reheapUp(int index) {
		int parent = (index - 1) / 2;
		if (parent < 0)return;
		if (*Arr[parent] < *Arr[index]) {
			Swap(parent, index);
			reheapUp(parent);
		}
	}
	void reheapDown(int index) {
		int child1 = (index * 2) + 1;
		int child2 = (index * 2) + 2;
		if (child1 >= free || child2 >= free)
			return;
		int max = MaxIndex(child1, child2);
		if (*Arr[max] > *Arr[index]) {
			Swap(max, index);
			reheapDown(max);
		}
	}
public:
	MaxHeap() {
		CurrCap = 1;
		Arr = new T[CurrCap];
		free = 0;
	}
	void Insert(T i) {
		if (free == CurrCap) {
			CurrCap *= 2;
			T* tArr = new T[CurrCap];
			for (int i = 0; i < CurrCap/2; i++)
				tArr[i] = Arr[i];
			delete[] Arr;
			Arr = tArr;
		}
		Arr[free] = i;
		reheapUp(free++);
	}
	bool ExtractMax(T& max) {
		if (free == 0)return false;
		max = Arr[0];
		Arr[0] = Arr[--free];
		reheapDown(0);
		return true;
	}
	bool isEmpty()const {
		return free == 0;
	}
	~MaxHeap() {
		delete[] Arr;
	}
	int getSize()const {
		return free==0? 0:free-1;
	}
	void print()const {
		for (int i = 0; i < free; i++)
		{
			if (i == free - 1) {
				cout << *Arr[i];
				break;
			}
			cout << *Arr[i] << ", ";
		}
	}
};