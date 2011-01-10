
#include "texture.hpp"

namespace texture
{
	Texture::Texture ( vec4& c )
	{
		color = c;
	}

	TextureColor::TextureColor ( vec4& c ) : Texture ( c ) { }

	vec4& TextureColor::GetColor ( vec4& coord )
	{
		return color;
	}
}

