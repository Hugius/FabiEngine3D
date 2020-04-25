#include "billboard_entity_manager.hpp"
#include "shader_bus.hpp"
#include "Logger.hpp"

BillboardEntityManager::BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, ShaderBus& shaderBus) :
	BaseEntityManager(objLoader, texLoader, shaderBus)
{

}

BillboardEntity * BillboardEntityManager::getEntity(const string & ID)
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

void BillboardEntityManager::addBillboardEntity
(
	const string & ID, const string & textureName,
	vec3 T, vec3 R, vec3 S,
	bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
)
{
	// Load OBJ model
	float plane_data[] =
	{
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	// Create entity
	_createEntity(EntityType::BILLBOARD, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, plane_data, sizeof(plane_data) / sizeof(float)));

	// Texture
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(textureName, textureFiltering, true));

	// Other
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setInitialRotation(R);
	getEntity(ID)->setScaling(S);
	getEntity(ID)->setTransparent(transparent);
	getEntity(ID)->setCameraFacing({ facingCameraX, facingCameraY });
}

void BillboardEntityManager::addBillboardEntity
(
	const string & ID, const string & text,
	const string & fontPath, vec3 color,
	vec3 T, vec3 R, vec3 S, bool facingCameraX, bool facingCameraY
)
{
	// Load OBJ model
	float plane_data[] =
	{
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	// Create entity
	_createEntity(EntityType::BILLBOARD, ID)->load(ID);
	getEntity(ID)->addOglBuffer(new OpenGLBuffer(SHAPE_SURFACE, plane_data, sizeof(plane_data) / sizeof(float)));

	// Texture
	getEntity(ID)->setDiffuseMap(_texLoader.getText(text, "../Game/Fonts/" + fontPath));

	// Other
	getEntity(ID)->setTranslation(T);
	getEntity(ID)->setRotation(R);
	getEntity(ID)->setInitialRotation(R);
	getEntity(ID)->setScaling(S);
	getEntity(ID)->setTransparent(true);
	getEntity(ID)->setCameraFacing({ facingCameraX, facingCameraY });
	getEntity(ID)->setText(text);
	getEntity(ID)->setFontPath(fontPath);
	getEntity(ID)->setColor(color);
}

void BillboardEntityManager::update(float delta)
{
	for (auto & baseEntity : _getBaseEntities())
	{
		// Create temporary billboard entity object
		auto * entity = getEntity(baseEntity->getID());

		// 3D camera facing
		if (entity->getCameraFacing() != ivec2(0))
		{
			auto facing = entity->getCameraFacing();
			vec3 rotation = vec3(0.0f);
			rotation.x = (((_shaderBus.getCameraPitch())) + entity->getInitialRotation().x) * facing.x;
			rotation.y = (((-_shaderBus.getCameraYaw() - 90.0f)) + entity->getInitialRotation().y) * facing.y;
			rotation.z = entity->getInitialRotation().z;
			entity->setRotation(rotation);
		}
		
		// Calculate model matrix
		if (entity->isEnabled())
		{
			entity->updateModelMatrix();
		}

		// Update sprite animation
		if (entity->hasSpriteAnimation() && entity->getAnimationRepeats() != entity->getMaxAnimationRepeats())
		{
			if (entity->getTotalDelta() >= entity->getMaxDelta()) // Is allowed to update
			{
				entity->resetDelta(); // Reset counter

				if (entity->getSpriteColumnIndex() == entity->getTotalSpriteColumns() - 1) // Reached total columns
				{
					entity->setSpriteColumnIndex(0); // Reset column index

					if (entity->getSpriteRowIndex() == entity->getTotalSpriteRows() - 1) // Reached total rows
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
				entity->addToDelta(delta);
			}
		}
	}
}