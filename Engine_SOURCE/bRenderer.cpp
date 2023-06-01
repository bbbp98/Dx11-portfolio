#include "bRenderer.h"
#include "bInput.h"

#include <math.h>

namespace b::renderer
{
	// triangle
	Vertex vertexes[3] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;
	ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleCSBuffer = nullptr;

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;
		
	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	Vector4 pos = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE_DYNAMIC; // 버퍼를 읽고 쓰는 방법
		// DYNAMIC은 GPU와 CPU에서 모두 액세스할 수 있는 리소스
		triangleDesc.ByteWidth = sizeof(Vertex) * 3; // 버퍼의 크기(바이트)
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼가 파이프라인에 바인딩되는 방법
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // 리소스에 허용되는 CPU 액세스 유형

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		b::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		// Index Buffer
		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size();
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indexes.data();
		graphics::GetDevice()->CreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);


		// Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		graphics::GetDevice()->CreateBuffer(&triangleCSBuffer, &triangleCSDesc, nullptr);

		//Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
		//graphics::GetDevice()->SetConstantBuffer(triangleCSBuffer, &pos, sizeof(Vector4));
		//graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleCSBuffer);
	}

	void LoadShader()
	{
		b::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//// rect
		//UINT rPoint = 3;

		////Vector3(0.3f, 0.8f, 0.0f); 0
		////Vector3(0.7f, 0.2f, 0.0f); 1
		////Vector3(0.3f, 0.2f, 0.0f); 2
		////Vector3(0.7f, 0.8f, 0.0f); 3

		//vertexes[rPoint].pos = Vector3(0.3f, 0.2f, 0.0f); // 2
		//vertexes[rPoint].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[rPoint + 1].pos = Vector3(0.3f, 0.8f, 0.0f); // 0
		//vertexes[rPoint + 1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[rPoint + 2].pos = Vector3(0.7f, 0.2f, 0.0f); // 1
		//vertexes[rPoint + 2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[rPoint + 3].pos = Vector3(0.7f, 0.2f, 0.0f); // 1
		//vertexes[rPoint + 3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//vertexes[rPoint + 4].pos = Vector3(0.3f, 0.8f, 0.0f); // 0
		//vertexes[rPoint + 4].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[rPoint + 5].pos = Vector3(0.7f, 0.8f, 0.0f); // 3
		//vertexes[rPoint + 5].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		//
		//// diamond
		//UINT dPoint = rPoint + 6;

		//// Vector3(0.5f, -0.2f, 0.0f); 0
		//// Vector3(0.5f, -0.8f, 0.0f); 1
		//// Vector3(0.3f, -0.5f, 0.0f); 2
		//// Vector3(0.7f, -0.5f, 0.0f); 3

		//vertexes[dPoint].pos = Vector3(0.7f, -0.5f, 0.0f); // 3
		//vertexes[dPoint].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[dPoint + 1].pos = Vector3(0.5f, -0.8f, 0.0f); // 1
		//vertexes[dPoint + 1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[dPoint + 2].pos = Vector3(0.3f, -0.5f, 0.0f); // 2
		//vertexes[dPoint + 2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		//vertexes[dPoint + 3].pos = Vector3(0.3f, -0.5f, 0.0f); // 2
		//vertexes[dPoint + 3].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		//vertexes[dPoint + 4].pos = Vector3(0.5f, -0.2f, 0.0f); // 0
		//vertexes[dPoint + 4].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		//vertexes[dPoint + 5].pos = Vector3(0.7f, -0.5f, 0.0f); // 3
		//vertexes[dPoint + 5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		//
		//// circle
		//UINT cPoint = dPoint + 6;
		//float r = 0.3f;
		//Vector3 cPos = Vector3(-0.5f, -0.5f, 0.0f);
		//int j = 0;
		//for (UINT i = 0; i < 360; i++)
		//{
		//	Vector3 pos = cPos;
		//	
		//	if (i % 3 == 0)
		//	{
		//		vertexes[cPoint + i].pos = cPos;
		//		continue;
		//	}
		//	double rad = (360 - i) * 3.14 / 180;
		//	pos.x += r * cos(rad);
		//	pos.y += r * sin(rad);

		//	vertexes[cPoint + i].pos = Vector3(pos.x, pos.y, 0.0f);
		//	vertexes[cPoint + i].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		//}
		//

		SetupState();
		LoadBuffer();
		LoadShader();
	}

	void Update()
	{
		if (Input::GetKey(eKeyCode::LEFT))
		{
			pos.x -= 0.005f;
		}
		if (Input::GetKey(eKeyCode::RIGHT))
		{
			pos.x += 0.005f;
		}
		if (Input::GetKey(eKeyCode::UP))
		{
			pos.y += 0.005f;
		}
		if (Input::GetKey(eKeyCode::DOWN))
		{
			pos.y -= 0.005f;
		}

		graphics::GetDevice()->SetConstantBuffer(triangleCSBuffer, &pos, sizeof(Vector4));
		graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleCSBuffer);
	}
}