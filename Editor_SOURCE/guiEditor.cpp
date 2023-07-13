#include "guiEditor.h"
#include "bMesh.h"
#include "bResources.h"
#include "bMaterial.h"
#include "bTransform.h"
#include "bMeshRenderer.h"
#include "bRenderer.h"
#include "bGridScript.h"

namespace gui
{
	using namespace b::enums;

	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<b::Mesh> mesh = b::Resources::Find<b::Mesh>(L"DebugRect");
		std::shared_ptr<b::Material> material = b::Resources::Find<b::Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<b::Transform>();
		b::MeshRenderer* mr = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<b::MeshRenderer>();
		mr->SetMesh(mesh);
		mr->SetMaterial(material);

		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<b::MeshRenderer>();
		mr->SetMesh(b::Resources::Find<b::Mesh>(L"RectMesh"));
		mr->SetMaterial(b::Resources::Find<b::Material>(L"GridMaterial"));
		b::GridScript* gridSc = grid->AddComponent<b::GridScript>();
		gridSc->SetCamera(renderer::mainCamera);

		mEditorObjects.push_back(grid);
	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const b::graphics::DebugMesh& mesh
			: renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const b::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치, 크기, 회전 정보를 받아와서
		// 해당 게임 오브젝트 위에 그려준다.
		b::Transform* tr = debugObj->GetComponent<b::Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.001f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate(); // projection 변환

		
			b::Camera* mainCamera = renderer::mainCamera;

			b::Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
			b::Camera::SetGpuProjectionMatrix(mainCamera->GetProjectionMatrix());
		

		debugObj->Render();
	}
}