#pragma once

#include "SFML\Graphics.hpp"
#include <iostream>
#include <string>

class enviroment_loader {
public:
	enviroment_loader(std::string path);
	~enviroment_loader();



	sf::Texture get_texture(int id);


	void render_enviro(int id , sf::RenderWindow *render);

private:

	sf::Texture *enviroment[20];
	sf::Sprite	*pSprite;


	sf::Sprite	*pSky;
	sf::Sprite	*pClouds;

};