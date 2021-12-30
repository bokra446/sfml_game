/*
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "Hero!");

    sf::Image heroImage;
    heroImage.loadFromFile("images/hero.png"); // загрузка текстуры
    sf::Texture heroTexture;
    heroTexture.loadFromImage(heroImage);
    sf::Sprite heroSprite;
    heroSprite.setTexture(heroTexture);
    heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96)); // прогружаем нужный квадрат
    heroSprite.setPosition(50,25);

    sf::Clock clock;
    float currentFrame = 0;
    //float heroTelepot;
    //shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) //основное событие, которое работает, пока не зарыто окно
    {
        sf::Event event;
        while (window.pollEvent(event)) //отвечает за закрытие окна
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //отвечает за fps, чем больше делитель, тем больше плавность и больше действий
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        //игра с телепортом
        /// *
        heroTelepot += time;
        if(heroTelepot > 3000){
            heroSprite.setPosition(0, 120);
            heroTelepot = 0;
        }
        //* /
        //std::cout << time << std::endl;

        //движение с помощью клавиатуры и покраска мышкой
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) { 
            currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 3) 
                currentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
			heroSprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 96, 96, 96)); //проходимся по координатам Х. получается начинаем рисование с координаты Х равной 0,96,96*2, и опять 0
            heroSprite.move(-0.1 * time, 0); 
            //heroSprite.setTextureRect(sf::IntRect(0, 96, 96, 96)); 
        } //добавили управление на клавиши W,S,A,D
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) { 
            currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 3) 
                currentFrame -= 3;
            heroSprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 192, 96, 96));
            heroSprite.move(0.1 * time, 0); 
            //heroSprite.setTextureRect(sf::IntRect(0, 192, 96, 96)); 
        } 
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) { 
            currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 3) 
                currentFrame -= 3; 
            heroSprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 288, 96, 96));
            heroSprite.move(0, -0.1 * time);
            //heroSprite.setTextureRect(sf::IntRect(0, 288, 96, 96)); 
        } 
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) { 
            currentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (currentFrame > 3) 
                currentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			heroSprite.setTextureRect(sf::IntRect(96 * int(currentFrame), 0, 96, 96));
            heroSprite.move(0, 0.1 * time); 
            //heroSprite.setTextureRect(sf::IntRect(0, 0, 96, 96)); 
        }  
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			heroSprite.setColor(sf::Color::Red);
		}
        //очистка старого и отрисовка нового
        window.clear();
        window.draw(heroSprite);
        window.display();
    }

    return 0;
}
*/

#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h" //подключили код с картой
 
using namespace sf;
 
 
 
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player { 
private:
	float x, y;
public:
	float w, h, dx, dy, speed ; 
	int dir ; 
	String File;
	Image image;
	Texture texture;
	Sprite sprite;
	Player(String F, float X, float Y, float W, float H){
                dx=0; dy=0; speed=0; dir = 0;
		File = F;
		w = W; h = H;
		image.loadFromFile("images/" + File);
		image.createMaskFromColor(Color(41, 33, 59));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;
		sprite.setTextureRect(IntRect(0, 0, w, h)); 
	}
	void update(float time) 
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}
 
		x += dx*time;
		y += dy*time;
 
		speed = 0;
		sprite.setPosition(x,y);
	}
	float getplayercoordinateX(){	//этим методом будем забирать координату Х	
		return x;
	}
	float getplayercoordinateY(){	//этим методом будем забирать координату Y 	
		return y;
	}
};
 
 
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Lesson 9. kychka-pc.ru");
 
	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
 
 
	Player p("hero.png", 250, 250, 96.0, 96.0);
 
	float CurrentFrame = 0;
	Clock clock;
 
	while (window.isOpen())
	{
 
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
 
 
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
 
 
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 1; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
		}
 
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
		}
 
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); 
 
		}
 
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { 
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005*time; 
			if (CurrentFrame > 3) CurrentFrame -= 3; 
			p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); 
 
		}
		p.update(time);
 
	
		window.clear();
 
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик
 
 
			s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
 
			window.draw(s_map);//рисуем квадратики на экран
		}
 
 
		window.draw(p.sprite);
		window.display();
	}
 
	return 0;
}