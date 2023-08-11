
#ifndef BULLETFIRE_H
#define BULLETFIRE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bulletfire
{

public:
	sf::Texture tex;
	sf::Sprite sprite;
	float speed;
	float x, y;


    Bulletfire()
    {

    }

    void set_x(float posx)
    {
        this->x = posx;
      
    }

    void set_y(float posy)
    {
        this->y = posy;
    }

	void setbulletfire(std::string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
	}

	float get_x()
	{
		return sprite.getPosition().x;
	}

	float get_y()
	{
		return sprite.getPosition().y;
	}

	void setter(std::string png_path,float posx, float posy, float x, float y, float speed)
	{	
		tex.loadFromFile(png_path);
        sprite.scale(0.37,0.37);
		sprite.setTexture(tex, false);
		this->x = x;
		this->y = y;
		this->speed = speed;
		this->sprite.setPosition(posx, posy);
	}

	void updatebulletfire()
	{
		float delta_x = 0, delta_y = -10;
		delta_x *= speed;
		delta_y *= speed;
		sprite.move(delta_x, delta_y);
		
		if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
		{
			delta_x = this->x+5.f;
			delta_y = this->y;
			delta_x *= speed;
			delta_y *= speed;
			sprite.setPosition(delta_x, delta_y);
		}
	}

	void wrapbullet(float x, float y)
	{
		float delta_x = x;
		float delta_y = y;
		delta_x *= speed;
		delta_y *= speed;
		sprite.setPosition(delta_x, delta_y);
	}

};

#endif