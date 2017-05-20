#include "hintergrund.hpp"

namespace GMS
{
	hintergrund::hintergrund(JGE::SpriteGen *pSpriteErsteller, GMS::riftBrowser *rB, GMS::himmel *h)
		: pRiftBrowser(rB) , pHimmel(h)
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


	void  hintergrund::update(const sf::Vector2f& vMousePosition,const bool& bTaverne,
							  sf::Event *pHauptEvent,const float& fUpdateZeit)
	{
		pRiftPortalSprite->rotate(1.3f);
		//pRiftPortalSprite->getGlobalBounds().contains(vMousePosition)
		if (osm::sprite_pressed(pRiftPortalSprite,vMousePosition) && !bTaverne &&
			pHauptEvent->key.code == sf::Mouse::Button::Left && !pRiftBrowser->getRiftBrowserStatus() &&
			!pRiftBrowser->getRiftStatus())
		{
			pHintergrundSprite->setTexture(RiftPortalTextureHover);
			pHimmelSprite->setTexture(RiftSkyTextureHover);

			bPortalHover = true;
			pRiftBrowser->show();
		}
		else if (!pRiftBrowser->getRiftBrowserStatus())
		{
			pHintergrundSprite->setTexture(HintergrundTexture);
			pHimmelSprite->setTexture(HimmelTexture);

			bPortalHover = false;
		}

		if (!bPortalHover && !pRiftBrowser->getRiftStatus() && !pRiftBrowser->getRiftBrowserStatus()) {
			pHimmel->update(fUpdateZeit);
		}
	}



	void hintergrund::render(sf::RenderWindow *rw)
	{
		rw->draw(*pHimmelSprite);
		if (!bPortalHover && !pRiftBrowser->getRiftStatus() && !pRiftBrowser->getRiftBrowserStatus()) {
			pHimmel->render(rw);
		}
		rw->draw(*pHintergrundSprite);
		rw->draw(*pRiftPortalSprite);
	}





}