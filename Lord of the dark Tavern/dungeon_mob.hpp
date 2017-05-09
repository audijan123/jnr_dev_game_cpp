#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"

class mob
{
public:
	mob(uint16_t position, const sf::Image Image, int diffi, int m_class, const sf::Font *pfont, const sf::Image hp_Image);
	~mob();

	int get_life() { return m_life; };
	sf::Sprite getSprite() { return *p_sprite; };
	void attack();
	void render(sf::RenderWindow *rw);

private:
	int m_life = 1000;
	sf::Sprite *p_sprite;
	sf::Texture *p_texture;


	sf::Sprite *p_sprite_life;
	sf::Texture *p_texture_life;

	sf::Text p_life;

};
