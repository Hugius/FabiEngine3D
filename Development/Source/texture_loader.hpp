#pragma once

#include <GLEW\\glew.h>
#include <array>
#include <vector>
#include <map>
#include <string>
#include <SDL\\SDL_ttf.h>
#include <GLM\\glm.hpp>

using std::pair;
using std::array;
using std::vector;
using std::string;
using std::map;
using glm::ivec3;

class TextureLoader final
{
public:
	TextureLoader()  = default;
	~TextureLoader() = default;

	GLuint		   getText(const string& textContent, const string& fontPath);
	GLuint         getTexture(const string& filePath, bool mipmap, bool aniso, bool repeat = true);
	GLuint         getCubeMap(const array<string, 6>& filePaths);
	vector<float>& getHeightMap(const string& filePath);

	void clearTextCache(const string& textContent, const string& fontPath);
	void clearFontCache(const string& filePath);
	void clearTextureCache(const string& filePath);
	void clearCubeMapCache(const array<string, 6>& filePaths);
	void clearHeightMapCache(const string& filePath);

private:
	map<string, GLuint>         _textures;
	map<pair<string, string>, GLuint> _textMaps;
	map<string, TTF_Font*>      _fonts;
	map<string, vector<float>>  _heightMaps;
	map<array<string, 6>, GLuint> _cubeMaps;

	TTF_Font *    _loadFont(const string& filePath);
	GLuint        _loadText(const string& textContent, const string& filePath);
	GLuint        _loadTexture(const string& filePath, bool mipmap, bool aniso, bool repeat);
	GLuint        _loadCubeMap(const array<string, 6>& filePaths);
	vector<float> _loadHeightMap(const string& filePath);
};