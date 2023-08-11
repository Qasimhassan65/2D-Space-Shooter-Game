
#ifndef ADDON_H
#define ADDON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Addon
{

public:
	sf::Texture tex;
	sf::Sprite sprite;
    float speed;
    float x,y;

	sf::SoundBuffer sfx;
    sf::Sound Sfx;

		

    Addon()
    {

    }

    void setpos(float posx,float posy)
    {
        this->sprite.setPosition(posx,posy);
      
    }

	float get_x()
	{
		return sprite.getPosition().x;
	}

	float get_y()
	{
		return sprite.getPosition().y;
	}

	void fall()
	{
		float delta_x = 0, delta_y = +0.7;
		sprite.move(delta_x, delta_y);
	}

	
};

#endif