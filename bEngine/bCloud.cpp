#include "bCloud.h"
#include "bCloudScript.h"
#include "bMeshRenderer.h"

namespace b
{
	Cloud::Cloud()
	{
		mMeshRenderer = AddComponent<MeshRenderer>();
		AddComponent<CloudScript>();
	}

	Cloud::~Cloud()
	{
	}

	void Cloud::Initialize()
	{
		
	}

	void Cloud::Update()
	{
		GameObject::Update();
	}

	void Cloud::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Cloud::Render()
	{
		GameObject::Render();
	}
}