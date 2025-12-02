/*
    NOTE ABOUT AI:
    Some of the  comments in this section were generated with
    the assistance of a  AI tool (ChatGPT) to help  teammates
    better understand the code structure and logic.
    All implementation and final decisions were made by my hands.
*/

#include <SFML/Graphics.hpp>
#include "PlayerOne.h"
#include "PlayerTwo.h"

int main()
{
    // Create a window for the game
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Fighter Test");

    // Create player objects
    PlayerOne player1;
    PlayerTwo player2;

    // Clock to calculate deltaTime for animations and movement
    sf::Clock clock;

    // Main game loop
    while (window.isOpen())
    {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if the user clicks the close button
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Calculate delta time since last frame
        float deltaTime = clock.restart().asSeconds();

        // -------------------------
        // PlayerOne Controls (WASD)
        // -------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            player1.moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            player1.moveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player1.attack();
        }

        // -------------------------
        // PlayerTwo Controls (Arrow keys)
        // -------------------------
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player2.moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player2.moveRight();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        {
            player2.attack();
        }

        // Update players (animations, landing logic, etc.)
        player1.update(deltaTime);
        player2.update(deltaTime);

        //Prevent players from walking through eachother
        player1.resolveCollision(player2);

        //Check if player 1 hit player 2
        if (player1.isHitting(player2) && !player1.getHasHitThisAttack()) {
            player2.takeDamage(10);
            player1.setHasHitThisAttack(true);
        }

        //Check if player 2 hit player 1
        if (player2.isHitting(player1) && !player2.getHasHitThisAttack()) {
            player1.takeDamage(15);
            player2.setHasHitThisAttack(true);
        }

        // Clear the window with black color
        window.clear(sf::Color::Black);

        // Draw both players
        window.draw(player1.getSprite());
        window.draw(player2.getSprite());

        // Display the updated frame
        window.display();
    }

    return 0;
}
