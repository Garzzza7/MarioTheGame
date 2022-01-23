#ifndef OOPPROJECT_PLAYER_H
#define OOPPROJECT_PLAYER_H

#include <SFML/Graphics.hpp>
#include "AnimatedGif.h"

class Player{

    sf::Sprite sprite;
    sf::Texture standingTexture;
    sf::Texture jumpingTexture;
    AnimatedGif gif;

    bool moveBoolDirection{true};

    sf::Event event;

    bool lockMovement[4];/*
    0 - top
    1 - right
    2 - bottom
    3 - left
     */
    bool onGround{false};
    unsigned jumpCount{0};
    //Private methods

    sf::FloatRect getPlayerBounds();

    void setPositionX(float x);
    void setPositionY(float y);

    //Physics:
    sf::Vector2f velocity{0,0};
    float gravity{10.f};
    float acceleration{0.2f};
    float maxVelocity{3.0f};
    float friction{0.5f};

public:
    Player(float x , float y);
    ~Player();
    //Update functions run every frame.
    void update(sf::RenderTarget & target);
    void updatePhysics();
    void updateMovement();
    void updateAnimations();

    sf::Vector2f getPos() {return sprite.getPosition();};

    void move(const float dir_x, const float dir_y);
    void jump(const float dir_x, const float dir_y);
    void stop(const float dir_x, const float dir_y);

    void render(sf::RenderTarget & target);

    void checkCollisions(sf::RenderTarget & target);

};

#endif //OOPPROJECT_PLAYER_H
