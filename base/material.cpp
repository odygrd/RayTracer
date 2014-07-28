#include "stdafx.h"
#include <math.h>

#include "material.h"

Material::Material(double cr, double cg, double cb)
  : ka((float)(cr*0.1), (float)(cg*0.1), (float)(cb*0.1), 0.0f),
	kd((float)(cr * 0.5), (float)(cg * 0.5), (float)(cb*0.5), 0.0f),
	ks(0.5f,0.5f,0.5f,0.0f),
	kr(0.5f, 0.5f, 0.5f, 0.0f),
	kt(0.0f,0.0f,0.0f,0.0f),
	shininess(10.0f),
	ior(1.0f)
{}

Material::Material(Colour& pka, Colour& pkd, Colour& pks, Colour& pkr, Colour& pkt,float spechigh)
:	ka(pka),
	kd(pkd),
	ks(pks),
	kr(pkr),
	kt(pkt),
	shininess(spechigh),
	ior(1)
{}

Material::Material(int material_ID) {
	ka.red = (float)AMBIENT[material_ID][0];
	kd.red = (float)DIFFUSE[material_ID][0];
	ks.red = (float)SPECULAR[material_ID][0];
	ka.green = (float)AMBIENT[material_ID][1];
	kd.green = (float)DIFFUSE[material_ID][1];
	ks.green = (float)SPECULAR[material_ID][1];
	ka.blue = (float)AMBIENT[material_ID][2];
	kd.blue = (float)DIFFUSE[material_ID][2];
	ks.blue = (float)SPECULAR[material_ID][2];

	shininess = (float) SHININESS[material_ID];

	kr.red = 0.5;
	kr.green = 0.5;
	kr.blue = 0.5;
	kt.red = 0.0;
	kt.green = 0.0;
	kt.blue = 0.0;
	ior = 1;
}

Material::Material(int material_ID, Colour& pkr, Colour& pkt, float pior)
{
	ka.red = (float)AMBIENT[material_ID][0];
	kd.red = (float)DIFFUSE[material_ID][0];
	ks.red = (float)SPECULAR[material_ID][0];
	ka.green = (float)AMBIENT[material_ID][1];
	kd.green = (float)DIFFUSE[material_ID][1];
	ks.green = (float)SPECULAR[material_ID][1];
	ka.blue = (float)AMBIENT[material_ID][2];
	kd.blue = (float)DIFFUSE[material_ID][2];
	ks.blue = (float)SPECULAR[material_ID][2];

	shininess = (float)SHININESS[material_ID];

	kr.red = pkr.red;
	kr.green = pkr.green;
	kr.blue = pkr.blue;
	kt.red = pkt.red;
	kt.green = pkt.green;
	kt.blue = pkt.blue;
	ior = pior;
}
