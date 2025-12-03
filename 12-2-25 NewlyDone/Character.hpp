/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
using sf::FloatRect;

const float FLOOR_Y = 472.f;        // Y position where the ground is
const float GRAVITY = 0.7f;         // How fast characters fall each frame

class Character
{
protected:
    // The sprite drawn to screen
    sf::Sprite bodySprite;                     // The picture of the character shown on screen

    // Core animations EVERY character has
    Animation idleAnimation;                   // Animation when standing still
    Animation jumpAnimation;                   // Animation when jumping
    bool onGround = true;                      // True if character is touching the ground

    // Attack state tracking
    bool isAttacking;                          // True when character is doing an attack
    float attackTimer;                         // Counts how long the attack has been playing
    bool hasHitThisAttack = false;             // Stops attack from hitting the same enemy many times

    // Collision detection
    FloatRect collisionBox;                    // Box used to stop characters walking through each other
    FloatRect hurtBox;                         // Area where the character can be hit
    FloatRect hitBox;                          // Area where the attack can hit an enemy
    bool hitBoxActive = false;                 // True only when the attack can hit something

    // Health bar graphics
    sf::RectangleShape healthBarBackground;   // Gray background of the health bar
    sf::RectangleShape healthBarForeground;   // Red/green part that shows current health

public:

    sf::Vector2f position;        // Where the character is on screen
    sf::Vector2f velocity;         // How fast the character is moving (x and y)
    float health;                  // Current health points
    float maxHealth;               // Highest health the character can have
    std::string name;              // Name of the character (Player, Enemy, etc.)

    Character();                   // Sets up a new character

    virtual void moveLeft() = 0;   // Makes character walk left (different for each character)
    virtual void moveRight() = 0;  // Makes character walk right
    virtual void moveJump() = 0;   // Makes character jump
    virtual void attack() = 0;     // Starts an attack
    virtual void takeDamage(int damage) = 0; // Reduces health when hit

    virtual void update(float dt); // Runs every frame to move and animate the character

    sf::Sprite getSprite() const { return bodySprite; } // Returns the picture to draw

    // Collision getters
    FloatRect getCollisionBox() const { return collisionBox; }   // Returns the solid box
    FloatRect getHurtBox() const { return hurtBox; }             // Returns the area that can be hit
    FloatRect getHitBox() const { return hitBox; }               // Returns the attack hit area
    bool isHitBoxActive() const { return hitBoxActive; }         // True if attack can hit right now
    bool getHasHitThisAttack() const { return hasHitThisAttack; } // Checks if attack already hit once
    void setHasHitThisAttack(bool state) { hasHitThisAttack = state; } // Sets the hit-once flag

    float getHealth() const { return health; } // Returns current health value

    // Collision and attack helpers
    virtual void updateCollisionBoxes();           // Moves all boxes to match character position
    bool isHitting(const Character& other) const; // Checks if this character's attack hits another
    void resolveCollision(Character& other);       // Fixes characters overlapping

    // Health bar
    void setHealthBarPosition(sf::Vector2f pos);   // Places the health bar above the character
    void drawHealthBar(sf::RenderWindow& window);  // Draws the health bar on screen
};