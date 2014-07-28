#include "stdafx.h"
#include "scene.h"
#include "algebra.h"
#include "wood.h"
Scene::Scene(void)
: scache(0), obj_list(nullptr), light_list(nullptr)
{}

void Scene::addObject(Object &obj)
{
	obj.link(obj_list);
	obj_list = &obj;
}

void Scene::addLight(Light &lt)
{
	lt.link(light_list);
	light_list = &lt;
}


Colour Scene::raytrace(Ray &ray, int level)
{
	double t;
	Colour col;
	Object *obj;
	Object *closest;
	Light *lt;
	Hit   hit;
	Vertex position;
	Vector normal;

	Vector reflRay;
	Vector transRay;


	if (level == 0)
	{
		col.clear();
		return col; // stop if recursed deep enough
	}

	// TEST EACH OBJECT AGAINST RAY, FIND THE CLOSEST

	t = 1000000000.0; // a long way aways
	closest = nullptr;
	obj = obj_list;

	while (obj != nullptr)
	{
		//calculate final transformation matrices
		while ((!obj->transform.empty()))
		{
			obj->transfinal = obj->transfinal * obj->transform.top();
			obj->transform.pop();
		}

		while ((!obj->transformInv.empty()))
		{
			obj->transfinalInv = obj->transfinalInv * obj->transformInv.top();
			obj->transformInv.pop();
		}

		//check for intersection
		if (obj->intersect(ray, &hit) == true)
		{
			if (hit.t < t)
			{
				closest = hit.obj;
				t = hit.t;
				normal = hit.n;
				position = hit.p;
			}
		}

		obj = obj->next();
	}

	col.clear();

	if (closest != nullptr)
	{
		lt = light_list;

		//double ior = closest->obj_mat->ior;

		Colour ka = closest->obj_mat->ka;
		Colour kd = closest->obj_mat->kd;
		Colour ks = closest->obj_mat->ks;
		Colour kr = closest->obj_mat->kr;
		Colour kt = closest->obj_mat->kt;

		Wood *wood = new Wood();
		Vector woodve(position.x, position.y, position.z);
		Colour woodCol = wood->getColor(woodve);
		kd.red = woodCol.red;
		kd.green = woodCol.green;
		kd.blue = woodCol.blue;
		ka = kd*0.2;

		delete wood;

		bool specular = false;
		bool transparent = false;

		//check if the object is specular or transparent
		if (ks.red > 0.0 || ks.blue > 0.0 || ks.green > 0.0)
			specular = true;
		if (kt.red > 0.0 || kt.blue > 0.0 || kt.green > 0.0)
			transparent = true;

		//get ambient lighting
		col += ka;

		// calculate diffuse  and specular component
		while (lt != nullptr)
		{
			Vertex lpos;
			Vector xldir;
			Colour lcol;

			lt->getLightProperties(position, &xldir, &lcol, &lpos);
			//	lt->getLightProperties(position, &ldir, &lcol);
			xldir.normalise();

			//// add shadow test here
			double dlc = xldir.dot(normal);
			if (dlc >= 0.0f)
			{
						Ray shadowray(Vertex(position.x + kEpsilon* xldir.x, position.y + kEpsilon * xldir.y, position.z + kEpsilon*xldir.z, 1), xldir);
						float d = (float)(lpos.distance(position));

						if (shadowtrace(shadowray, lpos, d) == true)
							{
								lt = lt->next(); // next light
								continue;
							}

			}

			if (dlc < 0.0f)
			{
				dlc = 0;
			}

			float blinnTerm = 0;
			if (specular)
			{
				Vector eyepos(ray.P.x - position.x, ray.P.y - position.y, ray.P.z - position.z);
				//Blinn - Phong
				if (xldir.dot(normal) > 0.0)
				{
					Vector halfwayVector = (xldir + ray.D.negative()); //Calculate the half vector between the light vector and the view vector.
					halfwayVector.normalise();
					float specTmp = (float)(normal.dot(halfwayVector)); //Intensity of the specular light
					blinnTerm = pow(specTmp, closest->obj_mat->shininess);
				}

				//calculate reflection ray
				reflRay = reflRay.reflect(normal, ray.D);
				reflRay.normalise();
			}

			//calculate transparency
			if (transparent)
			{
				float cosI = -normal.dot(ray.D);
				float ior = 1 ;
				if (cosI < 0.0f) //ray inside the object
				{
					cosI = -cosI;
					normal = normal.negative();
					ior = 1 / ior;
				}
				float temp = 1.0 - (1.0 - cosI*cosI) / (ior*ior);
				float cosI2 = sqrt(temp);
				transRay = ray.D * (1 / ior) - normal *(cosI2 - cosI / ior);
				transRay.normalise();
			}

			// combine components
			col.red += (float)(lcol.red*(dlc * kd.red + blinnTerm * ks.red));
			col.green += (float)(lcol.green*(dlc * kd.green + blinnTerm * ks.green));
			col.blue += (float)(lcol.blue*(dlc * kd.blue + blinnTerm * ks.blue));
			lt = lt->next(); // next light
		}

		// add reflected rays here
		if (specular)
		{
			Ray secray(Vertex(position.x + kEpsilon * reflRay.x, position.y + kEpsilon * reflRay.y, position.z + kEpsilon * reflRay.z, position.w), reflRay); //create a secondary ray with offset ERR
			col += raytrace(secray, level - 1) * kr; //trace seconary ray and add to parent object color
		}

		//// add refracted rays here
		if (transparent)
		{
			Ray secrayt(Vertex(position.x + kEpsilon * transRay.x, position.y + kEpsilon * transRay.y, position.z + kEpsilon * transRay.z, position.w), transRay); //create a secondary ray with offset ERR
			col += raytrace(secrayt, level - 1) * kt; //trace seconary ray and add to parent object color
		}
	}

	return col;
}


bool Scene::shadowtrace(Ray &ray, Vertex lpos, double tlimit)
{
	Object *objl;
	Hit   hit;

	objl = obj_list;
	while (objl != nullptr)
	{
		if (objl->intersect(ray, &hit) == true) //check for object intersections
		{
			if (hit.p.distance(lpos) - tlimit <= 0) //ifthe object is between the light and the parent object
				return true;
		}
		objl = objl->next();
	}
	return false;
}

