#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>

#if ENABLE_AUDIO
#include "AL/al.h"
#endif

void playSound();

class AudioEngine {
public: 
	AudioEngine();
	~AudioEngine();

	// Delete copy and move constructors & assignment
	AudioEngine(const AudioEngine&) = delete;
	AudioEngine& operator=(const AudioEngine&) = delete;
	AudioEngine(AudioEngine&&) = delete;
	AudioEngine&& operator=(AudioEngine&&) = delete;

	void Init();
	void Update();
	void Shutdown();

	void LoadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const std::string& strSoundName);
	void Set3dListenerAndOrientation(const glm::vec3& vPosition, const glm::vec3& vLoop, const glm::vec3& vUp);
	void Play(const std::string& strSoundName, const glm::vec3& vPos = { 0, 0, 0 }, float vVolumedB = 0.0f);
	void StopChannel(int nChannelId);
	void PauseChannel(int nChannelId);
	void StopAllChannels();
	void SetChannel3dPosition(int nChannelId, const glm::vec3& vPosition);
	void SetChannelVolume(int nChannelId, float fVolumedB);
	bool IsPlaying(const std::string& strSoundName) const;
	bool isLoaded(const std::string& soundName) const;

private:
	bool isShutdown;
	struct SoundDefinition {
		SoundDefinition() = default;
		~SoundDefinition() = default;

		std::string name;
#if ENABLE_AUDIO
		ALuint source;
		ALuint buffer;

		ALfloat offset;
		ALenum state;
#endif
		std::string err_msg;
	};

	using SoundMap = std::map<std::string, SoundDefinition>;
	SoundMap mSounds;

};