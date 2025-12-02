/*
    NOTE ABOUT AI:
    Some of the  comments in this section were generated with
    the assistance of a  AI tool (ChatGPT) to help  teammates
    better understand the code structure and logic.
    All implementation and final decisions were made by my hands.
*/


#include "PlayerOne.h"
#include <iostream>

using std::cout;
using std::endl;

// Constructor: Initialize the Skeleton character
PlayerOne::PlayerOne()
{
    // Basic attributes
    name = "Skeleton";
    health = 100.0;
    maxHealth = 100.0;

    // Set initial position on the ground
    position = sf::Vector2f(100.f, FLOOR_Y);

    // Velocity is unused since we are grounded
    velocity = sf::Vector2f(0.f, 0.f);

    facingRight = true;

    // Load animations from files
    animations["Idle"].loadFromFile("Assets/PlayerOne/Skeleton/Idle.png", 10, 64, 64);
    animations["Walk"].loadFromFile("Assets/PlayerOne/Skeleton/Walk.png", 10, 64, 64);
    animations["Attack"].loadFromFile("Assets/PlayerOne/Skeleton/Attack.png", 6, 64, 64);

    currentAction = "Idle";
}

// -------------------------
// MOVEMENT FUNCTIONS
// -------------------------

void PlayerOne::moveLeft()
{
    // Move character left
    position.x = position.x - 0.15f;

    // Face left
    facingRight = false;

    // Change animation to walking
    if (!isAttacking) {
        currentAction = "Walk";
    }
    
}

void PlayerOne::moveRight()
{
    // Move character right
    position.x = position.x + 0.15f;

    // Face right
    facingRight = true;

    // Change animation to walking
    if (!isAttacking) {
        currentAction = "Walk";
    }
}

// -------------------------
// COMBAT FUNCTIONS
// -------------------------

void PlayerOne::attack()
{
    if (!isAttacking) {
        // Print attack message
        cout << name << " attacks quickly!" << endl;

        // Set attack animation
        currentAction = "Attack";
        
        //Set attack flags
        isAttacking = true;
        attackTimer = 0.0f;
        hasHitThisAttack = false;
        animations[currentAction].reset();
    }


    // Damage logic can be handled elsewhere
}

void PlayerOne::takeDamage(int damage)
{
    // Reduce health by damage amount
    health = health - damage;

    // Prevent health from going below 0
    if (health < 0.0)
    {
        health = 0.0;
    }

    // Print remaining health
    cout << name << " takes " << damage << " damage, Health now: " << health << endl;
}

// -------------------------
// ANIMATION AND UPDATE
// -------------------------

void PlayerOne::update(float deltaTime)
{
    // Keep character on the ground
    position.y = FLOOR_Y;

    // Update current animation
    animations[currentAction].update(deltaTime);

    //// Reset attack to Idle after it finishes
    //if (currentAction == "Attack")
    //{
    //    static float attackTimer = 0.0f;

    //    // Add elapsed time
    //    attackTimer = attackTimer + deltaTime;

    //    // Check if attack duration is over
    //    if (attackTimer >= 0.3f)  // quick attack
    //    {
    //        currentAction = "Idle";
    //        attackTimer = 0.0f;
    //    }
    //}

    if (isAttacking && currentAction == "Attack") {
        attackTimer = attackTimer + deltaTime;
        
        if (attackTimer >= 0.1f && attackTimer < 0.3f) {
            hitBoxActive = true;
            updateHitBox();
        }
        else {
            hitBoxActive = false;
        }
        if (attackTimer >= 0.6f) {
            currentAction = "Idle";
            isAttacking = false;
            hitBoxActive = false;
            attackTimer = 0.0f;
        }
    }

    updateCollisionBoxes();
}

// -------------------------
// GET SPRITE FOR DRAWING
// -------------------------

sf::Sprite PlayerOne::getSprite() const
{
    // Get current animation frame
    sf::Sprite sprite = animations.at(currentAction).getSprite();

    // Set position
    sprite.setPosition(position);

    // Set scale depending on facing direction
    if (facingRight)
    {
        sprite.setScale(2.0f, 2.0f);
    }
    else
    {
        sprite.setScale(-2.0f, 2.0f);
    }

    // Set origin to center
    sprite.setOrigin(32, 32);

    return sprite;
}

//Updates hitbox based on the direction the character is facing
void PlayerOne::updateHitBox() {
    //Hitbox to the right
    if (facingRight) {
        hitBox.left = position.x + 10;
        hitBox.top = position.y - 20;
        hitBox.width = 50;
        hitBox.height = 30;
    }
    else { //Hitbox to the left
        hitBox.left = position.x - 60;
        hitBox.top = position.y - 20;
        hitBox.width = 50;
        hitBox.height = 30;
    }
}
