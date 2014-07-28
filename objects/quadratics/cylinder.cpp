#include "stdafx.h"
#include "cylinder.h"

Cylinder::Cylinder(Vertex pcenter)
{
	center = pcenter;
}

bool Cylinder::intersect(Ray &ray, Hit *hit)
{
	double Aq = pow(ray.D.x, 2) + pow(ray.D.z, 2);

	double	Bq = 2* (ray.P.x - center.x)*ray.D.x + 2* (ray.P.z - center.z)*ray.D.z;

	double	Cq = pow((ray.P.x - center.x), 2) + pow((ray.P.z - center.z), 2) - 1;

	if (!Object::SolveQuadratic(Aq, Bq, Cq))
		return false;
	double t = t0;
	if (t < 0.00001)
		t = t1;

	//if (t0>t1) { float tmp = t0; t0 = t1; t1 = tmp; }

	//float y0 = (ray.P.z - center.z) + t0 * ray.D.z;
	//float y1 = (ray.P.z - center.z) + t1 * ray.D.z;

	//if (y0<-1)
	//{
	//	if (y1<-1)
	//		return false;
	//	else
	//	{
	//		// hit the cap
	//		float th = t0 + (t1 - t0) * (y0 + 1) / (y0 - y1);
	//		if (th <= 0) return false;

	//		hit->obj = this;
	//		hit->t = th;
	//		hit->p.x = ray.P.x + th * ray.D.x;
	//		hit->p.y = ray.P.y + th * ray.D.y;
	//		hit->p.z = ray.P.z + th * ray.D.z;
	//		hit->p.w = 1.0;
	//		//xn = 2 * A*xi + D*yi + E*zi + G
	//		//	yn = 2 * B*yi + D*xi + F*zi + H
	//		//	z n = 2 * C*zi + E*xi + F*yi + I
	//		hit->n.x = 0;
	//		hit->n.y = -1;
	//		hit->n.z = 0;

	//		return true;
	//	}
	//}
	//else if (y0 >= -1 && y0 <= 1)
	//{
	//	// hit the cylinder bit
	//	if (t0 <= 0) return false;

	//	hit->obj = this;
	//	hit->t = t0;
	//	hit->p.x = ray.P.x + t0 * ray.D.x;
	//	hit->p.y = ray.P.y + t0 * ray.D.y;
	//	hit->p.z = ray.P.z + t0 * ray.D.z;
	//	hit->p.w = 1.0;
	//	//xn = 2 * A*xi + D*yi + E*zi + G
	//	//	yn = 2 * B*yi + D*xi + F*zi + H
	//	//	z n = 2 * C*zi + E*xi + F*yi + I
	//	hit->n.x = hit->p.x;
	//	hit->n.y = 0;
	//	hit->n.z = hit->p.y;
	//	hit->n.normalise();

	//	return true;
	//}
	//else if (y0 > 1)
	//{
	//	if (y1 > 1)
	//		return false;
	//	else
	//	{
	//		// hit the cap
	//		float th = t0 + (t1 - t0) * (y0 - 1) / (y0 - y1);
	//		if (th <= 0) return false;

	//		hit->obj = this;
	//		hit->t = th;
	//		hit->p.x = ray.P.x + th * ray.D.x;
	//		hit->p.y = ray.P.y + th * ray.D.y;
	//		hit->p.z = ray.P.z + th * ray.D.z;
	//		hit->p.w = 1.0;
	//		//xn = 2 * A*xi + D*yi + E*zi + G
	//		//	yn = 2 * B*yi + D*xi + F*zi + H
	//		//	z n = 2 * C*zi + E*xi + F*yi + I
	//		hit->n.x = 0;
	//		hit->n.y = 1;
	//		hit->n.z = 0;
	//		hit->n.normalise();

	//		return true;
	//	}
	//}
	//return false;
	hit->obj = this;

	hit->t = t;
	hit->p.x = ray.P.x + t * ray.D.x;
	hit->p.y = ray.P.y + t * ray.D.y;
	hit->p.z = ray.P.z + t * ray.D.z;
	hit->p.w = 1.0;
	//xn = 2 * A*xi + D*yi + E*zi + G
	//	yn = 2 * B*yi + D*xi + F*zi + H
	//	z n = 2 * C*zi + E*xi + F*yi + I
	hit->n.x = 2 * hit->p.x - center.x;
	hit->n.y = 0;
	hit->n.z = 2 * hit->p.z - center.z;
	hit->n.normalise();
	return true;
}