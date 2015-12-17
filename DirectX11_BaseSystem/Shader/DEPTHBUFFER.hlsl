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
};

cbuffer cLBuffers : register(b3)
{
	float4 LightDirection;
};
cbuffer cVBuffers : register(b4)
{
	float viewportDrawable;
	float viewportNum;
};

struct OutputVS
{
	float4 pos			: SV_POSITION;
	float4 color		: COLOR0;
	float4 eye			: COLOR1;
	float3 normal       : NORMAL;
	float2 texel        : TEXCOORD0;
};

// �W�I���g���V�F�[�_�[�̏o�̓p�����[�^
struct OutputGS
{
	float4 pos    : SV_POSITION;
	float2 depth  : TEXCOORD0;
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
				Out.pos = mul(In[i].pos, cam[j].matLVP);

				Out.depth.xy = mul(In[i].pos, cam[j].matLVP).zw;

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
float2 CreateDepthBuffer(OutputGS inPixel) : SV_TARGET
{
	float d = inPixel.depth.x / inPixel.depth.y;
	float2 Out = float2(d, d*d);
	return Out;
}
