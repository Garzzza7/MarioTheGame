//
// Created by specklew on 08.01.2022.
//

#include "Game.h"
#include "Tiles/ObjectRegistry.h"

//Definitions of static classes.
Game * Game::instance{nullptr};
std::mutex Game::mutex;

//Locking the storage location using lock_guard.
Game * Game::GetInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if(instance == nullptr){
        instance = new Game();
    }
    return instance;
}

Game::Game() {
    ObjectRegistry * objectRegistry = ObjectRegistry::GetInstance();

    this->player = new Player(300,300);
    texture.loadFromFile("../../textures/background.png");
    BG.setTexture(texture);
    BG.setPosition(0.f,0.f);

    initWindow();
    initLevels();
    running = true;
}

Game::~Game() {
    delete this->player;
    delete this->goomba;
}

void Game::initWindow() {

    this->videoMode.height = 800;
    this->videoMode.width = 1000;

    this->window.create(this->videoMode, "SFML Window", sf::Style::Titlebar | sf::Style::Close);

    this->window.setFramerateLimit(60);
}

void Game::initLevels() {

    Level * level1 = new Level("level_1");
    levels.push_back(level1);
}

//Rendering code:
void Game::render() {
    this->window.clear(/*sf::Color::Blue*/);
    this->window.draw(BG);

    this->levels.at(0)->render(this->window);

    this->view.setCenter(this->player->getPos());
    this->window.setView(view);
    this->player->render(this->window);

    this->window.display();
}

//Code that runs every frame of the game:
void Game::update() {

    this->pollEvents();
    this->render();

    //Passing on the update event.
    this->player->update(this->window);
    this->levels.at(currentLevel)->update();

    if(!this->window.isOpen()) running = false;
}

//Event polling
void Game::pollEvents() {

    while (this->window.pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window.close();
                running = false;
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window.close();
                    running = false;
                }
                break;
        }
    }
}

bool Game::isRunning() {
    return this->running;
}

Level *Game::getCurrentLevel() {
    return levels.at(this->currentLevel);
}

