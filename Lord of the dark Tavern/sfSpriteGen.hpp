#pragma once
#include "main_base.hpp"
#include "main_os_manager.hpp"



namespace JGE
{
	class SpriteGen
	{
	public:
		SpriteGen(main_base *r);
		~SpriteGen();

		sf::Sprite* erstelle_sprite(const std::string& texture,
									const bool& origin,
									const sf::Vector2f& position,
									const sf::Vector2f& scale );

		sf::Sprite* erstelle_sprite(const std::string& texture,
									const bool& origin,
									const sf::Vector2f& position,
									const sf::Vector2f& scale ,
									const uint16_t& number);

		sf::Texture erstelle_texture(const std::string& texture);


	private:





		main_base			*pResourcenManager;


		sf::Texture			*pBufferTexture;
		sf::Sprite			*pBufferSprite;

		std::vector<sf::Texture*> vGelandeneTexturen;



	};





}
