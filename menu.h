
#include "game.h"
#include <SFML/Audio.hpp>
#include <fstream>
class Menu
{
public:
    // add menu attributes here
    Texture tex_menu;
    Sprite sprite_menu;

    sf::Texture tex_help;
    sf::Sprite sprite_help;
    bool draw_help;
    bool draw_highscore;

    Texture tex_high;
    Sprite sprite_high;

    Texture name_tex;
    Sprite sprite_name;

    sf::Font font;
    sf::Text *scoretext;
    sf::Text playername;

    sf::SoundBuffer buffer_click;
    sf::Sound click;

    string name;

    bool name_enetered;
    

    Menu()
    {
        tex_menu.loadFromFile("img/1.png");
        sprite_menu.setTexture(tex_menu);


        if(!buffer_click.loadFromFile("img/sound/select.wav"))
        {
            cout << "error in click sound" << endl;
        }
        click.setBuffer(buffer_click);

        font.loadFromFile("img/FontsFree-Net-Starzone.ttf");
        scoretext = new Text [3];

        scoretext[0].setFont(font);
        scoretext[0].setScale(1.22,1.22);
        scoretext[0].setPosition(300,280);
        scoretext[0].setFillColor(sf::Color::White);


        scoretext[1].setFont(font);
        scoretext[1].setScale(1.22,1.22);
        scoretext[1].setPosition(300,450);
        scoretext[1].setFillColor(sf::Color::White);

        scoretext[2].setFont(font);
        scoretext[2].setScale(1.22,1.22);
        scoretext[2].setPosition(300,630);
        scoretext[2].setFillColor(sf::Color::White);

        playername.setFont(font);
        playername.setScale(1.5,1.5);
        playername.setPosition(160,380);
        playername.setFillColor(sf::Color::White);

        name_tex.loadFromFile("img/entername.png");
        sprite_name.setTexture(name_tex);
    
    
        name = "";
        name_enetered = 0;

    }

    

    void display_menu()

    {
        click.play();
        RenderWindow window(VideoMode(780, 780), title);

        Event e;

        while (window.isOpen())
        {
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)
                { 
                    click.play();
                    window.close();
                }         
            }

            if (Keyboard::isKeyPressed(Keyboard::E))
                window.close();

            if(!name_enetered)
            {
                this->Entername(window);
            }

            if (Keyboard::isKeyPressed(Keyboard::S)) // If left key is pressed
            {
                click.play();
                Game g;
                g.start_game(window,name);
            }


            if (Keyboard::isKeyPressed(Keyboard::H)) // If left key is pressed
            {
                click.play();
                this->display_help();
            }

            if(draw_help == true && Keyboard::isKeyPressed(Keyboard::B))
            {
                click.play();
                draw_help = 0;
            }

            if (Keyboard::isKeyPressed(Keyboard::A)) // If left key is pressed
            {
                click.play();
                this->display_highscore();
            }

            if(draw_highscore == true && Keyboard::isKeyPressed(Keyboard::B))
            {
                click.play();
                draw_highscore = 0;
            }

            window.clear(Color::Black);
            window.draw(sprite_menu);
            if(draw_help)
            window.draw(sprite_help);
            if(draw_highscore)
            {
                window.draw(sprite_high);

                for(int i=0;i<3;i++)
                window.draw(scoretext[i]);
            
            }
            window.display();

        }
    }

    void display_help()
    {
        draw_help = 1;
        tex_help.loadFromFile("img/help.png");
        sprite_help.setTexture(tex_help);
    }

    void display_highscore()
    {

        draw_highscore = 1;
        tex_high.loadFromFile("img/screen1.png");
        sprite_high.setTexture(tex_high);

        fstream highscore;

        highscore.open("tmphighscore" , ios::in);

        string  name[3];
        long int score[3]; 
        int j=0;

        while(!highscore.eof())
        {
            if(j>=3)
            break;
            else
            highscore >> name[j] >> score[j];
            j++;
        }

        string scoring;

        for(int i=0;i<3;i++)
        {
            scoring+=name[i];
            scoring+="    ";
            scoring+=to_string(score[i]);
            scoretext[i].setString(scoring);
            scoring = "";
        }


    }

    void Entername(RenderWindow &window)
    {

        while (!name_enetered)
        {
            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event::Closed)             // If cross/close is clicked/pressed
                    window.close();                      // close the game
                if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                    window.close();

                switch (e.type)
                {
                    case sf::Event::KeyPressed:

                            switch (e.key.code)
                            {
                                case sf::Keyboard::A:
                                                click.play();
                                                name += 'A';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::B:
                                                click.play();
                                                name += 'B';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::C:
                                                click.play();
                                                name += 'C';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::D:
                                                click.play();
                                                name += 'D';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::E:
                                                click.play();
                                                name += 'E';
                                                playername.setString(name);
                                                break;               
                                case sf::Keyboard::F:
                                                click.play();
                                                name += 'F';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::G:
                                                click.play();
                                                name += 'G';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::H:
                                                click.play();
                                                name += 'H';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::I:
                                                click.play();
                                                name += 'I';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::J:
                                                click.play();
                                                name += 'J';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::K:
                                                click.play();
                                                name += 'K';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::L:
                                                click.play();
                                                name += 'L';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::M:
                                                click.play();
                                                name += 'M';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::N:
                                                click.play();
                                                name += 'N';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::O:
                                                click.play();
                                                name += 'O';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::P:
                                                click.play();
                                                name += 'P';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::Q:
                                                click.play();
                                                name += 'Q';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::R:
                                                click.play();
                                                name += 'R';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::S:
                                                click.play();
                                                name += 'S';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::T:
                                                click.play();
                                                name += 'T';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::U:
                                                click.play();
                                                name += 'U';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::V:
                                                click.play();
                                                name += 'V';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::W:
                                                click.play();
                                                name += 'W';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::X:
                                                click.play();
                                                name += 'X';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::Y:
                                                click.play();
                                                name += 'Y';
                                                playername.setString(name);
                                                break;
                                case sf::Keyboard::Z:
                                                click.play();
                                                name += 'Z';
                                                playername.setString(name);
                                                break;  
                                case sf::Keyboard::Space:
                                                click.play();
                                                name += ' ';
                                                playername.setString(name);
                                                break;    
                                case sf::Keyboard::BackSpace:
                                                click.play();
                                                if (!name.empty()) 
                                                {
                                                    name.pop_back();
                                                }
                                                playername.setString(name);
                                                break;                                                                          
                                default:
                                break;
                            }
                    break;
                
                default:
                    break;
                }
  
            }

            if (Keyboard::isKeyPressed(Keyboard::E)) // If left key is pressed
                window.close();


            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                name_enetered = 1;
                click.play();
                break;
            }


            window.clear();
            window.draw(sprite_name);
            window.draw(playername);
            window.display();
        }
    }


};
