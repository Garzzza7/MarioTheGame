#ifndef OOPPROJECT_OBJECTBASE_H
#define OOPPROJECT_OBJECTBASE_H

#include <SFML/Graphics.hpp>

enum ObjectType{
    TILE,
    ENTITY,
    PLAYER
};

class ObjectBase{

    ObjectType type;
    sf::IntRect rect;

public:
    sf::Texture texture;

    ObjectBase(ObjectType type, std::string textureAddress, sf::IntRect rect);

    ObjectType getType(){return type;}
    sf::IntRect getRect(){return rect;};

};

#endif //OOPPROJECT_OBJECTBASE_H
