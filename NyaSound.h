#pragma once

#include <deque>
#include <list>
#include <string>
#include <vector>

namespace HNLIB
{

	class NyaDesign;

	class SoundFile
	{
	public:
		int id_;
		std::string pass_;
		SoundFile& operator=(const SoundFile& file);
	};

	class SoundPropertyX
	{
	public:
		bool loop_;
		SoundFile file_;
		SoundPropertyX()
		{
			loop_ = false;
		}
		SoundPropertyX& operator=(SoundPropertyX& sp);
	};

	class NyaSound
	{
	public:
		NyaSound(){}
		~NyaSound(){}
		static void ChangeVolume(SoundFile* file, int volume);
		static void Delete(SoundFile* file);
		static void Init(void);
		static void Load(std::string pass, SoundFile* file);
		static void Play(const SoundPropertyX* sp);
		static void Run(void);
	private:
		static std::list<SoundFile> file_collection_;
		static std::deque<SoundPropertyX> play_collection_;
	};

}
