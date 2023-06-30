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

		void SetMesh(std::shared_ptr<Mesh> mesh) { mMesh = mesh; }
		void SetMaterial(std::shared_ptr<Material> material) { mMaterial = material; }

		std::shared_ptr<Material> GetMaterial() { return mMaterial; }

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Material> mMaterial;
	};
}

