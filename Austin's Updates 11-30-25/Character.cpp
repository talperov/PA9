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
}
