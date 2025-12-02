#include "PlayerTwo.h"
#include <iostream>

using std::cout;
using std::endl;

// -------------------------
// Constructor
// -------------------------
PlayerTwo::PlayerTwo()
{
    name = "Skeleton";
  
    position = sf::Vector2f(700.f, FLOOR_Y);
    velocity = sf::Vector2f(0.f, 0.f);
    facingRight = false;

    animations["Idle"].loadFromFile("Assets/PlayerOne/Skeleton/Idle.png", 10, 64, 64);
    animations["Walk"].loadFromFile("Assets/PlayerOne/Skeleton/Walk.png", 10, 64, 64);
    animations["Attack"].loadFromFile("Assets/PlayerOne/Skeleton/Attack.png", 6, 64, 64);
    animations["Jump"].loadFromFile("Assets/PlayerOne/Skeleton/Jump.png", 1, 64, 64);

    currentAction = "Idle";
}

// -------------------------
// Movement
// -------------------------
void PlayerTwo::moveLeft()
{
    position.x -= 0.15f;
    facingRight = false;
    if (!isAttacking)
        currentAction = "Walk";
}

void PlayerTwo::moveRight()
{
    position.x += 0.15f;
    facingRight = true;
    if (!isAttacking)
        currentAction = "Walk";
}

void PlayerTwo::moveJump()
{
    if (onGround)
    {
        velocity.y = -8.0f;
        currentAction = "Jump";
        onGround = false;
    }
}

// -------------------------
// Combat
// -------------------------
void PlayerTwo::attack()
{
    if (!isAttacking)
    {
        cout << name << " attacks!" << endl;
        currentAction = "Attack";
        isAttacking = true;
        attackTimer = 0.0f;
        hasHitThisAttack = false;
        animations[currentAction].reset();
    }
}

void PlayerTwo::takeDamage(int damage)
{
    health -= damage;
    if (health < 0)
        health = 0;

    cout << name << " takes " << damage << " damage, Health now: " << health << endl;
}

// -------------------------
// Update
// -------------------------
void PlayerTwo::update(float deltaTime)
{
    position.y += velocity.y;
    if (!onGround)
        velocity.y += 0.15f;

    if (position.y >= FLOOR_Y)
    {
        position.y = FLOOR_Y;
        velocity.y = 0;
        if (currentAction != "Walk" && currentAction != "Attack")
            currentAction = "Idle";
        onGround = true;
    }
    else
    {
        onGround = false;
    }

    if (isAttacking && currentAction == "Attack")
    {
        attackTimer += deltaTime;

        if (attackTimer >= 0.1f && attackTimer < 0.3f)
        {
            hitBoxActive = true;
            updateHitBox();
        }
        else
        {
            hitBoxActive = false;
        }

        if (attackTimer >= 0.6f)
        {
            currentAction = "Idle";
            isAttacking = false;
            hitBoxActive = false;
            attackTimer = 0.0f;
        }
    }

    animations[currentAction].update(deltaTime);

    updateCollisionBoxes();
    Character::update(deltaTime);

}

// -------------------------
// Sprite
// -------------------------
sf::Sprite PlayerTwo::getSprite() const
{
    sf::Sprite sprite = animations.at(currentAction).getSprite();
    sprite.setPosition(position);
    sprite.setScale(facingRight ? 2.f : -2.f, 2.f);
    sprite.setOrigin(32, 32);
    return sprite;
}

// -------------------------
// Hitbox update
// -------------------------
void PlayerTwo::updateHitBox()
{
    if (facingRight)
    {
        hitBox.left = position.x + 10;
        hitBox.top = position.y - 20;
        hitBox.width = 50;
        hitBox.height = 30;
    }
    else
    {
        hitBox.left = position.x - 60;
        hitBox.top = position.y - 20;
        hitBox.width = 50;
        hitBox.height = 30;
    }
}
