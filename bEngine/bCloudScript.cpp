#include "bCloudScript.h"
#include "bTime.h"
#include "bConstantBuffer.h"
#include "bRenderer.h"
#include "bTransform.h"
#include "bGameObject.h"

namespace b
{
	void CloudScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 Pos = tr->GetPosition();

		Pos.x -= (mSpeed) * (Time::DeltaTime()) * 0.1f;

		// Ư�� ��ġ�� �����ϸ� �������� ������
		//if (Pos.x < -7.0f)
		//{
		//	Pos.x = 0.0f;
		//}

		tr->SetPosition(Pos);
	}
}