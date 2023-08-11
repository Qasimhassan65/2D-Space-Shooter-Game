
#ifndef INVADERS_H
#define INVADERS_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "bullet.h"
#include "Enemy.h"
#include <ctime>
using namespace std;

class Invaders : public Enemy
{

public:

    float speed;
    bool move;
    
    
    Invaders()
    {
        destroy_enemy = 0;
        bullet_destroy = 0;
        finish = 0;
        move = 0;
        bullet_released = 0;
        b = new Bullet [3];	
    }

    void setter(std::string png_path1,std::string png_path2,int x, int y, float posx, float posy, float speed) 
    {
   
    }

    void invader_bullet(float &timer,float delay)
    {
        if(timer>0.1)
        {
            b->updatebullet(7);
            bullet_released = 1;
        }
        if(timer >= delay-0.2)
        {
           
            if(b->sprite.getPosition().y >= 780 )//|| b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 40.f;
                float delta_y = this->sprite.getPosition().y;
                b->sprite.setPosition(delta_x, delta_y); 
            }
            timer = 0;
        }
       
    }

    bool invader_destroy(float posx, float posy)
    {
        float temp_px = +100.f;
        float temp_mx = -100.f;
        posx = posx - sprite.getPosition().x ;

        float temp_py = +10.f;
        float temp_my = -10.f;
        posy = posy - sprite.getPosition().y ;
    
    
        if (  (posx <= temp_px && posx >= temp_mx) && (posy <= temp_py && posy >= temp_my) )
        {
            sprite.move(-100.f, sprite.getPosition().y);
            destroy_enemy = 1;
            return true;
        }
        else
            return false;
    }

};


#endif