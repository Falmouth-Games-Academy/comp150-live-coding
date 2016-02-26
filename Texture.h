#pragma once

class Texture
{
public:
	Texture(const std::string& fileName);
	~Texture();

	SDL_Texture* getTexture() { return texture; }

	void render(SDL_Renderer* renderer, int x, int y, int width, int height);
	
private:
	std::string fileName;
	SDL_Texture* texture;
};

