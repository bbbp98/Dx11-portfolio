#include "bRenderer.h"
#include "bTexture.h"
#include "bResources.h"
#include "bMaterial.h"

namespace renderer
{
	using namespace b;
	using namespace b::graphics;

	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRasterizerStateType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDepthStencilStateType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBlendStateType::End] = {};

	std::vector<Camera*> cameras = {};

	void SetupState()
	{
#pragma region InputLayout
		// Input Layout ���� ���� ������ �Ѱ���� �Ѵ�.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

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

#pragma endregion

#pragma region Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};

		// Point
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // ���͸� ��� ����
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
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // �������� �� ����� ä��� ��� ����
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK; // ������ ������ ���� �ﰢ���� �׷����� ����
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
		depthStencilDesc.DepthEnable = true; // ���� �׽�Ʈ ��� ����
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS; // ���� ������ �� �Լ�
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // ���� �����͸� ���� ���� ���� ���ٽ� ���� �κ� �ĺ� ����
		depthStencilDesc.StencilEnable = false; // ���ٽ� �׽�Ʈ ��� ����

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
		blendDesc.AlphaToCoverageEnable = false; // ����-�˻�(alpha-to-coverage)�� ���� ���ø� ����� ������� ���� ����
		blendDesc.IndependentBlendEnable = false;
		// ���� ������ ��󿡼� �������� ȥ���� ������� ���� ����, ���� ȥ���� ����ϸ� true, false�� �����ϸ� RenderTarget[0] ����� ���

		blendDesc.RenderTarget[0].BlendEnable = true; // ȥ�� ��� ����
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // SrcBlend �� DestBlend �۾��� �����ϴ� ��� ����
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD; // SrcBlendAlpha �� DestBlendAlpha �۾��� �����ϴ� ����� ����

		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA; // �ȼ� ���̴��� ����ϴ� RGB ���� ���� ������ �۾� ����
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // �ȼ� ���̴��� ����ϴ� ���� ���� ���� ������ �۾� ����

		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; // ������ ����� ���� RGB���� ���� ������ �۾� ����
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // ������ ����� ���� ���� ���� ���� ������ �۾� ����

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

	void LoadBuffer(std::wstring name)
	{
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(name, mesh);

		// Vertex Buffer
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer
		if (constantBuffers[(UINT)eCBType::Transform] == nullptr)
		{
			constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
			constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
		}

		//Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		//constantBuffer->SetData(&pos);
		//constantBuffer->Bind(eShaderStage::VS);
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

		{
			// Title Scene
			std::shared_ptr<Texture> texture = Resources::Load<Texture>
				(L"TitleBG", L"..\\Resources\\Texture\\TitleScene\\DarkMirror_Title_Art_1.png");

			std::shared_ptr<Material> bgMaterial = std::make_shared<Material>();
			bgMaterial->SetShader(spriteShader);
			bgMaterial->SetTexture(texture);
			Resources::Insert(L"TitleBGMaterial", bgMaterial);

			texture = Resources::Load<Texture>
				(L"TitleLogo", L"..\\Resources\\Texture\\TitleScene\\DarkMirror_Title_Art_Logo.png");
			std::shared_ptr<Material> logoMaterial = std::make_shared<Material>();
			logoMaterial->SetShader(spriteShader);
			logoMaterial->SetTexture(texture);
			Resources::Insert(L"TitleLogoMaterial", logoMaterial);
		}

		{
			// Stage1 Lobby
			std::shared_ptr<Texture> texture = Resources::Load<Texture>
				(L"Stage1LobbyBGColor", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Background\\01 #512.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			Resources::Insert(L"Stage1LobbyBGColorMaterial", spriteMaterial);

			texture = Resources::Load<Texture>
				(L"Stage1Catle", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Background\\01 #409.png");
			std::shared_ptr<Material> CatleMaterial = std::make_shared<Material>();
			CatleMaterial->SetShader(LRspriteShader);
			CatleMaterial->SetTexture(texture);
			Resources::Insert(L"Stage1CatleMaterial", CatleMaterial);

			texture = Resources::Load<Texture>
				(L"Rampart_Base", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Background\\Rampart_Base.png");
			std::shared_ptr<Material> Rampart_BaseMaterial = std::make_shared<Material>();
			Rampart_BaseMaterial->SetShader(spriteShader);
			Rampart_BaseMaterial->SetTexture(texture);
			Resources::Insert(L"Stage1Rampart_BaseMaterial", Rampart_BaseMaterial);

			texture = Resources::Load<Texture>
				(L"Tree01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Tree01.png");
			std::shared_ptr<Material> Tree01Material = std::make_shared<Material>();
			Tree01Material->SetShader(spriteShader);
			Tree01Material->SetTexture(texture);
			Resources::Insert(L"Tree01Material", Tree01Material);

			texture = Resources::Load<Texture>
				(L"Tree02", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Tree02.png");
			std::shared_ptr<Material> Tree02Material = std::make_shared<Material>();
			Tree02Material->SetShader(spriteShader);
			Tree02Material->SetTexture(texture);
			Resources::Insert(L"Tree02Material", Tree02Material);

			texture = Resources::Load<Texture>
				(L"Pillar01", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Pillar01.png");
			std::shared_ptr<Material> Pillar01Material = std::make_shared<Material>();
			Pillar01Material->SetShader(spriteShader);
			Pillar01Material->SetTexture(texture);
			Resources::Insert(L"Pillar01Material", Pillar01Material);

			texture = Resources::Load<Texture>
				(L"Pillar02", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Pillar02.png");
			std::shared_ptr<Material> Pillar02Material = std::make_shared<Material>();
			Pillar02Material->SetShader(spriteShader);
			Pillar02Material->SetTexture(texture);
			Resources::Insert(L"Pillar02Material", Pillar02Material);
			
			texture = Resources::Load<Texture>
				(L"Pillar03", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Pillar03.png");
			std::shared_ptr<Material> Pillar03Material = std::make_shared<Material>();
			Pillar03Material->SetShader(spriteShader);
			Pillar03Material->SetTexture(texture);
			Resources::Insert(L"Pillar03Material", Pillar03Material);

			texture = Resources::Load<Texture>
				(L"Pillar04", L"..\\Resources\\Texture\\Stage1\\Chapter1\\1-1\\Object\\Pillar04.png");
			std::shared_ptr<Material> Pillar04Material = std::make_shared<Material>();
			Pillar04Material->SetShader(spriteShader);
			Pillar04Material->SetTexture(texture);
			Resources::Insert(L"Pillar04Material", Pillar04Material);
		}

		{
			std::shared_ptr<Texture> texture = Resources::Load<Texture>
				(L"BossSceneBG", L"..\\Resources\\Texture\\Stage1\\Chapter1\\Boss\\ch1-3_1.png");

			std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
			spriteMaterial->SetShader(spriteShader);
			spriteMaterial->SetTexture(texture);
			Resources::Insert(L"BossSceneBGMaterial", spriteMaterial);
		}

	}

	void Initialize()
	{
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


		LoadBuffer(L"DefaultMesh");
		LoadShader();
		SetupState();

		SetUV(Vector2(0.0f, 0.002f), Vector2(0.5f, 0.002f), Vector2(0.5f, 0.5f), Vector2(0.0f, 0.5f));
		LoadBuffer(L"2QuadrantMesh");

		/*std::shared_ptr<Texture> texture
			= Resources::Load<Texture>
			(L"Title", L"..\\Resources\\Texture\\Title_Art2.png");

		texture->BindShader(eShaderStage::PS, 0);*/
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

	void SetUV(Vector2 v0, Vector2 v1, Vector2 v2, Vector2 v3)
	{
		vertexes[0].uv = v0;
		vertexes[1].uv = v1;
		vertexes[2].uv = v2;
		vertexes[3].uv = v3;
	}

}