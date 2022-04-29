#pragma once

#include "captor.hpp"

#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::shared_ptr;

class CaptorManager final
{
public:
	void update();
	void createCaptor(const string & captorId);
	void deleteCaptor(const string & captorId);
	void deleteCaptors();

	const unordered_map<string, shared_ptr<Captor>> & getCaptors() const;

	const shared_ptr<Captor> getCaptor(const string & captorId) const;

	const bool isCaptorExisting(const string & captorId) const;
	const bool isCaptorsExisting() const;

private:
	unordered_map<string, shared_ptr<Captor>> _captors = {};
};