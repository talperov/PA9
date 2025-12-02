/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#pragma once
#include "Character.hpp"
#include <map>
#include <string>

class PlayerTwo : public Character
{
private:
    bool facingRight;                                      // true = looking right, false = looking left
    std::map<std::string, Animation> animations;          // Stores all animations (idle, run, jump, attack, etc.) by name
    std::string currentAction;                             // Name of the animation currently playing
    void updateHitBox();                                   // Updates the attack hitbox position and direction

public:
    PlayerTwo();                                           // Sets up PlayerTwo with position, health, and loads animations

    void moveLeft() override;                              // Moves the character left
    void moveRight() override;                             // Moves the character right
    void moveJump() override;                              // Makes the character jump (only when on ground)
    void attack() override;                                // Starts the attack animation and turns on hitbox
    void takeDamage(int damage) override;                  // Reduces health when hit

    void update(float deltaTime) override;                 // Runs every frame: handles movement, animation, and gravity

    sf::Sprite getSprite() const;                          // Returns the current sprite to draw on screen
};