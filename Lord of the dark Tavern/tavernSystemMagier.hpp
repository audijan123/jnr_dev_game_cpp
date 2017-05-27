#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "mainStateManager.hpp"

namespace GT
{
	class magier
	{
	public:
		magier();
		~magier();

		void update();
		void event();
		void render(sf::RenderWindow *rw);

	private:

		sf::Texture				MagierTexture[3];
		sf::Sprite				*pMagierSprite;

	};
}