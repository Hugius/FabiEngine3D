#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "tools.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

int FabiEngine3D::misc_getRandomInteger(int min, int max)
{
	return Tools::getInst().getRandomInt(min, max);
}

int FabiEngine3D::misc_getMsTimeSinceEpoch()
{
	using namespace std::chrono;
	return static_cast<int>(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
}

int FabiEngine3D::misc_getTriangleCount()
{
	return _core->_renderBus.getTriangleCount();
}

float FabiEngine3D::misc_getRandomFloat(float min, float max)
{
	return Tools::getInst().getRandomFloat(min, max);
}

float FabiEngine3D::misc_getAspectRatio()
{
	return static_cast<float>(misc_getWindowSize().x) / static_cast<float>(misc_getWindowSize().y);
}

float FabiEngine3D::misc_getFPS()
{
	return 1000.0f / _core->_deltaTimeMS;
}

float FabiEngine3D::misc_getPI()
{
	return Math::getPI();
}

float FabiEngine3D::misc_degreesToRadians(float angle)
{
	return Math::degreesToRadians(angle);
}

float FabiEngine3D::misc_radiansToDegrees(float angle)
{
	return Math::radiansToDegrees(angle);
}

float FabiEngine3D::misc_stopMillisecondTimer()
{
	return _core->_timer.stop();
}

float FabiEngine3D::misc_getLevelOfDetailDistance()
{
	return _core->_modelEntityManager.getLodDistance();
}

string FabiEngine3D::misc_getWinExplorerFilename(const string& startingDirectory, const string& fileType)
{
	// Prepare filter C-string
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';
	auto startingDirectoryString = string(misc_getRootDirectory() + startingDirectory);
	auto startingDirectoryStringC = startingDirectoryString.c_str();

	// Open file explorer
	OPENFILENAME ofn;
	char pathBuffer[256];
	char titleBuffer[100];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = pathBuffer;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(pathBuffer);
	ofn.lpstrFilter = filter.c_str();
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = titleBuffer;
	ofn.lpstrFileTitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(titleBuffer);
	ofn.lpstrInitialDir = startingDirectoryStringC;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	// Return chosen filename or nothing if cancelled
	string filePath = ofn.lpstrFile;
	return filePath;
}

string FabiEngine3D::misc_vec2str(Ivec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

string FabiEngine3D::misc_vec2str(Vec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

string FabiEngine3D::misc_vec2str(Vec3 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z);
}

string FabiEngine3D::misc_vec2str(Vec4 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w);
}

string FabiEngine3D::misc_getRootDirectory()
{
	return Tools::getInst().getRootDirectory();
}

string FabiEngine3D::misc_getCpuName() // https://stackoverflow.com/questions/850774/how-to-determine-the-hardware-cpu-and-ram-on-a-machine
{
	// Temporary values
	int CPUInfo[4];
	char nameString[48];

	// Retrieve full CPU name string
	__cpuid(CPUInfo, 0x80000002);
	memcpy(nameString, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000003);
	memcpy(nameString + 16, CPUInfo, sizeof(CPUInfo));
	__cpuid(CPUInfo, 0x80000004);
	memcpy(nameString + 32, CPUInfo, sizeof(CPUInfo));
	
	// Retrieve number of logical CPU cores
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	string coreCount = to_string(sysInfo.dwNumberOfProcessors);

	// Return
	return nameString;
}

string FabiEngine3D::misc_getGpuName()
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER))));
}

string FabiEngine3D::misc_getOpenglVersion()
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))).substr(0, 3);
}

Vec2 FabiEngine3D::misc_convertToNDC(Vec2 pos)
{
	pos.x = (pos.x * 2.0f) - 1.0f;
	pos.y = (pos.y * 2.0f) - 1.0f;

	return Vec2(pos.x, pos.y);
}

Vec2 FabiEngine3D::misc_convertFromNDC(Vec2 pos)
{
	pos.x += 1.0f;
	pos.x /= 2.0f;
	pos.y += 1.0f;
	pos.y /= 2.0f;

	return Vec2(pos.x, pos.y);
}

Ivec2 FabiEngine3D::misc_convertToScreenCoords(Vec2 pos)
{
	float x = static_cast<float>(pos.x) * static_cast<float>(misc_getWindowSize().x);
	float y = static_cast<float>(pos.y) * static_cast<float>(misc_getWindowSize().y);

	return Ivec2(static_cast<int>(x), static_cast<int>(y));
}

Ivec2 FabiEngine3D::misc_getCursorPosition()
{
	Ivec2 mousePos = _core->_windowManager.getCursorPos();

	return Ivec2(mousePos.x, misc_getWindowSize().y - mousePos.y);
}

Ivec2 FabiEngine3D::misc_getCursorPositionRelativeToViewport()
{
	if (engine_isGameExported())
	{
		return misc_getCursorPosition();
	}
	else
	{
		// Temporary values
		auto windowSize = Config::getInst().getWindowSize();
		auto viewportPosition = Config::getInst().getVpPos();
		auto viewportSize = Config::getInst().getVpSize();

		// Calculate viewport position Y offset, because GUI borders are not all of the same size
		Ivec2 offset = Ivec2(viewportPosition.x, windowSize.y - (viewportPosition.y + viewportSize.y));

		// Apply Y offset to cursor position
		Vec2 relativeCursorPosition = Vec2(_core->_windowManager.getCursorPos()) - Vec2(offset);

		// Convert fullscreen coords to viewport coords
		relativeCursorPosition = (relativeCursorPosition / Vec2(viewportSize)) * Vec2(windowSize);

		// Return
		Ivec2 result = Ivec2(relativeCursorPosition);
		return Ivec2(result.x, misc_getWindowSize().y - result.y);
	}
}

Vec2 FabiEngine3D::misc_convertFromScreenCoords(Ivec2 pos)
{
	float x = static_cast<float>(pos.x) / static_cast<float>(misc_getWindowSize().x);
	float y = static_cast<float>(pos.y) / static_cast<float>(misc_getWindowSize().y);

	return Vec2(x, y);
}

Vec3 FabiEngine3D::misc_getRaycastVector()
{
	return _core->_rayCaster.getRay();
}

Vec3 FabiEngine3D::misc_getRaycastPositionOnTerrain()
{
	return _core->_rayCaster.getTerrainPoint();
}

bool FabiEngine3D::misc_isRaycastPositionOnTerrainValid()
{
	return (_core->_rayCaster.getTerrainPoint() != Vec3(-1.0f));
}

bool FabiEngine3D::misc_isMillisecondTimerStarted()
{
	return _core->_timer.isTiming();
}

Ivec2 FabiEngine3D::misc_getWindowSize()
{
	return Config::getInst().getWindowSize();
}

Ivec2 FabiEngine3D::misc_getViewportPosition()
{
	return Config::getInst().getVpPos();
}

Ivec2 FabiEngine3D::misc_getViewportSize()
{
	return Config::getInst().getVpSize();
}

bool FabiEngine3D::misc_isCursorVisible()
{
	return _core->_windowManager.isCursorVisible();
}

bool FabiEngine3D::misc_isCursorInsideViewport()
{
	// Variables
	Ivec2 mousePos = misc_getCursorPosition();
	Ivec2 viewportPos = misc_getViewportPosition();
	Ivec2 viewportSize = misc_getViewportSize();

	// Checking if cursor is inside viewport
	if (mousePos.x > viewportPos.x && mousePos.x < viewportPos.x + viewportSize.x)
	{
		if (mousePos.y > viewportPos.y && mousePos.y < viewportPos.y + viewportSize.y)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::misc_isCursorInsideWindow()
{
	// Variables
	Ivec2 mousePos = misc_getCursorPosition();
	Ivec2 windowSize = misc_getWindowSize();
	
	// Checking if cursor is inside viewport
	if (mousePos.x > 1 && mousePos.x < windowSize.x - 1)
	{
		if (mousePos.y > 1 && mousePos.y < windowSize.y - 1)
		{
			return true;
		}
	}

	return false;
}

bool FabiEngine3D::misc_isDirectoryExisting(const string& filePath)
{
	struct stat fileInfo;
	int result = stat(filePath.c_str(), &fileInfo);
	return (result == 0 && (fileInfo.st_mode & S_IFDIR));
}

bool FabiEngine3D::misc_isFileExisting(const string& filePath)
{
	struct stat fileInfo;
	bool isExisting = stat(filePath.c_str(), &fileInfo) == 0;
	return (isExisting && !misc_isDirectoryExisting(filePath));
}

bool FabiEngine3D::misc_checkInterval(unsigned int frames)
{
	return ((_core->_timer.getPassedFrameCount() % frames) == 0);
}

vector<pair<string, int>> FabiEngine3D::misc_getUpdateProfilingStatistics()
{
	// Final list of timer IDs
	vector<pair<string, int>> result =
	{
		pair<string, int>("coreUpdate", 0),
		pair<string, int>("cameraUpdate", 0),
		pair<string, int>("raycastUpdate", 0),
		pair<string, int>("collisionUpdate", 0),
		pair<string, int>("skyEntityUpdate", 0),
		pair<string, int>("waterEntityUpdate", 0),
		pair<string, int>("modelEntityUpdate", 0),
		pair<string, int>("billboardEntityUpdate", 0),
		pair<string, int>("aabbEntityUpdate", 0),
		pair<string, int>("guiEntityUpdate", 0),
		pair<string, int>("shadowUpdate", 0),
		pair<string, int>("audioUpdate", 0),
		pair<string, int>("miscUpdate", 0)
	};

	// Calculate percentages
	for (auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

vector<pair<string, int>> FabiEngine3D::misc_getRenderProfilingStatistics()
{
	// Final list of timer IDs
	vector<pair<string, int>> result =
	{
		pair<string, int>("reflectionPreRender", 0),
		pair<string, int>("refractionPreRender", 0),
		pair<string, int>("shadowPreRender", 0),
		pair<string, int>("depthPreRender", 0),
		pair<string, int>("skyEntityRender", 0),
		pair<string, int>("terrainEntityRender", 0),
		pair<string, int>("waterEntityRender", 0),
		pair<string, int>("modelEntityRender", 0),
		pair<string, int>("billboardEntityRender", 0),
		pair<string, int>("aabbEntityRender", 0),
		pair<string, int>("guiEntityRender", 0),
		pair<string, int>("postProcessing", 0),
		pair<string, int>("bufferSwap", 0)
	};
	
	// Calculate percentages
	for (auto& [ID, percentage] : result)
	{
		int newPercentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);
		percentage = newPercentage;
	}

	return result;
}

void FabiEngine3D::misc_setSoundsEnabled(bool enabled)
{
	_core->_audioPlayer.setSoundsEnabled(enabled);
}

void FabiEngine3D::misc_setMusicEnabled(bool enabled)
{
	_core->_audioPlayer.setMusicEnabled(enabled);
}

void FabiEngine3D::misc_setMaxAudioChannels(unsigned int count)
{
	_core->_audioPlayer.allocateChannels(count);
}

int FabiEngine3D::misc_getMaxChannels()
{
	return _core->_audioPlayer.getAllocatedChannelCount();
}