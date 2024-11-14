#include "Buttons.h"
#include "Lists.h"
#include "UserLists.h"
int main()
{
    RenderWindow window(VideoMode(1200, 800), "Minecraft Map", Style::Close); 
    Resources resources;
    RectButton routeButton(830, 80, 200, 100,"Agregar Ruta"); 
    RectButton readyButton(830, 620, 195, 100, "Listo");

    UserList userList;
    int currentState = 0; 
    UserNode* currentNode = nullptr;
    userList.loadFromFile("rutas.txt");

    while (window.isOpen()) {

        Event event;
        Vector2i mousePos = Mouse::getPosition(window);

        if (readyButton.isButtonPressed()) {
            currentState = 1;
        }
        if (routeButton.isButtonPressed()) {   

            cout << "Ingrese el nombre de la nueva ruta:" << endl;
            string routeName;
            cin >> routeName;

            userList.userInsertLast(routeName);
            currentNode = userList.getTail();
            cout << "Presione click derecho para agregar un punto" << endl;
            currentState = 2;

        }


        while (window.pollEvent(event)) {

            if (event.type == Event::Closed || (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape))
            {
                window.close();
            }
            if (currentState == 2 && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
            {
                cout << "Ingrese el nombre del nuevo punto turistico:" << endl;
                string pointName;
                cin >> pointName;
                cout << "Seleccione el color que desee" << endl << endl;
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
                    currentNode->userList.insertLast(x, y, pointName, Color::Red);
                    break;
                case 2:
                    currentNode->userList.insertLast(x, y, pointName, Color::Cyan);
                    break;
                case 3:
                    currentNode->userList.insertLast(x, y, pointName, Color::Green);
                    break;
                default:
                    cout << "Blanco sera" << endl;
                    currentNode->userList.insertLast(x, y, pointName, Color::White);
                    break;
                }              
            }
        }
        window.clear();
        window.draw(resources.getMapSprite());

        routeButton.update(mousePos);
        routeButton.render(window);
        readyButton.update(mousePos);
        readyButton.render(window);       

        userList.userRenderList(window, mousePos);
        
        window.display();
    }
    userList.saveToFile("rutas.txt");

    return 0;
}

