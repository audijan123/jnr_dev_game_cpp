#include "himmel.hpp"

extern JGE::SpriteGen *pSpriteErsteller;
extern sf::Vector2f vMain;
extern JGE::mainStateManager *pState;


namespace GMS
{

	himmel::himmel()
	{
		// Wolken Objecte
		pWolkenSprite[0] = pSpriteErsteller->erstelle_sprite("cloud", false, sf::Vector2f(0.f, 0.f),
															sf::Vector2f(1.5f, 1.2f));
		pWolkenSprite[1] = pSpriteErsteller->erstelle_sprite("cloud", false, sf::Vector2f(-1200.f, 0.f),
															pWolkenSprite[0]->getScale());
	}

	himmel::~himmel()
	{
	}


	void himmel::update(float fUpdateZeit)
	{
		if (pState->getHimmelStatus())
		{
			if (pWolkenSprite[0]->getPosition().x >= vMain.x)
			{
				pWolkenSprite[0]->setPosition(0 - vMain.x, pWolkenSprite[0]->getPosition().y);
			}
			else if (pWolkenSprite[0]->getPosition().x <  vMain.x)
			{
				pWolkenSprite[0]->setPosition(pWolkenSprite[0]->getPosition().x + 60 * fUpdateZeit, pWolkenSprite[0]->getPosition().y);
			}
			if (pWolkenSprite[1]->getPosition().x >= vMain.x)
			{
				pWolkenSprite[1]->setPosition(0 - vMain.x, pWolkenSprite[1]->getPosition().y);
			}
			else if (pWolkenSprite[1]->getPosition().x < vMain.x)
			{
				pWolkenSprite[1]->setPosition(pWolkenSprite[1]->getPosition().x + 60 * fUpdateZeit, pWolkenSprite[1]->getPosition().y);
			}
		}

	}
	void himmel::render(sf::RenderWindow *rw)
	{
		if (pState->getHimmelStatus())
		{
			rw->draw(*pWolkenSprite[0]);
			rw->draw(*pWolkenSprite[1]);
		}
	}


}
