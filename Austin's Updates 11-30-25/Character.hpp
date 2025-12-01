#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"

const float FLOOR_Y = 472.f;
const float GRAVITY = 0.7f;

class Character
{
protected:

    // The sprite drawn to screen
    sf::Sprite bodySprite;

    // Core animations EVERY character has
    Animation idleAnimation;
    Animation jumpAnimation;

    bool onGround = true;

public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float health;
    float maxHealth;
    std::string name;

    Character();

    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;

    virtual void attack() = 0;
    virtual void takeDamage(int damage) = 0;

    virtual void update(float dt);

    sf::Sprite getSprite() const{ return bodySprite; }
};
