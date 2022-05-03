struct VS_IN
{
	float3 pos : POSITION0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
};

struct LightData
{
    float3 direction; // position
    float space1;
    float3 color;
    float space2;
    float3 view_position; // camera_position
    float space3;
};

cbuffer LightBuffer : register(b0)
{
	LightData light;
}

Texture2D Position : register(t0);
Texture2D NormalMap : register(t1);
Texture2D Color : register(t2);

SamplerState Sampler : register(s0);

PS_IN VSMain(VS_IN input)
{
	PS_IN output;
	output.pos = float4(input.pos, 1);
	return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
	// Data load

    const int3 data_uv = int3(input.pos.xy, 0);
    float3 data_normal = NormalMap.Load(data_uv).xyz;

    float4 raw_data = Position.Load(data_uv);
    float m_shininess = raw_data.a;
    float3 data_position = raw_data.xyz;

    raw_data = Color.Load(data_uv);
    float3 data_diffuse = raw_data.xyz;
    float m_specular = raw_data.a;

	// Light calculation

    float3 light_direction = light.direction;
	float3 light_color = light.color * data_diffuse;

	// diffuse
	float3 normal = normalize(data_normal);
	float3 to_light_direction = -light_direction;
	float diff = max(0.0, dot(to_light_direction, normal));
	float3 diffuse = diff * light_color;

	// specular
	float3 view_direction = normalize(light.view_position - data_position);
	float3 reflect_direction = normalize(reflect(light_direction, normal));
	float spec = pow(max(0.0, dot(view_direction, reflect_direction)), m_shininess);
	float3 specular = m_specular * spec * light_color;

	float3 result = clamp(diffuse + specular, 0, 1) * light_color.xyz;
	return pow(float4(result, 1.0f), 1 / 2.2f);
}