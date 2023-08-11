#include <SFML/Graphics.hpp>
int main()
{
    sf::RenderWindow app(sf::VideoMode(640, 480), "Platform Physics");

    // x = wind, y = gravity
    sf::Vector2f gravity(0.f, .5f);

    sf::RectangleShape playerShape;


    playerShape.setSize(sf::Vector2f(16, 64));
    playerShape.setPosition(32, 0);
    playerShape.setFillColor(sf::Color(140, 36, 58));
    
    sf::RectangleShape floor;
    floor.setPosition(0, 324);
    floor.setSize(sf::Vector2f(640, 16));
  
    sf::Vector2f velocity;

    sf::Time jumpTime;
    sf::Time jumpMaxTime = sf::seconds(0.1f);
    sf::Clock clock;
    sf::Time lastTime;

    sf::Texture texture;
    sf::Sprite background;
    if (texture.loadFromFile("img/background2.jpg"))
    {
        texture.setRepeated(true);
        background.setTexture(texture);
    }

    

    while(app.isOpen())
    {
        sf::Time currentTime = clock.restart();
        lastTime = currentTime;

        sf::Event event;
        while(app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }


        velocity.y += gravity.y*lastTime.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // Immediate stop
            if (velocity.x > 0)
                velocity.x = 0;
            velocity.x -= .2f*lastTime.asSeconds();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // Immediate stop
            if (velocity.x < 0)
                velocity.x = 0;
            velocity.x += .2f*lastTime.asSeconds();
        }
        else
            velocity.x *= .75f;

        if (velocity.x < -MAX_VELOCITY)
            velocity.x = -MAX_VELOCITY;
        else if (velocity.x > MAX_VELOCITY)
            velocity.x = MAX_VELOCITY;
        if (velocity.y < -MAX_VELOCITY)
            velocity.y = -MAX_VELOCITY;
        else if (velocity.y > MAX_VELOCITY)
            velocity.y = MAX_VELOCITY;


        playerShape.move(velocity);

        if (playerShape.getPosition().x < 0)
            playerShape.setPosition(0, playerShape.getPosition().y);
        if (playerShape.getPosition().x + playerShape.getSize().x > app.getSize().x)
            playerShape.setPosition(app.getSize().x - playerShape.getSize().x, playerShape.getPosition().y);

        background.setOrigin(background.getLocalBounds().width/2, background.getLocalBounds().height/2);
        background.setPosition(background.getLocalBounds().width/2,  background.getLocalBounds().height/2);
        background.setTextureRect(sf::IntRect(-((playerShape.getPosition().x*.125f)), -(playerShape.getPosition().y*.25f), 640, 256));
        

       // app.clear(sf::Color::Magenta);
        app.draw(background);
        //app.draw(floor);
        app.draw(playerShape);
        app.display();
    }

    return 0;
}