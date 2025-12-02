#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.hpp"
using sf::FloatRect;

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

    // Attack state tracking
    bool isAttacking;           // Flag for if the character is currently attacking
    float attackTimer;          // Count for current attack animation
    bool hasHitThisAttack = false;

    // Collision detection
    FloatRect collisionBox;
    FloatRect hurtBox;
    FloatRect hitBox;
    bool hitBoxActive = false;

    // Health bar graphics
    sf::RectangleShape healthBarBackground;
    sf::RectangleShape healthBarForeground;

public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float health;
    float maxHealth;
    std::string name;

    Character();

    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual void moveJump() = 0;

    virtual void attack() = 0;
    virtual void takeDamage(int damage) = 0;

    virtual void update(float dt);

    sf::Sprite getSprite() const { return bodySprite; }

    // Collision getters
    FloatRect getCollisionBox() const { return collisionBox; }
    FloatRect getHurtBox() const { return hurtBox; }
    FloatRect getHitBox() const { return hitBox; }
    bool isHitBoxActive() const { return hitBoxActive; }
    bool getHasHitThisAttack() const { return hasHitThisAttack; }
    void setHasHitThisAttack(bool state) { hasHitThisAttack = state; }
    float getHealth() const { return health; }

    // Collision and attack helpers
    virtual void updateCollisionBoxes();
    bool isHitting(const Character& other) const;
    void resolveCollision(Character& other);

    // Health bar
    void setHealthBarPosition(sf::Vector2f pos);
    void drawHealthBar(sf::RenderWindow& window);
};
