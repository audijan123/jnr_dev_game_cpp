#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
namespace JGE
{
	namespace types
	{
		typedef int32_t		sVierByte; //int 4Byte signed
		typedef int16_t		sZweiByte; //int 2Byte signed
		typedef int8_t		sEinByte;  //int 1Byte signed
		typedef int64_t		sAchtByte; //int 8Byte signed

		typedef uint32_t	uVierByte; //int 4Byte unsigned
		typedef uint16_t	uZweiByte; //int 2Byte unsigned
		typedef uint8_t		uEinByte;  //int 1Byte unsigned
		typedef uint64_t	uAchtByte; //int 8Byte unsigned

		typedef bool		EinBit; //Bool

		typedef char		sEinByteChar; // Char
		typedef sf::Text	SpielText;    // Text
		typedef sf::Texture	SpielTexture; // Texture
		typedef sf::Sprite	SpielObjekt;  // Objekt

		typedef std::string		SpielString; //String
		typedef std::wstring	SpielWString; //WString

		typedef std::ifstream	DatenInputStream;

#ifdef LONGLONGPrice
		typedef uint64_t	SpielShopInt;
#else
		typedef uint32_t	SpielShopInt;
#endif // LONGLONGPrice


	}
}