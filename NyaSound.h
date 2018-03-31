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
		SoundFile& operator=(const SoundFile& file)
		{
			id_ = file.id_;
			pass_.clear();
			pass_ = file.pass_;
			return *this;
		}
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
		SoundProperty& operator=(SoundProperty& sp)
		{
			loop_ = sp.loop_;
			sound_file_ = sp.sound_file_;
		}
	};

	class NyaSound
	{
	public:
		NyaSound();
		~NyaSound();
		void ChangeVolume(SoundProperty* sp, int volume);
		void DeleteSoundFile(SoundFile* file);
		void LoadSoundFile(std::string pass, SoundFile* file);
		void Play(const SoundProperty* sp);
		void Run(void);
	private:
		static std::list<SoundFile> file_list_;
		static std::deque<SoundProperty> play_deque_;
	};

}
