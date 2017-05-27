#include "hintergrund.hpp"

extern sf::Vector2f vMousePosition;
extern JGE::SpriteGen *pSpriteErsteller;
extern JGE::mainStateManager *pState;

namespace GMS
{
	hintergrund::hintergrund(GMS::himmel *h, GMS::riftBrowser *rb)
		: pHimmel(h), pRiftBrowser(rb)
	{
		//Hintergrund für das pHauptFenster erstellen und einen sf::Sprite zuordnen
		HintergrundTexture = pSpriteErsteller->erstelle_texture("backg");
		pHintergrundSprite = new sf::Sprite;

		pHintergrundSprite->setTexture(HintergrundTexture);

		pHintergrundSprite->setScale(2.67f, 2.85f);

								   // Himmel Object
		HimmelTexture = pSpriteErsteller->erstelle_texture("skybb");
		pHimmelSprite = new sf::Sprite;

		pHimmelSprite->setTexture(HimmelTexture);

		pHimmelSprite->setScale(2.67f, 2.85f);


		// Rift Portal und Rift Portal Hover//
		//Object
		pRiftPortalSprite = pSpriteErsteller->erstelle_sprite("porta", true, sf::Vector2f(1100.f, 390.f), sf::Vector2f(0.5f, 0.5f));

		//Hover
		RiftPortalTextureHover = pSpriteErsteller->erstelle_texture("porth");
		RiftSkyTextureHover = pSpriteErsteller->erstelle_texture("skybc");
	}

	hintergrund::~hintergrund()
	{
	}


	void  hintergrund::update(const float& fUpdateZeit)
	{
		pRiftPortalSprite->rotate(1.3f);
		if (!pState->getRiftBrowserStatus())
		{
			pHintergrundSprite->setTexture(HintergrundTexture);
			pHimmelSprite->setTexture(HimmelTexture);

			pState->setPortalHoverStatus(false);
		}

		if (!pState->getPortalHoverStatus()) {
			pHimmel->update(fUpdateZeit);
		}
	}

	void hintergrund::event()
	{
		if (osm::sprite_pressed(pRiftPortalSprite, vMousePosition) && pState->getHauptFensterStatus())
		{
			pHintergrundSprite->setTexture(RiftPortalTextureHover);
			pHimmelSprite->setTexture(RiftSkyTextureHover);

			pState->setPortalHoverStatus(true);
			pRiftBrowser->show();
		}
	}



	void hintergrund::render(sf::RenderWindow *rw)
	{
		rw->draw(*pHimmelSprite);
		if (!pState->getPortalHoverStatus() && !pState->getRiftStatus() && !pState->getRiftBrowserStatus()) {
			pHimmel->render(rw);
		}
		rw->draw(*pHintergrundSprite);
		rw->draw(*pRiftPortalSprite);
	}





}