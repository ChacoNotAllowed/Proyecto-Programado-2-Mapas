#include "Buttons.h"

Buttons::Buttons():normalColor(Color::Blue),hoverColor(Color::Cyan),pressedColor(Color::Magenta) {

    if (!font.loadFromFile("Resources/Fuente.ttf")) {
        cout << "Error al cargar la fuente" << endl;
        return;
    }

    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(Color::White);   
}
Text& Buttons::getText() {
    return text;
}
void Buttons::setColors(Color normal, Color hover, Color pressed) {
    normalColor = normal;
    hoverColor = hover;
    pressedColor = pressed;
}
bool Buttons::isButtonPressed() {
    return isPressed;
}
void Buttons::setPressed(bool is) {
    isPressed = is;
}
void Buttons::setDelete(bool borrar) {
    deleteButton = borrar;
}
bool Buttons::getDelete() {
   return deleteButton;
}
Color Buttons::getNormalColor() {
    return normalColor;
}
Color Buttons::getHoverColor() {
    return hoverColor;
}
Color Buttons::getPressedColor() {
    return pressedColor;
}

//////////////////////////////////////////////////////////////////////

RectButton::RectButton(float x, float y, float width, float height, string buttonText) {
    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));

    shape.setOutlineThickness(1.8);
    shape.setOutlineColor(Color(51, 51, 51));

    setColors(Color(105, 105, 105), Color(77, 77, 77), Color(51, 51, 51));

    getText().setString(buttonText);
    getText().setPosition(
        x + (width / 2.f) - (getText().getGlobalBounds().width / 2.f),
        y + (height / 2.f) - (getText().getGlobalBounds().height / 2.f)
    );
}
void RectButton::setPosition(int x, int y) {
    shape.setPosition(x, y);
}
void RectButton::setTextPosition(int x, int y) {
    getText().setPosition(x, y);
}
RectButton::RectButton(float x, float y, float width, float height, Color color) {

    shape.setPosition(x, y);
    shape.setSize(Vector2f(width, height));

    shape.setOutlineThickness(1.8);
    shape.setOutlineColor(Color(51, 51, 51));
    setColors(color, color, color);

}
void RectButton::render(RenderWindow& window) {
    window.draw(shape);
    window.draw(getText());
}
void RectButton::update(Vector2i& mousePos) {

    bool mouseOver = shape.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));

    if (mouseOver) {
        shape.setFillColor(getHoverColor());
        shape.setOutlineColor(Color::White);

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (!wasPressed) { 
                shape.setFillColor(getPressedColor());
                setPressed(true);
                wasPressed = true; 
            }
        } else {
            setPressed(false);
        }
    } else {
        shape.setFillColor(getNormalColor());
        shape.setOutlineColor(Color(51, 51, 51));
        setPressed(false);
    }

    
    if (!Mouse::isButtonPressed(Mouse::Left)) {
        wasPressed = false;
    } 
}

////////////////////////////////////////////////////////////////////

CircButton::CircButton(float x, float y, string circleText, Color color) {

    circle.setRadius(8);
    circle.setPosition(x, y);
    setColors(color, color, color);
    circle.setOutlineThickness(1.5);
    circle.setOutlineColor(Color(51, 51, 51));

    getText().setString(circleText);
    getText().setOutlineColor(Color::Black);
    getText().setOutlineThickness(1.5);
    getText().setPosition(x +18,y);
}

void CircButton::render(RenderWindow& window) {
    window.draw(circle);
    window.draw(getText());
}
void CircButton::update(Vector2i& mousePos) {

    static bool wasPressed = false;
    bool mouseOver = circle.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));

    if (mouseOver) {
        circle.setFillColor(getHoverColor());
        circle.setOutlineColor(Color::White);

       
        if (Mouse::isButtonPressed(Mouse::Left) && !wasPressed) {
            wasPressed = true;
            setPressed(!isButtonPressed());

            if (isButtonPressed()) {
                cout << "Modo edicion del punto activado" << endl << endl;
                cout << "Para borrar (presiona 'Back space')" << endl;
                cout << "Para cambiar color (presiona 'C')" << endl;
            }
        }
    }
    else {
        circle.setFillColor(getNormalColor());
        circle.setOutlineColor(Color(51, 51, 51));
    }
    
    if (!Mouse::isButtonPressed(Mouse::Left)) {
        wasPressed = false;
    }
    
    if (isButtonPressed()) {
        if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
            cout << "Borrando boton" << endl;
            setDelete(true);
            setPressed(false);
        }
        else if (Keyboard::isKeyPressed(Keyboard::C)) {

            cout << "Seleccione el color que desee" << endl;
            cout << "1) rojo" << endl;
            cout << "2) cyan" << endl;
            cout << "3) verde" << endl;
            int color;
            cin >> color;

            switch (color) {
            case 1:
                setColors(Color::Red, Color::Red, Color::Red);
                break;
            case 2:
                setColors(Color::Cyan, Color::Cyan, Color::Cyan);
                break;
            case 3:
                setColors(Color::Green, Color::Green, Color::Green);
                break;
            default:
                cout << "Blanco será" << endl;
                setColors(Color::White, Color::White, Color::White);
                break;
            }
            setPressed(false);
        }
    }

}
