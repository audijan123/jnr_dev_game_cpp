#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "dungeon_manager.hpp"
#include "mainStateManager.hpp"
#include "const.hpp"

namespace GMS
{
	class riftBrowser
	{
	public:
		riftBrowser(const uint16_t& iMobS);
		~riftBrowser();

		void eventRiftBrowser();
		void render(sf::RenderWindow *rw);
		void update();

		void deleteRift();

		void show();
		void hide();


	private:

		dungeon_manager			*pRiftManager;

		// Rift Menu //
		sf::Texture				pRiftMenuTexture[7];
		sf::Sprite				*pRiftMenuSprite[7];

		sf::Text				*pRiftMenuTitel;
		sf::Text				*pRiftMenuSchwierigkeit;
		sf::Text				*pRiftMenuText;
		sf::Text				*pRiftMenuTextHoch;

		std::vector<sf::Texture> p_texture;

		bool bRfitBrowserHardcore = false;

		uint16_t difficulty = 1;

	};







}