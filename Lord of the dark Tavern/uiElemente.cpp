#include "uiElemente.hpp"

namespace GMS 
{
	ui::ui(JGE::SpriteGen *pSpriteErsteller, GMS::riftBrowser *rB, tavern_main *t, const sf::Vector2f& main)
		: pRiftBrowser(rB), pTaverne(t)
	{
		// Menu Button Objecte
		for (uint16_t i = 0; i < 3; i++)
		{
			pMenuButtonSprite[i] = pSpriteErsteller->erstelle_sprite("btn", false, sf::Vector2f(main.x - (50 * (i + 1)), 0.f),
				sf::Vector2f(1.7f, 1.7f), i + 100);
		}

	}

	ui::~ui()
	{
	}

	void ui::update(const sf::Vector2f& vMousePosition, const bool& bHauptfensterAk,  bool bTaverneAk)
	{
		bTavern = bTaverneAk;
		if (osm::sprite_pressed(pMenuButtonSprite[0], vMousePosition))
		{
			if (pRiftBrowser->getRiftStatus())
			{
				pRiftBrowser->deleteRift();
			}
			else if (bHauptfensterAk)
			{
				bRun = false;
			}
			else if (pRiftBrowser->getRiftBrowserStatus())
			{
				pRiftBrowser->hide();
			}
			else if (bTavern && !pTaverne->o_menu())
			{
				bTavern = false;
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
