cbuffer cWBuffers : register(b0)
{
	matrix	matWorld[500];
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
	float3	pos			: IN_POSITION;
	float4	color		: IN_COLOR;
	float3	normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;   // �e�N�Z��
	uint4 boneIndex		: IN_BONEINDEX;
	float4 boneWeight	: IN_BONEWEIGHT;
	uint InstID         : SV_InstanceID; // �C���X�^���XID
};
struct OutputVS
{
	float4	pos			: SV_POSITION;
	float4	color		: COLOR0;
	float4 eye			: COLOR1;
	float3 normal       : NORMAL;
	float2 texel        : TEXCOORD0;
};


/*-----3D���f���`��p�n�[�t�����o�[�g-----*/


//! ���_�V�F�[�_
OutputVS RenderVS( InputVS inVert )
{
	int instanceMax = 500;
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, float4(inVert.pos,0.0f),inVert.normal, inVert.texel };
	Out.pos = mul(Out.pos, matWorld[inVert.InstID % instanceMax]);

	return Out;
}

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
	int i, j;

	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			// ���Ƃ̒��_���o��
			for (i = 0; i < 3; i++)
			{
				matrix matVP = mul(cam[j].matView, cam[j].matProjection);

				Out.pos = mul(In[i].pos, matVP);

				Out.texel = In[i].texel;

				Out.normal = In[i].normal;

				Out.eye = normalize(cam[j].eyePos.xyz - In[i].eye.xyz);

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