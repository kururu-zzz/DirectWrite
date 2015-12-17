#include "../../../header/System/Collision/Collision.h"

bool CollisionCheck::Ellipse_Ellipse(HitEllipse *E1, HitEllipse *E2)
{
	// STEP1 : E2‚ð’PˆÊ‰~‚É‚·‚é•ÏŠ·‚ðE1‚ÉŽ{‚·
	float DefAng = E1->fAngle - E2->fAngle;
	float Cos = cos(DefAng);
	float Sin = sin(DefAng);
	float nx = E2->fRad_X * Cos;
	float ny = -E2->fRad_X * Sin;
	float px = E2->fRad_Y * Sin;
	float py = E2->fRad_Y * Cos;
	float ox = cos(E1->fAngle)*(E2->fCx - E1->fCx) + sin(E1->fAngle)*(E2->fCy - E1->fCy);
	float oy = -sin(E1->fAngle)*(E2->fCx - E1->fCx) + cos(E1->fAngle)*(E2->fCy - E1->fCy);

	// STEP2 : ˆê”ÊŽ®A`G‚ÌŽZo
	float rx_pow2 = 1 / (E1->fRad_X*E1->fRad_X);
	float ry_pow2 = 1 / (E1->fRad_Y*E1->fRad_Y);
	float A = rx_pow2*nx*nx + ry_pow2*ny*ny;
	float B = rx_pow2*px*px + ry_pow2*py*py;
	float D = 2 * rx_pow2*nx*px + 2 * ry_pow2*ny*py;
	float E = 2 * rx_pow2*nx*ox + 2 * ry_pow2*ny*oy;
	float F = 2 * rx_pow2*px*ox + 2 * ry_pow2*py*oy;
	float G = (ox / E1->fRad_X)*(ox / E1->fRad_X) + (oy / E1->fRad_Y)*(oy / E1->fRad_Y) - 1;

	// STEP3 : •½sˆÚ“®—Ê(h,k)‹y‚Ñ‰ñ“]Šp“xƒÆ‚ÌŽZo
	float tmp1 = 1 / (D*D - 4 * A*B);
	float h = (F*D - 2 * E*B)*tmp1;
	float k = (E*D - 2 * A*F)*tmp1;
	float Th = (B - A) == 0 ? 0 : atan(D / (B - A)) * 0.5f;

	// STEP4 : +1‘È‰~‚ðŒ³‚É–ß‚µ‚½Ž®‚Å“–‚½‚è”»’è
	float CosTh = cos(Th);
	float SinTh = sin(Th);
	float A_tt = A*CosTh*CosTh + B*SinTh*SinTh - D*CosTh*SinTh;
	float B_tt = A*SinTh*SinTh + B*CosTh*CosTh + D*CosTh*SinTh;
	float KK = A*h*h + B*k*k + D*h*k - E*h - F*k + G;
	if (KK>0) KK = 0; // ”O‚Ì‚½‚ß
	float Rx_tt = 1 + sqrt(-KK / A_tt);
	float Ry_tt = 1 + sqrt(-KK / B_tt);
	float x_tt = CosTh*h - SinTh*k;
	float y_tt = SinTh*h + CosTh*k;
	float JudgeValue = x_tt*x_tt / (Rx_tt*Rx_tt) + y_tt*y_tt / (Ry_tt*Ry_tt);

	if (JudgeValue <= 1)
		return true; // Õ“Ë

	return false;
}