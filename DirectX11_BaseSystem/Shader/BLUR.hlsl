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
�V�X�e�����ɓn���Z�}���e�B�N�X��SV_�̐ړ��������Ă���
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

//! ���_�V�F�[�_
OutputVS RenderVS(InputVS inVert)
{
	OutputVS Out = { float4(inVert.pos, 1.0f), inVert.color, inVert.normal, inVert.texel };
	return Out;
}


// �W�I���g���V�F�[�_�[�̓��̓p�����[�^
//typedef OutputVS InputGS;

// �W�I���g���V�F�[�_�[�̏o�̓p�����[�^
struct OutputGS
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;          // ���_�J���[�̓W�I���g���V�F�[�_�[���Œǉ�����
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
};


// �s�N�Z���V�F�[�_
float4 BlurShader(OutputGS inPixel) : SV_TARGET
{
	/*float4 Out = (float4)0;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.a *= inPixel.color.a;
	return Out;
	*/

	float4 Color[9];

	float BlurPower = 0.4f;

	//�����x�N�g���̐��K�����A�P�e�N�Z�����̒����ƂȂ�����x�N�g�����v�Z����
	float2 ScreenTexelX = float2(1.0f / 1200.f, 0.f) * BlurPower;
	float2 ScreenTexelY = float2(0.f, 1.f / 900.f) * BlurPower;

	//��������
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