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

// ジオメトリシェーダーの出力パラメータ
struct OutputGS
{
	float4 pos    : SV_POSITION;
	float2 depth  : TEXCOORD0;
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
				Out.pos = mul(In[i].pos, cam[j].matLVP);

				Out.depth.xy = mul(In[i].pos, cam[j].matLVP).zw;

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


//! ピクセルシェーダ
float2 CreateDepthBuffer(OutputGS inPixel) : SV_TARGET
{
	float d = inPixel.depth.x / inPixel.depth.y;
	float2 Out = float2(d, d*d);
	return Out;
}
