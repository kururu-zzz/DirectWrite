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

//! 頂点属性
/*!
基本はD3D9と変わらない
ただし、いくつかのセマンティクスが変わっている
システム側に渡すセマンティクスはSV_の接頭辞がついている
*/
struct InputVS
{
	float3 pos			: IN_POSITION;
	float4 color		: IN_COLOR;
	float3 normal		: IN_NORMAL;
	float2 texel        : IN_TEXCOORD;   // テクセル
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


/*-----3Dモデル描画用ハーフランバート-----*/


//! 頂点シェーダ
OutputVS RenderVS( InputVS inVert )
{
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, float4(0.f,0.f,0.f,0.f),inVert.normal, inVert.texel };
	return Out;
}


// ジオメトリシェーダーの入力パラメータ
//typedef OutputVS InputGS;

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
	int i,j;

	for (j = 0; j < viewportNum; j++)
	{
		if (drawable & 0x01)
		{
			matrix matVP = mul(cam[j].matView, cam[j].matProjection);
			matrix matWVP = mul(matWorld, matVP);
			// もとの頂点を出力
			for (i = 0; i < 3; i++)
			{

				Out.pos = mul(In[i].pos, matWVP);

				Out.normal = In[i].normal;

				Out.texel = In[i].texel;

				Out.eye = normalize(cam[j].eyePos.xyz - In[i].pos.xyz);

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


//! ピクセルシェーダ
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

//! ピクセルシェーダ
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

/*-----フォンシェーダ-----*/

// ピクセルシェーダ
float4 PhoneShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out;


	//法線ベクトルを正規化する
	float3 N = normalize(inPixel.normal);
	//頂点 -> ライト位置ベクトル + 頂点 -> 視点ベクトル(注意１)
	float3 H = normalize(LightDirection.xyz + normalize(inPixel.eye));
	//スペキュラーカラーを計算する(注意２)
	float S = pow(max(0.0f, dot(N, H)), 20.0f) * 0.75f;

	//スペキュラーカラーを加算する
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.rgb = Out.rgb * 0.5f + S;


	return Out;
}

// リムライトシェーダ
float4 RimLightShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{

		//オブジェクトの輪郭付近の強度が強くなるようにする
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

// リムライトシェーダ
float4 RimLightMaterialShader(OutputGS inPixel) : SV_TARGET
{

	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{
		//オブジェクトの輪郭付近の強度が強くなるようにする
		float P = pow(1.0f - max(0.0f, dot(inPixel.normal, inPixel.eye)), 2.0f) * 0.5f;

		float4 rgb = HalfLambertMaterial(inPixel);

			Out.rgb = rgb.rgb + P * 0.3f;

		Out.a = rgb.a;
	}

	return Out;
}

// リムライトシェーダ
float4 RimLightBlendShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out = (float4)0;
	if (inPixel.pos.x >= 0.f && inPixel.pos.x <= 1200.f && inPixel.pos.y >= 0.f && inPixel.pos.y <= 900.f)
	{
		//オブジェクトの輪郭付近の強度が強くなるようにする
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

// マテリアル依存のシェーダ
float4 DiffuseShader(OutputGS inPixel) : SV_TARGET
{
	float4 Out;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);

	Out.a = 1.f;

	return Out;
}

// 重みを考慮に入れないトゥーンシェーダ
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