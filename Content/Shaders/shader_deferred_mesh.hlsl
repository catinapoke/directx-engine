
struct VS_IN
{
	float3 pos : POSITION0;
	float2 texture_coords : TEXCOORD0;
	float3 normal : NORMAL0;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float4 normal : NORMAL;
	float4 world_pos : TEXCOORD1;
};

struct TransformData
{
	float4x4 model_matrix;
	float4x4 inverse_model_matrix;
	float4x4 projection_view_matrix;
};

cbuffer TransformBuffer : register(b0)
{
	TransformData transform;
}

cbuffer MaterialData : register(b1)
{
	float m_shininess;
	float m_specular;
	float m_dummy;
	float m_dummy2;
};

struct PixelShaderOutput
{
    float4 Position				: SV_Target0;
    float3 Normal				: SV_Target1;			//Normal map
    float4 Diffuse				: SV_Target2;			//Color
};

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

PS_IN VSMain(VS_IN input)
{
	PS_IN output = (PS_IN)0;

	output.pos = mul(float4(input.pos, 1), mul(transform.model_matrix, transform.projection_view_matrix));
	output.uv = input.texture_coords;
	output.normal = mul(float4(input.normal, 0), transform.inverse_model_matrix);
	output.world_pos = mul(float4(input.pos, 1), transform.model_matrix);

	return output;
}

PixelShaderOutput PSMain(PS_IN input) : SV_Target
{
	PixelShaderOutput output;

	float3 color = DiffuseMap.Sample(Sampler, input.uv);

    output.Position = float4(input.world_pos.xyz, m_shininess);
    output.Diffuse = float4(color, m_specular);
    output.Normal = normalize(input.normal.xyz);

    return output;
}