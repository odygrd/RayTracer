// Sphere object
#include "stdafx.h"
#include <math.h>

#include "sphere.h"

// Sphere defined as vertex (in world space) and radius

Sphere::Sphere(Vertex &psp, float pr)
{
	sp = psp;
	r = pr;
}

// Sphere intersection test

bool Sphere::intersect(Ray &ray, Hit *hit)
{
	Vector ro;



	//this->transform.push(Translate(Vector(0, 5, 4)).m);
	//this->transformInv.push(Translate(Vector(0, 5, 4)).mInv);
	//this->transform.push(Scale(2, 1, 1).m);
	//this->transformInv.push(Scale(2, 1, 1).mInv);
	// ** Transformations ** // 
	//Matrix tr;

	////Transform trans = Translate(Vector(0, 0, 4));
	//Transform trans = Translate(Vector(3, 0, 0));
	////Transform scal = Scale(2, 1, 1);
	///*Transform rot = RotateZ(60);*/

	//tr = trans.mInv;
	//transformInvt = transformInv;
	//if(!transformInv.empty())
	//{
	//	ray.P = transformInv.top() * ray.P;
	//	ray.D = transformInv.top() * ray.D;
	//	//transformInv.pop();
	//}

	//ray.P = transfinalInv * ray.P;
	//ray.D = transfinalInv * ray.D;

	// *************************** //

	// offset ray by sphere position
	// equivalent to transforming ray into local sphere space

	Vector deltap;
	deltap = Vector(ray.P.x - sp.x, ray.P.y - sp.y, ray.P.z - sp.z);
	double a = ray.D.dot(ray.D);
	double b = deltap.dot(ray.D) * 2;
	double c = deltap.dot(deltap) - (r * r);

	double disc = b * b - 4 * a * c;
	if (disc < 0) {
		return false; // No intersection.
	}

	disc = sqrt(disc);

	double q;
	if (b < 0) {
		q = (-b - disc) * 0.5;
	}
	else {
		q = (-b + disc) * 0.5;
	}

	double r1 = q / a;
	double r2 = c / q;

	if (r1 > r2) {
		double tmp = r1;
		r1 = r2;
		r2 = tmp;
	}

	double distance = r1;
	if (distance < 0) {
		distance = r2;
	}

	if (distance < 0 || isnan(distance)) {
		return false(); // No intersection.
	}

	//// if an intersection has been found, record details in hit object

	hit->obj = this;

	hit->t = distance;

	hit->p.x = ray.P.x + distance * ray.D.x;
	hit->p.y = ray.P.y + distance * ray.D.y;
	hit->p.z = ray.P.z + distance * ray.D.z;
	hit->p.w = 1.0;
	hit->n.x = hit->p.x - sp.x;
	hit->n.y = hit->p.y - sp.y;
	hit->n.z = hit->p.z - sp.z;
	hit->n.normalise();
	return true;



}

