#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"

class enviroment_loader {
public:
	enviroment_loader();
	~enviroment_loader();

	void render_enviro(int id , sf::RenderWindow *render);

private:

	sf::Texture HintergrundTexturen[14];
	sf::Sprite	*pHintergrund;


	sf::Sprite	*pHimmel;
	sf::Sprite	*pWolken;

	sf::Vector2f scale = { 2.67f, 2.85f };

};