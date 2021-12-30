#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include "level.h"
#include "enemy.h"

void Enemy::checkCollisionWithMap(float Dx, float Dy)
	{ 
		for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		{
			if (obj[i].name == "solid")//если встретили препятствие
			{
                sf::FloatRect enemy_rect = getRect();
                if((enemy_rect.left < (obj[i].rect.left + obj[i].rect.width))){
                    if (Dx > 0)	{x += dx;}
                    if (Dx < 0) {x = obj[i].rect.left + obj[i].rect.width -2 * dx;}
                }
                if((obj[i].rect.left < (enemy_rect.left + enemy_rect.width)) && ((obj[i].rect.left + obj[i].rect.width) > (enemy_rect.left + enemy_rect.width))){
                    if (Dx > 0)	{x = obj[i].rect.left - enemy_rect.width -dx;}
                    if (Dx < 0) {x += dx;}
                }
			}
		}
	}

void Enemy::nothing(){
        if (state == _nothing){
            return;
        }
        state = _nothing;
        switch (dir)
        {
        case 1:
            dir = right;
            frames = &enemy_anima.attentionr;
            break;
        
        default:
            dir = left;
            frames = &enemy_anima.attentionl;
            break;
        }
        speed = 0.05;
        currentFrame = 0;
        dx = 0;
        dy = 0;
    }

void Enemy::move(){
        state = _move;
        if ((x_1 > x) && (x_0 < x)){
            dir = right;
            frames = &enemy_anima.mover;
        }
        else if ((x_1 < x) && (x_0 > x)){
            dir = left;
            frames = &enemy_anima.movel;
        } else{
            x_1 = x_1 + x_0;
            x_0 = x_1 - x_0;
            x_1 = x_1 - x_0;
            switch (dir)
            {
            case right:
                dir = left;
                frames = &enemy_anima.movel;
                currentFrame = 0;
                break;
            
            default:
                dir = right;
                frames = &enemy_anima.mover;
                currentFrame = 0;
                break;
            }
        }
        speed = 0.05;
        dx = 0.1 * dir;
        dy = 0;
    }

void Enemy::attention(){
        state = _attention;
        switch (dir)
        {
        case 1:
            dir = right;
            frames = &enemy_anima.attentionr;
            break;
        
        default:
            dir = left;
            frames = &enemy_anima.attentionl;
            break;
        }
        speed = 0.05;
        currentFrame = 0;
        dx = 0;
        dy = 0;
    }

void Enemy::run(float &playerx, float &playery){
        if(state == _punch){
            return;
        }
        x_1 = playerx + dir * 30;
        if (x_1 > x){
            if((state != _run) || (dir != right)){
                frames = &enemy_anima.mover;
                dir = right;
                currentFrame = 0;
            }
        }
        else{
            if((state != _run) || (dir != left)){
                dir = left;
                frames = &enemy_anima.movel;
                currentFrame = 0;
            }
        }
        dx = 0.1 * dir;
        speed = 0.05;
        dy = 0;
        state = _run;
    }

void Enemy::die(){
        if(state == _die){
            return;
        }
        state = _die;
        switch (dir)
        {
        case 1:
            dir = right;
            frames = &enemy_anima.dier;
            break;
        
        default:
            dir = left;
            frames = &enemy_anima.diel;
            break;
        }
        speed = 0.01;
        currentFrame = 0;
        dx = 0;
        dy = 0;
    }

void Enemy::punch (){
        state = _punch;
        switch (dir)
        {
        case 1:
            frames = &enemy_anima.punchr;
            break;
        
        default:
            frames = &enemy_anima.punchl;
            break;
        }
        speed = 0.01;
        currentFrame = 0;
        dy = 0;
        dx = 0;
    }

bool Enemy::checkPlayerInRange(float &playerx, float &playery, float rangex, float rangey){
        if ((abs(playerx - x) < rangex) && (abs(playery - y) < rangey)){
            return 1;
        }
        return 0;
    }

void Enemy::newState(float &playerx, float &playery){
        switch (state)
        {
        case _attention:
            run(playerx, playery);
            break;
        case _run:
            run(playerx, playery);
            if (checkPlayerInRange(playerx, playery, 27, 27)){
                punch();
            }
            break;
        case _punch:
            break;
        case _move:
            move();
            if(checkPlayerInRange(playerx, playery, 150, 50)){
                attention();
            }
            break;
        case _die:
            break;
        default:
            nothing();
            if(checkPlayerInRange(playerx, playery, 150, 50)){
                attention();
            }
            break;
        }
    }

void Enemy::update_die(float time){
        countOfFrames = frames->size() - 1;
        if (currentFrame > countOfFrames) currentFrame = countOfFrames;
        enemy_sprite.setTextureRect(frames->at(currentFrame));
        currentFrame += speed * time;
        enemy_sprite.setPosition(x, y);
    }

void Enemy::update_punch(float time){
        countOfFrames = frames->size() - 1;
        if (currentFrame > countOfFrames) {
            state = _nothing;
            return;
        }
        enemy_sprite.setTextureRect(frames->at(currentFrame));
        currentFrame += speed * time;
        checkCollisionWithMap(dx, dy);
        enemy_sprite.setPosition(x, y);
    }

void Enemy::update_run(float time){
        countOfFrames = frames->size() - 1;
        if (currentFrame > countOfFrames) currentFrame = 0;
        enemy_sprite.setTextureRect(frames->at(currentFrame));
        currentFrame += speed * time;
        checkCollisionWithMap(dx, dy);
        y += dy;
        x += dx;
        enemy_sprite.setPosition(x, y);
    }

void Enemy::update_move(float time){
        countOfFrames = frames->size() - 1;
        if (currentFrame > countOfFrames) currentFrame = 0;
        enemy_sprite.setTextureRect(frames->at(currentFrame));
        currentFrame += speed * time;
        y += dy;
        x += dx;
        enemy_sprite.setPosition(x, y);
    }

Enemy::Enemy(sf::Image &image, float X, float Y,
        std::string Name, int State, int d, TileMap &lvl){
        obj = lvl.getAllObjects();
		x = X;
        x_0 = x - 50;
        x_1 = x + 50;
        y = Y; 
        w = 33; 
        h = 43; 
        enemy_name = Name; 
		speed = 0; 
        dx = 0; 
        dy = 0;
		life = true; 
        onGround = true;
        currentFrame = 0;
        switch (State)
        {
        case 1:
            state = _move;
            break;
        
        default:
            state = _nothing;
            break;
        }
        switch (d)
        {
        case 1:
            dir = right;
            break;
        
        default:
            dir = left;
            break;
        }
		enemy_texture.loadFromImage(image);
		enemy_sprite.setTexture(enemy_texture);
        enemy_sprite.setTextureRect(sf::IntRect(36,53,-33,39));
        enemy_sprite.setPosition(X, Y);
        frames = &enemy_anima.main_frame;
	}

void Enemy::getDamage(){
        life = 0;
        die();
    }

bool Enemy::giveDamage(sf::FloatRect player){
		if (getRect().intersects(player))//проверяем пересечение игрока с объектом
		{      
            return 1;
		}
        return 0;
    }

void Enemy::update(float time, float playerx, float playery){
        newState(playerx, playery);
        switch (state)
        {
        case _punch:
            update_punch(time);
            break;
        case _run:
            update_run(time);
            break;
        case _move:
            update_move(time);
            break;
        case _die:
            update_die(time);
        default:
            countOfFrames = frames->size() - 1;
            if (currentFrame > countOfFrames) currentFrame = 0;
            enemy_sprite.setTextureRect(frames->at(currentFrame));
            currentFrame += speed * time;
            enemy_sprite.setPosition(x, y);
            break;
        }
    }

sf::FloatRect Enemy::getRect(){
        return enemy_sprite.getGlobalBounds();
    }

void Enemy::teleport(float new_x, float new_y, int new_state, int new_dir){
        switch (new_state)
        {
        case 1:
            state = _move;
            break;
        
        default:
            state = _nothing;
            break;
        }
        switch (new_dir)
        {
        case 1:
            dir = right;
            break;
        
        default:
            dir = left;
            break;
        }
        x = new_x;
        y = new_y;
        speed = 0; 
        dx = 0; 
        dy = 0;
		life = true; 
        onGround = true;
        x_0 = x - 50;
        x_1 = x + 50;
        enemy_sprite.setTextureRect(sf::IntRect(36,53,-33,39));
        enemy_sprite.setPosition(x, y);
        frames = &enemy_anima.main_frame;
    }

Enemy::statement Enemy::returnState(){
        return state;
    }