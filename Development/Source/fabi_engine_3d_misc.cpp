#include "fabi_engine_3d.hpp"
#include "core_engine.hpp"
#include "Tools.hpp"
#include "configuration.hpp"

#include <chrono>
#include <filesystem>

int FabiEngine3D::misc_getUniqueInt(int min, int max)
{
	static vector<int> uniqueInts;
	int randomInt = misc_getRandomInt(min, max);

	// Check if already existing
	if (std::find(uniqueInts.begin(), uniqueInts.end(), randomInt) != uniqueInts.end())
	{
		return misc_getUniqueInt(min, max);
	}
	else
	{
		uniqueInts.push_back(randomInt);
		return randomInt;
	}
}

int FabiEngine3D::misc_getWindowWidth()
{
	return Config::getInst().getWindowWidth();
}

int FabiEngine3D::misc_getWindowHeight()
{
	return Config::getInst().getWindowHeight();
}

int FabiEngine3D::misc_getRandomInt(int min, int max)
{
	return Tools::getInst().getRandomInt(min, max);
}

int FabiEngine3D::misc_getMsTimeSinceEpoch()
{
	using namespace std::chrono;
	return int(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count());
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
	return float(misc_getWindowWidth()) / float(misc_getWindowHeight());
}

float FabiEngine3D::misc_getFPS()
{
	return 1000.0f / _core->_deltaTime;
}

float FabiEngine3D::misc_getPI()
{
	return Tools::getInst().getPI();
}

void FabiEngine3D::misc_showCursor()
{
	_core->_windowManager.showMouseCursor();
}

void FabiEngine3D::misc_hideCursor()
{
	_core->_windowManager.hideMouseCursor();
}

void FabiEngine3D::misc_setCustomCursor(const string& guiEntityID)
{
	_core->_renderBus.setCursorEntityID(guiEntityID);
}

void FabiEngine3D::misc_enableWireframeRendering()
{
	_core->_renderBus.setWireframeRenderingEnabled(true);
}

void FabiEngine3D::misc_disableWireframeRendering()
{
	_core->_renderBus.setWireframeRenderingEnabled(false);
}

void FabiEngine3D::misc_enableShadowFrameRendering()
{
	_core->_renderBus.setShadowFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_disableShadowFrameRendering()
{
	_core->_renderBus.setShadowFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_enableAabbFrameRendering()
{
	_core->_renderBus.setAabbFrameRenderingEnabled(true);
}

void FabiEngine3D::misc_disableAabbFrameRendering()
{
	_core->_renderBus.setAabbFrameRenderingEnabled(false);
}

void FabiEngine3D::misc_enableDebugRendering()
{
	_core->_renderBus.setDebugRenderingEnabled(true);
}

void FabiEngine3D::misc_disableDebugRendering()
{
	_core->_renderBus.setDebugRenderingEnabled(false);
}

void FabiEngine3D::misc_setMousePos(ivec2 pos)
{
	_core->_mousePicker.update(pos, _core->_terrainEntityManager);
	_core->_windowManager.setMousePos(pos);
}

void FabiEngine3D::misc_showAudioDebugging()
{
	_core->_audioPlayer.setChannelDebugging(true);
}

void FabiEngine3D::misc_hideAudioDebugging()
{
	_core->_audioPlayer.setChannelDebugging(false);
}

void FabiEngine3D::misc_setMainRenderingColor(vec3 color)
{
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void FabiEngine3D::misc_setWindowTitle(const string& title)
{
	_core->_windowManager.setTitle(title);
}

void FabiEngine3D::misc_clearOBJCache(const string& filePath)
{
	_core->_objLoader.clearOBJCache(filePath);
}

void FabiEngine3D::misc_clearTextCache(const string& filePath)
{
	_core->_texLoader.clearTextCache(filePath);
}

void FabiEngine3D::misc_clearFontCache(const string& filePath)
{
	_core->_texLoader.clearFontCache(filePath);
}

void FabiEngine3D::misc_clearTextureCache(const string& filePath)
{
	_core->_texLoader.clearTextureCache(filePath);
}

void FabiEngine3D::misc_clearCubeMapCache(const array<string, 6>& filePaths)
{
	_core->_texLoader.clearCubeMapCache(filePaths);
}

void FabiEngine3D::misc_clearHeightMapCache(const string& filePath)
{
	_core->_texLoader.clearHeightMapCache(filePath);
}

string FabiEngine3D::misc_getWinExplorerFilename(const string& startingDir, const string& fileType)
{
	// Prepare filter C-string
	string filter = fileType;
	filter.push_back('\0');
	filter += "*." + fileType + '\0';

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
	ofn.lpstrInitialDir = string(misc_getRootDirectory() + startingDir).c_str(); // Starting directory
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	GetOpenFileName(&ofn);

	// Return chosen filename or nothing if cancelled
	string filePath = ofn.lpstrFile;
	return filePath;
}

string FabiEngine3D::misc_vec2str(ivec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

string FabiEngine3D::misc_vec2str(ivec3 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z);
}

string FabiEngine3D::misc_vec2str(ivec4 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w);
}

string FabiEngine3D::misc_vec2str(vec2 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y);
}

string FabiEngine3D::misc_vec2str(vec3 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z);
}

string FabiEngine3D::misc_vec2str(vec4 vec)
{
	return to_string(vec.x) + " " + to_string(vec.y) + " " + to_string(vec.z) + " " + to_string(vec.w);
}

string FabiEngine3D::misc_getRootDirectory()
{
	// Retrieve
	char buffer[256]; size_t len = sizeof(buffer);
	GetModuleFileName(NULL, buffer, len); // Get executable path
	string rootDir = buffer;
	rootDir = std::filesystem::absolute(rootDir).string(); // Remove any "..\" bullshit
	rootDir = rootDir.substr(0, rootDir.size() - string("bin\\FabiEngine3D.exe").size()); // Go to engine root directory

	// Return
	return rootDir;
}

string FabiEngine3D::misc_getGpuName()
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_RENDERER))));
}

string FabiEngine3D::misc_getOpenglVersion()
{
	return string(reinterpret_cast<char*>(const_cast<GLubyte*>(glGetString(GL_VERSION)))).substr(0, 3);
}

vec2 FabiEngine3D::misc_convertToNDC(vec2 pos)
{
	pos.x = (pos.x * 2.0f) - 1.0f;
	pos.y = (pos.y * 2.0f) - 1.0f;

	return vec2(pos.x, pos.y);
}

vec2 FabiEngine3D::misc_convertFromNDC(vec2 pos)
{
	pos.x += 1.0f;
	pos.x /= 2.0f;
	pos.y += 1.0f;
	pos.y /= 2.0f;

	return vec2(pos.x, pos.y);
}

ivec2 FabiEngine3D::misc_convertToScreenCoords(vec2 pos)
{
	float x = float(pos.x) * float(misc_getWindowWidth());
	float y = float(pos.y) * float(misc_getWindowHeight());

	return ivec2(int(x), int(y));
}

vec2 FabiEngine3D::misc_convertFromScreenCoords(ivec2 pos)
{
	float x = float(pos.x) / float(misc_getWindowWidth());
	float y = float(pos.y) / float(misc_getWindowHeight());

	return vec2(x, y);
}

ivec2 FabiEngine3D::misc_getMousePos()
{
	ivec2 mousePos = _core->_windowManager.getMousePos();

	return ivec2(mousePos.x, misc_getWindowHeight() - mousePos.y);
}

ivec2 FabiEngine3D::misc_getWindowSize()
{
	return Config::getInst().getWindowSize();
}

ivec2 FabiEngine3D::misc_getViewportPosition()
{
	return Config::getInst().getVpPos();
}

ivec2 FabiEngine3D::misc_getViewportSize()
{
	return Config::getInst().getVpSize();
}

bool FabiEngine3D::misc_isMouseInsideViewport()
{
	// Variables
	ivec2 mousePos = misc_getMousePos();
	ivec2 viewportPos = misc_getViewportPosition();
	ivec2 viewportSize = misc_getViewportSize();

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

bool FabiEngine3D::misc_isMouseInsideWindow()
{
	// Variables
	ivec2 mousePos = misc_getMousePos();
	ivec2 windowSize = misc_getWindowSize();
	
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

bool FabiEngine3D::misc_isDirectory(const string& filePath)
{
	struct stat fileInfo;
	stat(filePath.c_str(), &fileInfo);
	return (fileInfo.st_mode & S_IFDIR);
}

bool FabiEngine3D::misc_isFileExisting(const string& filePath)
{
	struct stat fileInfo;
	return stat(filePath.c_str(), &fileInfo) == 0;
}

bool FabiEngine3D::misc_checkInterval(const string& key, int frameCount)
{
	static std::map<string, int> intervalMap;

	// Check if key exists
	if (intervalMap.find(key) != intervalMap.end())
	{
		// Check if passed frames is more than interval minimum
		if ((_core->_timer.getPassedFrameCount() % intervalMap[key]) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// Create new interval
		intervalMap.insert(std::make_pair(key, frameCount));
		return true;
	}
}

unordered_map<string, int> FabiEngine3D::misc_getPerformanceProfilingStatistics()
{
	std::unordered_map<string, int> result = 
	{ 
		std::pair<string, int>("bufferSwap", 0),
		std::pair<string, int>("waterPreRender", 0),
		std::pair<string, int>("shadowPreRender", 0),
		std::pair<string, int>("postProcessing", 0),
		std::pair<string, int>("skyEntityRender", 0),
		std::pair<string, int>("terrainEntityRender", 0),
		std::pair<string, int>("waterEntityRender", 0),
		std::pair<string, int>("gameEntityRender", 0),
		std::pair<string, int>("billboardEntityRender", 0),
		std::pair<string, int>("guiEntityRender", 0)
	};

	vector<string> IDs =
	{
		"reflectionPreRender", "refractionPreRender", "shadowPreRender", "sceneDepthPreRender", 
		"skyEntityRender", "terrainEntityRender", "waterEntityRender", "gameEntityRender", "billboardEntityRender", "aabbEntityRender", 
		"antiAliasing", "postProcessing", "guiEntityRender", "textEntityRender", "bufferSwap"
	};
	
	// Calculate percentages
	for (auto& ID : IDs)
	{
		int percentage = static_cast<int>((_core->_timer.getDeltaPart(ID) / _core->_timer.getDeltaPartSum()) * 100.0f);

		if (ID == "reflectionPreRender")
		{
			result["waterPreRender"] += percentage;
		}
		else if (ID == "refractionPreRender")
		{
			result["waterPreRender"] += percentage;
		}
		else if (ID == "sceneDepthPreRender")
		{
			// Determine if depth rendering being used by water or post-processing
			if (_core->_renderBus.isDofEnabled() || _core->_renderBus.isLensFlareEnabled())
			{
				result["postProcessing"] += percentage;
			}
			else
			{
				result["waterPreRender"] += percentage;
			}
		}
		else if (ID == "antiAliasing")
		{
			result["postProcessing"] += percentage;
		}
		else if (ID == "textEntityRender")
		{
			result["guiEntityRender"] += percentage;
		}
		else if (ID == "aabbEntityRender")
		{
			result["gameEntityRender"] += percentage;
		}
		else
		{
			result[ID] += percentage;
		}
	}

	return result;
}