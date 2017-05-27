#pragma once

#include "sfSpriteGen.hpp"
#include "himmel.hpp"
#include "main_os_manager.hpp"
#include "mainStateManager.hpp"
#include "riftBrowser.hpp"



namespace GMS
{
	class hintergrund
	{
	public:
		hintergrund(GMS::himmel *h,GMS::riftBrowser *rb);
		~hintergrund();

		void update(const float& fUpdateZeit);

		void event();

		void render(sf::RenderWindow *rw);

	private:

		GMS::himmel				*pHimmel;
		GMS::riftBrowser		*pRiftBrowser;

		//Hintergrund
		sf::Texture				HintergrundTexture;
		sf::Sprite				*pHintergrundSprite;

		//Umwelt
		// Himmel Objecte
		sf::Texture				HimmelTexture;
		sf::Sprite				*pHimmelSprite;

		//Rift Portal und Hover
		sf::Texture				*pRiftPortalTexture;
		sf::Sprite				*pRiftPortalSprite;
		//Hover
		sf::Texture				RiftPortalTextureHover;
		sf::Texture				RiftSkyTextureHover;

	};

}