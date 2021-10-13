/*
This is bad! 
*/

#include <SFML/Graphics.hpp>
#include <iostream>
class Game
{
public:
    Game() : mWindow(sf::VideoMode(500, 500), "SFML works!"), mPlayer()
    {
        mPlayer.setRadius(40.f);
        mPlayer.setPosition(100.f, 100.f);
        mPlayer.setFillColor(sf::Color::Cyan);
    }
    void run()
    {
        sf::Clock clock;
        while (mWindow.isOpen())
        {
            sf::Time deltaTime = clock.restart();
            processEvents();
            update(deltaTime);
            render();
        }
    }

private:
    void update(sf::Time deltaTime)
    {
        sf::Vector2f movement(0.f, 0.f);
        velocity.x = 0;
        if (mIsMovingLeft)
        {
            velocity.x -= 500;
        }

        if (mIsMovingRight)
        {
            velocity.x += 500;
        }
        if (mPlayer.getPosition().y < 400)
        {
            velocity.y += gravity; // only in the y direction should speed change over time
        }
        else
        {
            // FLAG #1: If we jumped but had no flag here,
            // first frame is still in contact with ground, thus, velocity still gets set to 0
            if (!isJumping)
            {
                velocity.y = 0;
            }
            else
            {
                // if reach ground and we were in jumping state, we aren't jumping anymore
                isJumping = false;
            }
        }

        std::cout << velocity.y << std::endl;

        mPlayer.move(velocity * deltaTime.asSeconds()); // velocity * time = distance
    }
    void render()
    {
        mWindow.clear();
        mWindow.draw(mPlayer);
        mWindow.display();
    }

    void processEvents()
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow.close();
                break;
            }
        }
    }

    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {
        if (key == sf::Keyboard::A)
            mIsMovingLeft = isPressed;
        else if (key == sf::Keyboard::D)
            mIsMovingRight = isPressed;
        else if (key == sf::Keyboard::J)
        {

            // jump
            isJumping = true; 
            velocity.y = -500;
        }
    }

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    bool mIsMovingLeft = false, mIsMovingRight = false;
    sf::Vector2f velocity;
    float PlayerSpeed = 500;
    float gravity = 9.81;
    bool isJumping = false;
};

int main()
{
    Game game;
    game.run();
}