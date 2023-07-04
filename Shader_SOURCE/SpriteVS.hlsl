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
    row_major matrix mWorld;
    row_major matrix mView;
    row_major matrix mProjection;
    float4 startUV;
}

VSOut main(VSIn In)
{
    VSOut Out = (VSOut) 0.0f;
	
    float4 world = mul(float4(In.Pos, 1.0f), mWorld);
    float4 view = mul(world, mView);
    float4 projection = mul(view, mProjection);
	
    Out.Pos = projection;
    Out.Color = In.Color;
    //Out.UV = In.UV;
    Out.UV = In.UV + startUV.xy;
    
    if (Out.UV.x > 1.0f)
    {
        Out.UV.x - 1.0f;
    }
    if (Out.UV.y > 1.0f)
    {
        Out.UV.y - 1.0f;
    }

    return Out;
}