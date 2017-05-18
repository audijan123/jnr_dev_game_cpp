#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "sfSpriteGen.hpp"



namespace GMS
{
	class riftBrowser
	{
	public:
		riftBrowser(JGE::SpriteGen *s);
		~riftBrowser();

		void eventRiftBrowser(sf::Vector2f vMousePosition);
		void render(sf::RenderWindow *rw);
		void update();


	private:



		JGE::SpriteGen				*pSpriteErsteller;

		sf::Vector2f				vMousePosition;






	};







}