#pragma once

#include "sfSpriteGen.hpp"
#include "riftBrowser.hpp"
#include "himmel.hpp"
#include "main_os_manager.hpp"



namespace GMS
{
	class hintergrund
	{
	public:
		hintergrund(JGE::SpriteGen *SpriteErsteller,GMS::riftBrowser *rB ,GMS::himmel *h);
		~hintergrund();

		void update(const sf::Vector2f& vMousePosition, const bool& bTaverne,
					sf::Event *pHauptEvent, const float& fUpdateZeit);

		void render(sf::RenderWindow *rw);

	private:

		GMS::riftBrowser	*pRiftBrowser;
		GMS::himmel			*pHimmel;

		//Hintergrund
		sf::Texture			HintergrundTexture;
		sf::Sprite			*pHintergrundSprite;

		//Umwelt
		// Himmel Objecte
		sf::Texture			HimmelTexture;
		sf::Sprite			*pHimmelSprite;

		//Rift Portal und Hover
		sf::Texture			*pRiftPortalTexture;
		sf::Sprite			*pRiftPortalSprite;
		//Hover
		sf::Texture			RiftPortalTextureHover;
		sf::Texture			RiftSkyTextureHover;

		bool bPortalHover = false;

	};

}