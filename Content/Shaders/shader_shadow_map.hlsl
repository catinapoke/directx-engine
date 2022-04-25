cbuffer ModelBuffer : register(b0)
{
	float4x4 model_matrix;
}

cbuffer CameraBuffer : register(b1)
{
	float4x4 projection_view;
}

Texture2D DiffuseMap : register(t0);

SamplerState Sampler : register(s0);

struct VS_IN
{
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(float4(input.pos, 1.0), mul(model_matrix, projection_view));
	output.uv = input.uv;

	return output;
}

void PSMain(PS_IN input)
{
	float4 diffuse = DiffuseMap.Sample(Sampler, input.uv);
	clip(diffuse.a - 0.01f);
}