#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "level.h"

class V{
private:
    class v_animation{
    public:
        std::vector<sf::IntRect> shiftr = {sf::IntRect(55, 1, 51, 33), sf::IntRect(110, 1, 45, 33), 
                                            sf::IntRect(160, 1, 33, 33), sf::IntRect(200, 1, 34, 33)
                                            };
        std::vector<sf::IntRect> shiftl = {sf::IntRect(106, 1, -51, 33), sf::IntRect(155, 1, -45, 33), 
                                            sf::IntRect(193, 1, -33, 33), sf::IntRect(234, 1, -34, 33)
                                            };
        std::vector<sf::IntRect> movel = {sf::IntRect(50 + 36, 154, -36, 35), sf::IntRect(90 + 45, 154, -45, 35),
                                        sf::IntRect(140 + 38, 154, -38, 35), sf::IntRect(180 + 37, 151, -37, 38),
                                        sf::IntRect(220 + 42, 154, -42, 35), sf::IntRect(265 + 45, 154, -45, 35),
                                        sf::IntRect(315 + 45, 154, -45, 35), sf::IntRect(365 + 40, 152, -40, 37),
                                        sf::IntRect(410 + 40, 154, -40, 35)
                                        };
        std::vector<sf::IntRect> mover = {sf::IntRect(50,154,36,35), sf::IntRect(90,154,45,35), 
                                        sf::IntRect(140,154,38,35), sf::IntRect(180,151,37,38),    
                                        sf::IntRect(220,154,42,35), sf::IntRect(265,154,45,35), 
                                        sf::IntRect(315,154,45,35),sf::IntRect(365,152,40,37), 
                                        sf::IntRect(410,154,40,35)
                                        };
        std::vector<sf::IntRect> stay = {sf::IntRect(36, 53, 35, 41), sf::IntRect(72, 53, 35, 41),
                                        sf::IntRect(108, 53, 33, 41), sf::IntRect(72, 53, 35, 41), 
                                        sf::IntRect(36, 53, 35, 41), sf::IntRect(145, 53, 33, 41),
                                        sf::IntRect(72, 53, 35, 41), sf::IntRect(108, 53, 33, 41), 
                                        sf::IntRect(220, 53, 33, 41), sf::IntRect(258, 53, 33, 41)};
        std::vector<sf::IntRect> main_frame = {sf::IntRect(40, 53, 32, 41)};
        std::vector<sf::IntRect> punchr = {sf::IntRect(40, 114, 60, 30), sf::IntRect(40, 114, 60, 30),
                                            sf::IntRect(105, 109, 50, 35), sf::IntRect(160, 112, 42, 32)
                                            };
        std::vector<sf::IntRect> punchl = {sf::IntRect(100, 114, -60, 30), sf::IntRect(100, 114, -60, 30), 
                                            sf::IntRect(155, 109, -50, 35),sf::IntRect(202, 112, -42, 32)
                                            };
        std::vector<sf::IntRect> punchudr = {sf::IntRect(210, 107, 47, 37), sf::IntRect(260, 107, 46, 37),
                                            sf::IntRect(310, 110, 46, 37), sf::IntRect(360, 107, 46, 37)
                                            };
        std::vector<sf::IntRect> punchudl = {sf::IntRect(257, 107, -47, 37), sf::IntRect(306, 107, -46, 37),
                                            sf::IntRect(356, 110, -46, 37), sf::IntRect(406, 107, -46, 37)
                                            };
        std::vector<sf::IntRect> splashr = {sf::IntRect(300, 250, 35, 30), sf::IntRect(300, 250, 35, 30),
                                            sf::IntRect(350, 250, 35, 30), sf::IntRect(401, 250, 35, 30)
                                            };
        std::vector<sf::IntRect> splashl = {sf::IntRect(335, 250, -35, 30), sf::IntRect(335, 250, -35, 30), 
                                            sf::IntRect(385, 250, -35, 30), sf::IntRect(436, 250, -35, 30)
                                            };
        std::vector<sf::IntRect> fallr    = {sf::IntRect(5, 199, 40, 45), sf::IntRect(50, 199, 36, 45), 
                                            sf::IntRect(90, 199, 39, 45), sf::IntRect(135, 199, 38, 45),
                                            sf::IntRect(180, 199, 37, 45)
                                            };
        std::vector<sf::IntRect> falll    = {sf::IntRect(45, 199, -40, 45), sf::IntRect(86, 199, -36, 45), 
                                            sf::IntRect(129, 199, -39, 45), sf::IntRect(173, 199, -38, 45),
                                            sf::IntRect(217, 199, -37, 45)
                                            };
        
        v_animation(){}
    } v_anima;
    float x, y, w, h, speed;
    float currentFrame;
    int countOfFrames;
    sf::Image v_image;
    sf::Texture v_texture;
    std::string v_text = "images/v_friend.png";
    std::vector<sf::IntRect>* frames;
    std::vector<sf::IntRect>* splash_frames;
    std::vector<Object> obj;

    float getDirectionGrad(sf::Vector2f mpos);
    float getDirectionRad(sf::Vector2f mpos);

    void checkCollisionWithMapX(float Dx);
    void checkCollisionWithMapY(float Dy);
    void checkCollisionWithMapYJump(float Dy);
    void update_gravity(float time);
    void update_jump(float time);
    void update_punch(float time);
    void update_shift(float time);
    
public:
    sf::Sprite v_sprite, splash_sprite;
    float dx, dy;
    bool onGround;
    bool life;
    enum direction{
        left = -1,
        down = -2,
        up = 2,
        right = 1,
        downleft = -4,
        downright = 4,
        upright = 3,
        upleft = -3,
        nothing = 0
    } dir;
    enum statement{
        _move,
        _stay,
        _punch = 2,
        _shift,
        _nothing,
        _jump,
        _fall
    } state;

    V(float X, float Y, TileMap &lev);
    
    void punch(sf::Vector2f mpos);
    
    void jump();
    void gravity();
    void move();
    void stay();
    void shift();

    void draw(sf::RenderWindow* window);
    void update(float time);

    float getVCoordinateX();
    float getVCoordinateY();
        //функции для проверки столкновений
    sf::FloatRect getRect();
    sf::FloatRect getSplashRect();
    sf::FloatRect getMainRect();
    void teleport(float new_x, float new_y);
};