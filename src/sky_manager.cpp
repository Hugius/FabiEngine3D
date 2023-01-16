#include "sky_manager.hpp"
#include "render_storage.hpp"

using std::make_shared;

constexpr float bufferData[] =
{
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

constexpr int bufferDataCount = static_cast<int>(sizeof(bufferData) / sizeof(float));

void SkyManager::initialize()
{
	_vertexBuffer = make_shared<VertexBuffer>(VertexBufferType::POS, bufferData, bufferDataCount);
}

void SkyManager::inject(shared_ptr<RenderStorage> renderStorage)
{
	_renderStorage = renderStorage;
}

const shared_ptr<Sky> SkyManager::getSky(const string & skyId) const
{
	const auto iterator = _skies.find(skyId);

	if(iterator == _skies.end())
	{
		abort();
	}

	return iterator->second;
}

const shared_ptr<Sky> SkyManager::getSelectedSky() const
{
	if(_skies.empty() || _selectedSkyId.empty())
	{
		return nullptr;
	}

	return getSky(_selectedSkyId);
}

const unordered_map<string, shared_ptr<Sky>> & SkyManager::getSkies() const
{
	return _skies;
}

void SkyManager::selectSky(const string & skyId)
{
	if(!isSkyExisting(skyId) && !skyId.empty())
	{
		abort();
	}

	_selectedSkyId = skyId;
}

void SkyManager::createSky(const string & skyId)
{
	if(isSkyExisting(skyId))
	{
		abort();
	}

	const auto sky = make_shared<Sky>(skyId);

	sky->setVertexBuffer(_vertexBuffer);

	_skies.insert({skyId, sky});
}

void SkyManager::update()
{
	const auto sky = getSelectedSky();

	if(sky != nullptr)
	{
		sky->updateTarget();
		sky->updateTransformation();
	}
}

void SkyManager::deleteSky(const string & skyId)
{
	if(!isSkyExisting(skyId))
	{
		abort();
	}

	_skies.erase(skyId);

	if(skyId == _selectedSkyId)
	{
		selectSky("");
	}
}

void SkyManager::deleteSkies()
{
	_skies.clear();

	selectSky("");
}

const bool SkyManager::isSkyExisting(const string & skyId) const
{
	return (_skies.find(skyId) != _skies.end());
}

const bool SkyManager::isSkiesExisting() const
{
	return !_skies.empty();
}