#include "bGridScript.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bApplication.h"
#include "bConstantBuffer.h"
#include "bRenderer.h"
#include "bTime.h"

extern b::Application application;

namespace b
{
	GridScript::GridScript()
		: mCamera(nullptr)
	{
	}

	GridScript::~GridScript()
	{
	}

	void GridScript::Initialize()
	{
	}

	void GridScript::Update()
	{
		if (mCamera == nullptr)
			return;

		GameObject* gameobj = mCamera->GetOwner();

		Transform* tr = gameobj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		float scale = mCamera->GetSize();

		HWND hWnd = application.GetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		// constant buffer
		graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.CameraScale = Vector2(scale, scale);
		data.Resolution = resolution;

		cb->SetData(&data);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void GridScript::LateUpdate()
	{
	}

	void GridScript::Render()
	{
	}
}