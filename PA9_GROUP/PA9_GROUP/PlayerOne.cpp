/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/
#include "PlayerOne.h"
#include <iostream>
using std::cout;
using std::endl;

// Sets up Player One (the skeleton character)
PlayerOne::PlayerOne()
{
    name = "Skeleton(Player1)";
    position = sf::Vector2f(100.f, FLOOR_Y);
    velocity = sf::Vector2f(0.f, 0.f);
    facingRight = true;

    // Load all animations from image files
    animations["Idle"].loadFromFile("Assets/PlayerOne/Skeleton/Idle.png", 10, 64, 64);
    animations["Walk"].loadFromFile("Assets/PlayerOne/Skeleton/Walk.png", 10, 64, 64);
    animations["Attack"].loadFromFile("Assets/PlayerOne/Skeleton/Attack.png", 6, 64, 64);
    animations["Jump"].loadFromFile("Assets/PlayerOne/Skeleton/Jump.png", 1, 64, 64);
    animations["Hurt"].loadFromFile("Assets/PlayerOne/Skeleton/Hurt.png", 4, 64, 64);
    animations["Death"].loadFromFile("Assets/PlayerOne/Skeleton/Death.png", 8, 64, 64);

    currentAction = "Idle"; // Start standing still
    healthBarForeground.setFillColor(sf::Color(0, 150, 255)); // Blue health bar for Player 1
}

// Move left (A key)
void PlayerOne::moveLeft()
{
    if (health <= 0)
    {
        return;
    }
    position.x -= 0.15f;
    facingRight = false;
    if (!isAttacking && currentAction != "Hurt")
    {
        currentAction = "Walk";
    }
}

// Move right (D key)
void PlayerOne::moveRight()
{
    if (health <= 0)
    {
        return;
    }
    position.x += 0.15f;
    facingRight = true;
    if (!isAttacking && currentAction != "Hurt")
    {
        currentAction = "Walk";
    }
}

// Jump (W key) 
void PlayerOne::moveJump()
{
    if (health <= 0 || !onGround)
    {
        return;
    }
    velocity.y = -15.0f; // Jump up
    currentAction = "Jump";
    onGround = false;
}

// Start an attack (Space key)
void PlayerOne::attack()
{
    if (health <= 0 || isAttacking)
    {
        return;
    }
    cout << name << " attacks!" << endl;
    currentAction = "Attack";
    isAttacking = true;
    attackTimer = 0.0f;
    hasHitThisAttack = false; // Can hit again this attack
    animations[currentAction].reset(); // Restart attack animation
}

// Take damage when hit
void PlayerOne::takeDamage(int damage)
{
    if (health <= 0)
    {
        return;
    }

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

// Runs every frame - handles movement, animation, and attack timing
void PlayerOne::update(float deltaTime)
{
    // Move up/down from jumping or falling
    position.y += velocity.y;
    if (!onGround)
    {
        velocity.y += 0.10f; // Gravity pulls down
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

    // Control when the attack can hit
    if (isAttacking && currentAction == "Attack")
    {
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
        if (animations["Death"].currentFrame < 7)   // 7th frame of 8 
        {
            animations["Death"].update(deltaTime);
        }
    }
    else
    {
        animations[currentAction].update(deltaTime);
    }

    updateCollisionBoxes();
    Character::update(deltaTime);
}

// Returns the current sprite with correct position and flip
sf::Sprite PlayerOne::getSprite() const
{
    sf::Sprite sprite = animations.at(currentAction).getSprite();
    sprite.setPosition(position);

    if (facingRight)
    {
        sprite.setScale(2.f, 2.f);     // Normal size, facing right
    }
    else
    {
        sprite.setScale(-2.f, 2.f);    // Flipped horizontally, facing left
    }

    sprite.setOrigin(32.f, 32.f);      // Center of the 64x64 image
    return sprite;
}

// Places the attack hitbox in front of the player depending on direction
void PlayerOne::updateHitBox()
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