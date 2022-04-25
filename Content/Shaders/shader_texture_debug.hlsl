struct VS_IN
{
	float4 pos : POSITION0;
	float2 uv : TEXCOORD0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
 	float2 uv : TEXCOORD0;
};

cbuffer DisplayBuffer:register(b1)
{
	float x_aspect;
    float y_aspect;
    float2 buffer_fill;
}

Texture2D DiffuseMap : register(t1);
SamplerState Sampler : register(s0);

PS_IN VSMain( VS_IN input )
{
	PS_IN output = (PS_IN)0;
    
	output.pos = input.pos;
	output.uv = input.uv;
	
	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	float4 diffuse = DiffuseMap.Sample(Sampler, input.uv);
	clip(diffuse.a - 0.01f);
	return diffuse;
}