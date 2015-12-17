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
	float4 eyePos;
};

cbuffer cCBuffers : register(b1)
{
	camBuffer cam[5];
};

cbuffer cMBuffers : register(b2)
{
	float4 ambient;
	float4 diffuse;
	float4 emissive;
	float4 speculer;
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
	float Dummy;
	float Time;
};

Texture2D  texDiffuse : register(t0);
SamplerState samDiffuse  : register(s0);
Texture2D  texDiffuse1 : register(t1);
SamplerState samDiffuse1  : register(s1);


// �W�I���g���V�F�[�_�[�̓��̓p�����[�^
//typedef OutputVS InputGS;

// �W�I���g���V�F�[�_�[�̏o�̓p�����[�^
struct OutputGS
{
float4 pos    : SV_POSITION;
float4 color  : COLOR0;          // ���_�J���[�̓W�I���g���V�F�[�_�[���Œǉ�����
float3 eye	  : COLOR1;
float3 normal : NORMAL;
float2 texel  : TEXCOORD0;
uint   viewportIndex : SV_ViewportArrayIndex;
};

//! �s�N�Z���V�F�[�_
float4 HalfLambert( OutputGS inPixel ) : SV_TARGET
{
	float4 Out = (float4)0;
	float3 L = normalize(LightDirection.xyz);

	float p = max(dot(inPixel.normal, L), 0.f);
	p = p * 0.5f + 0.5f;
	p = p * p;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.rgb *= p;
	return Out;
}

//! �s�N�Z���V�F�[�_
float4 HalfLambertMaterial(OutputGS inPixel) : SV_TARGET
{
	float4 Out = (float4)0;
	float3 L = normalize(LightDirection.xyz);

	float p = max(dot(inPixel.normal, L), 0.f);
	p = p * 0.5f + 0.5f;
	p = p * p;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel) + diffuse;
	Out.rgb *= p;
	return Out;
}

/*-----�t�H���V�F�[�_-----*/

// �s�N�Z���V�F�[�_
float4 PhoneShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out;


	//�@���x�N�g���𐳋K������
	float3 N = normalize(inPixel.normal);
	//���_ -> ���C�g�ʒu�x�N�g�� + ���_ -> ���_�x�N�g��(���ӂP)
	float3 H = normalize(LightDirection.xyz + normalize(inPixel.eye));
	//�X�y�L�����[�J���[���v�Z����(���ӂQ)
	float S = pow(max(0.0f, dot(N, H)), 20.0f) * 0.75f;

	//�X�y�L�����[�J���[�����Z����
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.rgb = Out.rgb * 0.5f + S;


	return Out;
}

// �������C�g�V�F�[�_
float4 RimLightShader(OutputGS inPixel) : SV_TARGET
{

	float4 Out;

	//�I�u�W�F�N�g�̗֊s�t�߂̋��x�������Ȃ�悤�ɂ���
	float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)),2.0f) * 0.7f;

	float4 rgb = HalfLambert(inPixel);
	Out.rgb = rgb.rgb + P * 0.3f;

	Out.a = rgb.a;

	return Out;
}

// �������C�g�V�F�[�_
float4 RimLightMaterialShader(OutputGS inPixel) : SV_TARGET
{

	float4 Out;

	//�I�u�W�F�N�g�̗֊s�t�߂̋��x�������Ȃ�悤�ɂ���
	float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)), 2.0f) * 0.7f;

	float4 rgb = HalfLambertMaterial(inPixel);
		Out.rgb = rgb.rgb + P * 0.3f;

	Out.a = rgb.a;

	return Out;
}

float4 EnemyDeathShader(OutputGS inPixel) : SV_TARGET
{
	float4 rgb = HalfLambert(inPixel);
	if (Time <= 60)
	{
		rgb.rgb += float3(Time / 60.f, Time / 60.f, Time / 60.f);
		rgb.a = 1.0f - Time / 60.f;
	}
	return rgb;
}