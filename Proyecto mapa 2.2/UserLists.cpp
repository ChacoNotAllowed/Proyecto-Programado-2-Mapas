#include "UserLists.h"

UserList::UserList() :head(nullptr), tail(nullptr) {};

void UserList::userInsertLast(string name) {
    UserNode* newNode = new UserNode(name);

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
UserNode* UserList::getTail() {
    return tail;
}
void UserList::userRenderList(RenderWindow& window, Vector2i& mousePos) {
    UserNode* current = head;
    int yOffset = 0;
    int spacing = 70;
    bool wasPressed = false;
    bool addingPoint = false;

    while (current) {

        UserNode* nextNode = current->next;
        current->userList.renderList(window, mousePos);

        current->rectangle.setPosition(830, 210 + yOffset);
        current->rectangle.setTextPosition(840, 226 + yOffset);
        current->rectangle.render(window);
        current->rectangle.update(mousePos);

        yOffset += spacing;

        if (current->rectangle.isButtonPressed() && !wasPressed) {
            wasPressed = true;

            cout << "Modo edicion del punto activado para: " << current->listName << endl;
            cout << "Para borrar (presiona 'Back space')" << endl;
            cout << "Para agregar un punto turistico (presiona 'A')" << endl;
            system("pause");

            if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
                cout << "Borrando el boton: " << current->listName << endl;
                deleteRoute(current);
            }
            if (Keyboard::isKeyPressed(Keyboard::A)) {

                cout << "Click derecho en el mapa para agregar un punto nuevo " << current->listName << endl;
                addingPoint = true;

            }
        }
        if (addingPoint && Mouse::isButtonPressed(Mouse::Right)) {
            cout << "Ingrese el nombre del nuevo punto turistico:" << endl;
            string pointName;
            cin >> pointName;
            cout << "Seleccione el color que desee" << endl;
            cout << "1) rojo" << endl;
            cout << "2) cyan" << endl;
            cout << "3) verde" << endl;
            int color;
            cin >> color;

            int x = mousePos.x;
            int y = mousePos.y;
            switch (color)
            {
            case 1:
                current->userList.insertLast(x, y, pointName, Color::Red);
                break;
            case 2:
                current->userList.insertLast(x, y, pointName, Color::Cyan);
                break;
            case 3:
                current->userList.insertLast(x, y, pointName, Color::Green);
                break;
            default:
                cout << "Blanco sera" << endl;
                current->userList.insertLast(x, y, pointName, Color::White);
                break;
            }
            addingPoint = false;
        }
        if (!Mouse::isButtonPressed(Mouse::Left)) {
            wasPressed = false;
        }

        current = nextNode;
    }

}
void UserList::deleteRoute(UserNode* node) {
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

void UserList::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para guardar" << std::endl;
        return;
    }

    UserNode* current = head;
    while (current) {
        file << current->listName << '\n';
       
        Node* point = current->userList.getHead();
        while (point) {
            file << point->x << ' ' << point->y << ' ' << point->pointName << ' '
                << point->buttonColor.toInteger() << '\n';
            point = point->next;
        }

        file << "---\n";
        current = current->next;
    }
    file.close();
}
void UserList::insertLast(UserNode* newNode) {
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

void UserList::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo para cargar" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::string listName = line;
        UserNode* userNode = new UserNode(listName);

        while (std::getline(file, line) && line != "---") {
            std::istringstream ss(line);
            int x, y;
            std::string pointName;
            int colorInt;
            ss >> x >> y >> pointName >> colorInt;
            sf::Color color(colorInt);

            userNode->userList.insertLast(x, y, pointName, color);
        }
        
        insertLast(userNode);

        std::getline(file, line);
    }

    file.close();
}