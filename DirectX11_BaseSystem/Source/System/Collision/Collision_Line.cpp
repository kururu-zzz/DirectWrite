#include "../../../header/System/Collision/Collision.h"

XMFLOAT3 g_Vector = XMFLOAT3(0.f, 0.f, 0.f);

double CollisionCheck::CalDistant(const XMFLOAT2& PointA, const XMFLOAT2& PointB)
{
	return sqrt((PointA.x - PointB.x) * (PointA.x - PointB.x) + (PointA.y - PointB.y) * (PointA.y - PointB.y));
}

double CollisionCheck::CalDistant(const XMFLOAT3& PointA, const XMFLOAT3& PointB)
{
	return sqrt((PointA.x - PointB.x) * (PointA.x - PointB.x) + (PointA.y - PointB.y) * (PointA.y - PointB.y) + (PointA.z - PointB.z) * (PointA.z - PointB.z));
}

bool CollisionCheck::Segment_Plane(const XMFLOAT3& BasePoint, const HitSegment_3D& Segment, const XMFLOAT3& MeshNormal)
{
	XMFLOAT3 tmp;
	XMStoreFloat3(&tmp, XMVector3Dot(XMLoadFloat3(&Segment.Begin) - XMLoadFloat3(&BasePoint), XMLoadFloat3(&MeshNormal))
		* XMVector3Dot(XMLoadFloat3(&Segment.End) - XMLoadFloat3(&BasePoint), XMLoadFloat3(&MeshNormal)));
	if (tmp.x <= 0)
		return true;
	else
		return false;
}

void CollisionCheck::SearchCollisionPoint(XMFLOAT3* Point, const XMFLOAT3& BasePoint, const HitSegment_3D& Segment, const XMFLOAT3& MeshNormal)
{
	if (Segment_Plane(BasePoint, Segment, MeshNormal))
	{
		XMFLOAT3 tmp;
		XMStoreFloat3(&tmp, XMVector3Dot(XMLoadFloat3(&Segment.Begin) - XMLoadFloat3(&BasePoint), XMLoadFloat3(&MeshNormal)));
		float d1 = fabs(tmp.x);
		XMStoreFloat3(&tmp, XMVector3Dot(XMLoadFloat3(&Segment.End) - XMLoadFloat3(&BasePoint), XMLoadFloat3(&MeshNormal)));
		float d2 = fabs(tmp.x);
		float prop = d1 / (d1 + d2);
		XMStoreFloat3(Point, ((1 - prop) * (XMLoadFloat3(&Segment.Begin) - XMLoadFloat3(&BasePoint))
			+ (prop)* (XMLoadFloat3(&Segment.End) - XMLoadFloat3(&BasePoint))) + XMLoadFloat3(&BasePoint));
	}
	else
		return;
}

bool CollisionCheck::Line_Line(const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB)
{
	XMFLOAT3 tmp1,tmp2;
	//XMStoreFloat3(&tmp1, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&SegmentA.End) - XMLoadFloat3(&SegmentA.Begin), XMLoadFloat3(&SegmentB.End) - XMLoadFloat3(&SegmentB.Begin))));
	//XMStoreFloat3(&tmp2, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&SegmentA.End) - XMLoadFloat3(&SegmentA.Begin), XMLoadFloat3(&SegmentA.Begin) - XMLoadFloat3(&SegmentB.Begin))));
	XMFLOAT3 AB = SegmentA.End - SegmentA.Begin;
	XMFLOAT3 CD = SegmentB.End - SegmentB.Begin;

	XMFLOAT3 n1, n2;
	XMStoreFloat3(&n1, XMVector3Normalize(XMLoadFloat3(&AB)));
	XMStoreFloat3(&n2, XMVector3Normalize(XMLoadFloat3(&CD)));

	XMFLOAT3 work;
	XMStoreFloat3(&work, XMVector3Dot(XMLoadFloat3(&n1), XMLoadFloat3(&n2)));
	double work1 = work.x;
	double work2 = 1 - work1*work1;

	//直線が平行な場合は計算できない 平行だとwork2が0になる
	if (work2 == 0) { return false; }

	XMFLOAT3 AC = SegmentB.Begin - SegmentA.Begin;

	XMStoreFloat3(&work, XMVector3Dot(XMLoadFloat3(&AC), XMLoadFloat3(&n1)));
	double work3 = work.x;
	XMStoreFloat3(&work, XMVector3Dot(XMLoadFloat3(&AC), XMLoadFloat3(&n2)));
	double work4 = work.x;

	double d1 = (work3 - work1 * work4) / work2;
	double d2 = (work1 * work3 - work4) / work2;

	//AB上の最近点
	tmp1.x = SegmentA.Begin.x + static_cast<float>(d1) * n1.x;
	tmp1.y = SegmentA.Begin.y + static_cast<float>(d1) * n1.y;
	tmp1.z = SegmentA.Begin.z + static_cast<float>(d1) * n1.z;

	//BC上の最近点
	tmp2.x = SegmentB.Begin.x + static_cast<float>(d2) * n2.x;
	tmp2.y = SegmentB.Begin.y + static_cast<float>(d2) * n2.y;
	tmp2.z = SegmentB.Begin.z + static_cast<float>(d2) * n2.z;

	//交差の判定
	if (CalDistant(tmp1,tmp2) < 0.000001) 
	{
		//交差した
		g_Vector.x = tmp1.x;
		g_Vector.y = tmp1.y;
		g_Vector.z = tmp1.z;
		return true;
	}
	return false;
}

bool CollisionCheck::Segment_Point_2D(const HitSegment_2D& Segment, const XMFLOAT2& Point)
{
	float Length = sqrt((Segment.End.x - Segment.Begin.x) * (Segment.End.x - Segment.Begin.x) + (Segment.End.y - Segment.Begin.y) * (Segment.End.y - Segment.Begin.y));
	float Distant = sqrt((Point.x - Segment.Begin.x) * (Point.x - Segment.Begin.x) + (Point.y - Segment.Begin.y) * (Point.y - Segment.Begin.y));
	if (Length >= Distant)
	{
		float Tmp = (Segment.End.x - Segment.Begin.x) * (Point.x - Segment.Begin.x) + (Segment.End.y - Segment.Begin.y) * (Point.y - Segment.Begin.y);
		const float eps = 0.001f;
		if ((Length * Distant + eps >= Tmp) && (Length * Distant - eps <= Tmp))
			return true;
	}
	return false;
}

bool CollisionCheck::Segment_Segment_2D(const HitSegment_2D& SegmentA, const HitSegment_2D& SegmentB)
{
	XMFLOAT2 SegmentC;
	SegmentC.x = SegmentB.Begin.x - SegmentA.Begin.x;
	SegmentC.y = SegmentB.Begin.y - SegmentA.Begin.y;
	float Cross_A_B;
	XMStoreFloat(&Cross_A_B, XMVector2Cross(XMLoadFloat2(&SegmentA.End) - XMLoadFloat2(&SegmentA.Begin), XMLoadFloat2(&SegmentB.End) - XMLoadFloat2(&SegmentB.Begin)));
	if (Cross_A_B == 0.0f) {
		// 平行状態
		return false;
	}

	float Cross_A_C, Cross_B_C;
	XMStoreFloat(&Cross_A_C, XMVector2Cross(XMLoadFloat2(&SegmentC), XMLoadFloat2(&SegmentA.End) - XMLoadFloat2(&SegmentA.Begin)));
	XMStoreFloat(&Cross_B_C, XMVector2Cross(XMLoadFloat2(&SegmentC), XMLoadFloat2(&SegmentB.End) - XMLoadFloat2(&SegmentB.Begin)));

	float t1 = Cross_B_C / Cross_A_B;
	float t2 = Cross_A_C / Cross_A_B;

	const float eps = 0.00001f;
	if (t1 + eps < 0 || t1 - eps > 1 || t2 + eps < 0 || t2 - eps > 1) {
		// 交差していない
		return false;
	}

	return true;
}

bool CollisionCheck::Segment_Segment_3D(const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB)
{
	if (Line_Line(SegmentA, SegmentB))
	{
		bool Flag = false;
		HitSegment_2D tmpA, tmpB;
		tmpA.Begin.x = SegmentA.Begin.x;
		tmpA.Begin.y = SegmentA.Begin.y;
		tmpA.End.x = SegmentA.End.x;
		tmpA.End.y = SegmentA.End.y;
		tmpB.Begin.x = SegmentB.Begin.x;
		tmpB.Begin.y = SegmentB.Begin.y;
		tmpB.End.x = SegmentB.End.x;
		tmpB.End.y = SegmentB.End.y;
		if ((tmpA.Begin.x == tmpA.End.x) && (tmpA.Begin.y == tmpA.End.y))
			Flag = Segment_Point_2D(tmpB, tmpA.Begin);
		else if ((tmpB.Begin.x == tmpB.End.x) && (tmpB.Begin.y == tmpB.End.y))
			Flag = Segment_Point_2D(tmpA, tmpB.Begin);
		if ((Segment_Segment_2D(tmpA, tmpB))|| (Flag))
		{
			tmpA.Begin.x = SegmentA.Begin.z;
			tmpA.End.x = SegmentA.End.z;
			tmpB.Begin.x = SegmentB.Begin.z;
			tmpB.End.x = SegmentB.End.z;
			if ((tmpA.Begin.x == tmpA.End.x) && (tmpA.Begin.y == tmpA.End.y))
				Flag = Segment_Point_2D(tmpB, tmpA.Begin);
			else if ((tmpB.Begin.x == tmpB.End.x) && (tmpB.Begin.y == tmpB.End.y))
				Flag = Segment_Point_2D(tmpA, tmpB.Begin);
			if ((Segment_Segment_2D(tmpA, tmpB)) || (Flag))
			{
				tmpA.Begin.y = SegmentA.Begin.x;
				tmpA.End.y = SegmentA.End.x;
				tmpB.Begin.y = SegmentB.Begin.x;
				tmpB.End.y = SegmentB.End.x;
				if ((tmpA.Begin.x == tmpA.End.x) && (tmpA.Begin.y == tmpA.End.y))
					Flag = Segment_Point_2D(tmpB, tmpA.Begin);
				else if ((tmpB.Begin.x == tmpB.End.x) && (tmpB.Begin.y == tmpB.End.y))
					Flag = Segment_Point_2D(tmpA, tmpB.Begin);
				if ((Segment_Segment_2D(tmpA, tmpB)) || (Flag))
					return true;
			}
		}
	}
	return false;
}

void CollisionCheck::StoreHitSegment2D(XMFLOAT3 *Point, const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB)
{
	if (Line_Line(SegmentA, SegmentB))
	{
		HitSegment_2D tmpA, tmpB;
		tmpA.Begin.x = SegmentA.Begin.x;
		tmpA.Begin.y = SegmentA.Begin.y;
		tmpA.End.x = SegmentA.End.x;
		tmpA.End.y = SegmentA.End.y;
		tmpB.Begin.x = SegmentB.Begin.x;
		tmpB.Begin.y = SegmentB.Begin.y;
		tmpB.End.x = SegmentB.End.x;
		tmpB.End.y = SegmentB.End.y;
		if (Segment_Segment_2D(tmpA, tmpB))
		{
			Point->x = g_Vector.x;
			Point->y = g_Vector.y;
			Point->z = g_Vector.z;
		}
	}
}

void CollisionCheck::GetHitSegment3D(XMFLOAT3 *Point, const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB)
{
	if (Segment_Segment_3D(SegmentA, SegmentB))
	{
		Point->x = g_Vector.x;
		Point->y = g_Vector.y;
		Point->z = g_Vector.z;
	}
}