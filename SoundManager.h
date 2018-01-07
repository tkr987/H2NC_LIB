#pragma once

#include <vector>
#include <deque>

namespace NH2 {

	struct SoundLoad {
		int id_;
		std::string filename_;
	};

	struct SoundPlay {
		int id_;
		int mode_;
		bool posflag_;
	};

	class SoundManager {
	public:
		SoundManager() {}
		~SoundManager() {}
		// ‰Šú‰»ŠÖ˜A
		static void Clear(void);
		static void End();
		static void Init(void);
		// ‚»‚Ì‘¼
		static void ChangeVolume(int id, int set_volume);
		static int Play(int id, int mode, bool posflag = true);
		static void Stop(int id);
		static int Load(std::string filename);
	protected:
		static int sload_num_;
		static int splay_num_;
		static std::vector<SoundLoad>vec_sload_;
		static std::vector<SoundPlay>vec_splay_;
	};

}


