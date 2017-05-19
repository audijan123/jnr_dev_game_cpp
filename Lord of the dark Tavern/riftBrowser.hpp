#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "main_base.hpp"
#include "dungeon_manager.hpp"



namespace GMS
{
	class riftBrowser
	{
	public:
		riftBrowser(JGE::main_base *s, const sf::Vector2f& main,const std::string& mainPfad);
		~riftBrowser();

		void eventRiftBrowser(sf::Vector2f vMousePosition);
		void render(sf::RenderWindow *rw);
		void update();

		void deleteRift();

		bool getRiftBrowserStatus() { return bRiftBrowser; };
		bool getRiftStatus()		{ return bRift; };

		void show();
		void hide();


	private:

		dungeon_manager		*pRiftManager;
		JGE::main_base		*pResourcenManager;

		sf::Font			*pSchriftArt; //schriftart

		// Rift Menu //
		sf::Texture			*pRiftMenuTexture[7];
		sf::Sprite			*pRiftMenuSprite[7];

		sf::Text			*pRiftMenuTitel;
		sf::Text			*pRiftMenuSchwierigkeit;
		sf::Text			*pRiftMenuText;
		sf::Text			*pRiftMenuTextHoch;

		sf::Vector2f		vMousePosition;
		std::string			mainPfad;

		const uint8_t		iRiftBrowserSchriftGröße = 21;

		bool bRift = false;
		bool bRiftBrowser = false;
		bool bRfitBrowserHardcore = false;



		uint16_t difficulty = 1;






	};







}