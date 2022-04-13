struct VS_IN
{
    float3 pos : POSITION0;
    float2 texture_coords : TEXCOORD0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};

cbuffer CameraBuffer : register(b0)
{
    float4x4 projection_view_matrix;
}

cbuffer ModelBuffer : register(b1)
{
    float4x4 model_matrix;
}

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    output.pos = mul(float4(input.pos, 1), mul(model_matrix, projection_view_matrix));
    output.uv = input.texture_coords;
	
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 color = DiffuseMap.Sample(Sampler, input.uv);
    clip(color.a - 0.01f);
    return color;
}