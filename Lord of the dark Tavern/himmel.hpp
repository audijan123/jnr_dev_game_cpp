#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "mainStateManager.hpp"

namespace GMS
{
	class himmel
	{
	public:
		himmel();
		~himmel();

		void update(float fUpdateZeit);
		void render(sf::RenderWindow *rw);

	private:

		sf::Sprite				*pWolkenSprite[2];




	};

}