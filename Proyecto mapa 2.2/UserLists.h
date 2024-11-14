#pragma once
#include <fstream>
#include <sstream>
#include "UserNodes.h"

class UserList
{
private:
	UserNode* head;
	UserNode* tail;
public:
	UserList();
	void userInsertLast(string name);
	void userRenderList(RenderWindow& window, Vector2i& mousePos);
	UserNode* getTail();
	void deleteRoute(UserNode* node);
	void saveToFile(const std::string& filename);
	void loadFromFile(const std::string& filename);
	void insertLast(UserNode* newNode);
};

