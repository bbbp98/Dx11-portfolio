#pragma once
#include "bComponent.h"
#include "bMesh.h"
#include "bShader.h"

namespace b
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		Mesh* mesh;
		Shader* shader;
	};
}

