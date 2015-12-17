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
	float3	pos			: IN_POSITION;
	float4	color		: IN_COLOR;
	float3	normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;   // �e�N�Z��

};
struct OutputVS
{
	float4 pos	  : SV_POSITION;
	float4 color  : COLOR0;
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	float4 depth  : TEXCOORD1;
};


/*-----3D���f���`��p�n�[�t�����o�[�g-----*/


//! ���_�V�F�[�_
OutputVS RenderVS( InputVS inVert )
{
	OutputVS Out = { float4(inVert.pos, 1.0f), inVert.color, inVert.normal, inVert.texel, float4(0.f, 0.f, 0.f, 0.f)};
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
	float4 depth  : TEXCOORD1;
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
	int i, j;

	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			matrix matVP = mul(cam[j].matView, cam[j].matProjection);
			matrix matWVP = mul(matWorld, matVP);
			matrix matLWVP = mul(matWorld, cam[j].matLVP);
			// ���Ƃ̒��_���o��
			for (i = 0; i < 3; i++)
			{
				Out.pos = mul(In[i].pos, matWVP);

				Out.normal = mul(In[i].normal, matWorld);

				Out.texel = In[i].texel;

				Out.depth = mul(In[i].pos, matLWVP);

				Out.color = float4(1.0f, 1.0f, 1.0f, 1.0f);   // ���̒��_�͕s�����ŏo��

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


float VSM_Filter(float2 Tex, float2 depth,float fragDepth)
{
	float Ex_2 = depth.x * depth.x;
	float E_x2 = depth.y;
	float variance = (Ex_2 - E_x2);
	variance = abs(variance);
	float md = (fragDepth - depth.x);
	float p = variance / (variance + (md * md));
	return max(p, fragDepth <= depth.r);
}


//! �s�N�Z���V�F�[�_
float4 VarianceShadow(OutputGS inPixel) : SV_TARGET
{
	float2 Tex = float2(inPixel.depth.x / inPixel.depth.w * 0.5f + 0.5f, inPixel.depth.y / inPixel.depth.w * -0.5f + 0.5f);
	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{
		Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
		float ShadowColor;
		float Bias = 0.01f;

		//Z�o�b�t�@�T�[�t�F�C�X����[�x�l���擾����
		float2 d = texDiffuse1.Load(float3(Tex * float2(1200.f, 900.f), 0.f)).rg;
			if (Tex.x < 0 || Tex.x > 1 || Tex.y < 0 || Tex.y > 1 || d.r == 1.f){
				ShadowColor = 1.0f;
			}
			else{
				ShadowColor = VSM_Filter(Tex, d, inPixel.depth.z / inPixel.depth.w + Bias);
				ShadowColor *= 0.5f;
				ShadowColor += 0.5f;
			}
			Out.rgb *= ShadowColor;
			//	Out.rgb = d;
	}
	return Out;
}

