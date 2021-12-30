#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "level.h"
#include "v.h"

float V::getDirectionGrad(sf::Vector2f mpos){
    float dX = mpos.x - x;
    float dY = mpos.y - y;
    float rotation = (atan2(dY, dX)) * 180 / 3.14169265;
    return rotation;
}

float V::getDirectionRad(sf::Vector2f mpos){
    float dX = mpos.x - x;
    float dY = mpos.y - y;
    float rotation = (atan2(dY, dX));
    return rotation;
}

void V::checkCollisionWithMapX(float Dx)
{
	for (int i = 0; i < obj.size(); i++)//проходимся по объектам
	if ((getRect()).intersects(obj[i].rect))//проверяем пересечение игрока с объектом
	{
		if (obj[i].name == "solid")//если встретили препятствие
		{
            sf::FloatRect v_rect = getRect();
            if(((x < obj[i].rect.left) || (x > (obj[i].rect.left + obj[i].rect.width))) 
                && ((obj[i].rect.top) < (v_rect.top + v_rect.height / 2))){
                if (Dx>0)	{ 
                x = obj[i].rect.left - v_rect.width; 
                dx = 0;
                }
			    else	{ 
                    x = obj[i].rect.left + obj[i].rect.width + v_rect.width / 2; 
                    dx = 0;
                }
            }
		}
	}
}

void V::checkCollisionWithMapY(float Dy)
{
	for (int i = 0; i < obj.size(); i++)
    {
        sf::FloatRect v_rect = sf::FloatRect(v_anima.main_frame[0]);
        if ((getRect().intersects(obj[i].rect)) || (getMainRect().intersects(obj[i].rect)))//проверяем пересечение игрока с объектом
        {
            if (obj[i].name == "solid")//если встретили препятствие
            {
                if(Dy >= 0){
                    if((obj[i].rect.left <= x) && (obj[i].rect.left + obj[i].rect.width > x)){
                        y = obj[i].rect.top - h / 2;
                        onGround = true;
                        dy = 0;
                    }
                }
                else{y -= dy;}
            }
        }
    }
}

void V::checkCollisionWithMapYJump(float Dy){
    for (int i = 0; i < obj.size(); i++)
    {
        sf::FloatRect v_rect = sf::FloatRect(v_anima.main_frame[0]);
        if ((getRect().intersects(obj[i].rect)))//проверяем пересечение игрока с объектом
        {
            if (obj[i].name == "solid")//если встретили препятствие
            {
                if(Dy > 0){
                    if((obj[i].rect.left <= x) && (obj[i].rect.left + obj[i].rect.width > x)){
                        y = obj[i].rect.top - h / 2;
                        onGround = true;
                        dy = 0;
                    }
                }
                else{y -= dy;}
            }
        }
    }
}

void V::update_gravity(float time){
    countOfFrames = frames->size() - 1;
    if (currentFrame > countOfFrames) currentFrame = 0;
    v_sprite.setTextureRect(frames->at(currentFrame));
    currentFrame += speed * time;
    checkCollisionWithMapY(dy);
    y += dy;
    dy += 0.1;
    checkCollisionWithMapX(dx);
    x += dx;
    v_sprite.setPosition(x, y);
}

void V::update_jump(float time){
    countOfFrames = frames->size() - 1;
    if (currentFrame > countOfFrames) {
        state = _nothing;
        return;
    }
    v_sprite.setTextureRect(frames->at(currentFrame));
    currentFrame += speed * time;
    checkCollisionWithMapYJump(dy);
    y += dy;
    dy += 0.001;
    checkCollisionWithMapX(dx);
    x += dx;
    v_sprite.setPosition(x, y);
}

void V::update_punch(float time){
    countOfFrames = frames->size() - 1;
    if (currentFrame > countOfFrames) {
        state = _nothing;
        return;
    }
    v_sprite.setTextureRect(frames->at(currentFrame));
    splash_sprite.setTextureRect(splash_frames->at(currentFrame));
    currentFrame += speed * time;
    checkCollisionWithMapYJump(dy);
    y += dy;
    checkCollisionWithMapX(dx);
    x += dx;
    v_sprite.setPosition(x, y);
    splash_sprite.setPosition(x + 10 + dx * 600, y + dy * 400);
}

void V::update_shift(float time){
    countOfFrames = frames->size() - 1;
    if (currentFrame > countOfFrames) {
        state = _nothing;
        return;
    }
    v_sprite.setTextureRect(frames->at(currentFrame));
    currentFrame += speed * time;
    checkCollisionWithMapY(dy);
    y += dy;
    checkCollisionWithMapX(dx);
    x += dx;
    v_sprite.setPosition(x, y);
}

 V::V(float X, float Y, TileMap &lev){
        obj = lev.getAllObjects();
        v_image.loadFromFile(v_text);
        v_texture.loadFromImage(v_image);
        v_sprite.setTexture(v_texture);
        splash_sprite.setTexture(v_texture);
        x = X;
        y = Y;
        w = 32;
        h = 41;
        dir = right;
        v_sprite.setTextureRect(sf::IntRect(40, 53, w, h));
        v_sprite.setPosition(x, y);
        v_sprite.setOrigin(w/2, h/2);
        splash_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
        splash_sprite.setOrigin(17, 15);
        
        onGround = false;
        life = 1;
        currentFrame = 0;
        state = _nothing;
        frames = &v_anima.main_frame;
        splash_frames = &v_anima.splashr;
    }

void V::punch(sf::Vector2f mpos){
        if ((state == _shift) || (state == _punch)){
            return;
        }
        float rotation = getDirectionGrad(mpos);
        if ((rotation < 45) && (rotation > -45)){
            dir = right;
            frames = &v_anima.punchr;
            splash_frames = &v_anima.splashr;
            splash_sprite.setRotation(0);
            onGround = false;
        }
        else if ((rotation > 135) || (rotation < -135)){
            dir = left;
            frames = &v_anima.punchl;
            splash_frames = &v_anima.splashl;
            splash_sprite.setRotation(0);
            onGround = false;
        }
        else if ((rotation >= 45) && (rotation <= 90)){
            dir = downright;
            frames = &v_anima.punchudr;
            splash_frames = &v_anima.splashr;
            splash_sprite.setRotation(rotation);
            onGround = false;
        }
        else if ((rotation <= 135) && (rotation > 90)){
            dir = downleft;
            frames = &v_anima.punchudl;
            splash_frames = &v_anima.splashl;
            splash_sprite.setRotation(90 - rotation);
            onGround = false;
        }
        else if ((rotation >= -135) && (rotation < -90)){
            dir = upleft;
            frames = &v_anima.punchudl;
            splash_frames = &v_anima.splashl;
            splash_sprite.setRotation(90 + rotation);
            onGround = false;
            onGround = false;
        }
        else{
            dir = upright;
            frames = &v_anima.punchudr;
            splash_frames = &v_anima.splashr;
            splash_sprite.setRotation(rotation);
            onGround = false;
        }

        rotation = getDirectionRad(mpos);
        state = _punch;
        dx = 0.1 * cos(rotation);
        dy = (sin(rotation)) * 0.1;
        speed = 0.07;
        currentFrame = 0;
    }

void V::jump(){
        switch (dir)
        {
        case right:
            frames = &v_anima.punchudr;
            dx = 0.1;
            break;
        
        default:
            frames = &v_anima.punchudl;
            dx = -0.1;
            break;
        }
        state = _jump;
        dy = -0.3;
        speed = 0.005;
        onGround = false;
        currentFrame = 0;
    }

void V::gravity(){
        if (((state != _nothing) && (state != _move)) || (state == _jump)){
            return;
        }
        dy = 0.1;
        switch (dir)
        {
        case 1:
            frames = &v_anima.fallr;
            break;
        case 2:
            frames = &v_anima.fallr;
            break;
        case 3:
            frames = &v_anima.fallr;
            break;
        case 4:
            frames = &v_anima.fallr;
            break;
        case 5:
            frames = &v_anima.fallr;
            break;
        default:
            frames = &v_anima.falll;
            break;
        }
        state = _fall;
        speed = 0.1;
        currentFrame = 0;
    }

void V::move(){
        if((onGround == false)){
            gravity();
            return;
        }
        if ((state == _move) || (state == _shift) || (state == _punch) || (onGround == 0)){
            return;
        }
        state = _move;
        if (dir == right) {
            frames = &v_anima.mover;
        } 
        else frames = &v_anima.movel;
        speed = 0.05;
        currentFrame = 0;
        dx = 0.1 * dir;
        dy = 0;
        onGround = false;
    }

void V::stay(){
        if(onGround == 0){
            gravity();
            return;
        }
        if((state == _stay) || (state == _shift) || (state == _punch) || (onGround == 0)){
            return;
        }
        frames = &v_anima.stay;
        state = _stay;
        speed = 0.005;
        dx = 0;
        dy = 0;
    }

void V::shift(){
        if((state == _shift) || (state == _punch) || (onGround == 0)){
            return;
        }
        dx = dir * 0.07;
        currentFrame = 0;
        speed = 0.05;
        dy = 0;
        state = _shift;
        if (dir == right){
            frames = &v_anima.shiftr;
        }
        else frames = &v_anima.shiftl;
        onGround = false;
    }

void V::draw(sf::RenderWindow* window){
        window->draw(v_sprite);
        if (state == _punch){
            window->draw(splash_sprite);
        }
    }

void V::update(float time){
        switch (state)
        {
        case _jump:
            update_jump(time);
            break;
        case _shift:
            update_shift(time);
            break;
        case _punch:
            update_punch(time);
            break;
        default:
            countOfFrames = frames->size() - 1;
            if (currentFrame > countOfFrames) currentFrame = 0;
            v_sprite.setTextureRect(frames->at(currentFrame));
            currentFrame += speed * time;
            checkCollisionWithMapX(dx);
            x += dx;
            checkCollisionWithMapY(dy);
            y += dy;
            v_sprite.setPosition(x, y);
            //std::cout << onGround << std::endl;
            if (!onGround){
                gravity();
            }
            break;
        }
    }

float V::getVCoordinateX(){
        return x;
    }
float V::getVCoordinateY(){
        return y;
    }
sf::FloatRect V::getRect(){//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return v_sprite.getGlobalBounds();//эта ф-ция нужна для проверки столкновений 
	}
sf::FloatRect V::getSplashRect(){
        return splash_sprite.getGlobalBounds();
    }

sf::FloatRect V::getMainRect(){
        sf::Sprite t;
        t.setPosition(x, y);
        t.setTextureRect(v_anima.main_frame[0]);
        return t.getGlobalBounds();
    }

void V::teleport(float new_x, float new_y){
        x = new_x;
        y = new_y;
        dir = right;
        v_sprite.setTextureRect(sf::IntRect(40, 53, w, h));
        v_sprite.setPosition(x, y);
        splash_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
        splash_sprite.setOrigin(17, 15);
        
        onGround = false;
        life = 1;
        currentFrame = 0;
        state = _nothing;
        frames = &v_anima.main_frame;
        splash_frames = &v_anima.splashr;
    }