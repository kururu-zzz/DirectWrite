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

cbuffer cVBuffers : register(b6)
{
	float hpRate;
	float ovlRate;
	float time;
};

Texture2D  texDiffuse : register(t0);
SamplerState samDiffuse  : register(s0);

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
OutputVS RenderVS( InputVS inVert )
{
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, inVert.normal, inVert.texel };
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
uint   ViewportIndex : SV_ViewportArrayIndex;
};

/*-----Sprite�p�V�F�[�_�[-----*/

[maxvertexcount(15)]   // �W�I���g���V�F�[�_�[�ŏo�͂���ő咸�_��(viewport * 3�ł悢)
// �W�I���g���V�F�[�_�[
void RenderGSSpriteViewport(triangle OutputVS In[3],                    // �g���C�A���O�� ���X�g���\�����钸�_�z��̓��͏��
	inout TriangleStream<OutputGS> TriStream   // ���_����ǉ����邽�߂̃X�g���[���I�u�W�F�N�g
	)
{

	OutputGS Out;

	int drawable = viewportDrawable;//�r�b�g���Z�̂���int�^�ɃL���X�g
	int i, j;
	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			// ���Ƃ̒��_���o��
			for (i = 0; i < 3; i++)
			{
				Out.pos = mul(In[i].pos, cam[j].matViewPort);

				Out.normal = float3(0.f, 0.f, 0.f);

				Out.texel = In[i].texel;

				Out.color = In[i].color;   // ���̒��_�͕s�����ŏo��

				Out.ViewportIndex = j;

				// ���_��ǉ�����
				TriStream.Append(Out);
			}
			// ���݂̃X�g���b�v���I�����A�V�����X�g���b�v���J�n����B
			TriStream.RestartStrip();
		}
		drawable >>= 1;
	}
}

[maxvertexcount(15)]   // �W�I���g���V�F�[�_�[�ŏo�͂���ő咸�_��(viewport * 3�ł悢)
// �W�I���g���V�F�[�_�[
void RenderGSSprite(triangle OutputVS In[3],                    // �g���C�A���O�� ���X�g���\�����钸�_�z��̓��͏��
	inout TriangleStream<OutputGS> TriStream   // ���_����ǉ����邽�߂̃X�g���[���I�u�W�F�N�g
	)
{

	OutputGS Out;

	int drawable = viewportDrawable;//�r�b�g���Z�̂���int�^�ɃL���X�g
	int i;
	// ���Ƃ̒��_���o��
	for (i = 0; i < 3; i++)
	{
		Out.pos = mul(In[i].pos, cam[0].matViewPort);

		Out.normal = float3(0.f, 0.f, 0.f);

		Out.texel = In[i].texel;

		Out.color = In[i].color;   // ���̒��_�͕s�����ŏo��

		Out.ViewportIndex = 0;

		// ���_��ǉ�����
		TriStream.Append(Out);
	}
	// ���݂̃X�g���b�v���I�����A�V�����X�g���b�v���J�n����B
	TriStream.RestartStrip();
}

struct OutputPS
{
	float4 out0:SV_TARGET0;
};

// �s�N�Z���V�F�[�_
OutputPS SpriteShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.out0.a *= inPixel.color.a;
	return Out;
}

// �s�N�Z���V�F�[�_
OutputPS HPShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	if (Out.out0.a <= 0.3f)
	{
		float hpDiv = hpRate;
		float ovlDiv = ovlRate;
		float hpNoShownDegree = 360.f * hpDiv - 270.f;
		float R = 0.5;
		float r = 0.45;
		float theta = -degrees(atan((inPixel.texel.y - 0.5f) / (inPixel.texel.x - 0.5f)));
		if (inPixel.texel.x <= 0.5f)
		{
			theta = -180.f + theta;
		}
		float round = sqrt(pow((inPixel.texel.x - 0.5f), 2) + pow((inPixel.texel.y - 0.5f), 2));
		if (round <= R && round >= r && theta < hpNoShownDegree)
		{
			if (round >= R-0.001f && round <= R)
			{
				Out.out0 = float4(0.5f, 0.5f, 0.5f, 1.f);
			}
			else if (hpDiv > 0.5f)
			{
				Out.out0 = float4(0.2f, 0.8f, 0.2f, 1.f);
			}
			else if (hpDiv > 0.2f)
			{
				Out.out0 = float4(0.8f, 0.8f, 0.f, 1.f);
			}
			else
			{
				Out.out0 = float4(0.8f, 0.f, 0.f, 1.f);
			}
		}
	}
	else
	{
		float hpDiv = hpRate;
		if (hpDiv <= 0.2f)
		{
			Out.out0.g *= abs(sin(radians(time*2)));
			Out.out0.b *= abs(sin(radians(time*2)));
		}
	}
	Out.out0.a *= inPixel.color.a;
	return Out;
}

// �s�N�Z���V�F�[�_
OutputPS OvlShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	float ovl = ovlRate;
	if (inPixel.texel.y < (1.f - ovl))
	{
		Out.out0 = float4(0.f, 0.f, 0.f, 0.f);
	}
	if(ovl >= 1.f)
	{
		Out.out0.r += (1.f - Out.out0.r) * abs(sin(radians(time*2)));
		Out.out0.g += (1.f - Out.out0.g) * abs(sin(radians(time*2)));
		Out.out0.b += (1.f - Out.out0.b) * abs(sin(radians(time*2)));
	}
	Out.out0.a *= inPixel.color.a;
	return Out;
}

OutputPS BackWordShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.out0.a *= inPixel.color.a;
	if (inPixel.pos.y <= 220 || inPixel.pos.y >= 700)
	{
		float diff = abs(760.f - inPixel.pos.y - (inPixel.pos.y <= 220) * 600.f);
		float prop = diff / 60.f;
		Out.out0.a *= prop;
	};
	return Out;
}

OutputPS BackArrowShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.out0.a *= inPixel.color.a;
	bool limitMax = hpRate;
	if (limitMax)
	{
		Out.out0.r *= 0.5f;
		Out.out0.g *= 0.5f;
		Out.out0.b *= 0.5f;
	};
	return Out;
}