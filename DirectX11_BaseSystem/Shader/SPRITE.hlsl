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
システム側に渡すセマンティクスはSV_の接頭辞がついている
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

//! 頂点シェーダ
OutputVS RenderVS( InputVS inVert )
{
	OutputVS Out = { float4(inVert.pos,1.0f), inVert.color, inVert.normal, inVert.texel };
	return Out;
}


// ジオメトリシェーダーの入力パラメータ
//typedef OutputVS InputGS;

// ジオメトリシェーダーの出力パラメータ
struct OutputGS
{
float4 pos    : SV_POSITION;
float4 color  : COLOR0;          // 頂点カラーはジオメトリシェーダー内で追加する
float3 normal : NORMAL;
float2 texel  : TEXCOORD0;
uint   ViewportIndex : SV_ViewportArrayIndex;
};

/*-----Sprite用シェーダー-----*/

[maxvertexcount(15)]   // ジオメトリシェーダーで出力する最大頂点数(viewport * 3でよい)
// ジオメトリシェーダー
void RenderGSSpriteViewport(triangle OutputVS In[3],                    // トライアングル リストを構成する頂点配列の入力情報
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
				Out.pos = mul(In[i].pos, cam[j].matViewPort);

				Out.normal = float3(0.f, 0.f, 0.f);

				Out.texel = In[i].texel;

				Out.color = In[i].color;   // 元の頂点は不透明で出力

				Out.ViewportIndex = j;

				// 頂点を追加する
				TriStream.Append(Out);
			}
			// 現在のストリップを終了し、新しいストリップを開始する。
			TriStream.RestartStrip();
		}
		drawable >>= 1;
	}
}

[maxvertexcount(15)]   // ジオメトリシェーダーで出力する最大頂点数(viewport * 3でよい)
// ジオメトリシェーダー
void RenderGSSprite(triangle OutputVS In[3],                    // トライアングル リストを構成する頂点配列の入力情報
	inout TriangleStream<OutputGS> TriStream   // 頂点情報を追加するためのストリームオブジェクト
	)
{

	OutputGS Out;

	int drawable = viewportDrawable;//ビット演算のためint型にキャスト
	int i;
	// もとの頂点を出力
	for (i = 0; i < 3; i++)
	{
		Out.pos = mul(In[i].pos, cam[0].matViewPort);

		Out.normal = float3(0.f, 0.f, 0.f);

		Out.texel = In[i].texel;

		Out.color = In[i].color;   // 元の頂点は不透明で出力

		Out.ViewportIndex = 0;

		// 頂点を追加する
		TriStream.Append(Out);
	}
	// 現在のストリップを終了し、新しいストリップを開始する。
	TriStream.RestartStrip();
}

struct OutputPS
{
	float4 out0:SV_TARGET0;
};

// ピクセルシェーダ
OutputPS SpriteShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.out0.a *= inPixel.color.a;
	return Out;
}

// ピクセルシェーダ
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

// ピクセルシェーダ
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