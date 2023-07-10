#pragma once

namespace b::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		BackGround_In,
		BackGround_Mid,
		BackGround_Out,
		Grid,
		Player,
		Monster,
		UI,
		Camera,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};
}