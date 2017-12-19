#include "tavernSystem.hpp"

extern sf::Vector2f vMain;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;
extern sf::Font *pFont;

namespace GT
{

	tavernSystem::tavernSystem()
	{
		pHintergrund = pSpriteErsteller->erstelle_sprite("tavbg", false, sf::Vector2f(0.f, 0.f), scale);
		pTresen = pSpriteErsteller->erstelle_sprite("tavtr", false, sf::Vector2f(66.f, 370.f), scale);
		pBoden = pSpriteErsteller->erstelle_sprite("tavbo", false, sf::Vector2f(0.f, 366.f), scale);

		pTavernBank = new GT::bank();
		pTaverVerk�ufer = new GT::verk�ufer();
		pTaverMagier = new GT::magier();

	}

	tavernSystem::~tavernSystem()
	{


	}


	void tavernSystem::update()
	{
		if(pState->getTavernBankStatus())
		{
			pTavernBank->update();
		}
		else if (pState->getItemShopStatus())
		{
			pTaverVerk�ufer->update();
		}



	}

	void tavernSystem::event()
	{
		pTavernBank->event();
		pTaverMagier->event();
		pTaverVerk�ufer->event();

	}

	void tavernSystem::keyEvent(sf::Event *e)
	{
		pTavernBank->event_get_key(e);
	}

	void tavernSystem::render(sf::RenderWindow *rw)
	{
		rw->draw(*pBoden);
		rw->draw(*pHintergrund);
		rw->draw(*pTresen);

		pTaverMagier->render(rw);
		pTavernBank->render(rw);
		pTaverVerk�ufer->render(rw);


		if (pState->getTavernBankStatus())
		{
			pTavernBank->renderGUI(rw);
		}
		else if (pState->getItemShopStatus())
		{
			pTaverVerk�ufer->renderGUI(rw);
		}

	}

}