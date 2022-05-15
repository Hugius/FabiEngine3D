#pragma once

#include "base_editor.hpp"

class Sound2dEditor final : public BaseEditor
{
public:
	using BaseEditor::inject;

	void update();
	void deleteLoadedSound2ds();

	const vector<string> getAudioPathsFromFile() const;
	const vector<string> & getLoadedSound2dIds() const;

	const bool loadSound2dsFromFile();
	const bool saveSound2dsToFile() const;

private:
	void _load();
	void _unload();
	void _loadGUI();
	void _unloadGUI();
	void _updateMainMenu();
	void _updateChoiceMenu();
	void _updateSound2dCreating();
	void _updateSound2dChoosing();
	void _updateSound2dDeleting();
	void _updateMiscellaneous();

	static inline const string STATUS_ID = "@@status";
	static inline const string STATUS_START_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\start.tga";
	static inline const string STATUS_PAUSE_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\pause.tga";
	static inline const string STATUS_STOP_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\stop.tga";
	static inline const string SOUND2D_TITLE_ID = "sound2d_id";

	static inline const fvec3 STATUS_QUAD3D_POSITION = fvec3(0.0f, 0.0f, -1.5f);

	static inline const fvec2 SOUND2D_TITLE_POSITION = fvec2(0.0f, 0.85f);
	static inline const fvec2 SOUND2D_TITLE_SIZE = fvec2(0.025f, 0.1f);

	static inline constexpr float CAMERA_YAW = 270.0f;
	static inline constexpr float BLOOM_INTENSITY = 1.0f;

	static inline constexpr int ANISOTROPIC_FILTERING_QUALITY = 16;
	static inline constexpr int BLOOM_BLUR_COUNT = 5;
	static inline constexpr int BLOOM_QUALITY = 5;

	static inline constexpr BloomType BLOOM_TYPE = BloomType::PARTS;

	vector<string> _loadedSound2dIds = {};

	string _currentSound2dId = "";
	string _hoveredSound2dId = "";
};