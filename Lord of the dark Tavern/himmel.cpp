#include "himmel.hpp"

namespace GMS
{

	himmel::himmel(JGE::SpriteGen *SpriteErsteller, const sf::Vector2f& main)
		: main(main)
	{
		// Wolken Objecte
		pWolkenSprite[0] = SpriteErsteller->erstelle_sprite("cloud", false, sf::Vector2f(0.f, 0.f),
															sf::Vector2f(1.5f, 1.2f));
		pWolkenSprite[1] = SpriteErsteller->erstelle_sprite("cloud", false, sf::Vector2f(-1200.f, 0.f),
															pWolkenSprite[0]->getScale());
	}

	himmel::~himmel()
	{
	}


	void himmel::update(float fUpdateZeit)
	{
		if (bHimmel)
		{
			if (pWolkenSprite[0]->getPosition().x >= main.x)
			{
				pWolkenSprite[0]->setPosition(0 - main.x, pWolkenSprite[0]->getPosition().y);
			}
			else if (pWolkenSprite[0]->getPosition().x <  main.x)
			{
				pWolkenSprite[0]->setPosition(pWolkenSprite[0]->getPosition().x + 60 * fUpdateZeit, pWolkenSprite[0]->getPosition().y);
			}
			if (pWolkenSprite[1]->getPosition().x >= main.x)
			{
				pWolkenSprite[1]->setPosition(0 - main.x, pWolkenSprite[1]->getPosition().y);
			}
			else if (pWolkenSprite[1]->getPosition().x < main.x)
			{
				pWolkenSprite[1]->setPosition(pWolkenSprite[1]->getPosition().x + 60 * fUpdateZeit, pWolkenSprite[1]->getPosition().y);
			}
		}

	}
	void himmel::render(sf::RenderWindow *rw)
	{
		if (bHimmel)
		{
			rw->draw(*pWolkenSprite[0]);
			rw->draw(*pWolkenSprite[1]);
		}
	}

	void himmel::hide()
	{
		bHimmel = false;
	}
	void himmel::show()
	{
		bHimmel = true;
	}


}
