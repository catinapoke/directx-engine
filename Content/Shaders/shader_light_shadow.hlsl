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
	float4 light_pos : TEXCOORD2;
};

struct TransformData
{
	float4x4 model_matrix;
    float4x4 inverse_model_matrix;
    float4x4 projection_view_matrix;
	float4x4 light_view_matrix;
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
    float3 l_direction;
	float space2;
    float3 l_color;
	float space3;
}

Texture2D DiffuseMap : register(t0);
Texture2D ShadowMap : register(t1);
SamplerComparisonState Sampler : register(s0);
SamplerState SamplerTexture : register(s1);


PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    output.pos = mul(float4(input.pos, 1), mul(transform.model_matrix, transform.projection_view_matrix));
    output.uv = input.texture_coords;
	output.normal = mul(float4(input.normal, 0), transform.inverse_model_matrix);
	output.world_pos = mul(float4(input.pos, 1), transform.model_matrix);
	output.light_pos = mul(float4(input.pos, 1), mul(transform.model_matrix, transform.light_view_matrix));
	
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 color = DiffuseMap.Sample(SamplerTexture, input.uv);
    clip(color.a - 0.01f);

	// Ambient
	float3 ambient = m_ambient * l_color;

	// Diffuse
	float3 normal = normalize(input.normal.xyz);
	float3 to_light_direction = -l_direction;
	float diff = max(0.0, dot(to_light_direction, normal));
	float3 diffuse = diff * l_color;

	// Specular
	float3 view_direction = normalize(view_position - input.world_pos.xyz);
	float3 reflect_direction = normalize(reflect(l_direction, normal));
	float spec = pow(max(0.0, dot(view_direction, reflect_direction)), m_shininess);
	float3 specular = m_specular * spec * l_color;

	// Value from shadow map
	float3 proj = input.light_pos.xyz / input.light_pos.w;
	float proj_x = proj.x * 0.5 + 0.5;
	float proj_y = -proj.y * 0.5 + 0.5;
	float current_depth = proj.z;


    float bias = 0.005;
    float closest_depth = ShadowMap.SampleCmp(Sampler, float2(proj_x, proj_y), current_depth - bias);
    //float shadow = max(0, ceil(current_depth - bias - closest_depth));

	float3 result = clamp(ambient + (closest_depth) * (diffuse + specular), 0, 1) * color.xyz;
	return float4(result, 1.0f);
}