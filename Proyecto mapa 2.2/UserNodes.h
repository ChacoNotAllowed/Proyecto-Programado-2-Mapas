#pragma once
#include "Buttons.h"
#include "Lists.h"
class UserNode
{
public:
	List userList;
	string listName;
	RectButton rectangle;
	UserNode* next;
	UserNode* prev;
	UserNode(string listName);

};
