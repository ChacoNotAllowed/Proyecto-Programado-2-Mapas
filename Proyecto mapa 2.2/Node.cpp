#include "Node.h"

Node::Node(int x, int y, string name, Color color) :x(x), y(y), pointName(name), buttonColor(color), circle(x, y, name, color){
	next = nullptr;
	prev = nullptr;
}
