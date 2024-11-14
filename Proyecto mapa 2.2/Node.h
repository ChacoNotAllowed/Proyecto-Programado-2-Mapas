#pragma once
#include "Buttons.h"

class Node
{
public:
	int x;
	int y;
	string pointName;
	Color buttonColor;
	Node* next;
	Node* prev;
	CircButton circle;
	Node(int x, int y, string name,Color buttonColor);
	
};


