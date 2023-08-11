
#ifndef PLAYERFIRE_H
#define PLAYERFIRE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Addon.h"
#include <iostream>
using namespace std;

class Playerfire : public Addon
{

public:

    bool  fire_released;
    bool  collided;
    bool  fire_stop;

    Playerfire()
    {
        fire_released = 0;
        collided = 0;
        fire_stop = 0;
    }

	void setter(float posx, float posy, float x, float y, float speed)
	{
		tex.loadFromFile("img/fire.png");
        sprite.scale(0.34,0.34);
		sprite.setTexture(tex, false);
		this->speed = speed;
		this->sprite.setPosition(posx, posy);
	}

    bool check_collision(float posx,float posy)
    {
       
        float temp_px = +80.f;
        float temp_mx = -80.f;
        posx = posx - sprite.getPosition().x;
       
        if (  (posx <= temp_px && posx >= temp_mx) &&  ( posy - sprite.getPosition().y  <= +80.f  && posy - sprite.getPosition().y >= -80.f) )
        {
            sprite.setPosition(-1000.f, -1000.f);
            collided = 1;
            return true;
        }
        else
            return false;
    }

};

#endif