// Most of the coments were translated using ChatGPT
#include <iostream>
#include "Character.hpp"

using std::cout;
using std::endl;

// Simple derived class used only for testing base Character logic.
class TestCharacter : public Character
{
public:
    TestCharacter()
    {
        position = sf::Vector2f(0.0f, FLOOR_Y);
        velocity = sf::Vector2f(0.0f, 0.0f);
        health = 100.0f;
        maxHealth = 100.0f;
        name = "TestChar";

        setHealthBarPosition(sf::Vector2f(0.0f, 0.0f));
        updateCollisionBoxes();
    }

    // Minimal overrides
    void moveLeft() override {}
    void moveRight() override {}
    void moveJump() override {}
    void attack() override {}

    // Simple damage logic
    void takeDamage(int damage) override
    {
        health -= damage;
        if (health < 0.0f)
        {
            health = 0.0f;
        }
    }

    // Helpers for tests
    void setPosition(float x, float y)
    {
        position.x = x;
        position.y = y;
    }

    void setVelocity(float vx, float vy)
    {
        velocity.x = vx;
        velocity.y = vy;
    }

    void forceUpdateCollisionBoxes()
    {
        updateCollisionBoxes();
    }

    FloatRect getCollisionBoxPublic() const { return collisionBox; }
    FloatRect getHurtBoxPublic() const { return hurtBox; }
    bool getOnGroundPublic() const { return onGround; }

    void setHitBoxRect(float left, float top, float width, float height)
    {
        hitBox.left = left;
        hitBox.top = top;
        hitBox.width = width;
        hitBox.height = height;
    }

    void setHurtBoxRect(float left, float top, float width, float height)
    {
        hurtBox.left = left;
        hurtBox.top = top;
        hurtBox.width = width;
        hurtBox.height = height;
    }

    void setHitBoxActive(bool active)
    {
        hitBoxActive = active;
    }

    float getHealthBarWidth() const
    {
        return healthBarForeground.getSize().x;
    }
};

// Small helper to print PASS / FAIL
bool reportResult(const std::string& testName, bool condition)
{
    if (condition)
    {
        cout << " PASS " << testName << endl;
        return true;
    }
    else
    {
        cout << " FAIL " << testName << endl;
        return false;
    }
}

// Test 1: damage should not make health negative.
bool test_takeDamage_clamps_to_zero()
{
    TestCharacter c;
    c.takeDamage(150);
    return (c.getHealth() == 0.0f);
}

// Test 2: collision and hurt boxes follow character position.
bool test_updateCollisionBoxes_matches_position()
{
    TestCharacter c;
    c.setPosition(200.0f, FLOOR_Y);
    c.forceUpdateCollisionBoxes();

    FloatRect col = c.getCollisionBoxPublic();
    FloatRect hurt = c.getHurtBoxPublic();

    bool collisionOk =
        (col.left == 200.0f - 20.0f) &&
        (col.top == FLOOR_Y - 40.0f) &&
        (col.width == 40.0f) &&
        (col.height == 80.0f);

    bool hurtOk =
        (hurt.left == 200.0f - 18.0f) &&
        (hurt.top == FLOOR_Y - 38.0f) &&
        (hurt.width == 36.0f) &&
        (hurt.height == 76.0f);

    return collisionOk && hurtOk;
}

// Test 3: isHitting depends on active hitbox and overlap.
bool test_isHitting_requires_active_and_overlap()
{
    TestCharacter attacker;
    TestCharacter defender;

    defender.setPosition(0.0f, FLOOR_Y);
    defender.forceUpdateCollisionBoxes();
    FloatRect defenderHurt = defender.getHurtBoxPublic();

    // Case 1: inactive hitbox -> false
    attacker.setHitBoxActive(false);
    attacker.setHitBoxRect(defenderHurt.left,
        defenderHurt.top,
        defenderHurt.width,
        defenderHurt.height);
    bool case1 = (attacker.isHitting(defender) == false);

    // Case 2: active + overlap -> true
    attacker.setHitBoxActive(true);
    bool case2 = (attacker.isHitting(defender) == true);

    // Case 3: active but far away -> false
    attacker.setHitBoxRect(defenderHurt.left + 1000.0f,
        defenderHurt.top,
        defenderHurt.width,
        defenderHurt.height);
    bool case3 = (attacker.isHitting(defender) == false);

    return case1 && case2 && case3;
}

// Test 4: resolveCollision moves characters apart if they overlap.
bool test_resolveCollision_separates_characters()
{
    TestCharacter a;
    TestCharacter b;

    a.setPosition(300.0f, FLOOR_Y);
    b.setPosition(310.0f, FLOOR_Y);

    a.forceUpdateCollisionBoxes();
    b.forceUpdateCollisionBoxes();

    bool initiallyIntersect =
        a.getCollisionBoxPublic().intersects(b.getCollisionBoxPublic());

    a.resolveCollision(b);

    bool finallyIntersect =
        a.getCollisionBoxPublic().intersects(b.getCollisionBoxPublic());

    return initiallyIntersect && !finallyIntersect;
}

// Test 5: update applies gravity, lands on floor, and scales health bar.
bool test_update_applies_gravity_floor_and_healthbar()
{
    TestCharacter c;

    c.setPosition(0.0f, FLOOR_Y - 100.0f);
    c.setVelocity(0.0f, 0.0f);
    c.health = 50.0f;
    c.maxHealth = 100.0f;

    for (int i = 0; i < 60; ++i)
    {
        c.update(0.016f);
    }

    float finalY = c.position.y;
    bool onFloor = (finalY == FLOOR_Y);
    bool grounded = c.getOnGroundPublic();

    // Base width is 200.f (from Character). At 50% health we expect 100.f.
    float barWidth = c.getHealthBarWidth();
    bool barOk = (barWidth == 100.0f);

    return onFloor && grounded && barOk;
}

// Run all tests and print summary.
void runAllTests()
{
    int passed = 0;
    int total = 0;

    total++; if (reportResult("Test 1: damage clamps health to 0",
        test_takeDamage_clamps_to_zero())) passed++;

    total++; if (reportResult("Test 2: collision boxes follow position",
        test_updateCollisionBoxes_matches_position())) passed++;

    total++; if (reportResult("Test 3: hit detection needs active + overlap",
        test_isHitting_requires_active_and_overlap())) passed++;

    total++; if (reportResult("Test 4: resolveCollision separates characters",
        test_resolveCollision_separates_characters())) passed++;

    total++; if (reportResult("Test 5: update handles gravity + health bar",
        test_update_applies_gravity_floor_and_healthbar())) passed++;


    cout << "TESTS PASSED: " << passed << " / " << total << endl;

}

