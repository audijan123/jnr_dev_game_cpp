#pragma once

#include <SFML\Graphics.hpp>
#include "sfSpriteGen.hpp"

namespace GMS
{
	class himmel
	{
	public:
		himmel(JGE::SpriteGen *SpriteErsteller,const sf::Vector2f& main);
		~himmel();

		void update(float fUpdateZeit);
		void render(sf::RenderWindow *rw);

		void hide();
		void show();

	private:

		sf::Sprite			*pWolkenSprite[2];

		sf::Vector2f		main;

		bool bHimmel = true;


	};

}