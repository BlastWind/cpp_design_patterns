/*
Bad Code!
Reason that this sucks: We use flags (isJumping, isCrouching, isDiving) to represent states. 
If we have N flags and the player can only set a flag to be true after checking 
the other N-1 flags (not the case here because, for example, isJumping implies !isCrouching, so, 
isDiving doesn't need to check isCrouching). Then you have to write N-1 new lines everytime a new 
flag is added! 

Additionally, notice that even some flags imply other flags, as it is in the code below,
it's taxing on the brain to keep track of it (tax on brain = more errors!) 
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
            update(deltaTime); // To improve this, use fixed timesteps: https://subscription.packtpub.com/book/game_development/9781849696845/1/ch01lvl1sec11/game-loops-and-frames
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
        if (mPlayer.getPosition().y < groundBound) // if player is in air
        {
            velocity.y += isDiving ? gravity * 5 : gravity; // only in the y direction should speed change over time
        }
        else // if player is on ground
        {
            mPlayer.setPosition(mPlayer.getPosition().x, 400); // let's make sure they are on ground and not exceeding it
            isDiving = false;
            // notice that we can't set isJumping = false every single frame that player is on ground
            // or else, the player won't actually take off (input sets isJumping to true -> update() -> player still on ground -> isJumping = false would be incorrect)
            // instead, only set isJumping = false after the player lands.
            if (isJumping)
            {
                mPlayer.setFillColor(sf::Color::Cyan);
                isJumping = false;
            }
            else
            {
                velocity.y = 0;
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

        switch (key)
        {
        case sf::Keyboard::A:
            if (!isCrouching)
                mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::D:
            if (!isCrouching)
                mIsMovingRight = isPressed;
            break;
        case sf::Keyboard::J:
            // notice that in order to decide whether or not we want to jump, we need the isCrouching variable...
            if (!isJumping && !isCrouching)
            {
                isJumping = true;
                velocity.y = -1000;
            }
            break;
        case sf::Keyboard::C:
            // notice that in order to decide whether or not we want to crouch, we need the isJumping variable...
            if (!isJumping)
            {
                isCrouching = isPressed;
                mIsMovingLeft = mIsMovingRight = false;
                mPlayer.setFillColor(isPressed ? sf::Color::Red : sf::Color::Cyan);
            }
            break;
        case sf::Keyboard::Space:
            // notice that in order to decide whether or not we can dive, we need the isJumping variable
            // also, it is easy to write more complex check conditions that are given implicit
            // e.g., below, it feels natural to write (isJumping && !isCrouching), but we can omit !isCrouching
            // because if character isJumping, then it definitely isn't crouching.
            if (isJumping)
            {
                isDiving = true;
                mPlayer.setFillColor(sf::Color::Blue);
            }
            break;
        }
    }

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    sf::Vector2f velocity;
    bool mIsMovingLeft = false, mIsMovingRight = false;
    bool isJumping = false, isCrouching = false,
         isDiving = false;
    float PlayerSpeed = 500;
    float gravity = 10;
    float groundBound = 400; // objects should not exceed this, recall that
};

int main()
{
    Game game;
    game.run();
}