#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "prog1.h"

unsigned char *scale_img(const unsigned char *img, unsigned char *new_img, const int w, const int h, const int nw, const
int nh, const int c)
{
	float x_ratio = (float)w / nw;
	float y_ratio = (float)h / nh;
	for (int j=0; j < nh; ++j)
	{
		for (int i=0; i < nw; ++i)
		{
			int nx = floor(i * x_ratio);
			int ny = floor(j * y_ratio);
			
			for (int cc=0; cc < c; ++cc)
			{
				new_img[c*(i + j*nw) + cc] = img[c*(nx + ny*w) + cc];
			}
		}
	}
}
