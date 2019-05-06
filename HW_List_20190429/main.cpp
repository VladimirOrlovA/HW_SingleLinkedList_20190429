#include"SingleLinkedList.h"
using namespace std;


void main()
{
	SingleLinkedList<int> n;

	n.push_front(1);
	n.push_back(2);
	n.push_back(3);
	n.push_back(4);

	//n.pop_front();
	//n.pop_back();

	//n.clear();
	cout << n.getSize() << endl;
	cout << n.getElement(3) << endl;
	n.insert(4, 15);
	cout << n << endl;
	n.removeAt(4);
	n.push_back(150);
	n.pop_back();
	cout <<"Source "<< n << endl;
	//cout << n[3] << endl;
	//n[0] = 100;
	//cout << n << endl;

	SingleLinkedList<int> copy;
	
	copy = n;


	cout <<"Copy "<< copy;


	system("pause");
}

