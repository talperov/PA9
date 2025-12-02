/*
As the rubric stated we were allowed to use AI to better our code, in order to better our code, we
used Generative AI (Grok) to add comments on our functions and variables so the reader of the code, or
writer themselves can easily understand what is going on in it.
*/

#include <SFML/Graphics.hpp>
#include "PlayerOne.h"
#include "PlayerTwo.h"

int main()
{
    // Create the game window (800x600 pixels)
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Retro Fighter Game");

    // Create the two players
    PlayerOne player1;
    PlayerTwo player2;

    // Place health bars: Player 1 on the left top, Player 2 on the right top
    player1.setHealthBarPosition(sf::Vector2f(20.f, 20.f));
    player2.setHealthBarPosition(sf::Vector2f(580.f, 20.f));

    sf::Clock clock;   // Used to measure how much time passed each frame

    // Main game loop - runs until the window is closed
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();   // Close button pressed - exit game
            }
        }

        // Get how much time passed since last frame (for smooth movement)
        float deltaTime = clock.restart().asSeconds();

        // -------------------- Player 1 Controls --------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player1.moveLeft();          // A = move left
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player1.moveRight();         // D = move right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            player1.moveJump();          // W = jump
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player1.attack();            // Space = attack
        }

        // -------------------- Player 2 Controls --------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player2.moveLeft();          // Left Arrow = move left
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player2.moveRight();         // Right Arrow = move right
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player2.moveJump();          // Up Arrow = jump
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            player2.attack();            // Right Control = attack
        }

        // Update both players (movement, animation, gravity)
        player1.update(deltaTime);
        player2.update(deltaTime);

        // Stop players from walking through each other
        player1.resolveCollision(player2);

        // Check if Player 1 hits Player 2 (and hasn't hit already this attack)
        if (player1.isHitting(player2) && !player1.getHasHitThisAttack())
        {
            player2.takeDamage(15);      // Player 2 loses 15 health
            player1.setHasHitThisAttack(true); // Prevent hitting again same attack
        }

        // Check if Player 2 hits Player 1
        if (player2.isHitting(player1) && !player2.getHasHitThisAttack())
        {
            player1.takeDamage(15);      // Player 1 loses 15 health
            player2.setHasHitThisAttack(true);
        }

        // Clear screen with black color
        window.clear(sf::Color::Black);

        // Draw both characters and their health bars
        window.draw(player1.getSprite());
        window.draw(player2.getSprite());
        player1.drawHealthBar(window);
        player2.drawHealthBar(window);

        // Show everything on screen
        window.display();
    }

    return 0;   // Game ended successfully
}