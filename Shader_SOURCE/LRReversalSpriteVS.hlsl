#include "globals.hlsli"

struct VSIn
{
    float3 Pos : POSITION;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};

struct VSOut
{
    float4 Pos : SV_Position;
    float4 Color : COLOR;
    float2 UV : TEXCOORD;
};


VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
	
    float4 world = mul(float4(In.Pos, 1.0f), WorldMatrix);
    float4 view = mul(world, ViewMatrix);
    float4 projection = mul(view, ProjectionMatrix);
	
    Out.Pos = projection;
    Out.Color = In.Color;
    Out.UV.x = 1.0f - In.UV.x; // 텍스처 좌우 반전
    Out.UV.y = In.UV.y;

    return Out;
}