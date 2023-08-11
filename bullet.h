
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Bullet
{

public:
	sf::Texture tex;
	sf::Sprite sprite;
	float speed;
	float x, y;


    Bullet()
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

	void setbullet(std::string png_path)
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
        sprite.scale(0.8,0.8);
		sprite.setTexture(tex, false);
		this->x = x;
		this->y = y;
		this->speed = speed;
		this->sprite.setPosition(posx, posy);
	}

	void updatebullet(int a)
	{
		if(a == 1)
		{
			float delta_x = 0, delta_y = -4.5;
			// delta_x *= speed;
			// delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0)
			{
				delta_x = this->x;
				delta_y = this->y;
				// delta_x *= speed;
				// delta_y *= speed;
				sprite.setPosition(delta_x - 10.f, delta_y - 100.f);
			}
		}

		else if(a == 2)
		{
			float delta_x = 0, delta_y = -3;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
			{
				delta_x = this->x;
				delta_y = this->y;
				delta_x *= speed;
				delta_y *= speed;
				sprite.setPosition(delta_x, delta_y);
			}
		}

		else if(a == 3)
		{
			float delta_x = 3, delta_y = -3;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
			{
				delta_x = this->x;
				delta_y = this->y;
				delta_x *= speed;
				delta_y *= speed;
				sprite.setPosition(delta_x, delta_y);
			}
		}

		else if(a == 4)
		{
			float delta_x = 4, delta_y = -3;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
			{
				delta_x = this->x;
				delta_y = this->y;
				delta_x *= speed;
				delta_y *= speed;
				sprite.setPosition(delta_x, delta_y);
			}
		}

		else if(a == 5)
		{
			float delta_x = -3, delta_y = -3;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
			{
				delta_x = this->x;
				delta_y = this->y;
				delta_x *= speed;
				delta_y *= speed;
				sprite.setPosition(delta_x, delta_y);
			}
		}

		else if(a == 6)
		{
			float delta_x = -4, delta_y = -3;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
			
			if(this->sprite.getPosition().y < 0 || this->sprite.getPosition().x < 0 || this->sprite.getPosition().x > 780)
			{
				delta_x = this->x;
				delta_y = this->y;
				delta_x *= speed;
				delta_y *= speed;
				sprite.setPosition(delta_x, delta_y);
			}
		}

		else if(a == 7)
		{
			float delta_x = 0, delta_y = +1;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
		}

		else if(a == 8)
		{
			float delta_x = -5, delta_y = +5;
			sprite.move(delta_x, delta_y);
			
		}

		else if(a == 9)
		{
			float delta_x = 5, delta_y = +5;
			sprite.move(delta_x, delta_y);
			
		}

		else if(a == 10)
		{
			float delta_x = 0, delta_y = +5;
			delta_x *= speed;
			delta_y *= speed;
			sprite.move(delta_x, delta_y);
		}


	}

	void wrapbullet(float x, float y)
	{
		float delta_x = x;
		float delta_y = y;
		delta_x *= speed;
		delta_y *= speed;
		sprite.setPosition(delta_x , delta_y - 100.f);
	}

};

#endif