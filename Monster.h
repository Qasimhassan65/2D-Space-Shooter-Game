
#ifndef MONSTER_H
#define MONSTER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Enemy.h"
#include <ctime>
using namespace std;

class monster : public Enemy
{

public:

    monster()
    {
        destroy_enemy = 0;
        bullet_released = 1;
        b = new Bullet[3];	
    }

    void setter(std::string png_path1,std::string png_path2,int x, int y, float posx, float posy, float speed) 
    {
        tex.loadFromFile(png_path1);
        sprite.scale(0.2, 0.2);
        sprite.setTexture(tex, false);
        this->x = posx;
        this->y = posy;
        this->speed = speed;
        this->sprite.setPosition(x, y);
        b[0].setter(png_path2,this->sprite.getPosition().x+70.f,this->sprite.getPosition().y,0.f, 0.f, 1.f);
    }

    void Monster_fire(float &timer,float delay)
    {

        
        b[0].updatebullet(10);
        if(timer >= delay)
        {
            if(b[0].sprite.getPosition().y >= 780 || b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 80.f;
                float delta_y = this->sprite.getPosition().y + 100.f;
                b[0].sprite.setPosition(delta_x, delta_y);
            }
      
            timer = 0;
        }
    }

    void move()
    {
        float delta_x;
        float delta_y;

        if (monster_move_right)
        {
            delta_x = 0.15, delta_y = 0;
            sprite.move(delta_x, delta_y);
        }
        else
        {
            delta_x = -0.15, delta_y =0;
            sprite.move(delta_x, delta_y);    
        }


    }

};


#endif