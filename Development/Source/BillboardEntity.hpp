#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

using glm::ivec2;
using glm::mat4;

#include "Entity.hpp"

class BillboardEntity final: public Entity
{
public:
	BillboardEntity()  = default;
	~BillboardEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(vec3 val, float delta);
	void rotate(vec3 val, float delta);
	void scale(vec3 val, float delta);

	// Setters
	void setCameraFacing(ivec2 val);
	void setDiffuseMap(GLuint val);
	void setTranslation(vec3 val);
	void setInitialRotation(vec3 val);
	void setRotation(vec3 val);
	void setScaling(vec3 val);
	void setColor(vec3 color);
	void setText(const string & text);
	void setTransparent(bool val);
	void setSpriteAnimation(int rows, int columns, float maxDelta, int repeats);
	void setSpriteRowIndex(int val);
	void setSpriteColumnIndex(int val);
	void addToDelta(float val);
	void resetDelta();
	void increaseRepeats();

	// Getters
	const mat4 & getModelMatrix() const;
	const GLuint getDiffuseMap() const;
	const vec3 getTranslation() const;
	const vec3 getInitialRotation() const;
	const vec3 getRotation() const;
	const vec3 getScaling() const;
	const vec3 getColor() const;
	const ivec2 getCameraFacing() const;
	const string & getText() const;
	const float getMaxDelta() const;
	const float getTotalDelta() const;
	const int getTotalSpriteRows() const;
	const int getTotalSpriteColumns() const;
	const int getSpriteRowIndex() const;
	const int getSpriteColumnIndex() const;
	const int getRepeats() const;
	const int getMaxRepeats() const;
	const bool isTransparent() const;
	const bool hasSpriteAnimation() const;

private:
	mat4 p_modelMatrix = mat4(1.0f);

	vec3 p_translation     = vec3(0.0f, 0.0f, 0.0f);
	vec3 p_rotation        = vec3(0.0f, 0.0f, 0.0f);
	vec3 p_initialRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 p_scaling         = vec3(1.0f, 1.0f, 1.0f);
	vec3 p_color           = vec3(1.0f);

	ivec2 p_cameraFacing = ivec2(0);

	float p_maxDelta   = 0.0f;
	float p_totalDelta = 0.0f;
	
	int p_totalSpriteRows    = 0;
	int p_totalSpriteColumns = 0;
	int p_spriteRowIndex     = 0;
	int p_spriteColumnIndex  = 0;
	int p_repeats            = 0;
	int p_maxRepeats         = 0;
	
	GLuint p_diffuseMap = 0;

	string p_textContent = "";

	bool p_isTransparent      = false;
	bool p_hasSpriteAnimation = false;
};