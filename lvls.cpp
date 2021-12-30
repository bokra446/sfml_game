#include <SFML/Graphics.hpp>
#include "V.h"
#include "view.h"
#include "enemy.h"
#include <iostream>
#include "level.h"
#include <map>
#include <utility>
#include <vector>
#include "lvls.h"

int Lvls::lvl(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window, std::string lvl_name){

        TileMap lvl;
        lvl.load(lvl_name);
        Object playerObj=lvl.getObject("player");
        std::vector<Object> enemyObj = lvl.getObjectsByName("enemy");
        Object exitObj = lvl.getObject("exit");
        exit.setPosition(exitObj.rect.left, exitObj.rect.top);

        V v(playerObj.rect.left, playerObj.rect.top, lvl);
        Enemy enemy1(enemy_image, enemyObj[0].rect.left, enemyObj[0].rect.top, "Enemy1", 1, 1, lvl);
        //Enemy enemy2(enemy_image, enemyObj[1].rect.left, enemyObj[1].rect.top, "Enemy2", 1, 1, lvl);
        std::vector<Enemy*> enemys; 
        enemys.push_back(&enemy1);
        //enemys.push_back(&enemy2);

        char counterpunch = 0, counterjump = 0, countershift = 0;
        view.reset(sf::FloatRect(0, 0, 740, 525));
        sf::Clock clock;
        
        while(window.isOpen()){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 5000;
            sf::Vector2f mpos;

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
                if ((event.type == sf::Event::KeyReleased)) v.stay();
            }

            if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (counterpunch < 2) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W))){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
                mpos = window.mapPixelToCoords(pixelPos);
                v.punch(mpos);
                ++counterpunch;
                countershift = 0;
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (counterjump < 2) && !(sf::Mouse::isButtonPressed(sf::Mouse::Left))){
                v.jump();
                ++counterjump;
                countershift = 0;
                counterpunch = 0;
            }
            else if (!v.onGround){
                v.gravity();
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (countershift < 2)){
                v.shift();
                ++countershift;
                counterpunch = 0;
                counterjump = 0;
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
                v.dir = v.left;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                v.dir = v.right;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else {
                v.stay();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            
            getplayercoordinateforview(v.getVCoordinateX(), v.getVCoordinateY());
            v.update(time);
            for (int i = 0; i < enemys.size(); ++i){
                enemys[i]->update(time, v.getVCoordinateX(), v.getVCoordinateY());
            }

            window.setView(view);
            window.clear();
            window.draw(lvl);
            v.draw(&window);
            for(int i = 0; i < enemys.size(); ++i)
                window.draw(enemys[i]->enemy_sprite);

            if((v.state == 2)){
                sf::FloatRect sword_rect = v.getSplashRect();
                for (int i = 0; i < enemys.size(); i++){
                    if(sword_rect.intersects(enemys.at(i)->getRect())){
                        enemys[i]->getDamage();
                        enemys.erase((enemys.begin() + i));
                        //std::cout << "Why i alive" << std::endl;
                    }
                }
            }

            if(enemys.empty()){
                window.draw(exit);
                if (v.getRect().intersects(exit.getGlobalBounds())){
                    return 1;
                }
            }
            if(!v.life){
                v.teleport(playerObj.rect.left, playerObj.rect.top);
                enemys.clear();
                enemy1.teleport(enemyObj[0].rect.left, enemyObj[0].rect.top, 1, 1);
                enemys.push_back(&enemy1);
                //enemy2.teleport(enemyObj[1].rect.left, enemyObj[1].rect.top, 1, 1);
                //enemys.push_back(&enemy2);
            }
            for(size_t i = 0; i < enemys.size(); ++i){
                if(( enemys.at(i)->returnState()== Enemy::statement::_punch) && (enemys.at(i)->giveDamage(v.getRect()))){
                    v.life = false;
                }
            }

            window.display();
        }
        return 0;
    }

int Lvls::peacefulLvl(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window, std::string lvl_name){

        TileMap lvl;
        lvl.load(lvl_name);
        Object playerObj=lvl.getObject("player");
        std::vector<Object> enemyObj = lvl.getObjectsByName("enemy");
        Object exitObj = lvl.getObject("exit");
        exit.setPosition(exitObj.rect.left, exitObj.rect.top);

        V v(playerObj.rect.left, playerObj.rect.top, lvl);

        char counterpunch = 0, counterjump = 0, countershift = 0;
        view.reset(sf::FloatRect(0, 0, 740, 525));
        sf::Clock clock;
        
        while(window.isOpen()){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 5000;
            sf::Vector2f mpos;

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
                if ((event.type == sf::Event::KeyReleased)) v.stay();
            }

            if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (counterpunch < 2) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W))){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
                mpos = window.mapPixelToCoords(pixelPos);
                v.punch(mpos);
                ++counterpunch;
                countershift = 0;
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (counterjump < 2) && !(sf::Mouse::isButtonPressed(sf::Mouse::Left))){
                v.jump();
                ++counterjump;
                countershift = 0;
                counterpunch = 0;
            }
            else if (!v.onGround){
                v.gravity();
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (countershift < 2)){
                v.shift();
                ++countershift;
                counterpunch = 0;
                counterjump = 0;
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
                v.dir = v.left;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                v.dir = v.right;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else {
                v.stay();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            
            getplayercoordinateforview(v.getVCoordinateX(), v.getVCoordinateY());
            v.update(time);

            window.setView(view);
            window.clear();
            window.draw(lvl);
            v.draw(&window);
            
                window.draw(exit);
                if (v.getRect().intersects(exit.getGlobalBounds())){
                    return 1;
                }

            window.display();
        }
        return 0;
    }

int Lvls::level3(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window){
        TileMap lvl;
        lvl.load("tile_map/lvl3.tmx");
        Object playerObj=lvl.getObject("player");
        std::vector<Object> enemyObj = lvl.getObjectsByName("enemy");
        Object exitObj = lvl.getObject("exit");
        exit.setPosition(exitObj.rect.left, exitObj.rect.top);

        V v(playerObj.rect.left, playerObj.rect.top, lvl);
        Enemy enemy1(enemy_image, enemyObj[0].rect.left, enemyObj[0].rect.top, "Enemy1", 1, 1, lvl);
        Enemy enemy2(enemy_image, enemyObj[1].rect.left, enemyObj[1].rect.top, "Enemy2", 1, 1, lvl);
        std::vector<Enemy*> enemys; 
        enemys.push_back(&enemy1);
        enemys.push_back(&enemy2);

        char counterpunch = 0, counterjump = 0, countershift = 0;
        view.reset(sf::FloatRect(0, 0, 740, 525));
        sf::Clock clock;
        
        while(window.isOpen()){
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 5000;
            sf::Vector2f mpos;

            sf::Event event;
            while (window.pollEvent(event)){
                if (event.type == sf::Event::Closed)
                    window.close();
                if ((event.type == sf::Event::KeyReleased)) v.stay();
            }

            if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (counterpunch < 2) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::W))){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);//забираем коорд курсора
                mpos = window.mapPixelToCoords(pixelPos);
                v.punch(mpos);
                ++counterpunch;
                countershift = 0;
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && (counterjump < 2) && !(sf::Mouse::isButtonPressed(sf::Mouse::Left))){
                v.jump();
                ++counterjump;
                countershift = 0;
                counterpunch = 0;
            }
            else if (!v.onGround){
                v.gravity();
            }
            else if((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) && (countershift < 2)){
                v.shift();
                ++countershift;
                counterpunch = 0;
                counterjump = 0;
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
                v.dir = v.left;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                v.dir = v.right;
                v.move();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            else {
                v.stay();
                countershift = 0;
                counterpunch = 0;
                counterjump = 0;
            }
            
            getplayercoordinateforview(v.getVCoordinateX(), v.getVCoordinateY());
            v.update(time);
            enemy1.update(time, v.getVCoordinateX(), v.getVCoordinateY());
            enemy2.update(time, v.getVCoordinateX(), v.getVCoordinateY());

            window.setView(view);
            window.clear();
            window.draw(lvl);
            v.draw(&window);
            for(int i = 0; i < enemys.size(); ++i)
            window.draw(enemys[i]->enemy_sprite);

            if((v.state == 2)){
                sf::FloatRect sword_rect = v.getSplashRect();
                for (int i = 0; i < enemys.size(); i++){
                    if(sword_rect.intersects(enemys.at(i)->getRect())){
                        enemys[i]->getDamage();
                        enemys.erase((enemys.begin() + i));
                        //std::cout << "Why i alive" << std::endl;
                    }
                }
            }

            if(enemys.empty()){
                window.draw(exit);
                if (v.getRect().intersects(exit.getGlobalBounds())){
                    return 1;
                }
            }
            if(!v.life){
                v.teleport(playerObj.rect.left, playerObj.rect.top);
                for(size_t j = 0; j < enemys.size(); ++j)
                    enemys.at(j)->teleport(enemyObj[j].rect.left, enemyObj[j].rect.top, 1, 1);
            }
            for(size_t i = 0; i < enemys.size(); ++i){
                if(( enemys.at(i)->returnState()== Enemy::statement::_punch) && (enemys.at(i)->giveDamage(v.getRect()))){
                    v.life = false;
                }
            }

            window.display();
        }
        return 0;        
    }

