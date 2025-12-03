/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#pragma once
#include "Character.hpp"
#include <map>
#include <string>

class PlayerOne : public Character
{
private:
    bool facingRight;                                      // true = character looks right, false = looks left
    std::map<std::string, Animation> animations;          // Holds all animations (idle, run, jump, attack, etc.) by name
    std::string currentAction;                             // Name of the animation we are playing now ("idle", "run", etc.)
    void updateHitBox();                                   // Moves and flips the attack hitbox based on direction

public:
    PlayerOne();                                           // Sets up PlayerOne with position, health, and loads animations

    void moveLeft() override;                              // Makes player walk to the left
    void moveRight() override;                             // Makes player walk to the right
    void moveJump() override;                              // Makes player jump (only if on ground)
    void attack() override;                                 // Starts the attack animation and enables hitbox
    void takeDamage(int damage) override;                  // Lowers health and maybe plays hurt animation

    void update(float deltaTime) override;                 // Runs every frame: moves, animates, applies gravity

    sf::Sprite getSprite() const;                          // Returns the current sprite to draw on screen
};