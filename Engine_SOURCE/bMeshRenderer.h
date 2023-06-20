#pragma once
#include "bComponent.h"
#include "bMesh.h"
#include "bMaterial.h"

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

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetMaterial(Material* material) { mMaterial = material; }

	private:
		Mesh* mMesh;
		Material* mMaterial;
	};
}

