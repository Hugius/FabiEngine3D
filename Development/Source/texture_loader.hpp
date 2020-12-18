#pragma once

#include <GLEW\\glew.h>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <SDL\\SDL_ttf.h>

using std::pair;
using std::array;
using std::vector;
using std::string;
using std::map;

class TextureLoader final
{
public:
	TextureLoader()  = default;
	~TextureLoader() = default;

	GLuint		   getText(const string& textContent, const string& fontPath);
	GLuint         getTexture(const string& filePath, bool mipmap, bool aniso, bool repeat = true);
	GLuint         getCubeMap(const array<string, 6>& filePaths);
	const vector<float>& getHeightMap(const string& filePath);

	void clearTextCache(const string& textContent, const string& fontPath);
	void clearFontCache(const string& filePath);
	void clearTextureCache(const string& filePath);
	void clearCubeMapCache(const array<string, 6>& filePaths);
	void clearHeightMapCache(const string& filePath);

private:
	map<string, GLuint>				  _textureCache;
	map<pair<string, string>, GLuint> _textCache;
	map<string, TTF_Font*>			  _fontCache;
	map<string, vector<float>>		  _heightMapCache;
	map<array<string, 6>, GLuint>	  _cubeMapCache;

	TTF_Font *    _loadFont(const string& filePath);
	GLuint        _loadText(const string& textContent, const string& filePath);
	GLuint        _loadTexture(const string& filePath, bool mipmap, bool aniso, bool repeat);
	GLuint        _loadCubeMap(const array<string, 6>& filePaths);
	vector<float> _loadHeightMap(const string& filePath);
};