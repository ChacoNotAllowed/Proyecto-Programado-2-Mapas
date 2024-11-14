#include "Lists.h"

List::List() :head(nullptr), tail(nullptr) {};

void List::insertLast(int x, int y, string pointName,Color color) {
	Node* newNode = new Node(x, y, pointName,color);

	if (!head) {
		head = newNode;
		tail = newNode;
	}
	else {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
	}
}

Vector2f interpolacionCubic(float t, sf::Vector2f p0, sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3) {
    float t2 = t * t;
    float t3 = t2 * t;

    Vector2f result;
    result.x = 0.5f * ((2 * p1.x) +
        (-p0.x + p2.x) * t +
        (2 * p0.x - 5 * p1.x + 4 * p2.x - p3.x) * t2 +
        (-p0.x + 3 * p1.x - 3 * p2.x + p3.x) * t3);

    result.y = 0.5f * ((2 * p1.y) +
        (-p0.y + p2.y) * t +
        (2 * p0.y - 5 * p1.y + 4 * p2.y - p3.y) * t2 +
        (-p0.y + 3 * p1.y - 3 * p2.y + p3.y) * t3);

    return result;
}

void List::renderList(RenderWindow& window, Vector2i& mousePos) {
    if (!head) return;

    Node* current = head;

    if (current->next) {
        Node* node1 = current;
        Node* node2 = current->next;
        VertexArray line(LinesStrip, 101);

        for (int i = 0; i <= 100; ++i) {
            float t = i / 100.0f;
            Vector2f point = Vector2f(
                node1->x + (node2->x - node1->x) * t,
                node1->y + (node2->y - node1->y) * t
            );

            line[i].position = point;
            line[i].color = Color::Green;
        }

        window.draw(line);
    }
    current = head;

    while (current && current->next && current->next->next && current->next->next->next) {
        Node* node1 = current;
        Node* node2 = current->next;
        Node* node3 = current->next->next;
        Node* node4 = current->next->next->next;

        VertexArray curve(LinesStrip, 101);

        for (int i = 0; i <= 100; ++i) {
            float t = i / 100.0f;
            Vector2f point = interpolacionCubic(t,
                Vector2f(node1->x, node1->y),
                Vector2f(node2->x, node2->y),
                Vector2f(node3->x, node3->y),
                Vector2f(node4->x, node4->y));

            curve[i].position = point;
            curve[i].color = Color::Green;
        }

        window.draw(curve);
        current = current->next;
    }

    while (current && current->next) {
        Node* node1 = current;
        Node* node2 = current->next;
        VertexArray line(LinesStrip, 101);

        for (int i = 0; i <= 100; ++i) {
            float t = i / 100.0f;
            Vector2f point = Vector2f(
                node1->x + (node2->x - node1->x) * t,
                node1->y + (node2->y - node1->y) * t
            );

            line[i].position = point;
            line[i].color = Color::Green;
        }

        window.draw(line);
        current = current->next;
    }

    current = head;
    while (current) {
        Node* nextNode = current->next;
        current->circle.render(window);
        current->circle.update(mousePos);

        if (current->circle.getDelete()) {
            deleteNode(current);
        }
        current = nextNode;
    }

    
}
void List::deleteNode(Node* node) {
    if (node == nullptr) return;

    if (node == head) {
        head = node->next; 
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
    }
    else if (node == tail) {
        tail = node->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev; 
    }
    delete node;
}

Node* List::getHead() {
    return head;
}
