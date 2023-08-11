
#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Addon.h"
#include <iostream>
using namespace std;

class Powerup : public Addon
{

public:

    bool  powerup_released;
    bool  collided;
    bool powerup_stop;

   

    Powerup()
    {
        powerup_released = 0;
        collided = 0;
        powerup_stop = 0;

        sfx.loadFromFile("img/sound/powerup.wav");
	    Sfx.setBuffer(sfx);
    }

	void setter(float posx, float posy, float x, float y, float speed)
	{
		tex.loadFromFile("img/PNG/Power-ups/powerup.png");
        sprite.scale(1.3,1.3);
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