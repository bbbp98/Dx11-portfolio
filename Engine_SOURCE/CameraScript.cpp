#include "CameraScript.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bTime.h"

namespace b
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x += 1.0f * Time::DeltaTime();
		tr->SetPosition(pos);
	}
}