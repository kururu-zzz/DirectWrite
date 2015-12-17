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

Texture2D  texDiffuse : register(t0);
SamplerState samDiffuse  : register(s0);
Texture2D  texDiffuse1 : register(t1);
SamplerState samDiffuse1  : register(s1);

//! ���_����
/*!
��{��D3D9�ƕς��Ȃ�
�������A�������̃Z�}���e�B�N�X���ς���Ă���
�V�X�e�����ɓn���Z�}���e�B�N�X��SV_�̐ړ��������Ă���
*/
struct InputVS
{
	float3 pos			: IN_POSITION;
	float4 color		: IN_COLOR;
	float3 normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;   // �e�N�Z��
	uint4  boneIndex	: IN_BONEINDEX;
	float4 boneWeight	: IN_BONEWEIGHT;
};
struct OutputVS
{
	float4 pos			: SV_POSITION;
	float4 color		: COLOR0;
	float4 eye			: COLOR1;
	float3 normal       : NORMAL;
	float2 texel        : TEXCOORD0;
};


/*-----3D���f���`��p�n�[�t�����o�[�g-----*/


//! ���_�V�F�[�_
OutputVS RenderVS( InputVS inVert )
{
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, float4(0.f,0.f,0.f,0.f),inVert.normal, inVert.texel };
	return Out;
}


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

// �W�I���g�� �V�F�[�_�[ �I�u�W�F�N�g (DirectX HLSL)

[maxvertexcount(15)]   // �W�I���g���V�F�[�_�[�ŏo�͂���ő咸�_��
// �W�I���g���V�F�[�_�[
void RenderGS3(triangle OutputVS In[3],                    // �g���C�A���O�� ���X�g���\�����钸�_�z��̓��͏��
	inout TriangleStream<OutputGS> TriStream   // ���_����ǉ����邽�߂̃X�g���[���I�u�W�F�N�g
	)
{
	OutputGS Out;

	int drawable = viewportDrawable;//�r�b�g���Z�̂���int�^�ɃL���X�g
	int i,j;

	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			matrix matVP = mul(cam[j].matView, cam[j].matProjection);
			matrix matWVP = mul(matWorld, matVP);
			// ���Ƃ̒��_���o��
			for (i = 0; i < 3; i++)
			{

				Out.pos = mul(In[i].pos, matWVP);

				Out.normal = In[i].normal;

				Out.texel = In[i].texel;

				Out.eye = normalize(cam[j].eyePos.xyz - In[i].pos.xyz);

				Out.color = In[i].color;   // ���̒��_�͕s�����ŏo��

				Out.viewportIndex = j;
				// ���_��ǉ�����
				TriStream.Append(Out);
			}
			// ���݂̃X�g���b�v���I�����A�V�����X�g���b�v���J�n����B
			TriStream.RestartStrip();
		}
		drawable >>= 1;
	}
}


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
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.rgb *= p + speculer.rgb;
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
	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{

		//�I�u�W�F�N�g�̗֊s�t�߂̋��x�������Ȃ�悤�ɂ���
		float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)), 1.0f) * 0.2f;

		float4 rgb = HalfLambert(inPixel);
			if (rgb.a != 0.f)
			{
				Out.rgb = rgb.rgb;

				Out.a = rgb.a;
			}
	}
	return Out;
}

// �������C�g�V�F�[�_
float4 RimLightMaterialShader(OutputGS inPixel) : SV_TARGET
{

	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{
		//�I�u�W�F�N�g�̗֊s�t�߂̋��x�������Ȃ�悤�ɂ���
		float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)), 2.0f) * 0.5f;

		float4 rgb = HalfLambertMaterial(inPixel);

			Out.rgb = rgb.rgb + P * 0.3f;

		Out.a = rgb.a;
	}

	return Out;
}

// �������C�g�V�F�[�_
float4 RimLightBlendShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{
		//�I�u�W�F�N�g�̗֊s�t�߂̋��x�������Ȃ�悤�ɂ���
		float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)), 2.0f) * 0.7f;

		float4 rgb = HalfLambertMaterial(inPixel);
		if (rgb.a != 0.f)
		{
			Out.rgb = rgb.rgb + P * 0.3f;

			Out.a = rgb.a;
		}
	}
	return Out;
}

// �}�e���A���ˑ��̃V�F�[�_
float4 DiffuseShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);

	Out.a = 1.f;

	return Out;
}

// �d�݂��l���ɓ���Ȃ��g�D�[���V�F�[�_
float4 ToonShader(OutputGS inPixel) : SV_TARGET
{

	float4 Out;

	float3 L = normalize(LightDirection.xyz);

	int divide = 4;
	float p = max(dot(inPixel.normal, L), 0.f);
	p = p * 0.5f + 0.5f;
	p = p * p;
	p = (float)((int)(p * divide) / (float)(divide));
	Out = p * texDiffuse.Sample(samDiffuse, inPixel.texel);

	Out.a = 1.f;

	return Out;
}