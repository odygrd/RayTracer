// RaytracerProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "raytrace.h"

using namespace std;

Colour frame_buffer[YSIZE][XSIZE];

#pragma region Output

//print the frame buffer
void write_framebuffer()
{


	//printf("P3\n%d %d\n255\n", XSIZE, YSIZE);

	for (int y = YSIZE - 1; y >= 0; y -= 1)
	{
		for (int x = 0; x<XSIZE; x += 1)
		{
			float r = (float) (255.0 * frame_buffer[y][x].red);
			float g = (float) (255.0 * frame_buffer[y][x].green);
			float b = (float) (255.0 * frame_buffer[y][x].blue);
			if (r > 255.0) r = 255.0;
			if (g > 255.0) g = 255.0;
			if (b > 255.0) b = 255.0;
			printf("%d %d %d\n", (int)r, (int)g, (int)b);
		}
	}
}

//save to ppm image format
void saveppm(const char *filename)
{
	FILE *myimg;
	myimg = fopen(filename, "w");

	fprintf(myimg, "P3\n%d %d\n255\n", XSIZE, YSIZE);

	for (int y = YSIZE - 1; y >= 0; y -= 1)
	{
		for (int x = 0; x<XSIZE; x += 1)
		{
			float r = (float) (255.0 * frame_buffer[y][x].red);
			float g = (float) (255.0 * frame_buffer[y][x].green);
			float b = (float) (255.0 * frame_buffer[y][x].blue);
			if (r > 255.0) r = 255.0;
			if (g > 255.0) g = 255.0;
			if (b > 255.0) b = 255.0;
			fprintf(myimg, "%d %d %d\n", (int)r, (int)g, (int)b);
		}
	}
	fclose(myimg);
}

//save to bmp image format
void savebmp(const char *filename)
{
	int s = 4 * XSIZE * YSIZE;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);
	int ppm = DPI*m;

	//create the bmp headers
	uchar bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	uchar bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (uchar)(filesize);
	bmpfileheader[3] = (uchar)(filesize >> 8);
	bmpfileheader[4] = (uchar)(filesize >> 16);
	bmpfileheader[5] = (uchar)(filesize >> 24);

	bmpinfoheader[4] = (uchar)(XSIZE);
	bmpinfoheader[5] = (uchar)(XSIZE >> 8);
	bmpinfoheader[6] = (uchar)(XSIZE >> 16);
	bmpinfoheader[7] = (uchar)(XSIZE >> 24);

	bmpinfoheader[8] = (uchar)(YSIZE);
	bmpinfoheader[9] = (uchar)(YSIZE >> 8);
	bmpinfoheader[10] = (uchar)(YSIZE >> 16);
	bmpinfoheader[11] = (uchar)(YSIZE >> 24);

	bmpinfoheader[21] = (uchar)(s);
	bmpinfoheader[22] = (uchar)(s >> 8);
	bmpinfoheader[23] = (uchar)(s >> 16);
	bmpinfoheader[24] = (uchar)(s >> 24);

	bmpinfoheader[25] = (uchar)(ppm);
	bmpinfoheader[26] = (uchar)(ppm >> 8);
	bmpinfoheader[27] = (uchar)(ppm >> 16);
	bmpinfoheader[28] = (uchar)(ppm >> 24);

	bmpinfoheader[29] = (uchar)(ppm);
	bmpinfoheader[30] = (uchar)(ppm >> 8);
	bmpinfoheader[31] = (uchar)(ppm >> 16);
	bmpinfoheader[32] = (uchar)(ppm >> 24);

	//write the file
	FILE *myimg;
	myimg = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, myimg);
	fwrite(bmpinfoheader, 1, 40, myimg);

	for (int y = 0; y<YSIZE; y += 1)
	{
		for (int x = 0; x<XSIZE; x += 1)
		{
			float r = (float) (255.0 * frame_buffer[y][x].red);
			float g = (float) (255.0 * frame_buffer[y][x].green);
			float b = (float) (255.0 * frame_buffer[y][x].blue);
			if (r > 255.0) r = 255.0;
			if (g > 255.0) g = 255.0;
			if (b > 255.0) b = 255.0;

			uchar color[3] = { (int)floor(b), (int)floor(g), (int)floor(r) };
			fwrite(color, 1, 3, myimg);
		}
	}

	fclose(myimg);
}

#pragma endregion 
double frand()
{
	int x;
	double f;

	x = rand();
	f = (float)(x & 0xffff);
	f = f / 65536.0;

	return f;
}

//clear the frame buffer
void clear_framebuffer()
{
	for (int y = 0; y < YSIZE; y += 1)
	{
		for (int x = 0; x < XSIZE; x += 1)
		{
			frame_buffer[y][x].clear();
		}
	}
}

// The main raytacing entry point.
int _tmain(int argc, _TCHAR* argv[])
{
	auto clkstart = chrono::steady_clock::now();

	clear_framebuffer();

	// SETUP SCENE

	//*** Camera Setup ***//

	//Create the camera
	Vertex eyepos(0.0, 0.5, -2.2, 1.0);
	//Vertex eyepos(0, 0, -8.5, 1);
	Vertex lookat(0.0, 0.0, 1.0, 1.0);
	Vector camup(0.0, 1.0, 0.0); //arbitrary y direction

	Camera cam(eyepos, lookat, camup);

	// Create a new scene to render
	Scene *scene = new Scene();

	// Create and add a directional light to the scene
	Vector v = Vector(1.2, -0.6, 0.2);
	Colour cl = Colour(1.0, 1.0, 1.0, 1.0);
	Vertex pp = Vertex(-0.5, 2.5, 0, 1.0);

	DirectionalLight *dl = new DirectionalLight(v, cl);
	//PointLight *pll = new PointLight(pp,cl);
	scene->addLight(*dl);
	//scene->addLight(*pll);

	//*** Scene Setup - Add Primitives to the scene ***//

	//Sphere *s1 = new Sphere(Vertex(0.0, 0.0, 0.0, 1.0), 0.5f);	
	//
	////Translate(Vector(-1.1, 0.7, 2.0), s1);
	////Scale(2, 1, 1, s1);
	////RotateZ(60.0f, s1);
	//Material *m1 = new Material(4);
	//s1->setMaterial(m1); // set spheres material
	//scene->addObject(*s1); // as sphere to scene

	Sphere *s2 = new Sphere(Vertex(0.3, 0.25, 2.0, 1.0), 0.4f);
	Material *m2 = new Material(1);
	s2->setMaterial(m2); // set spheres material
	scene->addObject(*s2); // as sphere to scene

	//Sphere *s3 = new Sphere(Vertex(-0.7, -0.2, 2.8, 1.0), 0.3f);
	//Material *m9 = new Material(5);
	//s3->setMaterial(m9); // set spheres material
	//scene->addObject(*s3); // as sphere to scene

	//Sphere *s4 = new Sphere(Vertex(-0.1, 0.0, 0.5, 1.0), 0.4);
	//Material *m10 = new Material(Colour(0.2, 0.2, 0.2, 1.0), Colour(0.2, 0.2, 0.2, 1.0), Colour(0.0, 0.0, 0.0, 1.0), Colour(0.0, 0.0, 0.0, 1.0), Colour(0.5, 0.5, 0.5, 1.0), 10);
	//s4->setMaterial(m10); // set spheres material
	//scene->addObject(*s4); // as sphere to scene

	

	//Sphere *s5 = new Sphere(Vertex(-0.9, 0.5, 0.4, 1.0), 0.25);
	//Material *m11 = new Material(10);
	//s5->setMaterial(m11); // set spheres material
	//scene->addObject(*s5); // as sphere to scene

	Plane *pl = new Plane(Vertex(0, -0.5, 0, 1), Vector(0, 1, 0));
	Material *m3 = new Material(26);
	pl->setMaterial(m3); // set plane material
	scene->addObject(*pl); // as plane to scene

	////create 3d pyramid
	//Material *m4 = new Material(1);

	//// Front face
	//Triangle *tr1 = new Triangle(Vertex(-2.0, 1.0, 1.0, 1.0), Vertex(-3.0, -1.0, 2.0, 1.0), Vertex(-1.0, -1.0, 2.0, 1.0));
	//tr1->setMaterial(m4); 
	//scene->addObject(*tr1); 
	//// Right face
	//Triangle *tr2 = new Triangle(Vertex(-2.0, 1.0, 1.0, 1.0), Vertex(-1.0, -1.0, 2.0, 1.0), Vertex(-1.0, -1.0, 0.0, 1.0));
	//tr2->setMaterial(m4);
	//scene->addObject(*tr2);
	//// Back face
	//Triangle *tr3 = new Triangle(Vertex(-2.0, 1.0, 1.0, 1.0), Vertex(-1.0, -1.0, 0.0, 1.0), Vertex(-3.0, -1.0, 0.0, 1.0));
	//tr3->setMaterial(m4);
	//scene->addObject(*tr3);
	//// Left face
	//Triangle *tr4 = new Triangle(Vertex(-2.0, 1.0, 1.0, 1.0), Vertex(-3.0, -1.0, 0.0, 1.0), Vertex(-3.0, -1.0, 2.0, 1.0));
	//tr4->setMaterial(m4);
	//scene->addObject(*tr4);

	//Ellipsoid *q1 = new Ellipsoid(Vertex(0.0,1.0,0.0,1),1,3,5,3);
	//Material *m5 = new Material(frand(), frand(), frand()); // create new material with shared random Ka and Kd
	//q1->setMaterial(m5); // set spheres material
	//scene->addObject(*q1); // as sphere to scene

	//QSphere *q2 = new QSphere(Vertex(0, 0, 0, 1), 2);
	//Material *m6 = new Material(frand(), frand(), frand()); // create new material with shared random Ka and Kd
	//q2->setMaterial(m6); // set spheres material
	//scene->addObject(*q2); // as sphere to scene

	//Cone *q3 = new Cone(Vertex(0, 0, -18, 1), 1, 1);
	//Material *m7 = new Material(frand(), 3, frand()); // create new material with shared random Ka and Kd
	//q3->setMaterial(m7); // set spheres material
	//scene->addObject(*q3); // as sphere to scene

	//Cylinder *q4 = new Cylinder(Vertex(0, 0, 0, 1));
	//Material *m8 = new Material(frand(), frand(), frand()); // create new material with shared random Ka and Kd
	//q4->setMaterial(m8); // set spheres material
	//scene->addObject(*q4); // as sphere to scene

	//Create a Viewplane
	Viewplane vp(XSIZE, YSIZE, PIXELSIZE, SAMPLENUM);

	vp.pixelsize /= cam.zoom; //calculate zoom

	cout << "rendering ..." << endl;

	// RAYTRACE SCENE

	int subloops = (int)sqrt((float)vp.samples);
	double px, py;
	

	for (int y = 0; y < YSIZE; y += 1)
	{
		for (int x = 0; x < XSIZE; x += 1)
		{
			Colour avgcol;

			for (int p = 0; p < subloops; p++)		{	// up pixel
				for (int q = 0; q < subloops; q++) {	// across pixel
					px = vp.pixelsize * (x - 0.5 * XSIZE + (q + 0.5) / subloops);
					py = vp.pixelsize * ((0.5 * YSIZE - y) + (p + 0.5) / subloops);

					Vector ray_dir = (cam.u * px) + (cam.v * py) - (cam.w * cam.d); //calculate ray direction

					//create the ray
					Ray ray(eyepos, ray_dir);
					ray_dir.normalise();

					// Trace primary ray
					avgcol += scene->raytrace(ray,6);
				}
			}

			avgcol /= (float)vp.samples; //average the colour

			// Save result in frame buffer
			frame_buffer[y][x].red = avgcol.red;
			frame_buffer[y][x].green = avgcol.green;
			frame_buffer[y][x].blue = avgcol.blue;
		}
	}

	//print duration
	auto clkend = chrono::steady_clock::now();
	cout << "total time: " << chrono::duration_cast<chrono::seconds>(clkend - clkstart).count() << " seconds\n";

	// OUTPUT IMAGE

	//write_framebuffer();
	//saveppm("output.ppm");
	savebmp("../output.bmp");

}

