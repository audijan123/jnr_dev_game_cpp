#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "main_os_manager.hpp"
#include "sfSpriteGen.hpp"
#include "mainStateManager.hpp"

#include "tavernSystemBank.hpp"
#include "tavernSystemMagier.hpp"
#include "tavernSystemVerkäufer.hpp"


namespace GT
{

	class tavernSystem
	{
	public:
		tavernSystem();
		~tavernSystem();


		void update();
		void event();
		void keyEvent(sf::Event *e);
		void render(sf::RenderWindow *rw);



	private:


		GT::bank		*pTavernBank;
		GT::verkäufer	*pTaverVerkäufer;
		GT::magier		*pTaverMagier;


		sf::Sprite		*pHintergrund;
		sf::Sprite		*pTresen;
		sf::Sprite		*pBoden;




		sf::Vector2f m_pos;


		bool u_menu = false;

		const sf::Vector2f scale = { 2.67f,2.85f };



	};
}
