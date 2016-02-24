#pragma once

class Texture
{
public:
	Texture(SDL_Renderer* renderer, const std::string& fileName);
	~Texture();

	SDL_Texture* getTexture() { return texture; }

	void render(SDL_Renderer* renderer, int x, int y, int width, int height);
	
private:
	SDL_Texture* texture;
};

