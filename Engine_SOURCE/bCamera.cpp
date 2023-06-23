#include "bCamera.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bApplication.h"

extern b::Application application;

namespace b
{
	Matrix Camera::mView = Matrix::Identity;
	Matrix Camera::mProjection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::Orthographic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(5.0f)
	{
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
	}

	void Camera::Render()
	{
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

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else if (type == eProjectionType::Perpective)
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}

		return true;
	}
}