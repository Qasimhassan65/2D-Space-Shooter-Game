#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "player.h"
#include "Alpha.h"
#include "Beta.h"
#include "Gamma.h"
#include "Monster.h"
#include "Dragon.h"
#include "Enemy.h"
#include <fstream>
#include <iostream>
using namespace std;
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
    Sprite background; // Game background sprite
    Texture bg_texture;

    Sprite pause_background; // Game pause sprite
    Texture p_texture;

    Sprite scoreboard; // Game pause sprite
    Texture score_texture;

    Sprite level1_sp; // Game pause sprite
    Texture lvl1_texture;

    Sprite level2_sp; // Game pause sprite
    Texture lvl2_texture;

    Sprite level3_sp; // Game pause sprite
    Texture lvl3_texture;

    Sprite monsterlvl; // Game pause sprite
    Texture mon_texture;

    Sprite dragonlvl; // Game pause sprite
    Texture drag_texture;

    Sprite over_background; // Game over sprite
    Texture o_texture;

    Sprite alpha_lvl;
    Texture a_tex;

    Sprite beta_lvl;
    Texture b_tex;

    Sprite gamma_lvl;
    Texture g_tex;

    Sprite boss_lvl;
    Texture boss_tex;

    Sprite display_lvl;
    Texture displvl_tex;

    Player *p; // player
    Enemy *E[20];
  

    bool game_paused;
    bool Alpha_move_right;
    bool Beta_move_right;
    bool Gamma_move_right;
    bool space_pressed;
    float TIMER[31];
    float tt;

    sf::SoundBuffer spaceshipdownsfx;
    sf::Sound SpaceshipdownSfx;

    sf::SoundBuffer buffer_click;
    sf::Sound click;

    sf::Font font;
    sf::Text playername;
    sf::Text scoretext;



    int p_life;
    float betaposx;
    float betaposy;

    int count_alpha1;
    int count_beta1;
    int count_gamma1;

    bool level_1;
    bool level_2;
    bool level_3;

    bool a_setter_1;
    bool b_setter_1;
    bool g_setter_1;
    bool m_setter_1;
    bool d_setter_1;

    bool monster_released;
    bool dragon_released;
    bool draw_monsters;

    bool alpha;
    bool gamma;
    bool beta;
    bool boss;

    float delay_enemy_bulet;
    float monster_time;

    bool gameover;
    int displayed;

    int score_counter;

    bool win;

    Game()
    {
        p = new Player("img/newspaceship.png");
        p->sprite.setScale(0.7,0.7);
        
        spaceshipdownsfx.loadFromFile("img/sound/spaceshipdown.wav");
	    SpaceshipdownSfx.setBuffer(spaceshipdownsfx);

        gameover = 0;

        if(!buffer_click.loadFromFile("img/sound/select.wav"))
        {
            cout << "error in click sound" << endl;
        }
        click.setBuffer(buffer_click);	

        p_life = 3;

        p_texture.loadFromFile("img/2.png");
        pause_background.setTexture(p_texture);

        o_texture.loadFromFile("img/gameover.png");
        over_background.setTexture(o_texture);

        score_texture.loadFromFile("img/score.png");
        scoreboard.setTexture(score_texture);

        lvl1_texture.loadFromFile("img/level1.png");
        lvl2_texture.loadFromFile("img/level2.png");
        lvl3_texture.loadFromFile("img/level3.png");
        mon_texture.loadFromFile("img/monsterlevel.png");
        drag_texture.loadFromFile("img/dragonlevel.png");
        a_tex.loadFromFile("img/alpha.png");
        b_tex.loadFromFile("img/beta.png");
        g_tex.loadFromFile("img/gamma.png");
        boss_tex.loadFromFile("img/boss.png");
        

        level1_sp.setTexture(lvl1_texture);
        level2_sp.setTexture(lvl2_texture);
        level3_sp.setTexture(lvl3_texture);
        monsterlvl.setTexture(mon_texture);
        dragonlvl.setTexture(drag_texture);
        alpha_lvl.setTexture(a_tex);
        beta_lvl.setTexture(b_tex);
        gamma_lvl.setTexture(g_tex);
        boss_lvl.setTexture(boss_tex);

        

        float posx = 50.f;

        //Alpha

        for(int i=0;i<20;i++)
        E[i] = new Alpha;
        
        for (int i = 0; i < 14; i++)
        {
            if (i % 2)
            {
                E[i]->setter("img/enemy_1.png","img/enemy_laser.png",posx, 100.f, 50.f, 30.f, 1.f);
                posx += 100.f;
            }
            else
                E[i]->setter("img/enemy_1.png","img/enemy_laser.png",posx, 10.f, 50.f, 30.f, 1.f);
        }

        game_paused = false;
        Alpha_move_right = true;
        Beta_move_right = true;
        Gamma_move_right = true;
        space_pressed = false;
        

        displayed = 1;
        level_1 = 0;
        level_2 = 0;
        monster_released = 0;
        level_3 = 0;
        dragon_released = 0;
        draw_monsters = 0;
        
        count_alpha1 = 0;
        count_beta1 = 0;
        count_gamma1 = 0;
        d_setter_1 = 0;
        tt = 0;

        alpha = 1;
        gamma = 0;
        beta  = 0;
        boss  = 0;
        

        a_setter_1 = 0;
        b_setter_1 = 0;
        g_setter_1 = 0;
        m_setter_1 = 0;

        delay_enemy_bulet = 2.5;
        monster_time = 7;

        score_counter = 0;

        font.loadFromFile("img/FontsFree-Net-Starzone.ttf");
        scoretext.setFont(font);
        scoretext.setScale(1.22,1.22);
        scoretext.setPosition(80,690);
        scoretext.setFillColor(sf::Color::White);

        font.loadFromFile("img/FontsFree-Net-Starzone.ttf");
        playername.setFont(font);
        playername.setScale(1.22,1.22);
        playername.setPosition(400,400);
        playername.setFillColor(sf::Color::White);

        win = 0;

    }

    void start_game(RenderWindow &window, string name)
    {

        srand(time(0));
        sf::Vector2f gravity(0.f, .5f);
        sf::RectangleShape Shape;

        Shape.setSize(sf::Vector2f(780, 780));
        Shape.setPosition(0, 0);
        Shape.setFillColor(sf::Color(140, 36, 58));

        sf::RectangleShape Floor;
        Floor.setPosition(0, 0);
        Floor.setSize(sf::Vector2f(780, 780));

        sf::Vector2f velocity;

        if (bg_texture.loadFromFile("img/bc.png"))
        {
            bg_texture.setRepeated(true);
            background.setTexture(bg_texture);
            // background.setScale(0.9, 0.9);
        }

        Clock clock, CLOCK;
        sf::Time jpTime;
        sf::Time jpMaxTime = sf::seconds(0.1f);
        sf::Time lastTime;
        const float MAX_V = .4f;
        float timer = 0;
        float displaytimer = 0;
        
        

        
        // Game Start
        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            float TIME = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;
            for(int i=0;i<31;i++)
            TIMER[i] += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)             // If cross/close is clicked/pressed
                    window.close();                      // close the game
                if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::P))
            {
                click.play();
                Gamepause(window);
            }

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                p->bullet_fire();
                space_pressed = 1;
            }

            //Player
            this->player_move(e);
            this->Playerdestroy();

            // Fire Bullets
            if ((p->fireup[0].collided == 1 && p->fireup[0].fire_stop == 0) || (p->fireup[1].collided == 1 && p->fireup[1].fire_stop == 0) || (p->fireup[2].collided == 1 && p->fireup[2].fire_stop == 0))
            {
                p->fireup_fire();
            }      
            if ((p->powerup[0].collided == 1 && p->powerup[0].powerup_stop == 0) || (p->powerup[1].collided == 1 && p->powerup[1].powerup_stop == 0) || (p->powerup[2].collided == 1 && p->powerup[2].powerup_stop == 0))
            {
                p->powerup_fire();
            }
               
            
            //Levels 

            if(displayed == 1 && level_1 == 0)
            {
                this->DISPLAY_LEVEL(window,1);
            }

            else if(displayed == 0 && level_1 == 1)
            {
                delay_enemy_bulet = 2.5;
                this->LEVEL1();
            }

            else if(displayed == 2 && level_1 == 0)
            {
                this->DISPLAY_LEVEL(window,2);
            }

            else if(displayed == 0 && level_2 == 1)
            {
                delay_enemy_bulet = 2.0;
                this->LEVEL2();
            }

            else if(monster_released == 1)
            {
                tt  += time;
                delay_enemy_bulet = 1.5;
                monster_time = 7;
                this->Monster();
            }

            else if(displayed == 3 && level_3 == 0)
            {
                this->DISPLAY_LEVEL(window,3);
            }

            else if(displayed == 0 && level_3 == 1)
            {
                delay_enemy_bulet = 1.5;
                this->LEVEL3();
            }

            else if(level_3 == 0 && dragon_released == 1)
            {
                tt  += time;
                delay_enemy_bulet = 1.2;
                monster_time = 10;
                this->Dragon();
            }

            if(gameover == 1 || win == 1)
            {
                if(win)
                {
                    o_texture.loadFromFile("img/won.png");
                    over_background.setTexture(o_texture);
                }
                scoretext.setPosition(470,500);
                playername.setPosition(470,400);
                this->GAMEOVER(window, name);
            }


            // Addon
            p->POWERUP(timer);  // power up Addon
            p->FIREUP(timer);   // Fire Addon
            p->DANGERUP(timer,score_counter); // Danger Addon
            p->LIFEUP(timer);   // LIFE Addon

            // Infite Background
            Scrolling_Background(window, clock, lastTime, gravity, Shape, Floor, jpTime, MAX_V, velocity);
            Scrolling_Background(window, clock, lastTime, gravity, Shape, Floor, jpTime, MAX_V, velocity);

            // Display
            draw_attributes(window);
            window.display(); // Displying all the sprites
        }
    }

    void draw_attributes(RenderWindow &window)
    {

        window.clear(Color::Black); // clears the screen
        window.draw(background);    // setting background

        //Drawing Scoreboard
        window.draw(scoreboard);
        scoretext.setString(to_string(score_counter));
        window.draw(scoretext);

        //Drawing Levels 
        if(level_1)
        {
           window.draw(level1_sp);
        }

        else if(level_2 == 1)
        {
            window.draw(level2_sp);
        }

        else if(monster_released == 1)
        {
            window.draw(monsterlvl);
        }

        else if(level_3 == 1)
        {
            window.draw(level3_sp);
        }

        else if(level_3 == 0 && dragon_released == 1)
        {
            window.draw(dragonlvl);
        }

        if(alpha)
        {
            window.draw(alpha_lvl);
        }
        else if(beta)
        {
            window.draw(beta_lvl);
        }
        else if(gamma)
        {
            window.draw(gamma_lvl);
        }
        else if(boss)
        {
            window.draw(boss_lvl);
        }

        // Drawing Powerup
        for (int i = 0; i < 3; i++)
        {
            if (p->powerup[i].powerup_released)
            {
                window.draw(p->powerup[i].sprite);
            }
        }

        // Drawing Fireup
        for (int i = 0; i < 3; i++)
        {
            if (p->fireup[i].fire_released)
            {
                window.draw(p->fireup[i].sprite);
            }
        }

        // Drawing Danger
        for (int i = 0; i < 3; i++)
        {
            if (p->danger[i].danger_released && p->danger[i].danger_stop == 0)
            {
                window.draw(p->danger[i].sprite);
            }
        }

        // Drawing Lifeup
        for (int i = 0; i < 3; i++)
        {
            if (p->lifeup[i].lifeup_released && p->lifeup[i].lifeup_stop == 0)
            {
                window.draw(p->lifeup[i].sprite);
            }
        }

        //Normal Bullets
        if(space_pressed)
        {
            for (int i = 0; i < 1; i++)
            {
                window.draw(this->p->b[i].sprite);
            }
            space_pressed = 0;
        }

        
        // Drawing Fireup bullets
        if ((p->fireup[0].collided == 1 && p->fireup[0].fire_stop == 0) || (p->fireup[1].collided == 1 && p->fireup[1].fire_stop == 0) || (p->fireup[2].collided == 1 && p->fireup[2].fire_stop == 0))
        {
            for (int i = 0; i < 3; i++)
            window.draw(this->p->fire[i].sprite);
        }
        
        // Drawing Powerup Bullets
        if ((p->powerup[0].collided == 1 && p->powerup[0].powerup_stop == 0) || (p->powerup[1].collided == 1 && p->powerup[1].powerup_stop == 0) || (p->powerup[2].collided == 1 && p->powerup[2].powerup_stop == 0))
        {
            for (int i = 0; i < 1; i++)
            {
                window.draw(this->p->b1[i].sprite);
                window.draw(this->p->b2[i].sprite);
                window.draw(this->p->b3[i].sprite);
                window.draw(this->p->b4[i].sprite);
                window.draw(this->p->b5[i].sprite);
                window.draw(this->p->b6[i].sprite);
               
            }
        }

          
        //Drawing Enemies/Monster and It's Bullets
        for (int i = 0; i < 20; i++)
        {
            if (!E[i]->destroy_enemy)
            {
                for(int j=0;j<3;j++)
                {
                    if(E[i]->bullet_released)
                    {   
                        window.draw(E[i]->b[j].sprite);
                    }
                }
                window.draw(E[i]->sprite);
            }
        }
        
    
        //Drawing SpaceLifes
        for(int i=0;i<p->life_size;i++)
        {
            if(p->playerlife[i])
            window.draw(p->sp_life[i]);
        }

        // Drawing Spaceship
        window.draw(p->sprite);

        // if(p->diagnolright == 1 || p->diagnolleft == 1)
        // {
        //     p->diagnolright = 0;
        //     p->diagnolleft = 0;
        //     p->setspaceship("img/newspaceship.png");
        // }    

        if(p->playerlife[0] == 0)
        {
            gameover = true;
        }

    }

    void player_move(Event &e)
    {
        if (Keyboard::isKeyPressed(Keyboard::Left))  // If left key is pressed
        {
            p->move("l");                            // Player will move to left
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
        {
            p->move("r");                            // player will move to right
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))    // If up key is pressed
        {   
            p->move("u");                            // playet will move upwards
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))  // If down key is pressed
        {
            p->move("d");                            // player will move downwards
        }    
        // if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Right))   // Player will move to Diagnol Right 
        // {
        //     p->setspaceship("img/dright.png");
        //     p->diagnolright = 1;
        //     p->move("dr");
        // }                            
        // if (Keyboard::isKeyPressed(Keyboard::Up) && Keyboard::isKeyPressed(Keyboard::Left))  
        // {   
        //     p->setspaceship("img/dleft.png");
        //     p->move("dl");                            // Player will move to Diagnol Left    
        //     p->diagnolleft = 1;   
        // }

    }

    void LEVEL1()
    {
        //Enemies 

        //Alpha
        if(count_alpha1 < 14 &&  b_setter_1 == 0)
        {
            for(int i = 0; i < 14; i++)
            {
                E[i]->move();

                if(E[12]->sprite.getPosition().x >650 || E[13]->sprite.getPosition().x > 650)
                {
                    for(int j=0;j<14;j++)
                    E[j]->Alpha_move_right = 0;
                }

                if(E[0]->sprite.getPosition().x < 10 || E[1]->sprite.getPosition().x < 10)
                {
                    for(int j=0;j<14;j++)
                    E[j]->Alpha_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_alpha1++;
                    score_counter += 10;
                }
               
            }
        }

     
        //Beta
        if(count_alpha1 >= 14 && b_setter_1 == 0)
        {
            b_setter_1 = 1;
            alpha = 0;
            beta = 1;
 
            for(int i=0;i<20;i++)
            E[i] = new Beta;
            
            E[0]->setter("img/enemy_2.png","img/enemy_laser.png",300, 90.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_2.png","img/enemy_laser.png",200, 40.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_2.png","img/enemy_laser.png",110, 10.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_2.png","img/enemy_laser.png",110, 120.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_2.png","img/enemy_laser.png",110, 220.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_2.png","img/enemy_laser.png",110, 320.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_2.png","img/enemy_laser.png",400, 90.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_2.png","img/enemy_laser.png",490, 40.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_2.png","img/enemy_laser.png",580, 10.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_2.png","img/enemy_laser.png",580, 120.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_2.png","img/enemy_laser.png",580, 220.f, 50.f, 30.f, 1.f);
            E[11]->setter("img/enemy_2.png","img/enemy_laser.png",580, 320.f, 50.f, 30.f, 1.f);

        }

        if(b_setter_1 == 1 && count_alpha1>=12 &&  g_setter_1 == 0)
        {
            for(int i = 0; i < 12; i++)
            {
                E[i]->move();
                
                
                if((E[8]->sprite.getPosition().x >= 700 || E[11]->sprite.getPosition().x >= 700))
                {
                    for(int j=0;j<12;j++)
                    E[j]->Beta_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x <= 20 || E[4]->sprite.getPosition().x <= 20 )
                {
                    for(int j=0;j<12;j++)
                    E[j]->Beta_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_beta1++;
                    score_counter += 20;
                }
            }

        }
        

        //Gamma
        if(count_beta1 >= 12 && g_setter_1 == 0)
        { 
            g_setter_1 = 1;
            beta = 0;
            gamma = 1;

            score_counter += 20;

            for(int i=0;i<20;i++)
            E[i] = new Gamma;

            E[0]->setter("img/enemy_3.png","img/enemy_laser.png",130, 30.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_3.png","img/enemy_laser.png",270, 120.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_3.png","img/enemy_laser.png",410, 220.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_3.png","img/enemy_laser.png",130, 220.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_3.png","img/enemy_laser.png",400, 30.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_3.png","img/enemy_laser.png",550, 320.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_3.png","img/enemy_laser.png",30, 320.f, 50.f, 30.f, 1.f);

        }

        if(g_setter_1 == 1 && count_beta1>=9)
        {
            for(int i = 0, k=24; i < 7; i++,k++)
            {
                E[i]->move();

                if((E[4]->sprite.getPosition().x >= 750))
                {
                    for(int j=0;j<10;j++)
                    E[j]->Gamma_move_right = 0;
                }

                if(E[6]->sprite.getPosition().x <= 10)
                {
                    for(int j=0;j<10;j++)
                    E[j]->Gamma_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[k], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_gamma1++;
                    score_counter += 30;
                }
            }

        }

        if(count_gamma1 >= 7)
        {
            level_1 = 0;
            count_alpha1 = 0;
            count_beta1 = 0;
            count_gamma1 = 0;
            a_setter_1 = 0;
            b_setter_1 = 0;
            g_setter_1 = 0;
            displayed = 2;
        }

    }

    void LEVEL2()
    {
        //Enemies 

        //Alpha
        if(a_setter_1 == 0)
        {    
            a_setter_1 = 1;
            alpha = 1;
            gamma = 0;

            for(int i=0;i<20;i++)
            E[i] = new Alpha;
            
            E[0]->setter("img/enemy_1.png","img/enemy_laser.png",350, 10.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_1.png","img/enemy_laser.png",260, 80.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_1.png","img/enemy_laser.png",180, 150.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_1.png","img/enemy_laser.png",100, 220.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_1.png","img/enemy_laser.png",430, 80.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_1.png","img/enemy_laser.png",500, 150.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_1.png","img/enemy_laser.png",560, 220.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_1.png","img/enemy_laser.png",500, 300.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_1.png","img/enemy_laser.png",430, 380.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_1.png","img/enemy_laser.png",350, 450.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_1.png","img/enemy_laser.png",260, 380.f, 50.f, 30.f, 1.f);
            E[11]->setter("img/enemy_1.png","img/enemy_laser.png",180, 300.f, 50.f, 30.f, 1.f);
        }

        if(b_setter_1 == 0 && a_setter_1 == 1) 
        {
            for(int i = 0; i < 12; i++)
            {

                E[i]->move();

                if(E[6]->sprite.getPosition().x >650)
                {
                    for(int j=0;j<12;j++)
                    E[j]->Alpha_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x < 10)
                {
                    for(int j=0;j<12;j++)
                    E[j]->Alpha_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_alpha1++;
                    score_counter += 10;
                }
               
            }
        }


        //Beta
        if(count_alpha1 >= 12 && b_setter_1 == 0)
        {
            b_setter_1 = 1;
            alpha = 0;
            beta = 1;
 
            for(int i=0;i<20;i++)
            E[i] = new Beta;

            E[0]->setter("img/enemy_2.png","img/enemy_laser.png",350, 0.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_2.png","img/enemy_laser.png",250, 100.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_2.png","img/enemy_laser.png",150, 200.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_2.png","img/enemy_laser.png", 50, 300.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_2.png","img/enemy_laser.png",450, 110.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_2.png","img/enemy_laser.png",550, 200.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_2.png","img/enemy_laser.png",620, 310.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_2.png","img/enemy_laser.png",180, 310.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_2.png","img/enemy_laser.png",320, 310.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_2.png","img/enemy_laser.png",470, 310.f, 50.f, 30.f, 1.f);
        }

        if(b_setter_1 == 1 && count_alpha1>=12 &&  g_setter_1 == 0)
        {
            for(int i = 0; i < 10; i++)
            {
                E[i]->move();

                if((E[6]->sprite.getPosition().x >= 700))
                {
                    for(int j=0;j<10;j++)
                    E[j]->Beta_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x <= 20)
                {
                    for(int j=0;j<10;j++)
                    E[j]->Beta_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_beta1++;
                    score_counter += 20;
                }
            }

        }
      

        //Gamma
        if(count_beta1 >= 10 && g_setter_1 == 0)
        { 
            g_setter_1 = 1;
            beta = 0;
            gamma = 1;

            for(int i=0;i<20;i++)
            E[i] = new Gamma;

            E[0]->setter("img/enemy_3.png","img/enemy_laser.png",340, 10.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_3.png","img/enemy_laser.png",200, 35.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_3.png","img/enemy_laser.png",100, 120.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_3.png","img/enemy_laser.png",50, 220.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_3.png","img/enemy_laser.png",100,320.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_3.png","img/enemy_laser.png",220,400.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_3.png","img/enemy_laser.png",340,420.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_3.png","img/enemy_laser.png",460,400.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_3.png","img/enemy_laser.png",550,320.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_3.png","img/enemy_laser.png",570,220.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_3.png","img/enemy_laser.png",540,120.f, 50.f, 30.f, 1.f);
            E[11]->setter("img/enemy_3.png","img/enemy_laser.png",460,35.f, 50.f, 30.f, 1.f);

        }

        if(g_setter_1 == 1 && count_beta1>=10)
        {
            for(int i = 0, k=14; i < 12; i++,k++)
            {
                E[i]->move();

                if((E[9]->sprite.getPosition().x >= 750))
                {
                    for(int j=0;j<12;j++)
                    E[j]->Gamma_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x <= 10)
                {
                    for(int j=0;j<12;j++)
                    E[j]->Gamma_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[k], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_gamma1++;
                    score_counter += 30;
                }
            }

        }

        if(count_gamma1 >= 12)
        {
            level_2 = 0;
            monster_released = 1;
            count_alpha1 = 0;
            count_beta1 = 0;
            count_gamma1 = 0;
            a_setter_1 = 0;
            b_setter_1 = 0;
            g_setter_1 = 0;   
            draw_monsters = 1;
        }

    }

    void Monster()
    {
        //Monster
        if(m_setter_1 == 0)
        {    
            m_setter_1 = 1;
            gamma = 0;
            boss = 1;
         
            for(int i=0;i<20;i++)
            E[i] =  new monster;
            

            E[0]->setter("img/monster.png","img/lightning11.png",330, 10.f, 50.f, 30.f, 1.f);
            E[0]->sprite.setScale(0.23,0.23);
            E[0]->b->sprite.setScale(1.3,1.3);
           
        }

        else if (m_setter_1 == 1)
        {
                E[0]->move();

                if(E[0]->sprite.getPosition().x > 600)
                {
                    E[0]->monster_move_right = 0;
                }

                if(E[0]->sprite.getPosition().x < 30)
                {
                    E[0]->monster_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[0]->Monster_fire(TIMER[29], delay_enemy_bulet);
        }

        if(m_setter_1 == 1 && tt >= monster_time)
        {
            tt = 0;
            monster_released = 0;
            draw_monsters = 0; 
            score_counter += 40;
            displayed = 3;
        }
    }

    void LEVEL3()
    {
        //Enemies 

        //Alpha
        if(a_setter_1 == 0)
        {    
            a_setter_1 = 1;
            alpha = 1;
            gamma = 0;
            boss = 0;

            for(int i=0;i<20;i++)
            E[i] = new Alpha;
            
            E[0]->setter("img/enemy_1.png","img/enemy_laser.png",350, 10.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_1.png","img/enemy_laser.png",280, 60.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_1.png","img/enemy_laser.png",200, 110.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_1.png","img/enemy_laser.png",130, 160.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_1.png","img/enemy_laser.png",130, 240.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_1.png","img/enemy_laser.png",130, 320.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_1.png","img/enemy_laser.png",130, 400.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_1.png","img/enemy_laser.png",240, 400.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_1.png","img/enemy_laser.png",350, 400.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_1.png","img/enemy_laser.png",460, 400.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_1.png","img/enemy_laser.png",570, 400.f, 50.f, 30.f, 1.f);
            E[12]->setter("img/enemy_1.png","img/enemy_laser.png",570, 320.f, 50.f, 30.f, 1.f);
            E[13]->setter("img/enemy_1.png","img/enemy_laser.png",570, 240.f, 50.f, 30.f, 1.f);
            E[14]->setter("img/enemy_1.png","img/enemy_laser.png",570, 160.f, 50.f, 30.f, 1.f);
            E[15]->setter("img/enemy_1.png","img/enemy_laser.png",440, 60.f, 50.f, 30.f, 1.f);
            E[16]->setter("img/enemy_1.png","img/enemy_laser.png",520, 100.f, 50.f, 30.f, 1.f);
            E[17]->setter("img/enemy_1.png","img/enemy_laser.png",360, 160.f, 50.f, 30.f, 1.f);
            E[18]->setter("img/enemy_1.png","img/enemy_laser.png",260, 240.f, 50.f, 30.f, 1.f);
            E[19]->setter("img/enemy_1.png","img/enemy_laser.png",470, 240.f, 50.f, 30.f, 1.f);

        }

        if(b_setter_1 == 0 && a_setter_1 == 1) 
        {
            for(int i = 0; i < 20; i++)
            {

                E[i]->move();

                if(E[0]->sprite.getPosition().y <= 40)
                {
                    for(int j=0;j<20;j++)
                    E[j]->Alpha_move_up = 0;
                }

                if(E[7]->sprite.getPosition().y >= 570  || E[8]->sprite.getPosition().y >= 570)
                {
                    for(int j=0;j<20;j++)
                    E[j]->Alpha_move_up = 1;
                }

                if(E[10]->sprite.getPosition().x >650 || E[11]->sprite.getPosition().x >650)
                {
                    for(int j=0;j<20;j++)
                    E[j]->Alpha_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x < 10 || E[4]->sprite.getPosition().x < 10)
                {
                    for(int j=0;j<20;j++)
                    E[j]->Alpha_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_alpha1++;
                    score_counter += 10;
                }
               
            }
        }


        //Beta
        if(count_alpha1 >= 19 && b_setter_1 == 0)
        {
            b_setter_1 = 1;
            alpha = 0;
            beta = 1;
 
            for(int i=0;i<20;i++)
            E[i] = new Beta;

            E[0]->setter("img/enemy_2.png","img/enemy_laser.png",100, 10.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_2.png","img/enemy_laser.png",190, 80.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_2.png","img/enemy_laser.png",300, 120.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_2.png","img/enemy_laser.png",400, 120.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_2.png","img/enemy_laser.png",500, 80.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_2.png","img/enemy_laser.png",580, 10.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_2.png","img/enemy_laser.png",100, 110.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_2.png","img/enemy_laser.png",100, 210.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_2.png","img/enemy_laser.png",100, 310.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_2.png","img/enemy_laser.png",200, 250.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_2.png","img/enemy_laser.png",300, 210.f, 50.f, 30.f, 1.f);
            E[11]->setter("img/enemy_2.png","img/enemy_laser.png",400, 210.f, 50.f, 30.f, 1.f);
            E[12]->setter("img/enemy_2.png","img/enemy_laser.png",500, 250.f, 50.f, 30.f, 1.f);
            E[13]->setter("img/enemy_2.png","img/enemy_laser.png",580, 300.f, 50.f, 30.f, 1.f);
            E[14]->setter("img/enemy_2.png","img/enemy_laser.png",580, 200.f, 50.f, 30.f, 1.f);
            E[15]->setter("img/enemy_2.png","img/enemy_laser.png",580, 100.f, 50.f, 30.f, 1.f);
                    
        }

        if(b_setter_1 == 1 && count_alpha1>=19 &&  g_setter_1 == 0)
        {
            for(int i = 0; i < 16; i++)
            {
                E[i]->move();

                if(E[0]->sprite.getPosition().y <= 20 || E[5]->sprite.getPosition().y <= 20)
                {
                    for(int j=0;j<16;j++)
                    E[j]->Beta_move_up = 0;
                }

                if(E[8]->sprite.getPosition().y >= 600)
                {
                    for(int j=0;j<16;j++)
                    E[j]->Beta_move_up = 1;
                }

                if(E[5]->sprite.getPosition().x >= 650 || E[13]->sprite.getPosition().x >= 650)
                {
                    for(int j=0;j<16;j++)
                    E[j]->Beta_move_right = 0;
                }

                if(E[0]->sprite.getPosition().x <= 30 || E[8]->sprite.getPosition().x <= 30)
                {
                    for(int j=0;j<16;j++)
                    E[j]->Beta_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[i], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_beta1++;
                    score_counter += 20;
                }
            }

        }
      

        //Gamma
        if(count_beta1 >= 16 && g_setter_1 == 0)
        { 
            g_setter_1 = 1;
            beta = 0;
            gamma = 1;

            for(int i=0;i<20;i++)
            E[i] = new Gamma;

            E[0]->setter("img/enemy_3.png","img/enemy_laser.png",340, 10.f, 50.f, 30.f, 1.f);
            E[1]->setter("img/enemy_3.png","img/enemy_laser.png",200, 35.f, 50.f, 30.f, 1.f);
            E[2]->setter("img/enemy_3.png","img/enemy_laser.png",100, 120.f, 50.f, 30.f, 1.f);
            E[3]->setter("img/enemy_3.png","img/enemy_laser.png",50, 220.f, 50.f, 30.f, 1.f);
            E[4]->setter("img/enemy_3.png","img/enemy_laser.png",570,220.f, 50.f, 30.f, 1.f);
            E[5]->setter("img/enemy_3.png","img/enemy_laser.png",540,120.f, 50.f, 30.f, 1.f);
            E[6]->setter("img/enemy_3.png","img/enemy_laser.png",460,35.f, 50.f, 30.f, 1.f);
            E[7]->setter("img/enemy_3.png","img/enemy_laser.png",180,220.f, 50.f, 30.f, 1.f);
            E[8]->setter("img/enemy_3.png","img/enemy_laser.png",320,220.f, 50.f, 30.f, 1.f);
            E[9]->setter("img/enemy_3.png","img/enemy_laser.png",440,220.f, 50.f, 30.f, 1.f);
            E[10]->setter("img/enemy_3.png","img/enemy_laser.png",180,320.f, 50.f, 30.f, 1.f);
            E[11]->setter("img/enemy_3.png","img/enemy_laser.png",320,320.f, 50.f, 30.f, 1.f);
            E[12]->setter("img/enemy_3.png","img/enemy_laser.png",440,320.f, 50.f, 30.f, 1.f);
            E[13]->setter("img/enemy_3.png","img/enemy_laser.png",180,420.f, 50.f, 30.f, 1.f);
            E[14]->setter("img/enemy_3.png","img/enemy_laser.png",320,420.f, 50.f, 30.f, 1.f);
            E[15]->setter("img/enemy_3.png","img/enemy_laser.png",440,420.f, 50.f, 30.f, 1.f);
            E[16]->setter("img/enemy_3.png","img/enemy_laser.png",260,120.f, 50.f, 30.f, 1.f);
            E[17]->setter("img/enemy_3.png","img/enemy_laser.png",380,120.f, 50.f, 30.f, 1.f);
            

        }

        if(g_setter_1 == 1 && count_beta1>=16)
        {
            for(int i = 0, k=14; i < 18; i++,k++)
            {
                E[i]->move();

                if((E[9]->sprite.getPosition().x >= 650))
                {
                    for(int j=0;j<18;j++)
                    E[j]->Gamma_move_right = 0;
                }

                if(E[3]->sprite.getPosition().x <= 10)
                {
                    for(int j=0;j<18;j++)
                    E[j]->Gamma_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[i]->Destroy(p);
                E[i]->invader_bullet(TIMER[k], delay_enemy_bulet);
               
                if(!E[i]->destroy_enemy)
                continue;
                
                else if (E[i]->destroy_enemy == 1 && E[i]->finish == 0)
                {
                    E[i]->finish = 1;
                    count_gamma1++;
                    score_counter += 30;
                }
            }

        }

        if(count_gamma1 >= 18)
        {
            level_3 = 0;
            count_alpha1 = 0;
            count_beta1 = 0;
            count_gamma1 = 0;
            a_setter_1 = 0;
            b_setter_1 = 0;
            g_setter_1 = 0;
            dragon_released = 1;   
            draw_monsters = 0;
        }


    }

    void Dragon()
    {
        //Dragon
        if(d_setter_1 == 0)
        {    
            d_setter_1 = 1;
            gamma = 0;
            boss = 1;
         
            for(int i=0;i<20;i++)
            E[i] =  new dragon;
            

            E[0]->setter("img/dragon.png","img/firedown.png",350, 10.f, 50.f, 30.f, 1.f);
            E[0]->b[0].sprite.setScale(1.4,1.4);
            E[0]->b[1].sprite.setScale(1.4,1.4);
            E[0]->b[2].sprite.setScale(1.4,1.4);
        }

        else if (d_setter_1 == 1)
        {
                E[0]->move();

                if(E[0]->sprite.getPosition().x > 600)
                {
                    E[0]->monster_move_right = 0;
                }

                if(E[0]->sprite.getPosition().x < 30)
                {
                    E[0]->monster_move_right = 1;
                }

                //this->check_Spaceship_collision();
                E[0]->Monster_fire(TIMER[29], delay_enemy_bulet);
        }

        if(d_setter_1 == 1 && tt >= monster_time)
        {
            tt = 0;
            dragon_released = 0;
            draw_monsters = 0;
            win = 1;
        }

        if(win)
        score_counter += 60;
    }

    void Playerdestroy()
    {
        if(!p->sheild)
        {
            for(int i=0;i<20;i++)
            {
                    if(monster_released == 1 || dragon_released == 1 )
                    {   
                        for(int j=0;j<3;j++)
                        {
                             if (p->player_destroy(E[i]->b[j].get_x(), E[i]->b[j].get_y()))
                            {
                                E[i]->b[j].wrapbullet(E[i]->sprite.getPosition().x + 40.f, E[i]->sprite.getPosition().y);
                                break;
                            }
                        }
                    }

                    if(!E[i]->destroy_enemy)
                    {
                        if (p->player_destroy(E[i]->b->get_x(), E[i]->b->get_y()))
                        {
                            E[i]->b->wrapbullet(E[i]->sprite.getPosition().x + 40.f, E[i]->sprite.getPosition().y);
                            break;
                        }
                    }
            }
        }


    }

    void check_Spaceship_collision()
    {
        // float posx = p->sprite.getPosition().x;
        // float posy = p->sprite.getPosition().y;
        // float temp_px = +100.f;
        // float temp_mx = -100.f;

        // for (int i = 0; i < 14; i++)
        // {
        //     float temp_py = +100.f;
        //     float temp_my = -100.f;
        //     posx = posx - A[i].sprite.getPosition().x;
        //     posy = posy - A[i].sprite.getPosition().y;
        //     if ((posx <= temp_px && posx >= temp_mx) && (posy <= +100.f && posy >= -100.f))
        //     {
        //         //SpaceshipdownSfx.play();
        //         A[i].sprite.setPosition(-100.f, A[i].sprite.getPosition().y);
        //         A[i].destroy_enemy = 1;
        //     }
            
        // }
        
    }

    void GAMEOVER(RenderWindow & window, string name)
    {

        bool takehighscore = 1;


        while (window.isOpen())
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)             // If cross/close is clicked/pressed
                    window.close();                      // close the game
                if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                    window.close();
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                 window.close();

            if(takehighscore)
            {
               
                fstream highscore,tmphighscore;
               
                playername.setString(name);
                
                highscore.open("highscore", ios::app);

                highscore << name << " " << score_counter << endl;

                highscore.close();

                highscore.open("highscore", ios::in);

                tmphighscore.open("tmphighscore", ios::out);

                string  nme[4];
                long int scr[4]; 
                int j=0;

                while(!highscore.eof())
                {
                    if(j>=4)
                    break;
                    else
                    highscore >> nme[j] >> scr[j];
                    j++;
                }

                int temp;
                string tempname;

                for (int  l= 0; l < 4; l++) 
                {
                    for (int k = l + 1; k < 4; k++) 
                    {
                        if (scr[l] < scr[k]) 
                        {
                            temp = scr[l];
                            scr[l] = scr[k];
                            scr[k] = temp;

                            tempname = nme[l];
                            nme[l] = nme[k];
                            nme[k] = tempname;

                         }
                     }
                }          

                for(int i=0;i<3;i++)
                {
                    tmphighscore << nme[i] << " " << scr[i] << endl;
                    //cout << nme[i] << "   " << scr[i] << endl;
                }

                highscore.close();

                highscore.open("highscore" , ios::out);

                for(int count = 0;count<3;count++)
                highscore << nme[count] << " " << scr[count] << endl;
                
                highscore.close();

                takehighscore = 0;

            }

            window.clear();
            window.draw(over_background);
            window.draw(scoretext);
            window.draw(playername);
            window.display();
        }


    }

    void Gamepause(RenderWindow &window)
    {

        while (true)
        {
            bool close = 0;
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed){             // If cross/close is clicked/pressed
                    click.play();
                    window.close();
                    }                      // close the game
                if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                    window.close();
                if (Keyboard::isKeyPressed(Keyboard::Enter))
                {
                    if (game_paused == 1){
                        click.play();
                        window.close();
                    }
                        
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
            {
                click.play();
                window.close();
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                click.play();
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if (!game_paused)
                {
                    click.play();
                    p_texture.loadFromFile("img/3.png");
                    pause_background.setTexture(p_texture);
                    game_paused = 1;
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if (game_paused)
                {
                    click.play();
                    p_texture.loadFromFile("img/2.png");
                    pause_background.setTexture(p_texture);
                    game_paused = 0;
                }
            }

            window.clear();
            window.draw(pause_background);
            window.display();
        }
    }

    void DISPLAY_LEVEL(RenderWindow &window, int a)
    {
        if(a == 1)
        {
            displvl_tex.loadFromFile("img/displvl1.png");
            display_lvl.setTexture(displvl_tex);
        } 
        else if (a == 2)
        {
            displvl_tex.loadFromFile("img/displvl2.png");
            display_lvl.setTexture(displvl_tex);
        }
        else if (a == 3)
        {
            displvl_tex.loadFromFile("img/displvl3.png");
            display_lvl.setTexture(displvl_tex);
        }

        float timer = 0;
        Clock clock;
        
        while (displayed)
        {

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed){             // If cross/close is clicked/pressed
                    click.play();
                    window.close();
                    }                      // close the game
                if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                    window.close();
            }

            if(timer > 1.2 && a == 1)
            {
                level_1 = 1;
                displayed = 0;
                break;
            }

            else if(timer > 1.2 && a == 2)
            {
                level_2 = 1;
                displayed = 0;
                break;
            }

            else if(timer > 1.2 && a == 3)
            {
                level_3 = 1;
                displayed = 0;
                break;
            }

            window.clear();
            window.draw(display_lvl);
            window.display();
        }
    }

    void Scrolling_Background(RenderWindow &window, Clock &clock, Time &lastTime, sf::Vector2f &gravity,
                              sf::RectangleShape &Shape, sf::RectangleShape &Floor, sf::Time &jpTime, const float MAX_V, sf::Vector2f &velocity)
    {

        sf::Time c_time = clock.restart();
        lastTime = c_time;
        velocity.y += gravity.y * lastTime.asSeconds();
        velocity.x *= .75f;

        if (velocity.x < -MAX_V)
            velocity.x = -MAX_V;
        else if (velocity.x > MAX_V)
            velocity.x = MAX_V;
        if (velocity.y < -MAX_V)
            velocity.y = -MAX_V;
        else if (velocity.y > MAX_V)
            velocity.y = MAX_V;

        Shape.move(velocity);

        if (Shape.getPosition().x < 0)
            Shape.setPosition(0, Shape.getPosition().y);
        if (Shape.getPosition().x + Shape.getSize().x > window.getSize().x)
            Shape.setPosition(window.getSize().x - Shape.getSize().x, Shape.getPosition().y);

        background.setOrigin(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
        background.setPosition(background.getLocalBounds().width / 2, background.getLocalBounds().height / 2);
        background.setTextureRect(sf::IntRect(-((Shape.getPosition().x * .125f)), -(Shape.getPosition().y * .25f), 780, 780));
    }
};
