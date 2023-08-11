
#ifndef DANGER_H
#define DANGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Addon.h"
#include <iostream>
using namespace std;

class Danger : public Addon
{

public:

    bool  danger_released;
    bool  collided;
    bool danger_stop;
    bool score_added;
    bool stop;
    float delta_x,delta_y;

    sf::SoundBuffer destroyspaceship;
    sf::Sound Destroyspaceship;


    Danger()
    {
        danger_released = 0;
        collided = 0;
        danger_stop = 0;
        sprite.setScale(0.5,0.5);
        stop = 0;
        score_added = 0;
        delta_x = -0.6, delta_y = 0.9;
        sfx.loadFromFile("img/sound/danger.wav");
	    Sfx.setBuffer(sfx);

        destroyspaceship.loadFromFile("img/sound/spaceshipdown.wav");
	    Destroyspaceship.setBuffer(destroyspaceship);	

    }

	void setter(float posx, float posy, float x, float y, float speed)
	{
		tex.loadFromFile("img/danger.png");
        sprite.scale(1.5,1.5);
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
            Destroyspaceship.play();
            sprite.setPosition(-200.f, sprite.getPosition().y);
            collided = 1;
            return true;
        }
        else
            return false;
    }

    void falldanger()
	{
		sprite.move(delta_x, delta_y);
        //sprite.move(delta_x, delta_y);
	}

};

#endif