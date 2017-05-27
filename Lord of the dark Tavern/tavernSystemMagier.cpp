#include "tavernSystemMagier.hpp"

extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;
extern sf::Vector2f vMousePosition;

namespace GT
{
	magier::magier()
	{
		for (auto k = 0; k < 3; k++)
		{
			MagierTexture[k] = pSpriteErsteller->erstelle_texture("mage" + std::to_string(k + 2));
		}

		pMagierSprite = pSpriteErsteller->erstelle_sprite("mage1", false, sf::Vector2f(1000, 100), sf::Vector2f(2.67f, 2.85f));
	}

	magier::~magier()
	{
	}

	void magier::update()
	{

	}
	void magier::event()
	{
		if (osm::sprite_pressed(pMagierSprite, vMousePosition) && !pState->getTavernBankStatus() && !pState->getItemShopStatus())
		{
			std::cout << "mage test" << std::endl;
		}
	}
	void magier::render(sf::RenderWindow *rw)
	{
		rw->draw(*pMagierSprite);
	}

}