#pragma once
#include "base_entity.hpp"

class TerrainEntity final: public BaseEntity
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
	void setMaxHeight(float val);
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
	const float getMaxHeight()       const;

	// Other
	const vector<float>& getPixelColors() const;
	const bool isBlendMapped()    const;

private:
	vector<float> _pixelColors;

	GLuint _diffuseMap = 0;
	GLuint _blendMap = 0;
	GLuint _blendMapR = 0;
	GLuint _blendMapG = 0;
	GLuint _blendMapB = 0;

	float _blendRepeat  = 1.0f;
	float _blendRepeatR = 1.0f;
	float _blendRepeatG = 1.0f;
	float _blendRepeatB = 1.0f;
	float _maxHeight       = 0.0f;
	float _size         = 0.0f;

	bool _blendMapped = false;
};