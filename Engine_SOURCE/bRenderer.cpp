#include "bRenderer.h"
#include "bTexture.h"
#include "bResources.h"
#include "bMaterial.h"

namespace renderer
{
	using namespace b;
	using namespace b::graphics;

	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRasterizerStateType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDepthStencilStateType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBlendStateType::End] = {};

	b::Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshes = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input Layout 정점 구조 정보를 넘겨줘야 한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[4] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = b::Resources::Find<Shader>(L"TriangleShader");
		b::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = b::Resources::Find<Shader>(L"SpriteShader");
		b::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = b::Resources::Find<Shader>(L"LRSpriteShader");
		b::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = b::Resources::Find<Shader>(L"GridShader");
		b::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = b::Resources::Find<Shader>(L"DebugShader");
		b::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

#pragma endregion

#pragma region Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};

		// Point
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // 필터링 방법 설정
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());

		// Anisotropic
		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};

		// Solid Back
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // 렌더링할 때 사용할 채우기 모드 설정
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK; // 지정된 방향을 향한 삼각형이 그려지지 않음
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRasterizerStateType::SolidBack].GetAddressOf());

		// Solid Front
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRasterizerStateType::SolidFront].GetAddressOf());

		// Solid None
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRasterizerStateType::SolidNone].GetAddressOf());

		// Wireframe None
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, rasterizerStates[(UINT)eRasterizerStateType::WireframeNone].GetAddressOf());

#pragma endregion

#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		// Less
		depthStencilDesc.DepthEnable = true; // 깊이 테스트 사용 여부
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS; // 깊이 데이터 비교 함수
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이 데이터를 쓰기 위한 깊이 스텐실 버퍼 부분 식별 여부
		depthStencilDesc.StencilEnable = false; // 스텐실 테스트 사용 여부

		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDepthStencilStateType::Less].GetAddressOf());

		// Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDepthStencilStateType::Greater].GetAddressOf());

		// No Write
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDepthStencilStateType::NoWrite].GetAddressOf());

		// None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;

		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDepthStencilStateType::None].GetAddressOf());

#pragma endregion

#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};

		// Default
		blendStates[(UINT)eBlendStateType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false; // 알파-검사(alpha-to-coverage)를 다중 샘플링 기술로 사용할지 여부 지정
		blendDesc.IndependentBlendEnable = false;
		// 동시 렌더링 대상에서 독립적인 혼합을 사용할지 여부 지정, 독립 혼합을 사용하면 true, false로 설정하면 RenderTarget[0] 멤버만 사용

		blendDesc.RenderTarget[0].BlendEnable = true; // 혼합 사용 여부
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // SrcBlend 및 DestBlend 작업을 결합하는 방법 정의
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // SrcBlendAlpha 및 DestBlendAlpha 작업을 결합하는 방법을 정의

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // 픽셀 셰이더가 출력하는 RGB 값에 대해 수행할 작업 지정
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // 픽셀 셰이더가 출력하는 알파 값에 대해 수행할 작업 지정

		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // 렌더링 대상의 현재 RGB값에 대해 수행할 작업 지정
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // 렌더링 대상의 현재 알파 값에 대해 수행할 작업 지정

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, blendStates[(UINT)eBlendStateType::AlphaBlend].GetAddressOf());

		// One One
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc, blendStates[(UINT)eBlendStateType::OneOne].GetAddressOf());

#pragma endregion
	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		// RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		// Vertex Buffer
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// QuadrantMesh
		//std::shared_ptr<Mesh> Quadrant2Mesh = std::make_shared<Mesh>();
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"2QuadrantMesh", mesh);

		vertexes[0].uv = Vector2(0.0f, 0.0f);
		vertexes[1].uv = Vector2(0.5f, 0.0f);
		vertexes[2].uv = Vector2(0.5f, 0.5f);
		vertexes[3].uv = Vector2(0.0f, 0.5f);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// HalfMesh
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"lHalfMesh", mesh);

		vertexes[0].uv = Vector2(0.0f, 0.0f);
		vertexes[1].uv = Vector2(0.5f, 0.0f);
		vertexes[2].uv = Vector2(0.5f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		
		std::shared_ptr<Mesh> rHalfMesh = std::make_shared<Mesh>();
		Resources::Insert(L"rHalfMesh", rHalfMesh);

		vertexes[0].uv = Vector2(0.5f, 0.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.5f, 1.0f);

		rHalfMesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rHalfMesh->CreateIndexBuffer(indexes.data(), indexes.size());
		

		// Rect Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);

		vertexes[0].pos = Vector3(-1.0f, 1.0f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(1.0f, 1.0f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(1.0f, -1.0f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-1.0f, -1.0f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
	}

	void LoadBuffer()
	{
		// Constant Buffer
		if (constantBuffers[(UINT)eCBType::Transform] == nullptr)
		{
			constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
			constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
		}

		// Grid Buffer
		if (constantBuffers[(UINT)eCBType::Grid] == nullptr)
		{
		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));
		}
	}

	void LoadShader()
	{
		std::shared_ptr <Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		b::Resources::Insert(L"TriangleShader", shader);

		// default sprite shader
		std::shared_ptr <Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		b::Resources::Insert(L"SpriteShader", spriteShader);

		// left-right reversal sprite shader
		std::shared_ptr <Shader> LRspriteShader = std::make_shared<Shader>();
		LRspriteShader->Create(eShaderStage::VS, L"LRReversalSpriteVS.hlsl", "main");
		LRspriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		b::Resources::Insert(L"LRSpriteShader", LRspriteShader);

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		b::Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		debugShader->SetRasterizerState(eRasterizerStateType::SolidNone);
		b::Resources::Insert(L"DebugShader", debugShader);
	}

	void LoadMaterial()
	{
		// 리소스들 여기에서 로드
		std::shared_ptr<Shader> spriteShader = b::Resources::Find<Shader>(L"SpriteShader");

		std::shared_ptr <Shader> LRspriteShader = b::Resources::Find<Shader>(L"LRSpriteShader");

		std::shared_ptr <Shader> gridShader = b::Resources::Find<Shader>(L"GridShader");

		std::shared_ptr<Shader> debugShader = 
			b::Resources::Find<Shader>(L"DebugShader");

		std::shared_ptr<Texture> texture = std::make_shared<Texture>();
		std::shared_ptr<Material> material = std::make_shared<Material>();

		// Grid Material
		material = std::make_shared<Material>();
		material->SetShader(gridShader);
		INSERT_MATERIAL(material, L"GridMaterial");

		// Debug Material
		material = std::make_shared<Material>();
		material->SetShader(debugShader);
		INSERT_MATERIAL(material, L"DebugMaterial");
#pragma region Title
		material = std::make_shared<Material>();
		LOAD_TEXTURE(texture, L"TitleBG", L"..\\Resources\\Texture\\TitleScene\\DarkMirror_Title_Art_1.png");
		SET_MATERIAL(material, spriteShader, texture);
		INSERT_MATERIAL(material, L"TitleBGMaterial");

		material = std::make_shared<Material>();
		LOAD_TEXTURE(texture, L"TitleLogo", L"..\\Resources\\Texture\\TitleScene\\DarkMirror_Title_Art_Logo.png");
		SET_MATERIAL(material, spriteShader, texture);
		INSERT_MATERIAL(material, L"TitleLogoMaterial");

#pragma endregion

#pragma region UI
		material = std::make_shared<Material>();
		LOAD_TEXTURE(texture, L"PlayerFrame", L"..\\Resources\\Texture\\UI\\PlayerUI\\Player_Normal_Frame #2560.png");
		SET_MATERIAL(material, spriteShader, texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		INSERT_MATERIAL(material, L"PlayerFrameMaterial");

		material = std::make_shared<Material>();
		LOAD_TEXTURE(texture, L"Skill2FrameMaterial", L"..\\Resources\\Texture\\UI\\PlayerUI\\Player_Skill2_Frame.png");
		SET_MATERIAL(material, spriteShader, texture);
		material->SetRenderingMode(eRenderingMode::Transparent);
		INSERT_MATERIAL(material, L"Skill2FrameMaterial");
#pragma endregion

#pragma region Skul
		material = std::make_shared<Material>();
		LOAD_TEXTURE(texture, L"Skul", L"..\\Resources\\Texture\\Skul\\LittleBone\\Idle_0.png");
		SET_MATERIAL(material, spriteShader, texture);
		INSERT_MATERIAL(material, L"SkulIdle");
#pragma endregion

#pragma region Stage1
		// Public Objects
		{
			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1NoneDoor", L"..\\Resources\\Texture\\Stage1\\Public Objects\\Door\\None\\Deactivate_0 #1935.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1NoneDoorMt");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1ItemDoor", L"..\\Resources\\Texture\\Stage1\\Public Objects\\Door\\Item\\Deactivate_0 #1935.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1ItemDoorMt");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1GoldDoor", L"..\\Resources\\Texture\\Stage1\\Public Objects\\Door\\Gold\\Deactivate_0 #3532.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1GoldDoorMt");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1SkulDoor", L"..\\Resources\\Texture\\Stage1\\Public Objects\\Door\\Skul\\Deactivate_0 #499.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1SkulDoorMt");
		}
		// tile
		{
			for (size_t i = 0; i <= 35; i++)
			{
				material = std::make_shared<Material>();
				std::wstring path = L"..\\Resources\\Texture\\Stage1\\Chapter1\\Tile\\1_Tile01_" + std::to_wstring(i) + L".png";
				LOAD_TEXTURE(texture, L"1_Tile01_" + std::to_wstring(i), path);
				SET_MATERIAL(material, spriteShader, texture);
				std::wstring name = L"1_Tile01_" + std::to_wstring(i) + L"Material";
				INSERT_MATERIAL(material, name);
			}
		}
		// Lobby
		{
			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1LobbyBGColor", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Background\\01 #512.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"forestBGMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1Catle", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Background\\01 #409.png");
			SET_MATERIAL(material, LRspriteShader, texture);
			INSERT_MATERIAL(material, L"Stage1CastleMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Rampart_Base", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Background\\Rampart_Base.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Stage1Rampart_BaseMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Tree01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\\Object\\Tree01.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Tree01Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Tree02", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Tree02.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Tree02Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Pillar01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Pillar01.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Pillar01Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Pillar02", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Pillar02.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Pillar02Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Pillar03", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Pillar03.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Pillar03Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Pillar04", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Pillar04.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Pillar04Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Ch1_Gate_Wall", L"..\\Resources\\Texture\\Stage1\\Public Objects\\Ch1_Gate_Wall.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Ch1_Gate_WallMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Fore_Tree01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Fore_Tree01 #4743.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Fore_Tree01Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Fore_Bush02", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Fore_Bush02 #4977.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Fore_Bush02Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Fore_Bush01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Fore_Bush01.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Fore_Bush01Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"Fore_Bush04", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Object\\Fore_Bush04 #3192.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"Fore_Bush04Material");
		}
		// Boss Lobby
		{
			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1BossLobbyBGColor", L"..\\Resources\\Texture\\Stage1\\Boss\\Lobby\\04 #2878.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1BossLobbyBGColorMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1BossLobbyBG", L"..\\Resources\\Texture\\Stage1\\Boss\\Lobby\\05.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"S1BossLobbyBGMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"BossLobbyBGTree", L"..\\Resources\\Texture\\Stage1\\Boss\\Lobby\\03 #4046.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"BossLobbyBGTreeMaterial");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"cloud06", L"..\\Resources\\Texture\\Stage1\\Boss\\Lobby\\06 #5597.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"cloud06Material");

			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"cloud07", L"..\\Resources\\Texture\\Stage1\\Boss\\Lobby\\07 #5233.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"cloud07Material");

		}
		// Boss
		{
			material = std::make_shared<Material>();
			LOAD_TEXTURE(texture, L"S1BossSceneBG", L"..\\Resources\\Texture\\Stage1\\Boss\\ch1-3_1.png");
			SET_MATERIAL(material, spriteShader, texture);
			INSERT_MATERIAL(material, L"BossSceneBGMaterial");
		}
#pragma endregion

	}

	void Initialize()
	{
		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadMaterial();
	}

	void Render()
	{
		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffers)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}

	void PushDebugmeshAttribute(DebugMesh mesh)
	{
		debugMeshes.push_back(mesh);
	}
}