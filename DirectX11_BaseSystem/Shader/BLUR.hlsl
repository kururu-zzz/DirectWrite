cbuffer cWBuffers : register(b0)
{
	matrix	matWorld;
};
struct camBuffer
{
	matrix	matView;
	matrix	matProjection;
	matrix  matViewPort;
	matrix  matLVP;
	float4 EyePos;
};

cbuffer cCBuffers : register(b1)
{
	camBuffer cam[5];
};

cbuffer cMBuffers : register(b2)
{
	float3 ambient;
	float3 diffuse;
	float3 emissive;
	float3 speculer;
}

cbuffer cLBuffers : register(b3)
{
	float4 LightDirection;
};
cbuffer cVBuffers : register(b4)
{
	float viewportDrawable;
	float viewportNum;
};

cbuffer variableBuffers : register(b6)
{
	float Time;
};

Texture2D  texDiffuse : register(t1);
SamplerState sampler0  : register(s1);

/*
システム側に渡すセマンティクスはSV_の接頭辞がついている
*/
struct InputVS
{
	float3	pos			: IN_POSITION;
	float4	color		: IN_COLOR;
	float3	normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;
};
struct OutputVS
{
	float4	pos			: SV_POSITION;
	float4	color		: COLOR0;
	float3 normal       : NORMAL;
	float2 texel        : TEXCOORD0;
};

//! 頂点シェーダ
OutputVS RenderVS(InputVS inVert)
{
	OutputVS Out = { float4(inVert.pos, 1.0f), inVert.color, inVert.normal, inVert.texel };
	return Out;
}


// ジオメトリシェーダーの入力パラメータ
//typedef OutputVS InputGS;

// ジオメトリシェーダーの出力パラメータ
struct OutputGS
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;          // 頂点カラーはジオメトリシェーダー内で追加する
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
};


// ピクセルシェーダ
float4 BlurShader(OutputGS inPixel) : SV_TARGET
{
	/*float4 Out = (float4)0;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.a *= inPixel.color.a;
	return Out;
	*/

	float4 Color[9];

	float BlurPower = 0.4f;

	//方向ベクトルの正規化し、１テクセル分の長さとなる方向ベクトルを計算する
	float2 ScreenTexelX = float2(1.0f / 1200.f, 0.f) * BlurPower;
	float2 ScreenTexelY = float2(0.f, 1.f / 900.f) * BlurPower;

	//合成する
	Color[0] = texDiffuse.Sample(sampler0, inPixel.texel ) * 0.2f;
	Color[1] = texDiffuse.Sample(sampler0, inPixel.texel - ScreenTexelY) * 0.1f;
	Color[2] = texDiffuse.Sample(sampler0, inPixel.texel + ScreenTexelY) * 0.1f;
	Color[3] = texDiffuse.Sample(sampler0, inPixel.texel - ScreenTexelX) * 0.1f;
	Color[4] = texDiffuse.Sample(sampler0, inPixel.texel + ScreenTexelX) * 0.1f;
	Color[5] = texDiffuse.Sample(sampler0, inPixel.texel - ScreenTexelX - ScreenTexelY) * 0.1f;
	Color[6] = texDiffuse.Sample(sampler0, inPixel.texel + ScreenTexelX - ScreenTexelY) * 0.1f;
	Color[7] = texDiffuse.Sample(sampler0, inPixel.texel - ScreenTexelX + ScreenTexelY) * 0.1f;
	Color[8] = texDiffuse.Sample(sampler0, inPixel.texel + ScreenTexelX + ScreenTexelY) * 0.1f;

	float4 Out = (Color[0] + (Color[1] + Color[2] + Color[3] + Color[4] + Color[5] + Color[6] + Color[7] + Color[8]));
	//float4 Out = (Color[1] + Color[2] + Color[3] + Color[4] + Color[5] + Color[6] + Color[7] + Color[8]);
	Out.a = 1.0f;

	return Out;
}