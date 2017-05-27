#pragma once

#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "mainStateManager.hpp"


namespace GMS
{
	class ui
	{
	public:
		ui(GMS::riftBrowser *rB);
		~ui();

		void update();

		void render(sf::RenderWindow *rw);

	private:

		GMS::riftBrowser		*pRiftBrowser;

		// Menu Button Objecte
		sf::Sprite			*pMenuButtonSprite[3];


	};

}