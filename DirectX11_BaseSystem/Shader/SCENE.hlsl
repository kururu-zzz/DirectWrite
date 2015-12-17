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
	float OldTime;
};

Texture2D  texDiffuse : register(t1);
SamplerState sampler0  : register(s1);

struct OutputGS
{
	float4 pos    : SV_POSITION;
	float4 color  : COLOR0;          // 頂点カラーはジオメトリシェーダー内で追加する
	float3 normal : NORMAL;
	float2 texel  : TEXCOORD0;
	uint   ViewportIndex : SV_ViewportArrayIndex;
};

struct OutputPS
{
	float4 out0:SV_TARGET0;
};

/*// ピクセルシェーダ
float4 FeedBack(OutputGS inPixel) : SV_TARGET
{
	/*float4 Out = (float4)0;
	Out = texDiffuse.Sample(samDiffuse, inPixel.texel);
	Out.a *= inPixel.color.a;
	return Out;
	
	float2 m_CenterTexel = float2(0.5f,0.5f);

	float4 Color[10];

	//ブラーの中心位置 ← 現在のテクセル位置
	float2 dir = m_CenterTexel - inPixel.texel;

	//距離を計算する
	float len = length(dir);

	//方向ベクトルの正規化し、１テクセル分の長さとなる方向ベクトルを計算する
	dir = normalize(dir) * float2(1.0f / 1200.f, 1.f / 900.f);

	float m_BlurPower = 3.f;

	//m_BlurPower でボケ具合を調整する
	//距離を積算することにより、爆発の中心位置に近いほどブラーの影響が小さくなるようにする
	dir *= m_BlurPower * len;

	//合成する
	Color[0] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel) * 0.19f;
	Color[1] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir) * 0.17f;
	Color[2] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 2.0f) * 0.15f;
	Color[3] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 3.0f) * 0.13f;
	Color[4] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 4.0f) * 0.11f;
	Color[5] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 5.0f) * 0.09f;
	Color[6] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 6.0f) * 0.07f;
	Color[7] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 7.0f) * 0.05f;
	Color[8] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 8.0f) * 0.03f;
	Color[9] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel + dir * 9.0f) * 0.01f;

	float4 Out = Color[0] + Color[1] + Color[2] + Color[3] + Color[4] + Color[5] + Color[6] + Color[7] + Color[8] + Color[9];
	Out.a = 1.0f;
	return Out;
}*/

OutputPS SurfaceShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(sampler0, inPixel.texel);
	Out.out0.a = inPixel.color.a;
	return Out;
}

OutputPS MonoShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(sampler0, inPixel.texel);
	float brightness = 0.299*Out.out0.r+0.587*Out.out0.g+0.114*Out.out0.b;
	Out.out0.r = Out.out0.g = Out.out0.b = brightness;
	Out.out0.a = inPixel.color.a;
	return Out;
}
/*
// ピクセルシェーダ
float4 BoostBlurShader(OutputGS inPixel)
{
		float m_CenterLine = 0.5f;

		float4 Color[10];

		//ブラーの中心位置 ← 現在のテクセル位置
		float dir = m_CenterLine - inPixel.texel.x;

		float m_BlurPower = 3.f;

		//m_BlurPower でボケ具合を調整する
		//距離を積算することにより、爆発の中心位置に近いほどブラーの影響が小さくなるようにする
		dir *= m_BlurPower * (1 / 900.f);

		//合成する
		Color[0] = SurfaceDiffuse.Sample(SurfaceSam, inPixel.texel) * 0.19f;
		Color[1] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir, inPixel.texel.y)) * 0.17f;
		Color[2] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 2.0f, inPixel.texel.y)) * 0.15f;
		Color[3] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 3.0f, inPixel.texel.y)) * 0.13f;
		Color[4] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 4.0f, inPixel.texel.y)) * 0.11f;
		Color[5] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 5.0f, inPixel.texel.y)) * 0.09f;
		Color[6] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 6.0f, inPixel.texel.y)) * 0.07f;
		Color[7] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 7.0f, inPixel.texel.y)) * 0.05f;
		Color[8] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 8.0f, inPixel.texel.y)) * 0.03f;
		Color[9] = SurfaceDiffuse.Sample(SurfaceSam, float2(inPixel.texel.x + dir * 9.0f, inPixel.texel.y)) * 0.01f;

		float4 Out = Color[0] + Color[1] + Color[2] + Color[3] + Color[4] + Color[5] + Color[6] + Color[7] + Color[8] + Color[9];
		Out.a = 1.0f;

		return Out;
}*/

// ピクセルシェーダ
OutputPS BoostShader(OutputGS inPixel)
{
	float time = Time / 20.f;
	float2 m_CenterTexel = float2(0.5f, 0.5f);
	float2 dir = inPixel.texel - m_CenterTexel;
	float2 vec = normalize(dir);
	float len = length(dir);
	float degree = atan2(vec.y, vec.x);
	float4 Out;

	float2 Inner = float2(cos(degree), sin(degree)) * (time - 0.03);
	float2 Outer = float2(cos(degree), sin(degree)) * (time + 0.03);

	if ((length(Outer) > len) && (length(Inner) < len))
	{
		float2 BezierPoint;
		if (cos(degree) < 0.f)
			BezierPoint = float2(cos(degree - 0.5f), sin(degree - 0.5f)) * (time);
		else
			BezierPoint = float2(cos(degree + 0.5f), sin(degree + 0.5f)) * (time);
		float Prop = ((len - length(Inner))/(length(Outer) - length(Inner)));

		float2 OutPoint;
		OutPoint = (1 - Prop) * (1 - Prop) * Outer + (1 - Prop) * Prop * BezierPoint + Prop * Prop * Inner;
		OutPoint.x += 0.5f;
		OutPoint.y += 0.5f;
		

		Out = texDiffuse.Sample(sampler0, OutPoint);
		Out.a = inPixel.color.a;

	}
	else
	{
		Out = texDiffuse.Sample(sampler0, inPixel.texel);
		Out.a = inPixel.color.a;
	}
	OutputPS Output;
	Output.out0 = Out;
	return Output;
}

// ピクセルシェーダ
OutputPS SplitShader(OutputGS inPixel)
{
	int time = Time;
	float4 Out = (float4)1;
	int flushTime = 50;
	int splitTime = 100;
	if (time < flushTime)
	{
		if ((inPixel.pos.y >= 448.f) && (inPixel.pos.y <= 452.f) && (inPixel.pos.x <= 600 - time * (600 / flushTime) || inPixel.pos.x >= 600 + time * (600 / flushTime)))
			Out = float4(1,1,1,1);
		else
			Out = texDiffuse.Sample(sampler0, inPixel.texel);
			Out.a = inPixel.color.a;
	}
	else
	{
		if (inPixel.pos.y <= 450.f - (450.f / splitTime) * (time - flushTime))
		{
			inPixel.texel.y += ((450.f / splitTime) / 900.f) * (time - flushTime);
			Out = texDiffuse.Sample(sampler0, inPixel.texel);
			Out.a = inPixel.color.a;
		}
		else if (inPixel.pos.y >= 450.f + (450.f / splitTime) * (time - flushTime))
		{
			inPixel.texel.y -= ((450.f / splitTime) / 900.f) * (time - flushTime);
			Out = texDiffuse.Sample(sampler0, inPixel.texel);
			Out.a = inPixel.color.a;
		}
		else
			Out = 0;
	}
	OutputPS output;
	output.out0 = Out;
	return output;
}

OutputPS FadeShader(OutputGS inPixel)
{
	float4 Out;
	Out = texDiffuse.Sample(sampler0, inPixel.texel);
	Out.rgb *= Time;
	Out.a = inPixel.color.a;
	OutputPS output;
	output.out0 = Out;
	return output;
}

OutputPS LoadSceneShader(OutputGS inPixel)
{
	int time = Time;
	int oldTime = OldTime;
	float4 Out = texDiffuse.Sample(sampler0, inPixel.texel);
	if (inPixel.pos.y <= 10.f*time || inPixel.pos.y >= 900.f - 10.f*time)
	{
		Out = float4(0.f, 0.f, 0.f, 1.f);
	}
	else
	{
		if (oldTime <= time)
			Out.a = inPixel.color.a;
		else
			Out.a = 0;
	}
	OutputPS output;
	output.out0 = Out;
	return output;
}

OutputPS DiveSceneShader(OutputGS inPixel)
{
	int time = Time;
	float radius = time * time * time * 0.01f;
	float4 Out;
	float distantFromCenter = 0.f;
	float2 vectorFromCenter;
	{
		float x = inPixel.pos.x - 600.f;
		float y = inPixel.pos.y - 450.f;
		distantFromCenter = sqrt(x*x + y*y);
		vectorFromCenter = float2(x , y);
	}
	if (distantFromCenter < radius || time > 50)
	{
		Out = float4(0.f, 0.f, 0.f, 0.f);
	}
	else
	{
		float2 texel = clamp(float2(inPixel.texel.x + (sign(vectorFromCenter.x) * radius / 600.f), inPixel.texel.y + (sign(vectorFromCenter.y) * radius / 450.f)),0.f,1.f);

		Out = texDiffuse.Sample(sampler0, texel);
		Out.a = inPixel.color.a;
	}
	OutputPS output;
	output.out0 = Out;
	return output;
}

OutputPS HalfBlackSurfaceShader(OutputGS inPixel)
{
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(sampler0, inPixel.texel);
	Out.out0.r *= 0.5f;
	Out.out0.g *= 0.5f;
	Out.out0.b *= 0.5f;
	Out.out0.a = inPixel.color.a;
	return Out;
}

OutputPS WhiteOutSurfaceShader(OutputGS inPixel)
{
	float time = Time;
	bool inverseFlag = OldTime;
	time = saturate(time);
	if (inverseFlag)
	{
		time = 1.f - time;
	}
	OutputPS Out = (OutputPS)0;
	Out.out0 = texDiffuse.Sample(sampler0, inPixel.texel);
	Out.out0.rgb += float3(time, time, time);
	Out.out0.a = inPixel.color.a;
	return Out;
}