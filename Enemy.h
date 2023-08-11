
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "bullet.h"
#include "player.h"
#include <ctime>
using namespace std;

class Enemy
{

public:
    sf::Texture tex;
    sf::Sprite sprite;
    float speed;
    int x, y;
    bool destroy_enemy;
    Bullet *b;
    bool bullet_destroy;
    bool bullet_released;
    
    bool Alpha_move_right;
    bool Beta_move_right;
    bool Gamma_move_right;

    bool Alpha_move_up;
    bool Beta_move_up;
    bool Gamma_move_up;

    bool monster_move_right;

    bool finish;
    
    Enemy()
    {
        Alpha_move_right = 0;
        Beta_move_right = 0;
        Gamma_move_right = 0;
        monster_move_right = 0;

        Alpha_move_up = 1;
        Beta_move_up  = 1;
        Gamma_move_up = 1;
    }

    void set_pos()
    {
        sprite.setPosition(-30, 30);
    }

    void set_y(float posy)
    {
        this->y = posy;
    }

    virtual void setter(std::string png_path1,std::string png_path2,int x, int y, float posx, float posy, float speed)
    {

    }

    virtual void move()
    {
        
    }

    virtual void Destroy(Player *p)
    {

    }

    virtual void invader_bullet(float &timer,float delay)
    {
        b->updatebullet(7);
        if(timer >= delay)
        {
            if(b->sprite.getPosition().y >= 780 )//|| b->sprite.getPosition().x < 0 || b->sprite.getPosition().x > 780)               
            {
                float delta_x = this->sprite.getPosition().x + 40.f;
                float delta_y = this->sprite.getPosition().y;
                b->sprite.setPosition(delta_x, delta_y); 
            }
            timer = 0;
        }
        if (destroy_enemy)
        bullet_destroy = 1;	
    }

    virtual void Monster_fire(float &timer, float delay)
    {

    }

};


#endif