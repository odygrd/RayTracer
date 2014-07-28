#ifndef _VIEWPLANE_H_
#define _VIEWPLANE_H_

#endif

class Viewplane {
public:
	int 			width;   					// horizontal image resolution 
	int 			height;   					// vertical image resolution
	float			pixelsize;					// pixel size
	int				samples;				// number of samples per pixel

	Viewplane(int width, int height, float pixelsize, int samples);  

};
