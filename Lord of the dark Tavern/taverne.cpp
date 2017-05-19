#include "taverne.hpp"


namespace GMS
{

	taverne::taverne(JGE::SpriteGen *pSpriteErsteller)
	{
		//Erstellen des "Tavernen" Objectes + zugehöriges Hover effekt
		//Object
		pTaverneSprite = pSpriteErsteller->erstelle_sprite("taver", false, sf::Vector2f(0.f, 230.f),
																		   sf::Vector2f(2.67f, 2.85f));
		//Hover
		pTaverneSpriteHover = pSpriteErsteller->erstelle_sprite("taveh", false, sf::Vector2f(95.f, 335.f),
																				 pTaverneSprite->getScale());
	}

	taverne::~taverne()
	{
	}


	void taverne::update(sf::Vector2f vMousePosiiton)
	{
		if (pTaverneSprite->getGlobalBounds().contains(vMousePosiiton))
		{
			bTavernHoverStatus = true;
		}
		else
		{
			bTavernHoverStatus = false;
		}
		
	}
	void taverne::eventTaverne()
	{

	}
	void taverne::render(sf::RenderWindow *rw)
	{
		rw->draw(*pTaverneSprite);
		if (bTavernHoverStatus)
		{
			rw->draw(*pTaverneSpriteHover);
		}
	}




}