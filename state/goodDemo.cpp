/*
Better code
Insight: When you have a handful of flags where only one is true at a time, that’s a hint that what you have are states 
that can be represented through enums (the GoodDemo represents states using classes)
Instead of switching on the inputs in handleInput, we actually switch on the states, which is more intuitive. 
Samething in update(), we also switch on the states. This allows us to see how exactly the 
states are changing what to render. Conversely, in badDemo, this is often implicit
*/

#include <SFML/Graphics.hpp>
#include <iostream>

enum State
{
    STATE_GROUND,
    STATE_JUMPING,
    STATE_CROUCHING,
    STATE_DIVING
};

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
        switch (state_)
        {
        case STATE_GROUND:
            if (mIsMovingLeft)
            {
                velocity.x -= 500;
            }
            if (mIsMovingRight)
            {
                velocity.x += 500;
            }
            velocity.y = 0;
            break;
        case STATE_CROUCHING:
            break;
        case STATE_JUMPING:
            if (mIsMovingLeft)
            {
                velocity.x -= 500;
            }
            if (mIsMovingRight)
            {
                velocity.x += 500;
            }

            if (mPlayer.getPosition().y >= groundBound)
            {
                // ground state inititation code, should it go here?
                mPlayer.setPosition(mPlayer.getPosition().x, 400);
                mPlayer.setFillColor(sf::Color::Cyan);
                state_ = STATE_GROUND;
            }
            velocity.y += gravity;
            break;
        case STATE_DIVING:
            if (mPlayer.getPosition().y >= groundBound)
            {
                // ground state inititation code, should it go here?
                mPlayer.setPosition(mPlayer.getPosition().x, 400);
                mPlayer.setFillColor(sf::Color::Cyan);
                state_ = STATE_GROUND;
            }
            velocity.y += gravity * 5; // compare this to how much state jump changes y velocity.
            break;
        }

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

    // we switch on the state instead of the input!
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
    {
        switch (state_)
        {
        case STATE_GROUND:
            if (key == sf::Keyboard::A)
                mIsMovingLeft = isPressed;
            else if (key == sf::Keyboard::D)
                mIsMovingRight = isPressed;
            else if (key == sf::Keyboard::J)
            {
                velocity.y = -1000;
                state_ = STATE_JUMPING;
            }
            else if (key == sf::Keyboard::C)
            {
                mPlayer.setFillColor(sf::Color::Red);
                state_ = STATE_CROUCHING;
            }
            break;
        case STATE_CROUCHING:
            if (key == sf::Keyboard::C)
            {
                if (isPressed)
                {
                    mPlayer.setFillColor(sf::Color::Red);
                }
                else
                {
                    // on crouch release
                    // when setting state to ground, we will render player like it is on ground (has color Cyan)
                    // notice that this piece of code is in crouch, not ground
                    // we can do better in goodDemo.cpp
                    mPlayer.setFillColor(sf::Color::Cyan);
                    state_ = STATE_GROUND;
                }
            }
            break;
        case STATE_JUMPING:
            if (key == sf::Keyboard::A)
                mIsMovingLeft = isPressed;
            else if (key == sf::Keyboard::D)
                mIsMovingRight = isPressed;
            else if (key == sf::Keyboard::Space)
            {
                // diving includes initializing player to blue
                // notice that this piece of code is in the jump, not dive
                // we can do better in goodDemo.cpp
                mPlayer.setFillColor(sf::Color::Blue);
                state_ = STATE_DIVING;
            }
        case STATE_DIVING:
            if (key == sf::Keyboard::A)
                mIsMovingLeft = isPressed;
            else if (key == sf::Keyboard::D)
                mIsMovingRight = isPressed;
        }
    }

private:
    sf::RenderWindow mWindow;
    sf::CircleShape mPlayer;
    sf::Vector2f velocity;
    bool mIsMovingLeft = false, mIsMovingRight = false;
    float PlayerSpeed = 500;
    float gravity = 10;
    float groundBound = 400;      // objects should not exceed this, recall that
    State state_ = STATE_JUMPING; // start off jumping because object starts in air
};

int main()
{
    Game game;
    game.run();
}