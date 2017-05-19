#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"

namespace GMS
{
	class taverne
	{
	public:
		taverne(JGE::SpriteGen *pSpriteErsteller);
		~taverne();

		void update(sf::Vector2f vMousePosition);
		void eventTaverne();
		void render(sf::RenderWindow *rw);

		bool getTavernHover()  { return bTavernHoverStatus; };


	private:

	sf::Sprite			*pTaverneSprite;
	sf::Sprite			*pTaverneSpriteHover;
	bool bTavernHoverStatus = false;



	};


}