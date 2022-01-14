#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "reflection_type.hpp"
#include "texture_buffer.hpp"

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
	bool isBright = false;
	bool isFaceCulled = false;

	shared_ptr<VertexBuffer> vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> diffuseMap = nullptr;
	shared_ptr<TextureBuffer> emissionMap = nullptr;
	shared_ptr<TextureBuffer> specularMap = nullptr;
	shared_ptr<TextureBuffer> reflectionMap = nullptr;
	shared_ptr<TextureBuffer> normalMap = nullptr;
	ReflectionType reflectionType = ReflectionType::CUBE;
};