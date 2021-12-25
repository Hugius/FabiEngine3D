#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "reflection_type.hpp"

#include <memory>

using std::shared_ptr;

struct ModelEntityPart final
{
	ModelEntityPart(const string& ID)
		:
		ID(ID)
	{

	}

	const string ID;
	string diffuseMapPath = "";
	string emissionMapPath = "";
	string specularMapPath = "";
	string reflectionMapPath = "";
	string normalMapPath = "";

	mat44 transformationMatrix = mat44(1.0f);

	fvec3 position = fvec3(0.0f);
	fvec3 rotation = fvec3(0.0f);
	fvec3 rotationOrigin = fvec3(0.0f);
	fvec3 size = fvec3(1.0f);
	fvec3 positionTarget = fvec3(0.0f);
	fvec3 rotationTarget = fvec3(0.0f);
	fvec3 sizeTarget = fvec3(1.0f);
	fvec3 color = fvec3(1.0f);
	fvec3 wireframeColor = fvec3(1.0f);

	float positionTargetSpeed = 0.0f;
	float rotationTargetSpeed = 0.0f;
	float sizeTargetSpeed = 0.0f;
	float reflectivity = 0.5f;
	float lightness = 1.0f;
	float specularShininess = 1.0f;
	float specularIntensity = 1.0f;
	float transparency = 1.0f;
	float emissionIntensity = 1.0f;
	float textureRepeat = 1.0f;

	bool isSpecular = false;
	bool isReflective = false;
	bool isWireframed = false;

	shared_ptr<RenderBuffer> renderBuffer = nullptr;
	TextureID diffuseMap = 0;
	TextureID emissionMap = 0;
	TextureID specularMap = 0;
	TextureID reflectionMap = 0;
	TextureID normalMap = 0;
	ReflectionType reflectionType = ReflectionType::CUBE;
};