#include "bRenderer.h"
#include <math.h>

namespace b::renderer
{
	// triangle
	Vertex vertexes[375] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

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

	//-------------------------------------------------
	// rectangle
	//Vertex rVertexes[6] = {};
	//ID3D11InputLayout* rectLayout = nullptr;
	//ID3D11Buffer* rectBuffer = nullptr;
	//ID3DBlob* rectVSBlob = nullptr;
	//ID3D11VertexShader* rectVSShader = nullptr;
	//ID3DBlob* rectPSBlob = nullptr;
	//ID3D11PixelShader* rectPSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE_DYNAMIC; // 버퍼를 읽고 쓰는 방법
		// DYNAMIC은 GPU와 CPU에서 모두 액세스할 수 있는 리소스
		triangleDesc.ByteWidth = sizeof(Vertex) * 375; // 버퍼의 크기(바이트)
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER; // 버퍼가 파이프라인에 바인딩되는 방법
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE; // 리소스에 허용되는 CPU 액세스 유형

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		b::graphics::GetDevice()->CreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		// rect
		//D3D11_BUFFER_DESC rectDesc = {};
		//rectDesc.Usage = D3D11_USAGE_DYNAMIC;
		//rectDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//rectDesc.ByteWidth = sizeof(Vertex) * 6;
		//rectDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		//D3D11_SUBRESOURCE_DATA rectData = {};
		//rectData.pSysMem = rVertexes;
		//b::graphics::GetDevice()->CreateBuffer(&rectBuffer, &rectDesc, &rectData);

		//mBuffers[0] = triangleBuffer;
		//mBuffers[1] = rectBuffer;

	}

	void LoadShader()
	{
		b::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.8f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(-0.3f, 0.3f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.7f, 0.3f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		// rect
		UINT rPoint = 3;

		//Vector3(0.3f, 0.8f, 0.0f); 0
		//Vector3(0.7f, 0.2f, 0.0f); 1
		//Vector3(0.3f, 0.2f, 0.0f); 2
		//Vector3(0.7f, 0.8f, 0.0f); 3

		vertexes[rPoint].pos = Vector3(0.3f, 0.2f, 0.0f); // 2
		vertexes[rPoint].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		vertexes[rPoint + 1].pos = Vector3(0.3f, 0.8f, 0.0f); // 0
		vertexes[rPoint + 1].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[rPoint + 2].pos = Vector3(0.7f, 0.2f, 0.0f); // 1
		vertexes[rPoint + 2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[rPoint + 3].pos = Vector3(0.7f, 0.2f, 0.0f); // 1
		vertexes[rPoint + 3].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[rPoint + 4].pos = Vector3(0.3f, 0.8f, 0.0f); // 0
		vertexes[rPoint + 4].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[rPoint + 5].pos = Vector3(0.7f, 0.8f, 0.0f); // 3
		vertexes[rPoint + 5].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		
		// diamond
		UINT dPoint = rPoint + 6;

		// Vector3(0.5f, -0.2f, 0.0f); 0
		// Vector3(0.5f, -0.8f, 0.0f); 1
		// Vector3(0.3f, -0.5f, 0.0f); 2
		// Vector3(0.7f, -0.5f, 0.0f); 3

		vertexes[dPoint].pos = Vector3(0.7f, -0.5f, 0.0f); // 3
		vertexes[dPoint].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		vertexes[dPoint + 1].pos = Vector3(0.5f, -0.8f, 0.0f); // 1
		vertexes[dPoint + 1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[dPoint + 2].pos = Vector3(0.3f, -0.5f, 0.0f); // 2
		vertexes[dPoint + 2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[dPoint + 3].pos = Vector3(0.3f, -0.5f, 0.0f); // 2
		vertexes[dPoint + 3].color = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		vertexes[dPoint + 4].pos = Vector3(0.5f, -0.2f, 0.0f); // 0
		vertexes[dPoint + 4].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[dPoint + 5].pos = Vector3(0.7f, -0.5f, 0.0f); // 3
		vertexes[dPoint + 5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		
		// circle
		UINT cPoint = dPoint + 6;
		float r = 0.3f;
		Vector3 cPos = Vector3(-0.5f, -0.5f, 0.0f);
		int j = 0;
		for (UINT i = 0; i < 360; i++)
		{
			Vector3 pos = cPos;
			//pos.x += r * cos(float(360 - i));
			//pos.y += r * sin(float(360 - i));
			
			if (i % 3 == 2)
			{
				vertexes[cPoint + i].pos = cPos;
				continue;
			}
			double rad = (360 - i) * 3.14 / 180;
			pos.x += r * cos(rad);
			pos.y += r * sin(rad);

			vertexes[cPoint + i].pos = Vector3(pos.x, pos.y, 0.0f);
			vertexes[cPoint + i].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			/*
			if (j >= 360)
				break;
			else
				j++;*/
		}
		

		SetupState();
		LoadBuffer();
		LoadShader();
	}
}