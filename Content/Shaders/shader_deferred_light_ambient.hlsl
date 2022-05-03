struct VS_IN
{
	float3 pos : POSITION0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;// pos * MVP;
};

cbuffer LightBuffer : register(b0)
{
	float3 color;
	float strength;
}

Texture2D Position : register(t0);
Texture2D NormalMap : register(t1);
Texture2D Color : register(t2);

SamplerState Sampler : register(s0);

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;
	output.pos = float4(input.pos, 1);
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	int3 data_uv = int3(input.pos.x, input.pos.y, 0);
	float3 data_diffuse = Color.Load(data_uv).xyz;

	float3 result = (strength * color) * data_diffuse;
	return pow(float4(result, 1.0f), 1 / 2.2f);
}