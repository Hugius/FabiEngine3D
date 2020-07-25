#pragma once

#include <GLEW\\glew.h>
#include <vector>
#include <map>
#include <string>
#include <SDL\\SDL_ttf.h>
#include <GLM\\glm.hpp>

using std::vector;
using std::string;
using std::map;
using glm::ivec3;

class TextureLoader final
{
public:
	TextureLoader()  = default;
	~TextureLoader() = default;

	GLuint		   getText(const string &text, const string &filePath);
	GLuint         getTexture(const string &filePath, bool mipmap, bool aniso, bool repeat = true);
	GLuint         getCubeMap(const vector<string> filePaths);
	vector<float>& getHeightMap(const string &filePath);

	void clearTextCache(const string& filePath);
	void clearFontCache(const string& filePath);
	void clearTextureCache(const string& filePath);
	void clearCubeMapCache(const vector<string> filePaths);
	void clearHeightMapCache(const string& filePath);

private:
	map<string, GLuint>         _textures;
	map<string, GLuint>         _texts;
	map<string, TTF_Font*>      _fonts;
	map<string, vector<float>>  _heightMaps;
	map<vector<string>, GLuint> _cubeMaps;

	TTF_Font *    _loadFont(const string &filePath);
	GLuint        _loadText(const string &text, const string &filePath);
	GLuint        _loadTexture(const string &filePath, bool mipmap, bool aniso, bool repeat);
	GLuint        _loadCubemap(const vector<string> fileNames);
	vector<float> _loadHeightmap(const string &filePath);
};