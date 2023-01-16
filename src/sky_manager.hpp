#pragma once

#include "render_storage.hpp"
#include "sky.hpp"

#include <unordered_map>

using std::unordered_map;

class SkyManager final
{
public:
	void initialize();
	void inject(shared_ptr<RenderStorage> renderStorage);
	void update();
	void createSky(const string & skyId);
	void deleteSky(const string & skyId);
	void deleteSkies();
	void selectSky(const string & skyId);

	const unordered_map<string, shared_ptr<Sky>> & getSkies() const;

	const shared_ptr<Sky> getSky(const string & skyId) const;
	const shared_ptr<Sky> getSelectedSky() const;

	const bool isSkyExisting(const string & skyId) const;
	const bool isSkiesExisting() const;

private:
	unordered_map<string, shared_ptr<Sky>> _skies = {};

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<RenderStorage> _renderStorage = nullptr;

	string _selectedSkyId = "";
};