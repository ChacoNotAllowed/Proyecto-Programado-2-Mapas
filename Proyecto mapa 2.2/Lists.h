#pragma once
#include "Node.h"

class List
{
private:
	Node* head;
	Node* tail;
public:
	List();
	void insertLast(int x, int y, string pointName,Color color);
	void renderList(RenderWindow& window, Vector2i& mousePos);
	void deleteNode(Node* node);
	Node* getHead();
};


