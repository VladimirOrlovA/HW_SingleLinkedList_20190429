#pragma once
#include<iostream>
using namespace std;

// ������� ������� ���������� ������ � ����� ���������� ��������
template<class T>
class elem
{
public:
	T obj;
	elem<T>*next = nullptr;
};

// ������� ����
template<class T>
class SingleLinkedList
{
	elem<T>*head = nullptr;
	int size_ = 0;
public:
	SingleLinkedList();
	// �������� ������ � �����
	void push_back(const T & obj);
	// �������� ������ � ������
	void push_front(const T & obj);
	// ������� ������ � �����
	void pop_back();
	// ������� ������ � ������
	void pop_front();
	// �������� ������ � �������� �������
	void insert(int pos, const T & obj);
	// �������� ������ �� �������� �������
	T & getElement(int pos);
	// ������� ������ �� �������� �������
	void removeAt(int pos);
	// �������� ������ ������
	int getSize() const;
	// ��������
	void clear();
	// ���������� ������
	SingleLinkedList(const SingleLinkedList & SLL);
	// ���������� ������ �� r-value ������
	SingleLinkedList(SingleLinkedList && SLL);
	// ���������� ���������� =
	SingleLinkedList<T> & operator=(const SingleLinkedList<T> & SLL);
	// ���������� ��������� = �� r-value ������
	SingleLinkedList<T> & operator=(SingleLinkedList<T> && SLL);
	T& operator[](const int index);

	~SingleLinkedList();

	template<class T>
	friend ostream& operator<<(ostream&os, SingleLinkedList<T>& SLL);
};

// ����������� �� ���������
template<class T>
inline SingleLinkedList<T>::SingleLinkedList()
{
	size_ = 0;
	head = nullptr;
}

template<class T>
inline void SingleLinkedList<T>::push_back(const T & obj)
{
	// ������� ��������� �� ����� ������� ������ � �������� ��� ���� ������
	elem<T> *nElem = new elem<T>;
	// ��������� ������� �������� ����������� ��������� ������� 
	nElem->obj = obj;
	// ��������� ���� �� ������ � ������, ���� ��� �� ����������� ��������� ������ ��������� ������� �������� ������
	if (this->head == nullptr)
	{
		this->head = nElem;
		this->size_ = 1;
		return;
	}
	// ���� ������ ����, �� ������� �������� ��������� �������� ��������, �.�. ��� ������ (������ ���������� � ������, ��������� � ������)
	elem<T> *curElem = head;
	// ��������� ���� �� � �������� �������� ��������� �� ��������� �������
	while (curElem->next != nullptr) // ���� ���� ������� � ���� ����� ������ �� ���������� ��������
		curElem = curElem->next;
	curElem->next = nElem;	// � ������� �������� ����������� ��������� �� ����������� �������
	nElem->next = nullptr;	// ��������� � ����������� (���������) �������� ����� �� ���� ������� ������ 0, ����� ���������� ��� ��� �����
	size_++; // ����������� ������ ������ �� 1 �������
}

template<class T>
inline void SingleLinkedList<T>::push_front(const T & obj)
{
	// ������� ��������� �� ����� ������� ������ � �������� ��� ���� ������
	elem<T> *nElem = new elem<T>;
	// ��������� ������� �������� ����������� ��������� ������� 
	nElem->obj = obj;
	// ������� ��������� ��������� ��� �������� ��������, �.�. ��� ������ ������
	elem<T> *curElem = head;
	// ������ ������ ����������� ����� ������ ��������, �.�. ����� ������� ���������� ������� ������
	head = nElem;
	// ���������� ��������� ������ ������������ �������� (�������� ������� ������) ����� ���������� �������� (����� ������ ������)
	nElem->next = curElem;
	// ����������� ������ ������ �� 1
	size_++;
}

template<class T>
inline void SingleLinkedList<T>::pop_back()
{
	// ��������� ���� �� ������ � ������, ���� ���, �� ������� ������, ������� ����� return
	if (head == nullptr)
		return;
	// ������� ��������� ��������� �������� �������� ������, �.�. ��� ������ ������ 
	elem<T> *curElem = head;
	// ���� ������ �� ����� ��������, �� ������� ������ � �������
	if (size_ == 1)
	{
		head = nullptr;
		size_ = 0;
		return;
	}
	// ��������� ������ ���� ���� �� ����� �� ���������� ��������
	for (size_t i = 0; i < size_ - 2; i++)
	{
		curElem = curElem->next; // ��������� �� ��������� ������� ������� 
	} // ������� �� ����� �� ������ �������������� ��������
	// ������� ��������� �� ����� ���������� ��������
	delete curElem->next;
	// � ��������� �������������� �������� ������� ��������� ���������� ��������� �� ���� ������ 0
	curElem->next = nullptr;
	// ��������� ������ ����� �� 1
	size_--;
}

template<class T>
inline void SingleLinkedList<T>::pop_front()
{
	// ������� ��������� ��������� �������� �������� ������
	elem<T> *curElem = head;
	// ��������� � ������ ����� ���������� �������� ������� ���� �������
	head = head->next;
	// ��������� ������ ����� �� 1
	size_--;
}

template<class T>
inline void SingleLinkedList<T>::insert(int pos, const T & obj)
{
	// ������� ��������� �� ����� ������� �����
	elem<T> *nElem = new elem<T>;
	// � ����� ������� �������� ���������� ����� ������� 
	nElem->obj = obj;
	// ������� ��������� ��������� � ���������� � ���� ����� ������
	elem<T> *curElem = head;
	// ���� ������� ������� ������ 0 ��� ������ ������� �����, �� �������
	if (pos < 0 || pos > size_)
	{
		cout << "Error - Position out of range\n";
		return;
	}
	// ���� ������� ����� ����, �� ��������� ����� ������� � ������ ������� � �������� � ��� ������
	if (pos == 0)
	{
		push_front(obj);
		return;
	}
	// ���� ������� ����� ������� �����, �� ��������� ����� ������� ����� ��������� ������� � �������� � ��� ������
	if (pos == size_)
	{
		push_back(obj);
		return;
	}
	// ���� ������� ���-�� � ��������� ����� �� 0 �� size_ ���� ������ �� ������� ������� �� �������� ������� 
	for (size_t i = 0; i < pos - 1; i++)
	{
		curElem = curElem->next;
	}
	nElem->next = curElem->next;
	curElem->next = nElem;
	size_++;
}

template<class T>
inline T & SingleLinkedList<T>::getElement(int pos)
{
	elem<T> *curElem = head;
	int counter = 0;
	while (curElem != nullptr)
	{
		if (pos == counter)
		{
			return curElem->obj;
		}
		curElem = curElem->next;
		counter++;
	}
}

template<class T>
inline void SingleLinkedList<T>::removeAt(int pos)
{
	if (pos == 0)
	{
		pop_front();
		return;
	}
	
	if (pos < 0 || pos > size_)
	{
		cout << "Error - Position out of range\n";
		return;
	}
	elem<T> *curElem = head;
	for (size_t i = 0; i < pos - 1; i++)
	{
		curElem = curElem->next;
	}
	// -----------------------------------------------------------------
	// ������� ��������� ��������� �� ��������� �������
	elem<T> *delElem = curElem->next;
	// ��������� ������� ������� 
	curElem->next = delElem->next;
	// ������� ��������� �� ��������� �������
	delete delElem;
	size_--;
}

template<class T>
inline int SingleLinkedList<T>::getSize() const
{
	return size_;
}

template<class T>
inline void SingleLinkedList<T>::clear()
{
	// ��������� �� ����� �� ���������� �������� ����� �� ��������
	while (size_)
		pop_front(); // size_ ����������� �� ���� �������� ��������� ����� �� ����� � ������
}

template<class T>
inline SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> & SLL)
{
	this->size_ = SLL.size_;
	// ��������� ���������� ���� �� ����������, ���� ����� �������
	if (SLL.head == nullptr)
	{
		this->head = nullptr;
		this->size_ = 0;
		return;
	}
	// �������� ������ ��� �������� �������
	this->head = new elem<T>;
	// �������� �������� ������� ��������� � ����
	this->head = SLL.head;
	// ������� ��������� ��������� 
	elem<T> *curElem = this->head;
	elem<T> *curElemSLL = SLL.head;
	for (size_t i = 0; i < SLL.getSize() - 1; i++)
	{
		curElem->obj = curElemSLL->obj;
		curElem->next = curElemSLL->next;
		curElem = curElem->next;
		curElemSLL = curElemSLL->next;
	}
}

template<class T>
inline SingleLinkedList<T>::SingleLinkedList(SingleLinkedList<T> && SLL)
{
	this->head = nullptr;
	this->size_ = 0;
	swap(this->head, SLL.head);
	swap(this->size_, SLL.size_);
}

template<class T>
inline SingleLinkedList<T> & SingleLinkedList<T>::operator=(const SingleLinkedList<T> & SLL)
{
	if (this == &SLL)
		return*this;
	this->clear();
	this->size_ = SLL.size_;
	if (SLL.head == nullptr)
	{
		this->head = nullptr;
		return *this;
	}
	this->head = new elem<T>;
	this->head = SLL.head;
	elem<T> *curElem = this->head;
	elem<T> *curElemSLL = SLL.head;
	for (size_t i = 0; i < SLL.getSize() - 1; i++)
	{
		curElem->obj = curElemSLL->obj;
		curElem->next = curElemSLL->next;
		curElem = curElem->next;
		curElemSLL = curElemSLL->next;
	}
	return *this;
}

template<class T>
inline SingleLinkedList<T> & SingleLinkedList<T>::operator=(SingleLinkedList<T> && SLL)
{
	this->clear();
	swap(this->head, SLL.head);
	swap(this->size_, SLL.size_);
	return *this;
}


template<class T>
inline T & SingleLinkedList<T>::operator[](const int index)
{
	int counter = 0;
	elem<T> *curElem = head;

	if (index<0 || index > size_)
		return curElem->obj;		// ������ ��� ������������� ����� ������ ��� �� ���������

	while (curElem != nullptr) {
		if (index == counter)
			return curElem->obj;
		curElem = curElem->next;
		counter++;
	}
}

template<class T>
inline SingleLinkedList<T>::~SingleLinkedList()
{
	while (size_)
		pop_front();
}

template<class T>
ostream& operator<<(ostream&os, SingleLinkedList<T>& SLL)
{
	for (size_t i = 0; i < SLL.size_; i++)
	{
		os << SLL[i] << " ";
		//os << SLL.getElement(i) << " ";
	}
	os << "\n\n";

	return os;
}
