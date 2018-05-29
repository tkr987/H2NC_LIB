#pragma once

#include <deque>
#include <list>
#include <string>
#include <vector>

namespace H2NLIB
{

	class NyaDesign;

	class SoundFile
	{
	public:
		int id_;
		std::string pass_;
		SoundFile& operator=(const SoundFile& file);
	};

	class SoundProperty
	{
	public:
		bool loop_;
		SoundFile sound_file_;
		SoundProperty()
		{
			loop_ = false;
		}
		SoundProperty& operator=(SoundProperty& sp);
	};

	class NyaSound
	{
	public:
		NyaSound(){}
		~NyaSound(){}
		static void ChangeVolume(SoundFile* file, int volume);
		static void DeleteSoundFile(SoundFile* file);
		static void LoadSoundFile(std::string pass, SoundFile* file);
		static void Play(const SoundProperty* sp);
		static void Run(void);
	private:
		static std::list<SoundFile> file_collection_;
		static std::deque<SoundProperty> play_collection_;
	};

}
