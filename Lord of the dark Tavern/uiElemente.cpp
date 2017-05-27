#include "uiElemente.hpp"

extern sf::Vector2f vMain;
extern sf::Vector2f vMousePosition;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;



namespace GMS 
{
	ui::ui(GMS::riftBrowser *rB)
		: pRiftBrowser(rB)
	{
		// Menu Button Objecte
		for (uint16_t i = 0; i < 3; i++)
		{
			pMenuButtonSprite[i] = pSpriteErsteller->erstelle_sprite("btn", false, sf::Vector2f(vMain.x - (50 * (i + 1)), 0.f),
				sf::Vector2f(1.7f, 1.7f), i + 100);
		}

	}

	ui::~ui()
	{
	}

	void ui::update()
	{
		if (osm::sprite_pressed(pMenuButtonSprite[0], vMousePosition))
		{
			if (pState->getRiftStatus())
			{
				pRiftBrowser->deleteRift();
			}
			else if (pState->getHauptFensterStatus())
			{
				pState->setProgrammStatus(false);
			}
			else if (pState->getRiftBrowserStatus())
			{
				pRiftBrowser->hide();
			}
			else if (pState->getTavernStatus()) // tavern under menu
			{
				pState->setTavernStatus(false);
				pState->setHauptFensterStatus(true);
			}
		}
	}

	void ui::render(sf::RenderWindow *rw)
	{
		for (auto i = 0; i < 3; i++)
		{
			rw->draw(*pMenuButtonSprite[i]);
		}
	}


}
