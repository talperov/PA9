/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/
#include "PlayerTwo.h"
#include <iostream>
using std::cout;
using std::endl;

// Sets up Player Two (also a skeleton, but on the right side)
PlayerTwo::PlayerTwo()
{
    name = "Skeleton(Player2)";
    position = sf::Vector2f(700.f, FLOOR_Y);
    velocity = sf::Vector2f(0.f, 0.f);
    facingRight = false;

    // Load all animations from image files
    animations["Idle"].loadFromFile("Assets/PlayerOne/Skeleton/Idle.png", 10, 64, 64);
    animations["Walk"].loadFromFile("Assets/PlayerOne/Skeleton/Walk.png", 10, 64, 64);
    animations["Attack"].loadFromFile("Assets/PlayerOne/Skeleton/Attack.png", 6, 64, 64);
    animations["Jump"].loadFromFile("Assets/PlayerOne/Skeleton/Jump.png", 1, 64, 64);
    animations["Hurt"].loadFromFile("Assets/PlayerOne/Skeleton/Hurt.png", 4, 64, 64);
    animations["Death"].loadFromFile("Assets/PlayerOne/Skeleton/Death.png", 8, 64, 64);

    currentAction = "Idle"; // Start standing still
    healthBarForeground.setFillColor(sf::Color::Green); // Green for Player 2
}

// Move left (Left Arrow key)
void PlayerTwo::moveLeft()
{
    if (health <= 0) return;
    position.x -= 0.15f;
    facingRight = false;
    if (!isAttacking && currentAction != "Hurt")
        currentAction = "Walk";
}

// Move right (Right Arrow key)
void PlayerTwo::moveRight()
{
    if (health <= 0) return;
    position.x += 0.15f;
    facingRight = true;
    if (!isAttacking && currentAction != "Hurt")
        currentAction = "Walk";
}

// Jump (Up Arrow key)
void PlayerTwo::moveJump()
{
    if (health <= 0 || !onGround) return;
    velocity.y = -8.0f;
    currentAction = "Jump";
    onGround = false;
}

// Start attack (Right Control key)
void PlayerTwo::attack()
{
    if (health <= 0 || isAttacking) return;
    cout << name << " attacks!" << endl;
    currentAction = "Attack";
    isAttacking = true;
    attackTimer = 0.0f;
    hasHitThisAttack = false;
    animations[currentAction].reset();
}

// Take damage when hit
void PlayerTwo::takeDamage(int damage)
{
    if (health <= 0) return;

    health -= damage;
    if (health <= 0)
    {
        health = 0;
        currentAction = "Death";
        animations["Death"].reset();
        isAttacking = false;
        cout << name << " has died!" << endl;
    }
    else
    {
        currentAction = "Hurt";
        animations["Hurt"].reset();
        attackTimer = 0.0f;
    }
    cout << name << " takes " << damage << " damage, Health now: " << health << endl; //Test to see if Damage Works, potentially keep for main game
}

// Runs every frame - handles movement, gravity, landing, and attack timing
void PlayerTwo::update(float deltaTime)
{
    // Move up/down from jumping or falling
    position.y += velocity.y;
    if (!onGround)
    {
        velocity.y += 0.15f; // Gravity pulls down
    }

    // Land on the floor
    if (position.y >= FLOOR_Y)
    {
        position.y = FLOOR_Y;
        velocity.y = 0;
        if (currentAction != "Walk" && currentAction != "Attack" && currentAction != "Hurt" && currentAction != "Death")
        {
            currentAction = "Idle"; // Stand still when landed
        }
        onGround = true;
    }
    else
    {
        onGround = false;
    }

    if (isAttacking && currentAction == "Attack")
    {    
        // Control when the attack can hit
        attackTimer += deltaTime;      
        // Hitbox is active only during the middle of the attack
        if (attackTimer >= 0.1f && attackTimer < 0.3f)
        {
            hitBoxActive = true;
            updateHitBox(); // Place hitbox in front of player
        }
        else
        {
            hitBoxActive = false;
        }
        // Attack animation finished
        if (attackTimer >= 0.6f)
        {
            currentAction = "Idle";
            isAttacking = false;
            hitBoxActive = false;
            attackTimer = 0.0f;
        }
    }    

    //  Hurt animation timing
    if (currentAction == "Hurt")
    {
        attackTimer += deltaTime;
        if (attackTimer >= 0.35f)
        {
            currentAction = onGround ? "Idle" : "Jump";
            attackTimer = 0.0f;
        }
    }

    //Death animation plays once and stops on last frame
    if (currentAction == "Death")
    {
        if (animations["Death"].currentFrame < 7)  // 7th frame of 8 
            animations["Death"].update(deltaTime);
    }
    else
    {
        animations[currentAction].update(deltaTime);
    }

    updateCollisionBoxes();
    Character::update(deltaTime);
}

sf::Sprite PlayerTwo::getSprite() const
{
    sf::Sprite sprite = animations.at(currentAction).getSprite();
    sprite.setPosition(position);

    if (facingRight)
    {
        sprite.setScale(2.f, 2.f);
    }
    else
    {
        sprite.setScale(-2.f, 2.f);
    }

    sprite.setOrigin(32.f, 32.f);
    return sprite;
}

// Places the attack hitbox in front of the player depending on direction
void PlayerTwo::updateHitBox()
{
    if (facingRight)
    {
        hitBox.left = position.x + 10;
        hitBox.top = position.y - 20;
    }
    else
    {
        hitBox.left = position.x - 60;
        hitBox.top = position.y - 20;
    }
    hitBox.width = 50;
    hitBox.height = 30;
}