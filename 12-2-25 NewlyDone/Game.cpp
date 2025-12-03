#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include "Character.hpp"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "Game.hpp"

// Helper: basic platform collision so players can land on the jump-up
static void handlePlatformCollision(Character& player, float prevY, const sf::RectangleShape& platform)
{
    // Platform bounds
    sf::FloatRect platBounds = platform.getGlobalBounds();

    // Current collision box
    sf::FloatRect boxNow = player.getCollisionBox();

    // Where the feet are now
    float feetNow = boxNow.top + boxNow.height;

    // Where the feet were last frame (approx, using change in y position)
    float dy = player.position.y - prevY;
    float feetPrev = feetNow - dy;

    // Simple horizontal overlap check with platform
    bool horizontalOverlap =
        boxNow.left < platBounds.left + platBounds.width &&
        boxNow.left + boxNow.width > platBounds.left;

    // Only land on platform when falling down
    bool movingDown = player.velocity.y > 0.f;

    // Check if we crossed the top of the platform between frames
    if (movingDown && horizontalOverlap &&
        feetPrev <= platBounds.top && feetNow >= platBounds.top)
    {
        // Snap feet to the top of the platform
        float correction = feetNow - platBounds.top;
        player.position.y -= correction;

        // Stop falling
        player.velocity.y = 0.f;

        // Update collision box after we moved the player
        player.updateCollisionBoxes();
    }
}

void runGame()
{
    // Main game window
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Fighter - Simple Stage");

    // --- Players ---
    PlayerOne player1;
    PlayerTwo player2;

    // Health bar positions (already wired in your Character class)
    player1.setHealthBarPosition(sf::Vector2f(20.f, 20.f));     // top-left
    player2.setHealthBarPosition(sf::Vector2f(800.f - 220.f, 20.f)); // top-right-ish

    // --- Background / Stage ---

    // Full background (just a dark color)
    sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setPosition(0.f, 0.f);
    background.setFillColor(sf::Color(20, 20, 40)); // dark blue-ish

    // Ground: matches FLOOR_Y from Character.hpp (472.f)
    sf::RectangleShape ground;
    ground.setSize(sf::Vector2f(800.f, 600.f - FLOOR_Y));
    ground.setPosition(0.f, FLOOR_Y);
    ground.setFillColor(sf::Color(60, 40, 20)); // brown-ish

    // Jump-up platform in the middle of the stage
    // Top of the platform at y = 400 so the players can reach it with your jump
    sf::RectangleShape midPlatform;
    midPlatform.setSize(sf::Vector2f(220.f, 20.f));
    midPlatform.setPosition(290.f, 400.f);  // centered-ish
    midPlatform.setFillColor(sf::Color(100, 80, 40));

    sf::Clock clock;

    while (window.isOpen())
    {
        // --- Event handling ---
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Save previous Y so we can tell if we crossed a platform this frame
        float prevY1 = player1.position.y;
        float prevY2 = player2.position.y;

        // --- Player controls ---

        // Player 1 (WASD + Space)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player1.moveLeft();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player1.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player1.moveJump();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player1.attack();

        // Player 2 (Arrow keys + Right Ctrl)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player2.moveLeft();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player2.moveRight();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player2.moveJump();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            player2.attack();

        // --- Update characters (movement, gravity, animations, etc.) ---
        player1.update(deltaTime);
        player2.update(deltaTime);

        // Characters bump into each other
        player1.resolveCollision(player2);

        // Landing on the middle platform (jump-up)
        handlePlatformCollision(player1, prevY1, midPlatform);
        handlePlatformCollision(player2, prevY2, midPlatform);

        // --- Hit detection (same as you had) ---

        // P1 hitting P2
        if (player1.isHitting(player2) && !player1.getHasHitThisAttack())
        {
            player2.takeDamage(10);
            player1.setHasHitThisAttack(true);
        }

        // P2 hitting P1
        if (player2.isHitting(player1) && !player2.getHasHitThisAttack())
        {
            player1.takeDamage(15);
            player2.setHasHitThisAttack(true);
        }

        // --- Drawing ---

        window.clear();

        // Draw background and stage first
        window.draw(background);
        window.draw(ground);
        window.draw(midPlatform);

        // Then draw players
        window.draw(player1.getSprite());
        window.draw(player2.getSprite());

        // Then health bars so they stay on top
        player1.drawHealthBar(window);
        player2.drawHealthBar(window);

        window.display();
    }

}

