#include "../../../header/System/Collision/Collision.h"

XMFLOAT2 g_Float2;

bool CollisionCheck::Circle_Circle(HitCircle* CircleA, HitCircle* CircleB)
{
	double Distant = CalDistant(CircleA->Center,CircleB->Center);
	if (Distant <= CircleA->Radius + CircleB->Radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CollisionCheck::MoveToContactCircle(HitCircle *CircleA, HitCircle *CircleB)
{
	if (Circle_Circle(CircleA, CircleB))
	{
		XMFLOAT2 Tmp;
		Tmp.x = CircleB->Center.x - CircleA->Center.x;
		Tmp.y = CircleB->Center.y - CircleA->Center.y;
		XMStoreFloat2(&Tmp , XMVector2Normalize(XMLoadFloat2(&Tmp)));
		Tmp.x *= CircleA->Radius + CircleB->Radius;
		Tmp.y *= CircleA->Radius + CircleB->Radius;
		Tmp.x += CircleA->Center.x;
		Tmp.y += CircleA->Center.y;
		CircleB->Center = Tmp;
		return true;
	}
	return false;
}