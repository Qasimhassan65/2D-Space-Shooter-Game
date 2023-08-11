#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string.h>
#include "bullet.h"
#include "Powerup.h"
#include "Playerfire.h"
#include "Bulletfire.h"
#include "Danger.h"
#include "lifeup.h"
#include <ctime>

using namespace sf;

class Player
{

public:
	Texture tex;
	Sprite sprite;

	Texture *tex_life;
	Sprite *sp_life;

	float speed;
	int x, y;
	Bullet *b;
	Powerup *powerup;
	Playerfire *fireup;
	float random_power[12];
	Clock clock;
	Bullet *b1,*b2,*b3,*b4,*b5,*b6;
	Bulletfire *fire;
	Danger *danger;
	Lifeup *lifeup,l1,l2,l3;
	int *a;
	int  numlife;
	bool *playerlife;
	int life_size;
	float lifeposy;
	bool sheild;
	bool diagnolright;
	bool diagnolleft;


	sf::SoundBuffer shootingbullets;
    sf::Sound Shootingbullets;

	sf::SoundBuffer destroyspaceship;
    sf::Sound Destroyspaceship;

	   
	
	Player(std::string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
		x = 340;
		y = 600;
		speed = 0.65;
		sprite.setPosition(x, y);
		sprite.setScale(0.35, 0.35);

		diagnolright = 0;
		diagnolleft = 0;

		destroyspaceship.loadFromFile("img/sound/spaceshipdown.wav");
	    Destroyspaceship.setBuffer(destroyspaceship);	

		life_size = 3;
		playerlife = new bool [6];
		for(int i=0;i<6;i++) 
		playerlife[i] = 1;

		tex_life =  new Texture [6];
		sp_life =  new Sprite [6];

		lifeposy = 710;

		for(int i=0;i<life_size;i++)
		{	
			tex_life[i].loadFromFile("img/PNG/playerShip2_green.png");
			sp_life[i].setTexture(tex_life[0]);
			sp_life[i].setPosition(700,lifeposy);
			sp_life[i].setScale(0.6,0.6);
			lifeposy -= 70;
		}

		

		b = new Bullet [4];
		fire = new Bulletfire [4];
		b1 = new Bullet [4];
		b2 = new Bullet [4];
		b3 = new Bullet [4];
		b4 = new Bullet [4];
		b5 = new Bullet [4];
		b6 = new Bullet [4];
		float posy = 50;
		for(int i=0;i<1;i++)
		{
			b[i].setter("img/PNG/Laser Sprites/34.png",this->sprite.getPosition().x - 15.f,this->sprite.getPosition().y - 40,0.f, 0.f, 1.f);
			posy+=50;
		}

		for(int i=0;i<4;i++)
		{
			fire[i].setter("img/PNG/fire1.png",this->sprite.getPosition().x+26.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b1[i].setter("img/PNG/Laser Sprites/34.png",this->sprite.getPosition().x+50.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b2[i].setter("img/PNG/Laser Sprites/34.png",this->sprite.getPosition().x-5.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b3[i].setter("img/PNG/Laser Sprites/tilt3.png",this->sprite.getPosition().x+65.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b4[i].setter("img/PNG/Laser Sprites/tilt1.png",this->sprite.getPosition().x-15.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b5[i].setter("img/PNG/Laser Sprites/tilt4.png",this->sprite.getPosition().x+85.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		posy = 50;

		for(int i=0;i<4;i++)
		{
			b6[i].setter("img/PNG/Laser Sprites/tilt2.png",this->sprite.getPosition().x-30.f,this->sprite.getPosition().y - posy,0.f, 0.f, 1.f);
			posy+=50;
		}

		powerup = new Powerup [3];
		powerup[0].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		powerup[1].setter((rand() % 700) + 20,-3- 100.f,0.f, 0.f, 1.f);
		powerup[2].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		
		fireup = new Playerfire [3];
		fireup[0].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		fireup[1].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		fireup[2].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);

		danger = new Danger [3];
		danger[0].setter(750,+10,0.f, 0.f, 1.f);
		danger[1].setter(750,+10,0.f, 0.f, 1.f);
		danger[2].setter(750,-+10,0.f, 0.f, 1.f);

		lifeup = new Lifeup [3];
		lifeup[0].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		lifeup[1].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);
		lifeup[2].setter((rand() % 700) + 20,-3,0.f, 0.f, 1.f);

		srand(time(0));

		random_power[0] = (rand() % 10) + 3;
		random_power[1] = (rand() % 20) + random_power[0] + 5;
		random_power[2] = (rand() % 20) + random_power[1] + 5;
		random_power[3] = (rand() % 20) + random_power[0] + 5;
		random_power[4] = (rand() % 20) + random_power[3] + 5;
		random_power[5] = (rand() % 20) + random_power[4] + 5;
		random_power[6] = (rand() % 20) + 3;
		random_power[7] = (rand() % 20) + random_power[3];
		random_power[8] = (rand() % 20) + random_power[6];
		random_power[9] = (rand() % 20) + 4;
		random_power[10] = (rand() % 20) + random_power[8];
		random_power[11] = (rand() % 20) + random_power[9];

		this->a = new int [6];
		this->a[0] = 1;
		this->a[1] = 1;
		this->a[2] = 1;
		this->a[3] = 1;
		this->a[4] = 1;
		this->a[5] = 1;

		sheild = 0;

	}

	void setspaceship(std::string png_path)
	{
		tex.loadFromFile(png_path);
		sprite.setTexture(tex);
	}

	void bullet_fire()
	{
			b[0].set_x(this->sprite.getPosition().x - 15.f);
			b[0].set_y(this->sprite.getPosition().y - 10.f);
			b[0].updatebullet(1);
		
	}

	void powerup_fire()
	{
		float posy = 40;
				 
		for(int i=0;i<4;i++)
		{
			b[0].updatebullet(2);
	
			b1[i].set_x(this->sprite.getPosition().x + 50.f);
			b1[i].set_y(this->sprite.getPosition().y - posy);
			b1[i].updatebullet(2);
		
			b2[i].set_x(this->sprite.getPosition().x - 5.f);
			b2[i].set_y(this->sprite.getPosition().y - posy);
			b2[i].updatebullet(2);

			b3[i].set_x(this->sprite.getPosition().x + 65.f);
			b3[i].set_y(this->sprite.getPosition().y - posy);
			b3[i].updatebullet(3);

			b4[i].set_x(this->sprite.getPosition().x - 15.f);
			b4[i].set_y(this->sprite.getPosition().y - posy);
			b4[i].updatebullet(5);

			b5[i].set_x(this->sprite.getPosition().x + 80.f);
			b5[i].set_y(this->sprite.getPosition().y - posy);
			b5[i].updatebullet(4);

			b6[i].set_x(this->sprite.getPosition().x - 30.f);
			b6[i].set_y(this->sprite.getPosition().y - posy);
			b6[i].updatebullet(6);
		
			posy+=40;
		}

	}

	void fireup_fire()
	{
			fire[0].set_x(this->sprite.getPosition().x + 70.f);
			fire[0].set_y(this->sprite.getPosition().y);
			fire[0].updatebulletfire();

			fire[1].set_x(this->sprite.getPosition().x + 70.f);
			fire[1].set_y(this->sprite.getPosition().y - 30.f);
			fire[1].updatebulletfire();

			fire[2].set_x(this->sprite.getPosition().x + 70.f);
			fire[2].set_y(this->sprite.getPosition().y - 60.f);
			fire[2].updatebulletfire();

			fire[3].set_x(this->sprite.getPosition().x + 70.f);
			fire[3].set_y(this->sprite.getPosition().y - 100.f);
			fire[3].updatebulletfire();
	}

	void move(std::string s)
	{
		float delta_x = 0, delta_y = 0;
		if (s == "l")
			delta_x = -1; // move the player left
		else if (s == "r")
			delta_x = +1; // move the player right
		if (s == "u")
			delta_y = -1;
		else if (s == "d")
			delta_y = 1;

		

		delta_x *= speed;
		delta_y *= speed;

		if (sprite.getPosition().x > 780)
		{
			sprite.setPosition(0, sprite.getPosition().y);
		}

		else if (sprite.getPosition().x < 0)
		{
			sprite.setPosition(780, sprite.getPosition().y);
		}

		if (sprite.getPosition().y > 780)
		{
			sprite.setPosition(sprite.getPosition().x, 0);
		}

		else if (sprite.getPosition().y < 0)
		{
			sprite.setPosition(sprite.getPosition().x, 780);
		}

		sprite.move(delta_x, delta_y);
	}

	void POWERUP(float &timer)
	{
		float time_stop = timer + 5;
		for(int i=0;i<3;i++)
		{
			if(timer >= random_power[i])
			{
				powerup[i].powerup_released = 1;
				powerup[i].fall();
				powerup[i].check_collision(this->sprite.getPosition().x,this->sprite.getPosition().y);
			}	
		}

		for(int i=0;i<3;i++)
		{
			if(powerup[i].collided)
			{
				sheild = 1;			
				sprite.setScale(1, 1);
				if(timer >= (this->random_power[i]+5) )
				{
					sheild = 0;
					this->sprite.setScale(0.7,0.7);
					this->powerup[i].powerup_stop = 1;
				}	
			
			}	
		}

	}

	void FIREUP(float &timer)
	{
		float time_stop = timer + 5;
		for(int i=0,j=3;i<3,j<6;i++,j++)
		{
			if(timer >= random_power[j])
			{
				fireup[i].fire_released = 1;
				fireup[i].fall();
				fireup[i].check_collision(this->sprite.getPosition().x,this->sprite.getPosition().y);
			}	
		}

		for(int i=0,j=3;i<3,j<6;i++,j++)
		{
			if(fireup[i].collided)
			{
				// this->setspaceship("img/space2.png");
				sprite.setScale(1, 1);
				if(timer >= (this->random_power[j]+5) )
				{
					this->sprite.setScale(0.7,0.7);
					this->fireup[i].fire_stop = 1;
				}	
				// for(int i=0;i<4;i++)
				// {
				// 	b[i].setbullet("img/PNG/Laser Sprites/30.png");
				// 	b1[i].setbullet("img/PNG/Laser Sprites/30.png");
				// 	b2[i].setbullet("img/PNG/Laser Sprites/30.png");
				// }
			}	
		}
	}

	void DANGERUP(float &timer, int &score)
	{
		float time_stop = timer + 5;
		
		for(int i=0,j=6;i<3,j<9;i++,j++)
		{
			if(timer >= random_power[j])
			{
				
				danger[i].danger_released = 1;
				danger[i].falldanger();
				//danger[i].Sfx.play();
				if(!sheild)
				danger[i].check_collision(this->sprite.getPosition().x,this->sprite.getPosition().y);
				
			}	
		}

		for(int i=0;i<3;i++)
		{
			if(danger[i].collided && a[i] == 1)
			{
				sprite.setPosition(340, 600);
				this->danger[i].danger_stop = 1;
				a[i]++;
				for(int i=life_size-1;i>=0;i--)
				{
					if(playerlife[i] != 0)
					{
						playerlife[i] = 0;
						break;
					}
				}	
			}
			if(danger[i].sprite.getPosition().x <= 0 && danger[i].score_added == 0)
			{	
				score += 20;
				danger[i].score_added = 1;
			}	
		}
	}

	void LIFEUP(float &timer)
	{
		float time_stop = timer + 5;
		for(int i=0,j=9;i<3,j<12;i++,j++)
		{
			if(timer >= random_power[j])
			{
				lifeup[i].lifeup_released = 1;
				lifeup[i].fall();
				lifeup[i].check_collision(this->sprite.getPosition().x,this->sprite.getPosition().y);
			}	
		}

		for(int i=0,j=3;i<life_size;i++,j++)
		{
			if(lifeup[i].collided && a[j] == 1  && lifeup[i].lifeup_stop == 0)
			{
				//sprite.setPosition(340, 600);
				this->lifeup[i].lifeup_stop = 1;
				a[i]++;
				this->increase_life();
				lifeup[i].lifeup_stop = 1;
			}	
		}
	}

	bool player_destroy(float posx,float posy)
	{
		float temp_px = +30.f;
        float temp_mx = -30.f;
        posx = posx - sprite.getPosition().x ;

        float temp_py = +50.f;
        float temp_my = -50.f;
        posy = posy - sprite.getPosition().y ;
    
    
        if (  (posx <= temp_px && posx >= temp_mx) && (posy <= temp_py && posy >= temp_my) )
        {
			Destroyspaceship.play();
            sprite.setPosition(340, 600);
			
			for(int i=life_size-1;i>=0;i--)
			{
				if(playerlife[i] != 0)
				{
					playerlife[i] = 0;
					break;
				}
			}

            return true;
        }
        else
            return false;
	}

	void increase_life()
	{
		tex_life[life_size].loadFromFile("img/PNG/playerShip2_green.png");
		sp_life[life_size].setTexture(tex_life[0]);
		sp_life[life_size].setPosition(700,lifeposy);
		sp_life[life_size].setScale(0.6,0.6);
		lifeposy -= 70;
		life_size++;
		

		// Texture *temp_tex_life =  new Texture [life_size+1];
		// Sprite *temp_sp_life =  new Sprite [life_size+1];
		// bool *temp_playerlife = new bool [life_size+1];


		// int i=0;
		// for(;i<life_size;i++)
		// {
		// 	temp_tex_life[i] = tex_life[i];
		// 	temp_sp_life[i] = sp_life[i];
		// 	temp_playerlife[i] = playerlife[i];
		// }

		// temp_tex_life[i].loadFromFile("img/PNG/playerShip2_green.png");
		// temp_sp_life[i].setTexture(tex_life[i]);
		// temp_sp_life[i].setPosition(700,lifeposy);
		// temp_sp_life[i].setScale(0.6,0.6);
		// temp_playerlife[i] = 1;
		// lifeposy -= 70;

		// delete[] tex_life; 
		// delete[] sp_life;
		// delete[] playerlife;

		// tex_life = temp_tex_life;
		// sp_life = temp_sp_life;
		// playerlife = temp_playerlife;
		// life_size++;

		// tex_life =  new Texture [life_size+1];
		// sp_life =  new Sprite [life_size+1];
		// playerlife = new bool [life_size+1];
		// life_size++;

		// for(int j=0;j<life_size;j++)
		// {
		// 	tex_life[j] = temp_tex_life[j];
		// 	sp_life[j] = temp_sp_life[j];
		// 	playerlife[j] = temp_playerlife[j];
		// }

	}
};

#endif