#include <SFML/Graphics.hpp>
#include "lvls.h"

int main() {
    sf::Texture end_screentxt;
    end_screentxt.loadFromFile("images/lvl_end_screen.png");
    sf::Sprite end_screen;
    end_screen.setTexture(end_screentxt);
    end_screen.setTextureRect(sf::IntRect(0, 0, 740, 525));
    sf::Texture exit_txt;
    exit_txt.loadFromFile("images/exit.png");
    sf::Sprite exit;
    exit.setTexture(exit_txt);
    exit.setTextureRect(sf::IntRect(0, 0, 44, 30));
    sf::Image enemy_image;
    enemy_image.loadFromFile("images/enemy.png");

    sf::RenderWindow window(sf::VideoMode(740, 525), "katano_zero_maybe");
    Lvls lvls;
    
    lvls.lvl(exit, enemy_image, window, "tile_map/testenemy.tmx");
    lvls.lvl(exit, enemy_image, window, "tile_map/lvl1.tmx");
    lvls.peacefulLvl(exit, enemy_image, window, "tile_map/testparkur.tmx");
    lvls.lvl(exit, enemy_image, window, "tile_map/lvl2.tmx");
    lvls.level3(exit, enemy_image, window);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
            window.close();
        }
        window.clear();
        window.draw(end_screen);
        window.display();
    }
    return 0;
}