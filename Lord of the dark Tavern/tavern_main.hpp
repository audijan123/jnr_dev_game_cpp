#pragma once


#include <iostream>
#include <SFML\Graphics.hpp>



class tavern_main
{
public:
	tavern_main(std::string const &path);
	~tavern_main();


	void update();

	void render(sf::RenderWindow *rw);
	

private:


	std::string m_path;

	sf::Texture *bg_tavern;
	sf::Texture *floor_tavern;
	sf::Texture *counter_tavern;
	sf::Texture *sell_man_t;
	sf::Texture *mage_t;

	sf::Sprite *p_sell_man;
	sf::Sprite *p_mage;

	sf::Sprite *main_sprites[3];


};
