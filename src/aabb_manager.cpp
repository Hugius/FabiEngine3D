#include "aabb_manager.hpp"
#include "render_storage.hpp"
#include "tools.hpp"

using std::make_shared;

constexpr float centeredBufferData[] =
{
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, 0.5f,
	-0.5f, -0.5f, -0.5f
};

constexpr float standingBufferData[] =
{
	-0.5f, 1.0f, -0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	-0.5f, 0.0f, -0.5f,
	-0.5f, 1.0f, -0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, 0.5f,
	0.5f, 1.0f, -0.5f,
	0.5f, 0.0f, -0.5f,
	0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, 0.5f,
	-0.5f, 0.0f, -0.5f
};

constexpr int centeredBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));
constexpr int standingBufferDataCount = static_cast<int>(sizeof(centeredBufferData) / sizeof(float));

AabbManager::AabbManager()
	:
	_centeredVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, centeredBufferData, centeredBufferDataCount)),
	_standingVertexBuffer(make_shared<VertexBuffer>(VertexBufferType::POS, standingBufferData, standingBufferDataCount))
{

}

void AabbManager::inject(shared_ptr<ModelManager> modelManager)
{
	_modelManager = modelManager;
}

void AabbManager::inject(shared_ptr<Quad3dManager> quad3dManager)
{
	_quad3dManager = quad3dManager;
}

void AabbManager::inject(shared_ptr<Text3dManager> text3dManager)
{
	_text3dManager = text3dManager;
}

const shared_ptr<Aabb> AabbManager::getAabb(const string & aabbId) const
{
	const auto iterator = _aabbs.find(aabbId);

	if(iterator == _aabbs.end())
	{
		abort();
	}

	return iterator->second;
}

const unordered_map<string, shared_ptr<Aabb>> & AabbManager::getAabbs() const
{
	return _aabbs;
}

const vector<string> AabbManager::getChildAabbIds(const string & parentId, AabbParentType parentType) const
{
	switch(parentType)
	{
		case AabbParentType::MODEL:
		{
			const auto iterator = _modelChildAabbIds.find(parentId);

			if(iterator != _modelChildAabbIds.end())
			{
				return iterator->second;
			}
		}
		case AabbParentType::QUAD3D:
		{
			const auto iterator = _quad3dChildAabbIds.find(parentId);

			if(iterator != _quad3dChildAabbIds.end())
			{
				return iterator->second;
			}
		}
		case AabbParentType::TEXT3D:
		{
			const auto iterator = _text3dChildAabbIds.find(parentId);

			if(iterator != _text3dChildAabbIds.end())
			{
				return iterator->second;
			}
		}
	}

	return {};
}

void AabbManager::createAabb(const string & aabbId, bool isCentered)
{
	if(isAabbExisting(aabbId))
	{
		abort();
	}

	const auto aabb = make_shared<Aabb>(aabbId);

	aabb->setVertexBuffer(isCentered ? _centeredVertexBuffer : _standingVertexBuffer);
	aabb->setCentered(isCentered);

	_aabbs.insert({aabbId, aabb});
}

void AabbManager::update()
{
	for(const auto & [aabbId, aabb] : _aabbs)
	{
		aabb->updateTarget();

		const auto parentId = aabb->getParentId();

		if(!parentId.empty())
		{
			switch(aabb->getParentType())
			{
				case AabbParentType::MODEL:
				{
					const auto model = _modelManager->getModel(parentId);

					aabb->followModelParentTransformation(model->getBasePosition(), model->getBaseRotation(), model->getBaseSize());
					aabb->followModelParentVisibility(model->isVisible(), model->getLevelOfDetailId(), model->isLevelOfDetailed());

					break;
				}
				case AabbParentType::QUAD3D:
				{
					const auto quad3d = _quad3dManager->getQuad3d(parentId);

					aabb->followQuad3dParentTransformation(quad3d->getPosition(), quad3d->getRotation(), quad3d->getSize());
					aabb->followQuad3dParentVisibility(quad3d->isVisible());

					break;
				}
				case AabbParentType::TEXT3D:
				{
					const auto text3d = _text3dManager->getText3d(parentId);

					aabb->followText3dParentTransformation(text3d->getPosition(), text3d->getRotation(), text3d->getSize());
					aabb->followText3dParentVisibility(text3d->isVisible());

					break;
				}
			}
		}

		if(aabb->isVisible())
		{
			aabb->updateTransformation();
		}
	}
}

void AabbManager::deleteAabb(const string & aabbId)
{
	if(!isAabbExisting(aabbId))
	{
		abort();
	}

	_aabbs.erase(aabbId);

	for(auto & [parentId, childAabbIds] : _modelChildAabbIds)
	{
		childAabbIds.erase(remove(childAabbIds.begin(), childAabbIds.end(), aabbId), childAabbIds.end());
	}

	for(auto & [parentId, childAabbIds] : _quad3dChildAabbIds)
	{
		childAabbIds.erase(remove(childAabbIds.begin(), childAabbIds.end(), aabbId), childAabbIds.end());
	}

	for(auto & [parentId, childAabbIds] : _text3dChildAabbIds)
	{
		childAabbIds.erase(remove(childAabbIds.begin(), childAabbIds.end(), aabbId), childAabbIds.end());
	}
}

void AabbManager::deleteAabbs()
{
	_aabbs.clear();

	for(auto & [parentId, childAabbIds] : _modelChildAabbIds)
	{
		childAabbIds.clear();
	}

	for(auto & [parentId, childAabbIds] : _quad3dChildAabbIds)
	{
		childAabbIds.clear();
	}

	for(auto & [parentId, childAabbIds] : _text3dChildAabbIds)
	{
		childAabbIds.clear();
	}
}

void AabbManager::registerParent(const string & parentId, AabbParentType parentType)
{
	switch(parentType)
	{
		case AabbParentType::MODEL:
		{
			const auto iterator = _modelChildAabbIds.find(parentId);

			if(iterator != _modelChildAabbIds.end())
			{
				abort();
			}

			_modelChildAabbIds.insert({parentId, {}});
		}
		case AabbParentType::QUAD3D:
		{
			const auto iterator = _quad3dChildAabbIds.find(parentId);

			if(iterator != _quad3dChildAabbIds.end())
			{
				abort();
			}

			_quad3dChildAabbIds.insert({parentId, {}});
		}
		case AabbParentType::TEXT3D:
		{
			const auto iterator = _text3dChildAabbIds.find(parentId);

			if(iterator != _text3dChildAabbIds.end())
			{
				abort();
			}

			_text3dChildAabbIds.insert({parentId, {}});
		}
	}
}

void AabbManager::unregisterParent(const string & parentId, AabbParentType parentType)
{
	switch(parentType)
	{
		case AabbParentType::MODEL:
		{
			const auto iterator = _modelChildAabbIds.find(parentId);

			if(iterator == _modelChildAabbIds.end())
			{
				abort();
			}

			_modelChildAabbIds.erase(parentId);
		}
		case AabbParentType::QUAD3D:
		{
			const auto iterator = _quad3dChildAabbIds.find(parentId);

			if(iterator == _quad3dChildAabbIds.end())
			{
				abort();
			}

			_quad3dChildAabbIds.erase(parentId);
		}
		case AabbParentType::TEXT3D:
		{
			const auto iterator = _text3dChildAabbIds.find(parentId);

			if(iterator == _text3dChildAabbIds.end())
			{
				abort();
			}

			_text3dChildAabbIds.erase(parentId);
		}
	}
}

void AabbManager::bindAabbToParent(const string & aabbId, const string & parentId, AabbParentType parentType)
{
	if(_aabbs.find(aabbId) == _aabbs.end())
	{
		abort();
	}

	getAabb(aabbId)->setParentId(parentId);
	getAabb(aabbId)->setParentType(parentType);

	switch(parentType)
	{
		case AabbParentType::MODEL:
		{
			const auto iterator = _modelChildAabbIds.find(parentId);

			if(iterator == _modelChildAabbIds.end())
			{
				abort();
			}

			iterator->second.push_back(aabbId);
		}
		case AabbParentType::QUAD3D:
		{
			const auto iterator = _quad3dChildAabbIds.find(parentId);

			if(iterator == _quad3dChildAabbIds.end())
			{
				abort();
			}

			iterator->second.push_back(aabbId);
		}
		case AabbParentType::TEXT3D:
		{
			const auto iterator = _text3dChildAabbIds.find(parentId);

			if(iterator == _text3dChildAabbIds.end())
			{
				abort();
			}

			iterator->second.push_back(aabbId);
		}
	}
}

void AabbManager::unbindAabbFromParent(const string & aabbId, const string & parentId, AabbParentType parentType)
{
	if(_aabbs.find(aabbId) == _aabbs.end())
	{
		abort();
	}

	switch(parentType)
	{
		case AabbParentType::MODEL:
		{
			const auto iterator = _modelChildAabbIds.find(parentId);

			if(iterator != _modelChildAabbIds.end())
			{
				abort();
			}

			iterator->second.erase(remove(iterator->second.begin(), iterator->second.end(), aabbId), iterator->second.end());
		}
		case AabbParentType::QUAD3D:
		{
			const auto iterator = _quad3dChildAabbIds.find(parentId);

			if(iterator != _quad3dChildAabbIds.end())
			{
				abort();
			}

			iterator->second.erase(remove(iterator->second.begin(), iterator->second.end(), aabbId), iterator->second.end());
		}
		case AabbParentType::TEXT3D:
		{
			const auto iterator = _text3dChildAabbIds.find(parentId);

			if(iterator != _text3dChildAabbIds.end())
			{
				abort();
			}

			iterator->second.erase(remove(iterator->second.begin(), iterator->second.end(), aabbId), iterator->second.end());
		}
	}
}

const bool AabbManager::isAabbExisting(const string & aabbId) const
{
	return (_aabbs.find(aabbId) != _aabbs.end());
}

const bool AabbManager::isAabbsExisting() const
{
	return !_aabbs.empty();
}