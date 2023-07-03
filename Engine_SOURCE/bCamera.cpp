#include "bCamera.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bApplication.h"
#include "bRenderer.h"
#include "bSceneManager.h"
#include "bMeshRenderer.h"

extern b::Application application;

// 

namespace b
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			< b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}

	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthographic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(5.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}

	void Camera::Initialize()
	{
	}

	void Camera::Update()
	{
	}

	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();
	}

	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		AlphaSortGameObjects();
		ZSortGameObjects();

		RenderOpaque();

		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}

	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView = Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 right = tr->Right();
		Vector3 up = tr->Up();
		Vector3 foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;		viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y; 		viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z; 		viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}

	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;

		if (type == eProjectionType::Orthographic)
		{
			float orthographicRatio = mSize / 1000.0f;
			width *= orthographicRatio;
			height *= orthographicRatio;

			if (width != 0 && height != 0)
				mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else if (type == eProjectionType::Perpective)
		{
			if (mAspectRatio != 0)
				mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}

		return true;
	}

	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}

	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}

	void Camera::AlphaSortGameObjects()
	{
		Clear();

		Scene* scene = SceneManager::GetActiveScene();

		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				const std::vector<GameObject*> gameObjs = layer.GetGameObjects();

				DivideAlphaBlendGameObjects(gameObjs);
			}
		}
	}

	void Camera::ZSortGameObjects()
	{
		std::sort(mCutOutGameObjects.begin(), mCutOutGameObjects.end(), CompareZSort);

		std::sort(mTransparentGameObjects.begin(), mTransparentGameObjects.end(), CompareZSort);
	}

	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			MeshRenderer* mr = obj->GetComponent<MeshRenderer>();
			if (mr == nullptr)
				continue;

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();

			switch (mode)
			{
			case b::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(obj);
				break;
			case b::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(obj);
				break;
			case b::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}

	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}

	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			gameObj->Render();
		}
	}

	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)eDepthStencilStateType::Less];

		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)eDepthStencilStateType::None];

		GetDevice()->BindDepthStencilState(dsState.Get());
	}

	void Camera::Clear()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();
	}

}