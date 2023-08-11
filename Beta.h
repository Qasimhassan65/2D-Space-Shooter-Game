
#ifndef BETA_H
#define BETA_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Invaders.h"
#include <ctime>
using namespace std;

class Beta : public Invaders
{

public:

    Beta()
    {

    }

     void setter(std::string png_path1,std::string png_path2,int x, int y, float posx, float posy, float speed) 
    {
        tex.loadFromFile(png_path1);
        sprite.scale(0.7, 0.7);
        sprite.setTexture(tex, false);
        this->x = posx;
        this->y = posy;
        this->speed = speed;
        this->sprite.setPosition(x, y);
        b->setter(png_path2,this->sprite.getPosition().x+40.f,this->sprite.getPosition().y,0.f, 0.f, 1.f);
        b->sprite.setScale(1.1,1.1);
    }

    void move()
    {
        float delta_x;
        float delta_y;


       
        delta_x = 0, delta_y = +0.03;
        sprite.move(delta_x, delta_y);
    

        if (Beta_move_right)
        {
            delta_x = 0.25, delta_y = 0;
            sprite.move(delta_x, delta_y);
        }
        else
        {
            delta_x = -0.25, delta_y =0;
            sprite.move(delta_x, delta_y);    
        }

    }

    void Destroy(Player *p)
    {
        if (p->powerup[0].collided || p->powerup[1].collided || p->powerup[2].collided)
        {
            for (int j = 0; j < 1; j++)
            {
                if (this->invader_destroy(p->b[j].get_x(), p->b[j].get_y()))
                {
                    p->b[j].wrapbullet(p->sprite.getPosition().x, p->sprite.getPosition().y);
                    break;
                }
                if (this->invader_destroy(p->b1[j].get_x(), p->b1[j].get_y()))
                {
                    p->b1[j].wrapbullet(p->sprite.getPosition().x - 5.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
                if (this->invader_destroy(p->b2[j].get_x(), p->b2[j].get_y()))
                {
                    p->b2[j].wrapbullet(p->sprite.getPosition().x + 50.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
                if (this->invader_destroy(p->b3[j].get_x(), p->b3[j].get_y()))
                {
                    p->b3[j].wrapbullet(p->sprite.getPosition().x + 50.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
                if (this->invader_destroy(p->b4[j].get_x(), p->b4[j].get_y()))
                {
                    p->b4[j].wrapbullet(p->sprite.getPosition().x + 50.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
                if (this->invader_destroy(p->b5[j].get_x(), p->b5[j].get_y()))
                {
                    p->b5[j].wrapbullet(p->sprite.getPosition().x + 50.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
                if (this->invader_destroy(p->b6[j].get_x(), p->b6[j].get_y()))
                {
                    p->b6[j].wrapbullet(p->sprite.getPosition().x + 50.f, p->sprite.getPosition().y - 50.f);
                    break;
                }
            }
        }
        

        else
        {
          
            for (int j = 0; j < 1; j++)
            {
                if ((p->fireup[0].collided == 1 && p->fireup[0].fire_stop == 0) || (p->fireup[1].collided == 1 && p->fireup[1].fire_stop == 0) || (p->fireup[2].collided == 1 && p->fireup[2].fire_stop == 0))
                {
                    if (this->invader_destroy(p->fire[j].get_x(), p->fire[j].get_y()))
                    {
                        p->fire[j].wrapbullet(p->sprite.getPosition().x, p->sprite.getPosition().y);
                        break;
                    }
                }
                else
                {
                    if (this->invader_destroy(p->b[j].get_x(), p->b[j].get_y()))
                    {
                        p->b[j].wrapbullet(p->sprite.getPosition().x, p->sprite.getPosition().y);
                        break;
                    }    
                }
            }
            
        }

    }

};


#endif