#pragma once
#include<iostream>
using namespace std;

// создаем элемент содержащий данные и адрес следующего элемента
template<class T>
class elem
{
public:
	T obj;
	elem<T>*next = nullptr;
};

// создаем лист
template<class T>
class SingleLinkedList
{
	elem<T>*head = nullptr;
	int size_ = 0;
public:
	SingleLinkedList();
	// вставить объект в конец
	void push_back(const T & obj);
	// вставить объект в начало
	void push_front(const T & obj);
	// удалить объект в конце
	void pop_back();
	// удалить объект в начале
	void pop_front();
	// вставить объект в заданную позицию
	void insert(int pos, const T & obj);
	// получить объект из заданной позиции
	T & getElement(int pos);
	// удалить объект из заданной позиции
	void removeAt(int pos);
	// получить размер списка
	int getSize() const;
	// очистить
	void clear();
	// копировать объект
	SingleLinkedList(const SingleLinkedList & SLL);
	// копировать объект по r-value ссылке
	SingleLinkedList(SingleLinkedList && SLL);
	// перегрузка операртора =
	SingleLinkedList<T> & operator=(const SingleLinkedList<T> & SLL);
	// перегрузка оператора = по r-value ссылке
	SingleLinkedList<T> & operator=(SingleLinkedList<T> && SLL);
	T& operator[](const int index);

	~SingleLinkedList();

	template<class T>
	friend ostream& operator<<(ostream&os, SingleLinkedList<T>& SLL);
};

// конструктор по умолчанию
template<class T>
inline SingleLinkedList<T>::SingleLinkedList()
{
	size_ = 0;
	head = nullptr;
}

template<class T>
inline void SingleLinkedList<T>::push_back(const T & obj)
{
	// создаем указатель на новый элемент списка и выделяем под него память
	elem<T> *nElem = new elem<T>;
	// указателю объекта элемента присваиваем указатель объекта 
	nElem->obj = obj;
	// проверяем есть ли голова у списка, если нет то присваиваем указателю головы указатель первого элемента списка
	if (this->head == nullptr)
	{
		this->head = nElem;
		this->size_ = 1;
		return;
	}
	// если голова есть, то создаем временый указатель текущего элемента, т.е. для головы (список начинается с головы, начсинаем с головы)
	elem<T> *curElem = head;
	// проверяем есть ли у текущего элемента указатель на следующий элемент
	while (curElem->next != nullptr) // если есть заходим в цикл чтобы пройти до последнего элемента
		curElem = curElem->next;
	curElem->next = nElem;	// в текущем элементе прописываем указатель на добавленный элемент
	nElem->next = nullptr;	// указываем в добавленном (последнем) элементе адрес на след элемент равным 0, чтобы определить его как хвост
	size_++; // увеличиваем размер списка на 1 элемент
}

template<class T>
inline void SingleLinkedList<T>::push_front(const T & obj)
{
	// создаем указатель на новый элемент списка и выделяем под него память
	elem<T> *nElem = new elem<T>;
	// указателю объекта элемента присваиваем указатель объекта 
	nElem->obj = obj;
	// создаем временный указатель для текущего элемента, т.е. для головы списка
	elem<T> *curElem = head;
	// адресу головы присваиваем адрес нового элемента, т.к. новый элемент становится головой списка
	head = nElem;
	// прописыаем указателю нового добавленного элемента (ставшему головой списка) адрес следующего элемента (адрес бывшей головы)
	nElem->next = curElem;
	// увеличиваем размер списка на 1
	size_++;
}

template<class T>
inline void SingleLinkedList<T>::pop_back()
{
	// проверяем есть ли голова у списка, если нет, то удалять нечего, выходим через return
	if (head == nullptr)
		return;
	// создаем временный указатель текущего элемента списка, т.е. для головы списка 
	elem<T> *curElem = head;
	// если список из однго элемента, то удаляем голову и выходим
	if (size_ == 1)
	{
		head = nullptr;
		size_ = 0;
		return;
	}
	// элементов больше двух идем по циклу до последнего элемента
	for (size_t i = 0; i < size_ - 2; i++)
	{
		curElem = curElem->next; // двигаемся по связанной цепочке адресов 
	} // выходим из цикла на адресе предпоследнего элемента
	// удаляем указатель на адрес последнего элемента
	delete curElem->next;
	// в указатель предпоследнего элемента ставшим последним записываем указатель на след равным 0
	curElem->next = nullptr;
	// умеьншаем размер листа на 1
	size_--;
}

template<class T>
inline void SingleLinkedList<T>::pop_front()
{
	// создаем временный указатель текущего элемента списка
	elem<T> *curElem = head;
	// записывем в голову адрес следующего элемента который стал головой
	head = head->next;
	// уменьшаем размер листа на 1
	size_--;
}

template<class T>
inline void SingleLinkedList<T>::insert(int pos, const T & obj)
{
	// создаем указатель на новый элемент листа
	elem<T> *nElem = new elem<T>;
	// в адрес объекта элемента записываем адрес объекта 
	nElem->obj = obj;
	// создаем временный указатель и записываем в него адрес головы
	elem<T> *curElem = head;
	// если позиция вставки меньше 0 или больше размера листа, то выходим
	if (pos < 0 || pos > size_)
	{
		cout << "Error - Position out of range\n";
		return;
	}
	// если позиция равна нулю, то добавляем новый элемент в первую позицию и копируем в нее объект
	if (pos == 0)
	{
		push_front(obj);
		return;
	}
	// если позиция равна размеру листа, то добавляем новый элемент после последней позиции и копируем в нее объект
	if (pos == size_)
	{
		push_back(obj);
		return;
	}
	// если позиция где-то в интервале листа от 0 до size_ идем циклом по цепочке адресов до заданной позиции 
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
	// создаем временный указатель на удаляемый элемент
	elem<T> *delElem = curElem->next;
	// соединяем цепочку адресов 
	curElem->next = delElem->next;
	// удаляем указатель на удаляемый элемент
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
	// двигаемся по циклу от последнего элемента листа до нулевого
	while (size_)
		pop_front(); // size_ уменьшается по мере удаления элементов листа от конца к началу
}

template<class T>
inline SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList<T> & SLL)
{
	this->size_ = SLL.size_;
	// проверяем копируемый лист на содержимое, если пусто выходим
	if (SLL.head == nullptr)
	{
		this->head = nullptr;
		this->size_ = 0;
		return;
	}
	// выделяем память под головной элемент
	this->head = new elem<T>;
	// копируем головной элемент источника в себя
	this->head = SLL.head;
	// создаем временный указатель 
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
		return curElem->obj;		// узнать как реализовывать вывод ошибок или их отработку

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
