#include "UserNodes.h"
UserNode::UserNode(string listName) :listName(listName), next(nullptr), prev(nullptr), rectangle(700, 200, 200, 50, listName) {}
