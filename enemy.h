#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "level.h"

class Enemy {
private:
    class enemy_animation{
    public:
        std::vector<sf::IntRect> mover = {sf::IntRect(1,3,26,43), sf::IntRect(31,3,28,43), 
                                        sf::IntRect(62,3,25,43), sf::IntRect(94,3,24,43),     
                                        sf::IntRect(128,3,24,43)
                                        };
        std::vector<sf::IntRect> movel = {sf::IntRect(27,3,-26,43), sf::IntRect(59,3,-28,43), 
                                        sf::IntRect(87,3,-25,43), sf::IntRect(118,3,-24,43),     
                                        sf::IntRect(152,3,-24,43)
                                        };
        std::vector<sf::IntRect> attentionr = {sf::IntRect(3,53,33,39), sf::IntRect(50,53,33,39), 
                                        };
        std::vector<sf::IntRect> attentionl = {sf::IntRect(36,53,-33,39), sf::IntRect(83,53,-33,39), 
                                        };
        std::vector<sf::IntRect> main_frame = {sf::IntRect(36,53,-33,39)};
        std::vector<sf::IntRect> punchl = {sf::IntRect(44,94,-42,41), sf::IntRect(93,94,-48,41), 
                                        sf::IntRect(140,94,-43,41), sf::IntRect(179,94,-38,41),     
                                        sf::IntRect(221,94,-31,41)
                                        };
        std::vector<sf::IntRect> punchr = {sf::IntRect(2,94,42,41), sf::IntRect(45,94,48,41), 
                                        sf::IntRect(97,94,43,41), sf::IntRect(141,94,38,41),     
                                        sf::IntRect(180,94,31,41)
                                        };
        std::vector<sf::IntRect> dier = {sf::IntRect(4,140,41,37), sf::IntRect(48,140,32,37), 
                                        sf::IntRect(85,140,45,37), sf::IntRect(130,140,50,37),
                                        };
        std::vector<sf::IntRect> diel = {sf::IntRect(45,140,-41,37), sf::IntRect(80,140,-32,37), 
                                        sf::IntRect(130,140,-45,37), sf::IntRect(180,140,-50,37),
                                        };
    }enemy_anima;

	sf::Texture enemy_texture;
	std::string enemy_name;

    float currentFrame;
    int countOfFrames;
    std::vector<sf::IntRect>* frames;
    std::vector<Object> obj;

    float dx, dy, x, y, x_0, x_1, speed;
    int w,h;
	bool life, onGround;
    enum direction{
        left = -1,
        right = 1,
    } dir;

    //проверка соприкосновения с стенками
    void checkCollisionWithMap(float Dx, float Dy);


    //блок управления анимациями состояний
    void nothing();

    void move();

    void attention();
    
    void run(float &playerx, float &playery);

    void die();

    void punch ();

    //проверка на местоположение игрока
    bool checkPlayerInRange(float &playerx, float &playery, float rangex, float rangey);

    //менеджер состояний
    void newState(float &playerx, float &playery);

    //обновление картинки и местоположения
    void update_die(float time);
    void update_punch(float time);

    void update_run(float time);

    void update_move(float time);
public:
    sf::Sprite enemy_sprite;
    enum statement{
            _move = 1,
            _punch = 2,
            _attention = 3,
            _nothing = 0,
            _run = 4,
            _die = 5
    } state;

	Enemy(sf::Image &image, float X, float Y,
        std::string Name, int State, int d, TileMap &lvl);

    void getDamage();

    bool giveDamage(sf::FloatRect player);

    //менеджер обновления
    void update(float time, float playerx, float playery);

    sf::FloatRect getRect();
    
    //возвращение на изначальную позицию
    void teleport(float new_x, float new_y, int new_state, int new_dir);

    statement returnState();
};