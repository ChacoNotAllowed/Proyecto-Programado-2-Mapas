#include "Resources.h"

Resources::Resources() {

    if (!mapTexture.loadFromFile("Resources/Mapa.jpg")) {
        cout << "Error al cargar la imagen del mapa" << endl;
        return;
    }
    mapSprite.setTexture(mapTexture);

    if (!font.loadFromFile("Resources/Fuente.ttf")) {
        cout << "Error al cargar la fuente" << endl;
        return;
    }
}

Sprite Resources::getMapSprite() {
    return mapSprite;
}
Font Resources::getFont() {
    return font;
}