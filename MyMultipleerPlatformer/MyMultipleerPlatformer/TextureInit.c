#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma comment( lib, "glew32.lib" )
#pragma comment (lib, "OpenGL32.lib")

#include "TextureInit.h"


GLuint textureId;
GLuint playertextureId;
GLuint menuTextureId;
GLuint FontTextureId;
float charwidth[256];


void fillCharWidhth(unsigned char* data, int width, int cnt, float* cWA, int checkByte);

void TextureInit()
{
	int x, y, n;
	unsigned char* data = stbi_load("texture.png", &x, &y, &n, 0);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, n == 4 ? GL_RGBA : GL_RGB, x, y, 0, n == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	data = stbi_load("player.png", &x, &y, &n, 0);

	glGenTextures(1, &playertextureId);
	glBindTexture(GL_TEXTURE_2D, playertextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, n == 4 ? GL_RGBA : GL_RGB, x, y, 0, n == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	data = stbi_load("menu.png", &x, &y, &n, 0);

	glGenTextures(1, &menuTextureId);
	glBindTexture(GL_TEXTURE_2D, menuTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, n == 4 ? GL_RGBA : GL_RGB, x, y, 0, n == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);

	data = stbi_load("font.png", &x, &y, &n, 0);

	fillCharWidhth(data, x, n, charwidth, 3);
	glGenTextures(1, &FontTextureId);
	glBindTexture(GL_TEXTURE_2D, FontTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, n == 4 ? GL_RGBA : GL_RGB, x, y, 0, n == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}



void fillCharWidhth(unsigned char* data, int width, int cnt, float *cWA, int checkByte)
{
	int pixPerChar = width / 16;

	for (int k = 0; k < 256; k++)
	{
		int x = (k % 16) * pixPerChar;
		int y = (k / 16) * pixPerChar;
		int i;

		unsigned char alpfa;

		for (i = x + pixPerChar - 1; i > x; i--)
		{
			for (int j = y + pixPerChar - 1; j > y; j--)
			{
				alpfa = data[(j * width + i) * cnt + checkByte];
				

				if (alpfa > 0)break;
			}
			if (alpfa > 0)break;
		}

		cWA[k] = (i - x) / (float)pixPerChar;
		//cWA[k] +=0.1;
		//if (cWA[k] > 1)cWA[k] = 1;
		if (k == 32)cWA[k] = 0.5;
	}


}