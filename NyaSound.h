#pragma once

#include <deque>
#include <string>
#include <vector>

namespace H2NLIB
{

	class NyaDesign;

	struct SoundFile
	{
		int id_;
		std::string pass_;
	};

	class SoundPropertyX
	{
	public:
		int file_id_;
		bool loop_;
		SoundPropertyX()
		{
			loop_ = false;
		}
	};

	class NyaSound
	{
	public:
		NyaSound();
		~NyaSound();
		void ChangeVolume(SoundPropertyX* spx, int volume);
		int LoadFile(std::string pass);
		void Play(std::string pass, bool loop = false);
		void Play(SoundPropertyX* spx);
		void Run(void);
	private:
		static std::vector<SoundFile> file_vector_;
		static std::deque<SoundPropertyX> play_deque_;
	};

}
