#pragma once
#include <SFML/Graphics.hpp>
 
sf::View view;

void getplayercoordinateforview(float x,float y) { //функция для считывания координат игрока
	 /*float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края
 
	if (x < 320) tempX = 320;//убираем из вида левую сторону
	if (y < 240) tempY = 240;//верхнюю сторону
	if (y > 554) tempY = 554;//нижнюю сторону
    if (x < 640) tempX = 320;	*/
	view.setCenter(370, 263);
}