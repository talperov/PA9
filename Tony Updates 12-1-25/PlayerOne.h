#pragma once
#include "Character.hpp"
#include <map>
#include <string>

class PlayerOne : public Character
{
private:
    bool facingRight;
    std::map<std::string, Animation> animations;
    std::string currentAction;

    void updateHitBox();

public:
    PlayerOne();

    void moveLeft() override;
    void moveRight() override;
    void moveJump() override;

    void attack() override;
    void takeDamage(int damage) override;

    void update(float deltaTime) override;
    sf::Sprite getSprite() const;
};

