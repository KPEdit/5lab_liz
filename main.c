#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "prog1.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "Program shoul recieve 3 argument, but %d were recieved.\n", argc-1);
		return 1;
	}
	int w, h, c;
	unsigned char *img = stbi_load(argv[1], &w, &h, &c, 0);
	if (img == NULL)
	{
		fprintf(stderr, "Not an image file\n");
		return 1;
	}
	
	const char *c_filename = argv[2];
	const char *s_filename = argv[3];
	
	int new_w, new_h;
	printf("Enter new w and h: ");
	scanf("%d %d", &new_w, &new_h);

	int area = new_w * new_h * c;
	unsigned char *new_img = (unsigned char*)calloc(area, sizeof(unsigned char));

	clock_t t = clock();

	scale_img(img, new_img, w, h, new_w, new_h, c);
	t = clock() - t;
	printf("C:	%d\n", t);

	stbi_write_jpg(c_filename, new_w, new_h, c, new_img, 80);

	t = clock();
	asm_scale_img(img, new_img, w, h, new_w, new_h, c);
	t = clock() - t;
	printf("ASM:	%d\n", t);
	
	stbi_write_jpg(s_filename, new_w, new_h, c, new_img, 80);
	
	stbi_image_free(img);
	free(new_img);
	return 0;
}
