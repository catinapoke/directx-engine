struct VS_IN
{
    float4 pos : POSITION0;
    float4 col : COLOR0;
};

struct PS_IN
{
    float4 pos : SV_POSITION;
    float4 col : COLOR;
};

cbuffer CameraBuffer : register(b0)
{
    float4x4 projection_view_matrix;
}

cbuffer ModelBuffer : register(b1)
{
    float4x4 model_matrix;
}

PS_IN VSMain(VS_IN input)
{
    PS_IN output = (PS_IN) 0;
    
    output.pos = mul(input.pos, mul(model_matrix, projection_view_matrix));
    output.col = input.col;
	
    return output;
}

float4 PSMain(PS_IN input) : SV_Target
{
    float4 col = input.col;
    return col;
}