#include <SFML/Graphics.hpp>
#include <string>

class Lvls{
public:
    int lvl(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window, std::string lvl_name);
    int peacefulLvl(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window, std::string lvl_name);
    int level3(sf::Sprite& exit, sf::Image& enemy_image, sf::RenderWindow& window);
};