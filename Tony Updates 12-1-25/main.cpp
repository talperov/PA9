#include <SFML/Graphics.hpp>
#include "PlayerOne.h"
#include "PlayerTwo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Fighter Test");

    PlayerOne player1;
    PlayerTwo player2;

    // Set health bar positions
    player1.setHealthBarPosition(sf::Vector2f(20.f, 20.f));
    player2.setHealthBarPosition(sf::Vector2f(580.f, 20.f));

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // PlayerOne Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player1.moveLeft();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player1.moveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player1.moveJump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player1.attack();

        // PlayerTwo Controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player2.moveLeft();
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player2.moveRight();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player2.moveJump();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
            player2.attack();

        // Update
        player1.update(deltaTime);
        player2.update(deltaTime);

        player1.resolveCollision(player2);

        if (player1.isHitting(player2) && !player1.getHasHitThisAttack())
        {
            player2.takeDamage(10);
            player1.setHasHitThisAttack(true);
        }

        if (player2.isHitting(player1) && !player2.getHasHitThisAttack())
        {
            player1.takeDamage(15);
            player2.setHasHitThisAttack(true);
        }

        window.clear(sf::Color::Black);

        window.draw(player1.getSprite());
        window.draw(player2.getSprite());

        player1.drawHealthBar(window);
        player2.drawHealthBar(window);

        window.display();
    }

    return 0;
}
