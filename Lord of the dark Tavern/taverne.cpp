#include "taverne.hpp"

extern sf::Vector2f				vMousePosition;
extern JGE::SpriteGen			*pSpriteErsteller;
extern JGE::mainStateManager	*pState;

namespace GMS
{

	taverne::taverne()
	{
		//Laden der Taverne und dessen Funktionen
		pTavernSystem = new GT::tavernSystem();
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


	void taverne::update()
	{
		if (pTaverneSprite->getGlobalBounds().contains(vMousePosition) && !pState->getTavernStatus())
		{
			pState->setTavernHoverStatus(true);
		}
		else
		{
			pState->setTavernHoverStatus(false);
		}

		if (pState->getTavernStatus())
		{
			pTavernSystem->update();
		}
		
	}
	void taverne::eventTaverne()
	{
		if (pState->getTavernHoverStatus() && pState->getHauptFensterStatus() && !pState->getRiftStatus())
		{
			pState->setTavernStatus(true);
			pState->setHauptFensterStatus(false);
		}
		else if (pState->getTavernStatus())
		{
			pTavernSystem->event();
		}
	}
	void taverne::keyEvent(sf::Event *e)
	{
		pTavernSystem->keyEvent(e);
	}
	void taverne::render(sf::RenderWindow *rw)
	{

		if (!pState->getTavernStatus())
		{
			rw->draw(*pTaverneSprite);
		}
		if (pState->getTavernHoverStatus())
		{
			rw->draw(*pTaverneSpriteHover);
		}
		if (pState->getTavernStatus())
		{
			pTavernSystem->render(rw);
		}
	}




}