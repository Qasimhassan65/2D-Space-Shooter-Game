
#ifndef LIFEUP_H
#define LIFEUP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Addon.h"
#include <iostream>
using namespace std;

class Lifeup : public Addon
{

public:

    bool  lifeup_released;
    bool  collided;
    bool lifeup_stop;

    Lifeup()
    {
        lifeup_released = 0;
        collided = 0;
        lifeup_stop = 0;
        sprite.setScale(0.5,0.5);
        sfx.loadFromFile("img/sound/health.wav");
	    Sfx.setBuffer(sfx);
    }

	void setter(float posx, float posy, float x, float y, float speed)
	{
		tex.loadFromFile("img/heart.png");
        sprite.scale(1,1);
		sprite.setTexture(tex, false);
		this->speed = speed;
		this->sprite.setPosition(posx, posy);
	}

    bool check_collision(float posx,float posy)
    {
       
        float temp_px = +50.f;
        float temp_mx = -50.f;
        posx = posx - sprite.getPosition().x;
       
        if (  (posx <= temp_px && posx >= temp_mx) &&  ( posy - sprite.getPosition().y  <= +50.f  && posy - sprite.getPosition().y >= -50.f) )
        {
            Sfx.play();
            sprite.setPosition(-200.f, sprite.getPosition().y);
            collided = 1;
            return true;
        }
        else
            return false;
    }

};

#endif