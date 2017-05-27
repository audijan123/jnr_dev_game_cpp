#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"
#include "mainStateManager.hpp"
#include "tavernSystem.hpp"

namespace GMS
{
	class taverne
	{
	public:
		taverne();
		~taverne();

		void update();
		void eventTaverne();
		void keyEvent(sf::Event *e);
		void render(sf::RenderWindow *rw);


	private:
	// Tavernen Systeme
	GT::tavernSystem		*pTavernSystem;

	sf::Sprite				*pTaverneSprite;
	sf::Sprite				*pTaverneSpriteHover;



	};


}