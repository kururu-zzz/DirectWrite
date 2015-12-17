#ifndef _COLLISION
#define _COLLISION

#include "../Base/DXMath.h" 
using namespace DirectX;
//using namespace DirectX;

struct HitSegment_2D
{
	XMFLOAT2 Begin;
	XMFLOAT2 End;
};

struct HitSegment_3D
{
	XMFLOAT3 Begin;
	XMFLOAT3 End;
};

struct HitCircle
{
	XMFLOAT2 Center;
	float Radius;
};

struct HitEllipse
{
	float fRad_X; // Xé≤åa
	float fRad_Y; // Yé≤åa
	float fAngle; // âÒì]äpìx
	float fCx; // êßå‰ì_Xç¿ïW
	float fCy; // êßå‰ì_Yç¿ïW

	HitEllipse()
	{
		fRad_X = 100.0f;
		fRad_Y = 100.0f;
		fAngle = 0.0f;
		fCx = 0.0f;
		fCy = 0.0f;
	}
};

namespace CollisionCheck{
	double CalDistant(const XMFLOAT2& PointA, const XMFLOAT2& PointB);
	double CalDistant(const XMFLOAT3& PointA, const XMFLOAT3& PointB);
	bool Segment_Plane(const XMFLOAT3& BasePoint,const HitSegment_3D& Segment,const XMFLOAT3& MeshNormal);
	void SearchCollisionPoint(XMFLOAT3* Point, const XMFLOAT3& BasePoint, const HitSegment_3D& Segment, const XMFLOAT3& MeshNormal);
	bool Line_Line(const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB);
	bool Segment_Segment_2D(const HitSegment_2D& SegmentA, const HitSegment_2D& SegmentB);
	bool Segment_Segment_3D(const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB);
	bool Segment_Point_2D(const HitSegment_2D& Segment, const XMFLOAT2& Point);
	void StoreHitSegment2D(XMFLOAT3 *Point, const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB);
	void GetHitSegment3D(XMFLOAT3 *Point, const HitSegment_3D& SegmentA, const HitSegment_3D& SegmentB);

	bool Circle_Circle(HitCircle* CircleA, HitCircle* CircleB);
	//è’ìÀâ~BÇê⁄ÇµÇƒÇÈèÛë‘Ç‹Ç≈ìÆÇ©Ç∑
	bool MoveToContactCircle(HitCircle *CircleA, HitCircle *CircleB);

	bool Ellipse_Ellipse(HitEllipse *EllipseA, HitEllipse *EllipseB);
};

#endif