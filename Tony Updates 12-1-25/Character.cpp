#include "Character.hpp"

// -------------------------
// Constructor
// -------------------------
Character::Character()
{
    // Initial position
    position = sf::Vector2f(0.0f, FLOOR_Y);
    velocity = sf::Vector2f(0.0f, 0.0f);

    // Health
    health = 100;
    maxHealth = 100;

    // Ground state
    onGround = true;

    // Attack state
    isAttacking = false;
    attackTimer = 0.0f;
    hitBoxActive = false;

    // Collision boxes
    collisionBox = FloatRect(0, 0, 40, 80);
    hurtBox = FloatRect(0, 0, 40, 80);
    hitBox = FloatRect(0, 0, 50, 30);

    // Health bar visuals
    healthBarBackground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarBackground.setFillColor(sf::Color(50, 50, 50));

    healthBarForeground.setSize(sf::Vector2f(200.f, 20.f));
    healthBarForeground.setFillColor(sf::Color::Red); // Default (PlayerTwo overrides this)
}

// -------------------------
// Update character
// -------------------------
void Character::update(float dt)
{
    // Gravity
    velocity.y += GRAVITY;

    // Movement update
    position.x += velocity.x;
    position.y += velocity.y;

    // Floor collision
    if (position.y >= FLOOR_Y)
    {
        position.y = FLOOR_Y;
        velocity.y = 0.0f;
        onGround = true;
    }
    else
    {
        onGround = false;
    }

    // Update sprite position
    bodySprite.setPosition(position);

    // Update collision boxes
    updateCollisionBoxes();

    // --- Update health bar size ---
    float healthPercent = static_cast<float>(health) / static_cast<float>(maxHealth);
    if (healthPercent < 0) healthPercent = 0; // Prevent negative size

    healthBarForeground.setSize(sf::Vector2f(200.f * healthPercent, 20.f));
}

// -------------------------
// Collision helpers
// -------------------------
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

bool Character::isHitting(const Character& other) const
{
    if (!hitBoxActive)
        return false;

    return hitBox.intersects(other.getHurtBox());
}

void Character::resolveCollision(Character& other)
{
    FloatRect thisBox = getCollisionBox();
    FloatRect otherBox = other.getCollisionBox();

    if (thisBox.intersects(otherBox))
    {
        float overlapLeft = (thisBox.left + thisBox.width) - otherBox.left;
        float overlapRight = (otherBox.left + otherBox.width) - thisBox.left;

        if (overlapLeft < overlapRight)
        {
            position.x -= overlapLeft / 2.f;
            other.position.x += overlapLeft / 2.f;
        }
        else
        {
            position.x -= overlapRight / 2.f;
            other.position.x += overlapRight / 2.f;
        }

        updateCollisionBoxes();
        other.updateCollisionBoxes();
    }
}

// -------------------------
// Health bar helpers
// -------------------------
void Character::setHealthBarPosition(sf::Vector2f pos)
{
    healthBarBackground.setPosition(pos);
    healthBarForeground.setPosition(pos);
}

void Character::drawHealthBar(sf::RenderWindow& window)
{
    window.draw(healthBarBackground);
    window.draw(healthBarForeground);
}
