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

//! 頂点属性
/*!
基本はD3D9と変わらない
ただし、いくつかのセマンティクスが変わっている
システム側に渡すセマンティクスはSV_の接頭辞がついている
*/
struct InputVS
{
	float3	pos			: IN_POSITION;
	float4	color		: IN_COLOR;
	float3	normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;   // テクセル
	uint4 boneIndex		: IN_BONEINDEX;
	float4 boneWeight	: IN_BONEWEIGHT;
	uint InstID         : SV_InstanceID; // インスタンスID
};
struct OutputVS
{
	float4	pos			: SV_POSITION;
	float4	color		: COLOR0;
	float4 eye			: COLOR1;
	float3 normal       : NORMAL;
	float2 texel        : TEXCOORD0;
};


/*-----3Dモデル描画用ハーフランバート-----*/


//! 頂点シェーダ
OutputVS RenderVS( InputVS inVert )
{
	int instanceMax = 500;
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, float4(inVert.pos,0.0f),inVert.normal, inVert.texel };
	Out.pos = mul(Out.pos, matWorld[inVert.InstID % instanceMax]);

	return Out;
}

// ジオメトリシェーダーの出力パラメータ
struct OutputGS
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;          // 頂点カラーはジオメトリシェーダー内で追加する
	float3 eye	  : COLOR1;
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	uint   viewportIndex : SV_ViewportArrayIndex;
};

// ジオメトリ シェーダー オブジェクト (DirectX HLSL)

[maxvertexcount(15)]   // ジオメトリシェーダーで出力する最大頂点数
// ジオメトリシェーダー
void RenderGS3(triangle OutputVS In[3],                    // トライアングル リストを構成する頂点配列の入力情報
	inout TriangleStream<OutputGS> TriStream   // 頂点情報を追加するためのストリームオブジェクト
	)
{
	OutputGS Out;

	int drawable = viewportDrawable;//ビット演算のためint型にキャスト
	int i, j;

	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			// もとの頂点を出力
			for (i = 0; i < 3; i++)
			{
				matrix matVP = mul(cam[j].matView, cam[j].matProjection);

				Out.pos = mul(In[i].pos, matVP);

				Out.texel = In[i].texel;

				Out.normal = In[i].normal;

				Out.eye = normalize(cam[j].eyePos.xyz - In[i].eye.xyz);

				Out.color = In[i].color;   // 元の頂点は不透明で出力

				Out.viewportIndex = j;
				// 頂点を追加する
				TriStream.Append(Out);
			}
			// 現在のストリップを終了し、新しいストリップを開始する。
			TriStream.RestartStrip();
		}
		drawable >>= 1;
	}
}