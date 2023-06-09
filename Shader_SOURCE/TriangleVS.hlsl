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

cbuffer Transform : register(b0)
{
    float4 Position;
    //float4 Rotation;
    //float4 mScale;
}

VSOut main(VSIn In)
{
	VSOut Out = (VSOut)0.0f;
	
    Out.Pos = float4(In.Pos, 1.0f);
    //Out.Pos.x += Position.x;
    //Out.Pos.y += Position.y;
	
    //Out.UV.x = In.UV.x + 0.7f;
    //if (Out.UV.x > 1.0f)
    //    Out.UV.x - 1.0f;
    //Out.UV.y = In.UV.y;
    Out.UV = In.UV;
	Out.Color = In.Color;

	return Out;
}