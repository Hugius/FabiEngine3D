#include <WE3D/TextureLoader.hpp>
#include <WE3D/Logger.hpp>

GLuint TextureLoader::getText(const string & text, const string & fontPath)
{
	auto it = p_textMap.find(text);
	if (it == p_textMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = p_loadText(text, fontPath);
		p_textMap.insert(std::make_pair(text, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getTexture(const string &filePath, bool mipmap, bool aniso, bool repeat)
{
	auto it = p_textureMap.find(filePath);
	if (it == p_textureMap.end()) // Not in map (yet)
	{ 
		GLuint tempTxt = p_loadTexture(filePath, mipmap, aniso, repeat);
		p_textureMap.insert(std::make_pair(filePath, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

GLuint TextureLoader::getCubeMap(const string & filePath)
{
	auto it = p_textureMap.find(filePath);
	if (it == p_textureMap.end()) // Not in map (yet)
	{
		GLuint tempTxt = p_loadCubemap(filePath);
		p_textureMap.insert(std::make_pair(filePath, tempTxt));
		return tempTxt; // Use new texture
	}

	return it->second; // Cache texture
}

vector<float> & TextureLoader::getHeightMap(const string &filePath, int size)
{
	cuzRef : auto it = p_pixelMap.find(filePath);
	if (it == p_pixelMap.end()) // Not in map (yet)
	{
		auto tempPixels = p_loadHeightmap(filePath, size);
		p_pixelMap.insert(std::make_pair(filePath, tempPixels));
		goto cuzRef;
	}

	return it->second; // Cache texture
}