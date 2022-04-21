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
	float m_ambient;
	float m_shininess;
	float m_specular;
	float m_dummy;
};

cbuffer LightBuffer : register(b2)
{
    float3 view_position;
	float space1;
    float3 l_direction; // position
	float space2;
    float3 l_color;
	float space3;
}

Texture2D DiffuseMap : register(t0);
SamplerState Sampler : register(s0);

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    output.pos = mul(float4(input.pos, 1), mul(transform.model_matrix, transform.projection_view_matrix));
    output.uv = input.texture_coords;
	output.normal = mul(float4(input.normal, 0), transform.inverse_model_matrix);
	output.world_pos = mul(float4(input.pos, 1), transform.model_matrix);
	
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 color = DiffuseMap.Sample(Sampler, input.uv);
    clip(color.a - 0.01f);

	// ambient
	float3 ambient = m_ambient * l_color;

	float3 light_direction = -normalize(l_direction - input.world_pos.xyz);
	float distance = length(l_direction - input.world_pos.xyz);
	float3 light_color = l_color * pow(clamp((20 - distance) / 10, 0, 1), 2);

	// diffuse
	float3 normal = normalize(input.normal.xyz);
	float3 to_light_direction = -light_direction;
	float diff = max(0.0, dot(to_light_direction, normal));
	float3 diffuse = diff * light_color;

	// specular
	float3 view_direction = normalize(view_position - input.world_pos.xyz);
	float3 reflect_direction = normalize(reflect(light_direction, normal));
	float spec = pow(max(0.0, dot(view_direction, reflect_direction)), m_shininess);
	float3 specular = m_specular * spec * light_color;

	float3 result = clamp(ambient + diffuse + specular, 0, 1) * color.xyz;
	return float4(result, 1.0f);
}