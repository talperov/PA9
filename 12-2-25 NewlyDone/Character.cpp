/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#include "Character.hpp"

// Sets up a new character with starting values
Character::Character()
{
    // Start on the ground at the left side
    position = sf::Vector2f(0.0f, FLOOR_Y);
    velocity = sf::Vector2f(0.0f, 0.0f);

    // Full health at the start
    health = 100;
    maxHealth = 100;

    // Starts on the ground and not attacking
    onGround = true;
    isAttacking = false;
    attackTimer = 0.0f;
    hitBoxActive = false;

    // Set up basic collision and hit boxes
    collisionBox = FloatRect(0, 0, 40, 80);   // Main solid box
    hurtBox = FloatRect(0, 0, 40, 80);        // Area that can be hit
    hitBox = FloatRect(0, 0, 50, 30);         // Attack hit area

    // Health bar background (dark gray)
    healthBarBackground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50));

    // Health bar foreground (red for now, PlayerTwo may change it)
    healthBarForeground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarForeground.setFillColor(sf::Color::Red);
}

// Runs every frame to move and update the character
void Character::update(float dt)
{
    // Make character fall faster each frame
    velocity.y += GRAVITY;

    // Move character based on speed
    position.x += velocity.x;
    position.y += velocity.y;

    // Stop at the floor
    if (position.y >= FLOOR_Y)
    {
        position.y = FLOOR_Y;
        velocity.y = 0.0f;
        onGround = true;
    }
    else
    {
        onGround = false;   // In the air
    }

    // Put the sprite in the right place
    bodySprite.setPosition(position);

    // Move all hitboxes to match new position
    updateCollisionBoxes();

    // Make health bar shorter when hurt
    float healthPercent = static_cast<float>(health) / static_cast<float>(maxHealth);
    if (healthPercent < 0) healthPercent = 0;
    {
        healthBarForeground.setSize(sf::Vector2f(200.f * healthPercent, 20.f));
    }
}

// Moves all hitboxes and hurtboxes to the character's current position
void Character::updateCollisionBoxes()
{
    collisionBox.left = position.x - 20;
    collisionBox.top = position.y - 40;
    collisionBox.width = 40;
    collisionBox.height = 80;

    hurtBox.left = position.x - 18;
    hurtBox.top = position.y - 38;
    hurtBox.width = 36;
    hurtBox.height = 76;
}

// Checks if this character's attack is hitting another character
bool Character::isHitting(const Character& other) const
{
    if (!hitBoxActive)              // No attack active = no hit
    {
        return false;
    }
    return hitBox.intersects(other.getHurtBox());
}

// Pushes characters apart so they don't get stuck inside each other
void Character::resolveCollision(Character& other)
{
    FloatRect thisBox = getCollisionBox();
    FloatRect otherBox = other.getCollisionBox();

    if (thisBox.intersects(otherBox))
    {
        // Figure out how much they overlap on left or right
        float overlapLeft = (thisBox.left + thisBox.width) - otherBox.left;
        float overlapRight = (otherBox.left + otherBox.width) - thisBox.left;

        if (overlapLeft < overlapRight)
        {
            position.x -= overlapLeft / 2.f;    // Push this character left
            other.position.x += overlapLeft / 2.f; // Push other right
        }
        else
        {
            position.x -= overlapRight / 2.f;
            other.position.x += overlapRight / 2.f;
        }

        // Update boxes again after moving
        updateCollisionBoxes();
        other.updateCollisionBoxes();
    }
}

// Places the health bar above the character
void Character::setHealthBarPosition(sf::Vector2f pos)
{
    healthBarBackground.setPosition(pos);
    healthBarForeground.setPosition(pos);
}

// Draws the health bar on screen
void Character::drawHealthBar(sf::RenderWindow& window)
{
    window.draw(healthBarBackground);
    window.draw(healthBarForeground);
}