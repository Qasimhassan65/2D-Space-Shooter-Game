
#ifndef DRAGON_H
#define DRAGON_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Enemy.h"
#include <ctime>
using namespace std;

class dragon : public Enemy
{

public:

    dragon()
    {
        destroy_enemy = 0;
        bullet_released = 1;
        b = new Bullet[3];	
    }

    void setter(std::string png_path1,std::string png_path2,int x, int y, float posx, float posy, float speed) 
    {
        tex.loadFromFile(png_path1);
        sprite.scale(1.5,1.5);
        sprite.setTexture(tex, false);
        this->x = posx;
        this->y = posy;
        this->speed = speed;
        this->sprite.setPosition(x, y);
        b[0].setter(png_path2,this->sprite.getPosition().x + 15.f,this->sprite.getPosition().y+20.f,0.f, 0.f, 1.f);
        b[1].setter("img/fireleft.png",this->sprite.getPosition().x + 40.f,this->sprite.getPosition().y + 130.f,0.f, 0.f, 1.f);
        b[2].setter("img/fireright.png",this->sprite.getPosition().x+20.f,this->sprite.getPosition().y + 180.f,0.f, 0.f, 1.f);
    }

    void Monster_fire(float &timer,float delay)
    {

        b[0].updatebullet(10);
        b[1].updatebullet(8);
        b[2].updatebullet(9);
        if(timer >= delay)
        {
            if(b[0].sprite.getPosition().y >= 780 || b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 20.f;
                float delta_y = this->sprite.getPosition().y + 180.f;
                b[0].sprite.setPosition(delta_x, delta_y);
            }

            if(b[1].sprite.getPosition().y >= 780 || b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 15.f;
                float delta_y = this->sprite.getPosition().y + 180.f;
                b[1].sprite.setPosition(delta_x, delta_y);
            }

            if(b[2].sprite.getPosition().y >= 780 || b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 45.f;
                float delta_y = this->sprite.getPosition().y + 200.f;
                b[2].sprite.setPosition(delta_x, delta_y);
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
            delta_x = 0.40, delta_y = 0;
            sprite.move(delta_x, delta_y);
        }
        else
        {
            delta_x = -0.40, delta_y =0;
            sprite.move(delta_x, delta_y);    
        }


    }

};


#endif