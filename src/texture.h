#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	void* mPixels;
	int mPitch;

	int mWidth;
	int mHeight;

public:
	Texture(SDL_Renderer* renderer);

	~Texture();

	bool loadFromFile(std::string path);

	bool createBlank(int width, int height);

	void free();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth();
	int getHeight();

	bool lockTexture();
	bool unlockTexture();
	void* getPixels();
	void copyPixels(void* pixels);
	int getPitch();
	int getPixel32(unsigned int x, unsigned int y);

};

#endif