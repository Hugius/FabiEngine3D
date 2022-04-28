#pragma once

#include "captor_entity.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class CaptorEntityManager final
{
public:
	void update();
	void createEntity(const string & captorId);
	void deleteEntity(const string & captorId);
	void deleteEntities();

	const unordered_map<string, shared_ptr<CaptorEntity>> & getEntities() const;

	const shared_ptr<CaptorEntity> getEntity(const string & captorId) const;

	const bool isEntityExisting(const string & captorId) const;
	const bool isEntitiesExisting() const;

private:
	unordered_map<string, shared_ptr<CaptorEntity>> _entities = {};
};