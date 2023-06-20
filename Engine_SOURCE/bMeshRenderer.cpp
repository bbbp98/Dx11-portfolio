#include "bMeshRenderer.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bRenderer.h"

namespace b
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
		
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::LateUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();
	}
}