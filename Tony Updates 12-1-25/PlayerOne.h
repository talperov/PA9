#pragma once
#include "Character.hpp"
#include "Animation.hpp"
#include <map>
#include <string>

class PlayerOne : public Character
{
private:
    std::map<std::string, Animation> animations;
    std::string currentAction;
    bool facingRight;  // Track direction

public:
    PlayerOne();

    //MOVEMENT
    void moveLeft() override;
    void moveRight() override;
  

    //COMBAT
    void attack() override;
    void takeDamage(int damage) override;

    //ANIMATION
    void update(float deltaTime);   // Update current animation
    sf::Sprite getSprite() const;   // Get current sprite to draw
};
