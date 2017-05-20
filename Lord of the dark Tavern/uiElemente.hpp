#pragma once

#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "tavern_main.hpp"


namespace GMS
{
	class ui
	{
	public:
		ui(JGE::SpriteGen *SpriteErsteller,GMS::riftBrowser *rB,tavern_main *t,const sf::Vector2f& main);
		~ui();

		void update(const sf::Vector2f& vMousePosition,const bool& bHauptfensterAk,bool bTaverneAk);

		void render(sf::RenderWindow *rw);

		bool getbRun() { return bRun; };
		bool getTavernStatus() { return bTavern; };

	private:

		GMS::riftBrowser	*pRiftBrowser;
		tavern_main			*pTaverne;


		// Menu Button Objecte
		sf::Sprite			*pMenuButtonSprite[3];


		bool bRun = true;
		bool bTavern = false;


	};

}