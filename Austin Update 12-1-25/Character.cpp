/*
    NOTE ABOUT AI:
    Some of the  comments in this section were generated with
    the assistance of a  AI tool (ChatGPT) to help  teammates
    better understand the code structure and logic.
    All implementation and final decisions were made by my hands.
*/

#include "Character.hpp"

// -------------------------
// Constructor
// -------------------------
Character::Character()
{
    // Set initial position on the ground
    position = sf::Vector2f(0.0f, FLOOR_Y);

    // Initial velocity (unused if always grounded)
    velocity = sf::Vector2f(0.0f, 0.0f);

    // Set health
    health = 100;
    maxHealth = 100;

    // Start on the ground
    onGround = true;

    //Attack state
    isAttacking = false;
    attackTimer = 0.0f;
    hitBoxActive = false;

    //Collision boxes
    collisionBox = FloatRect(0, 0, 40, 80);
    hurtBox = FloatRect(0, 0, 40, 80);
    hitBox = FloatRect(0, 0, 50, 30);
}

// -------------------------
// Update character position
// -------------------------
void Character::update(float dt)
{
    // Apply gravity
    velocity.y = velocity.y + GRAVITY;

    // Update position based on velocity
    position.x = position.x + velocity.x;
    position.y = position.y + velocity.y;

    // Check floor collision
    if (position.y >= FLOOR_Y)
    {
        // Snap to floor
        position.y = FLOOR_Y;

        // Stop downward velocity
        velocity.y = 0.0f;

        // Character is on the ground
        onGround = true;
    }
    else
    {
        // Character is in the air
        onGround = false;
    }

    // Update sprite position
    bodySprite.setPosition(position);

    //Update collision boxes
    updateCollisionBoxes();
}

//Updates collision boxes based on a characters position
void Character::updateCollisionBoxes() {

    //Collision box for players running into eachother
    collisionBox.left = position.x - 20;
    collisionBox.top = position.y - 40;
    collisionBox.width = 40;
    collisionBox.height = 80;

    //Hurbox for players getting hit by attacks
    hurtBox.left = position.x - 18;
    hurtBox.top = position.y - 38;
    hurtBox.width = 36;
    hurtBox.height = 76;
}

//Checks if a character is hitting another
bool Character::isHitting(const Character& other) const {

    if (!hitBoxActive) {
        return false;
    }

    return hitBox.intersects(other.getHurtBox());
}


void Character::resolveCollision(Character& other) {
    FloatRect thisBox = getCollisionBox();
    FloatRect otherBox = other.getCollisionBox();

    if (thisBox.intersects(otherBox)) {
        
        float overlapLeft = (thisBox.left + thisBox.width) - otherBox.left;
        float overlapRight = (otherBox.left + otherBox.width) - thisBox.left;

        if (overlapLeft < overlapRight) {
            position.x = position.x - (overlapLeft / 2.0f);
            other.position.x = other.position.x + (overlapLeft / 2.0f);
        }
        else {
            position.x = position.x - (overlapRight / 2.0f);
            other.position.x = other.position.x + (overlapRight / 2.0f);
        }

        updateCollisionBoxes();
        other.updateCollisionBoxes();
    }
}