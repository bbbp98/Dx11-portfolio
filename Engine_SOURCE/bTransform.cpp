#include "bTransform.h"
#include "bRenderer.h"
#include "bConstantBuffer.h"
#include "bCamera.h"

namespace b
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mParent(nullptr)
		, mStartUV(Vector2::Zero)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
		// �̵�, ȸ��, ũ�� ����
	}

	void Transform::LateUpdate()
	{
		mWorld = Matrix::Identity;

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x); // x�� �߽����� ȸ��
		rotation *= Matrix::CreateRotationY(mRotation.y); // y�� �߽����� ȸ��
		rotation *= Matrix::CreateRotationZ(mRotation.z); // z�� �߽����� ȸ��

		Matrix position;
		position.Translation(mPosition);

		// ũ�� > ȸ�� > �̵� ������ ������� �Ѵ�.
		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetGpuViewMatrix();
		trCB.mProjection = Camera::GetGpuProjectionMatrix();

		trCB.mStartUV.x = mStartUV.x;
		trCB.mStartUV.y = mStartUV.y;

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}