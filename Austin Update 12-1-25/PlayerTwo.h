#pragma once
#include "Character.hpp"
#include "Animation.hpp"
#include <map>
#include <string>

class PlayerTwo : public Character
{
private:
    std::map<std::string, Animation> animations;
    std::string currentAction;
    bool facingRight;  // Track direction

    void updateHitBox();

public:
    PlayerTwo();

    //MOVEMENT
    void moveLeft() override;
    void moveRight() override;

    //COMBAT
    void attack() override;
    void takeDamage(int damage) override;

    //ANIMATION
    void update(float deltaTime);
    sf::Sprite getSprite() const;
};
