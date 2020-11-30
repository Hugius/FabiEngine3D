#include "billboard_entity_manager.hpp"
#include "render_bus.hpp"
#include "logger.hpp"

BillboardEntityManager::BillboardEntityManager(OBJLoader& objLoader, TextureLoader& texLoader, RenderBus& renderBus, CameraManager& camera) :
	BaseEntityManager(EntityType::BILLBOARD, objLoader, texLoader, renderBus),
	_camera(camera)
{
	float plane_data[] =
	{
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,  -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	_openglBuffer = new OpenGLBuffer(BufferType::SURFACE, plane_data, sizeof(plane_data) / sizeof(float));
}

shared_ptr<BillboardEntity> BillboardEntityManager::getEntity(const string& ID)
{
	auto result = _getBillboardEntity(ID);

	if (result == nullptr)
	{
		Logger::throwError("Nonexisting BILLBOARD entity with ID \"" + ID + "\" requested");
	}

	return result;
}

const unordered_map<string, shared_ptr<BillboardEntity>>& BillboardEntityManager::getEntities()
{
	return _getBillboardEntities();
}

void BillboardEntityManager::addBillboardEntity(const string& ID, Vec3 color, Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY)
{
	// Create entity
	_createEntity(ID);
	getEntity(ID)->addOglBuffer(_openglBuffer, false);

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
	Vec3 T, Vec3 R, Vec3 S,
	bool transparent, bool facingCameraX, bool facingCameraY, bool textureFiltering
)
{
	addBillboardEntity(ID, Vec3(1.0f), T, R, S, facingCameraX, facingCameraY);
	getEntity(ID)->setDiffuseMap(_texLoader.getTexture(texturePath, textureFiltering, true));
	getEntity(ID)->setDiffuseMapPath(texturePath);
	getEntity(ID)->setTransparent(transparent);
}

void BillboardEntityManager::addBillboardEntity
(
	const string& ID, const string& text,
	const string& fontPath, Vec3 color,
	Vec3 T, Vec3 R, Vec3 S, bool facingCameraX, bool facingCameraY
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
	for (auto& [keyID, entity] : _getBillboardEntities())
	{
		// 3D camera facing
		auto facingX = entity->isCameraFacingX();
		auto facingY = entity->isCameraFacingY();
		Vec3 rotation = entity->getRotation();
		if (facingX || facingY)
		{
			Vec3 direction = entity->getTranslation() - _renderBus.getCameraPosition();
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