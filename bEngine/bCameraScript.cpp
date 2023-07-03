#include "bCameraScript.h"
#include "bTransform.h"
#include "bGameObject.h"
#include "bTime.h"
#include "bInput.h"

namespace b
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::W))
		{
			pos.y += 3.0f * Time::DeltaTime() * mSpeed;
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			pos.y -= 3.0f * Time::DeltaTime() * mSpeed;
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			pos.x -= 3.0f * Time::DeltaTime() * mSpeed;
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			pos.x += 3.0f * Time::DeltaTime() * mSpeed;
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::Q))
		{
			pos.z -= 3.0f * Time::DeltaTime() * mSpeed;
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::E))
		{
			pos.z += 3.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
	}
}