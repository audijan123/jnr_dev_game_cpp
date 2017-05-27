#include "sfSpriteGen.hpp"



namespace JGE
{

	SpriteGen::SpriteGen(main_base *r)
		: pResourcenManager(r)
	{
	}

	SpriteGen::~SpriteGen()
	{
	}


	sf::Sprite* SpriteGen::erstelle_sprite(const std::string& texture,
										   const bool& origin,
										   const sf::Vector2f& position,
										   const sf::Vector2f& scale)
	{
		pBufferTexture		 = new sf::Texture;
		vGelandeneTexturen.push_back(pBufferTexture);
		pBufferSprite		 = new sf::Sprite;

		if (texture.length() > 5)
		{
			osm::call("Invaild Texture");
			exit(0x10);
		} else {
			vGelandeneTexturen[vGelandeneTexturen.size()-1]->loadFromMemory(&pResourcenManager->get_memory_data(texture)[0],
				pResourcenManager->get_memory_data(texture).size());
		}

		pBufferSprite->setTexture(*vGelandeneTexturen[vGelandeneTexturen.size() - 1]);
		if (origin)
		{
			pBufferSprite->setOrigin(vGelandeneTexturen[vGelandeneTexturen.size() - 1]->getSize().x / 2.f,
									 vGelandeneTexturen[vGelandeneTexturen.size() - 1]->getSize().y / 2.f);
		}

		pBufferSprite->setPosition(position);
		pBufferSprite->setScale(scale);

		pBufferTexture = nullptr;


		return pBufferSprite;
	}


	sf::Sprite* SpriteGen::erstelle_sprite(const std::string& texture,
										   const bool& origin,
										   const sf::Vector2f& position,
										   const sf::Vector2f& scale,
										   const uint16_t& number)
	{
		pBufferTexture = new sf::Texture;
		vGelandeneTexturen.push_back(pBufferTexture);
		pBufferSprite = new sf::Sprite;

		if (texture.length() > 5)
		{
			osm::call("Invaild Texture");
			exit(0x10);
		}
		else {
			vGelandeneTexturen[vGelandeneTexturen.size() - 1]->loadFromMemory(&pResourcenManager->get_memory_data(texture, number)[0],
				pResourcenManager->get_memory_data(texture, number).size());
		}

		pBufferSprite->setTexture(*vGelandeneTexturen[vGelandeneTexturen.size() - 1]);
		if (origin)
		{
			pBufferSprite->setOrigin(vGelandeneTexturen[vGelandeneTexturen.size() - 1]->getSize().x / 2.f,
				vGelandeneTexturen[vGelandeneTexturen.size() - 1]->getSize().y / 2.f);
		}

		pBufferSprite->setPosition(position);
		pBufferSprite->setScale(scale);

		pBufferTexture = nullptr;


		return pBufferSprite;
	}

	sf::Texture SpriteGen::erstelle_texture(const std::string& texture)
	{
		//pBufferTexture = new sf::Texture;
		sf::Texture Buff;
		//vGelandeneTexturen.push_back(Buff);
		if (texture.length() > 5)
		{
			osm::call("Invaild Texture");
			exit(0x10);
		}
		else {
			Buff.loadFromMemory(&pResourcenManager->get_memory_data(texture)[0],
				pResourcenManager->get_memory_data(texture).size());
		}
		pBufferTexture = nullptr;
		return Buff;

	}

	sf::Texture SpriteGen::erstelle_texture_mob(const int& mob_size)
	{
		sf::Image image;
		image.loadFromMemory(&pResourcenManager->get_memory_data("mob", mob_size + 99)[0],
							pResourcenManager->get_memory_data("mob", mob_size + 99).size());
		sf::Texture buff;
		buff.loadFromImage(image, sf::IntRect(0, 0, image.getSize().x / 2, image.getSize().y));
		return buff;

	}





}