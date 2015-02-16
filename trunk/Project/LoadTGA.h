#include <iostream>
#include "GL/freeglut.h"
#pragma once
using namespace std;

typedef struct
{
	GLubyte	*imageData;			// image data
	GLuint	bpp;				// image color depth ( bits per pixel )
	GLuint	width;				// image width
	GLuint	height;				// image height
	GLuint	id;				// texture id
} TextureImage;
 


//TextureImage textures[9]; WHO THE FUCK PUT THIS HERE!!

// only for uncompressed file

bool LoadTGA(TextureImage *texture, char *filename)	;			// load TGA file to memory


