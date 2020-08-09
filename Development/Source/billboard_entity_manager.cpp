#include "billboard_entity_manager.hpp"
#include "shader_bus.hpp"
#include "logger.hpp"

BillboardEntityManager::BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus, CameraManager& camera) :
	BaseEntityManager(objLoader, texLoader, shaderBus),
	_camera(camera)
{

}

BillboardEntity * BillboardEntityManager::getEntity(const string& ID)
{
	return dynamic_cast<BillboardEntity*>(_getBaseEntity(ID, EntityType::BILLBOARD));
}

const vector<BillboardEntity*> BillboardEntityManager::getEntities()
{
	vector<BillboardEntity*> newVector;

	for (auto& entity : _getBaseEntities())
	{
		newVector.push_back(dynamic_cast<BillboardEntity*>(entity));
	}

	return newVector;
}

void BillboardEntityManager::addBillboardEntity(const string& ID, vec3 color, vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY)
{
	// Load OBJ model
	float plane_data[] =
	{
		-0.5f,  1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.0f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  1.0f, 0.0f, 1.0f, 1.0f,
		-0.5f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	// Create entity
	_createEntity(EntityType::BILLBOARD, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, plane_data, sizeof(plane_data) / sizeof(float)));

	// Other
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setInitialRotation(R);
	getEntity(ID)->setScaling(S);
	getEntity(ID)->setCameraFacingX(facingCameraX);
	getEntity(ID)->setCameraFacingY(facingCameraY);
	getEntity(ID)->setColor(color);
}

void BillboardEntityManager::addBillboardEntity
(
	const string& ID, const string& texturePath,
	vec3 T, vec3 R, vec3 S,
	bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
)
{
	addBillboardEntity(ID, vec3(1.0f), T, R, S, facingCameraX, facingCameraY);
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(texturePath, textureFiltering, true));
	getEntity(ID)->setDiffuseMapPath(texturePath);
	getEntity(ID)->setTransparent(transparent);
}

void BillboardEntityManager::addBillboardEntity
(
	const string& ID, const string& text,
	const string& fontPath, vec3 color,
	vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
)
{
	addBillboardEntity(ID, color, T, R, S, facingCameraX, facingCameraY);
	getEntity(ID)->setDiffuseMap(_texLoader.getText(text, fontPath));
	getEntity(ID)->setTransparent(true);
	getEntity(ID)->setTextContent(text);
	getEntity(ID)->setFontPath(fontPath);
}

void BillboardEntityManager::update()
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary billboard entity object
		auto * entity = getEntity(baseEntity->getID());

		// 3D camera facing
		auto facingX = entity->isCameraFacingX();
		auto facingY = entity->isCameraFacingY();
		vec3 rotation = entity->getRotation();
		if (facingX || facingY)
		{
			vec3 direction = entity->getTranslation() - _shaderBus.getCameraPos();
			float radiansX = atan2f(direction.y, (fabsf(direction.x) + fabsf(direction.z)) / 2.0f);
			float radiansY = atan2f(direction.z, direction.x);
			rotation.x = (radiansX * (180.0f / 3.141592653589793238463f)) * facingX;
			rotation.y = (-(radiansY * (180.0f / 3.141592653589793238463f)) - 90.0f) * facingY;
		}

		// Update rotation
		entity->setRotation(rotation);
		
		// Calculate model matrix
		if (entity->isVisible())
		{
			entity->updateModelMatrix();
		}

		// Update sprite animation
		if (entity->hasSpriteAnimation() && entity->getAnimationRepeats() != entity->getMaxAnimationRepeats())
		{
			if (entity->getPassedFrames() >= entity->getMaxFramestep()) // Is allowed to update
			{
				entity->resetPassedFrames(); // Reset counter

				if (entity->getSpriteColumnIndex() >= entity->getTotalSpriteColumns() - 1) // Reached total columns
				{
					entity->setSpriteColumnIndex(0); // Reset column index
					
					if (entity->getSpriteRowIndex() >= entity->getTotalSpriteRows() - 1) // Reached total rows
					{
						entity->increaseAnimationRepeats();
						entity->setSpriteRowIndex(0); // Reset row index (animation finished)
					}
					else // Next row
					{
						entity->setSpriteRowIndex(entity->getSpriteRowIndex() + 1);
					}
				}
				else // Next column
				{
					entity->setSpriteColumnIndex(entity->getSpriteColumnIndex() + 1);
				}
			}
			else // Increase counter
			{
				entity->increasePassedFrames();
			}
		}
	}
}