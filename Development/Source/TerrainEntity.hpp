#pragma once
#include "Entity.hpp"

class TerrainEntity final: public Entity
{
public:
	TerrainEntity()  = default;
	~TerrainEntity() = default;

	// Setters
	void setPixelColors(vector<float>& val);
	void setDiffuseMap(GLuint val);
	void setBlendMap(GLuint val);
	void setBlendMapR(GLuint val);
	void setBlendMapG(GLuint val);
	void setBlendMapB(GLuint val);
	void setBlendRepeat(float val);
	void setBlendRepeatR(float val);
	void setBlendRepeatG(float val);
	void setBlendRepeatB(float val);
	void setSize(float val);
	void setHeight(float val);
	void setBlendMapped(bool val);

	// Textures
	const GLuint getDiffuseMap() const;
	const GLuint getBlendMap()   const;
	const GLuint getBlendMapR()  const;
	const GLuint getBlendMapG()  const;
	const GLuint getBlendMapB()  const;

	// Repeats
	const float getBlendRepeat()  const;
	const float getBlendRepeatR() const;
	const float getBlendRepeatG() const;
	const float getBlendRepeatB() const;
	const float getSize()         const;
	const float getHeight()       const;

	// Other
	const vector<float>& getPixelColors() const;
	const bool isBlendMapped()    const;

private:
	vector<float> p_pixelColors;

	GLuint p_diffuseMap = 0;
	GLuint p_blendMap = 0;
	GLuint p_blendMapR = 0;
	GLuint p_blendMapG = 0;
	GLuint p_blendMapB = 0;

	float p_blendRepeat  = 1.0f;
	float p_blendRepeatR = 1.0f;
	float p_blendRepeatG = 1.0f;
	float p_blendRepeatB = 1.0f;
	float p_height       = 0.0f;
	float p_size         = 0.0f;

	bool p_blendMapped = false;
};