
#include "lights.hpp"

namespace light
{

	Lights::Lights ( ) { }

	Lights::Lights ( vec4& Pos, vec4 &ia, vec4 &is, vec4 &id )
	{
		pos = Pos;
		Ia = ia;
		Is = is;
		Id = id;
		status = 1;
	}

	inline void Lights::On ( )
	{
		status = 1;
	}

	inline void Lights::Off ( )
	{
		status = 0;
	}

	void Lights::Move ( vec4& npos )
	{
		pos = npos;
	}

	vec4& Lights::Position ( )
	{
		return pos;
	}

	void Lights::settings ( vec4& Pos, vec4 &ia, vec4 &is, vec4 &id )
	{
		pos = Pos;
		Ia = ia;
		Is = is;
		Id = id;
		status = 1;
	}

	vec4 & Lights::GetColor_Ia ()
	{
		return Ia;
	}

	vec4 & Lights::GetColor_Id ()
	{
		return Id;
	}

	vec4 & Lights::GetColor_Is ()
	{
		return Is;
	}

	//////////////////////////////////////////////////////////////////

	PointLight::PointLight ( vec4& Pos, vec4 &ia, vec4 &is, vec4 &id ) : Lights ( Pos, ia, is, id ) { }

	PointLight::PointLight ( ) : Lights ( ) { }

}
