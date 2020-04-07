#pragma once
#include <GLEW/glew.h>
#include <vector>
#include <map>
#include <string>
#include <SDL/SDL_ttf.h>
#include <GLM/glm.hpp>

using std::vector;
using std::string;
using std::map;
using glm::ivec3;

class TextureLoader final
{
public:
	TextureLoader()  = default;
	~TextureLoader() = default;

	GLuint		   getText(const string & text, const string & fontPath);
	GLuint         getTexture(const string & filePath, bool mipmap, bool aniso, bool repeat = true);
	GLuint         getCubeMap(const string & filePath);
	vector<float> & getHeightMap(const string & filePath, int size);

private:
	map<string, GLuint>        p_textureMap;
	map<string, GLuint>        p_textMap;
	map<string, TTF_Font*>     p_fontMap;
	map<string, vector<float>> p_pixelMap;

	TTF_Font *    p_loadFont(const string & fontPath);
	GLuint        p_loadText(const string & text, const string &fontPath);
	GLuint        p_loadTexture(const string & filePath, bool mipmap, bool aniso, bool repeat);
	GLuint        p_loadCubemap(const string & filePath);
	vector<float> p_loadHeightmap(const string & filePath, int size);
};