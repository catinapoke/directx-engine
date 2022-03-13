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

cbuffer PositionBuffer:register(b0)
{
	float4 position;
}

cbuffer DisplayBuffer:register(b1)
{
	float x_aspect;
    float y_aspect;
    float2 buffer_fill;
}

PS_IN VSMain( VS_IN input )
{
	PS_IN output = (PS_IN)0;
	input.pos.x /= x_aspect;
    input.pos.y /= y_aspect;
    
	output.pos = input.pos + float4(position.x, position.y, 0, 0);
	output.col = input.col;
	
	return output;
}

float4 PSMain( PS_IN input ) : SV_Target
{
	float4 col = input.col;
#ifdef TEST
	if (input.pos.x > 400) col = TCOLOR;
#endif
	return col;
}