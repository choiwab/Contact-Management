#include "myvector.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
#include<cstdlib>

using namespace std;

template <typename T>
MyVector<T>::MyVector(int cap)
{
	data = NULL;
	v_size = 0;
	v_capacity = cap;
	if(cap >0)
	{
		reserve(cap);
	}
}

template <typename T>
MyVector<T>::~MyVector()
{
	return;
	//delete[] data;
}

template <typename T>
void MyVector<T>::push_back(T element)
{
	if(v_size >= v_capacity)
	{
		reserve(max(1, 2*v_capacity));
	}
	data[v_size] = element;
	v_size++;
}

template <typename T>
void MyVector<T>::reserve(int N)
{
	if(v_capacity >= N)
		return;
	
	T* new_vector = new T[N];
	for(int j= 0; j<v_size; j++)
	{
		new_vector[j] = data[j];
	}
	
	if(data == NULL)
	{
		delete[] data;
	}
	data = new_vector;
	v_capacity = N;
}


template <typename T>
void MyVector<T>::insert(int index, T element)
{
	if(v_size >= v_capacity)
	{
		reserve(max(1, 2*v_capacity));
	}
	for(int j = v_size-1; j>= index; j--)
	{
		data[j+1] = data[j];
	}
	data[index] = element;
	v_size++;
}

template <typename T>
void MyVector<T>::erase(int index)
{
	if(index < 0 || index >= v_size)
	{
		throw std::out_of_range("invalid index to erase");
	}

	for(int i = index; i< v_size-1; i++)
	{
		data[i] = data[i+1];
	}
	v_size--;
}

template <typename T>
T& MyVector<T>::at(int index)
{
	if(index < 0 || index >= v_size)
	{
		throw std::out_of_range("invalid index to return");
	}
	return data[index];
}

template <typename T>
const T& MyVector<T>::front()
{
	if(v_size ==0)
	{
		throw std::out_of_range("empty vector");
	}
	return data[0];
}

template <typename T>
const T& MyVector<T>::back()
{
	if(v_size == 0)
	{
		throw std::out_of_range("empty vector");
	}
	return data[v_size-1];
}

template <typename T>
int MyVector<T>::size() const
{
	return v_size;
}

template <typename T>
int MyVector<T>::capacity() const
{
	return v_capacity;
}

template <typename T>
bool MyVector<T>::empty() const
{
	return v_size == 0;
}

template <typename T>
void MyVector<T>::shrink_to_fit() 
{
	if(v_capacity > v_size)
	{
		v_capacity = v_size;
	}
}

template class MyVector<Contact*>;