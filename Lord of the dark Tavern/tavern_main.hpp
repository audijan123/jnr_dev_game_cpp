#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>



class tavern_main
{
public:
	tavern_main(std::string const &path);
	~tavern_main();


	void update(float const &m_time);

	void render(sf::RenderWindow *rw);

	void test_func();
	

private:


	std::string m_path;

	sf::Texture *bg_tavern;
	sf::Texture *floor_tavern;
	sf::Texture *counter_tavern;
	sf::Texture *sell_man_t[3];
	sf::Image test_image;
	sf::Texture *mage_t[4];

	sf::Sprite *p_sell_man;
	sf::Sprite *p_mage;


	sf::Texture *safe_t[6];

	sf::Sprite *main_sprites[4];

	int test = 0;

};
