#include <SFML/Graphics.hpp>
#include <iostream>
#include <deque>

using namespace sf;

int main()
{
    // create a window object with dimensions of 600x600 pixels and a title of "SFML Snake Game"
    RenderWindow window(VideoMode(800, 600), "Snake Game");


    // create a deque container to hold the snake's body rectangles
    std::deque<RectangleShape> snake;

    // create the head of the snake, set its color to green, and place it in the center of the window
    RectangleShape head(Vector2f(20, 20));
    head.setFillColor(Color::Black);
    head.setPosition(400, 300);

    // add the head to the back of the snake container
    snake.push_back(head);

    // create the food rectangle, set its color to red, and place it in a random location in the window
    RectangleShape food(Vector2f(20, 20));
    food.setFillColor(Color::Green);
    food.setPosition(200, 200);

     // create a vector to represent the direction of the snake's movement
    Vector2f direction(1, 0);

    // Initialize clock and timer for snake movement delay
    Clock clock;
    float timer = 0;
    float delay = 0.1;

    // Get the dimensions of the window
    const int windowWidth = window.getSize().x;
    const int windowHeight = window.getSize().y;

    while (window.isOpen())
    {
        // Update timer and handle events
        timer += clock.restart().asSeconds();

        Event event;
        while (window.pollEvent(event))
        {

            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (event.type == Event::KeyPressed)
            {
                // Change direction of snake based on arrow key pressed
                if (event.key.code == Keyboard::Left && direction.x != 1)
                {
                    direction = Vector2f(-1, 0);
                }
                else if (event.key.code == Keyboard::Right && direction.x != -1)
                {
                    direction = Vector2f(1, 0);
                }
                else if (event.key.code == Keyboard::Up && direction.y != 1)
                {
                    direction = Vector2f(0, -1);
                }
                else if (event.key.code == Keyboard::Down && direction.y != -1)
                {
                    direction = Vector2f(0, 1);
                }
            }
        }



        // Check if the head of the snake is outside the window boundaries
        if (snake.front().getPosition().x < 0 ||
            snake.front().getPosition().x + snake.front().getSize().x > windowWidth ||
            snake.front().getPosition().y < 0 ||
            snake.front().getPosition().y + snake.front().getSize().y > windowHeight)
        {
            std::cout << "Game over!" << std::endl;
            window.close();
        }

        // Move snake if enough time has elapsed
        if (timer > delay)
        {
            timer = 0;

            // Calculate new position of snake head based on current direction
            Vector2f prevPosition = snake.front().getPosition();
            prevPosition.x += direction.x * 20;
            prevPosition.y += direction.y * 20;

            // Create new green rectangle to be the new head of the snake
            RectangleShape newHead(Vector2f(20, 20));
            newHead.setFillColor(Color::Black);
            newHead.setPosition(prevPosition);

            // Check if snake has eaten the food
            if (prevPosition == food.getPosition())
            {
             // Generate new random position for food
               food.setPosition((rand() % 39 + 1) * 20, (rand() % 29 + 1) * 20);
            }
            else
            {
                // Remove the tail of the snake since it hasn't eaten the food
                snake.pop_back();
            }

            // Check if snake has collided with itself
            for (auto it = snake.begin(); it != snake.end(); ++it)
            {
                if (newHead.getGlobalBounds().intersects(it->getGlobalBounds()))
                {
                    std::cout << "Game over!" << std::endl;
                    window.close();
                }
            }

            // Add new head to the front of the snake deque
            snake.push_front(newHead);
        }

        window.clear(Color(173, 216, 230));
        window.draw(food);

        for (auto it = snake.begin(); it != snake.end(); ++it)
        {
            window.draw(*it);
        }

        window.display();
    }

    return 0;
}
