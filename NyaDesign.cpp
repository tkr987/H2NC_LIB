#include <tuple>
#include "DxLib.h"
#include "NyaDesign.h"
#include "NyaInput.h"
#include "NyaSound.h"
#include "NyaString.h"
#include "NyaTarget.h"

#define __DEBUG__

using namespace std;
using namespace H2NLIB;

int NyaDesign::count_mission_frame_;
ePROCESS::NUM NyaDesign::process_;
DesignSkillInfo NyaDesign::skill_info_[4];
DesignUserInfo NyaDesign::user_info_;
pair<bool, int> NyaDesign::warning_sound_pair_;
pair<bool, DesignWarningString> NyaDesign::warning_string_pair_;


NyaDesign::NyaDesign()
{
	static bool first_call = true;
	DesignSkillInfo init_skill_info;

	nya_sound_ = new NyaSound;

	// 初期化するのは1回だけ
	if (first_call) {
		count_mission_frame_ = 0;
		init_skill_info.exp_ = 0;
		init_skill_info.exp_next_[0] = 2147483647;
		init_skill_info.exp_next_[1] = 2147483647;
		init_skill_info.exp_next_[2] = 2147483647;
		init_skill_info.exp_next_[3] = 2147483647;
		init_skill_info.lv_ = 1;
		init_skill_info.name_ = "Skill Q";
		init_skill_info.select_ = true;
		skill_info_[0] = init_skill_info;
		init_skill_info.name_ = "Skill W";
		init_skill_info.select_ = false;
		skill_info_[1] = init_skill_info;
		init_skill_info.name_ = "Skill E";
		init_skill_info.select_ = false;
		skill_info_[2] = init_skill_info;
		init_skill_info.name_ = "Skill R";
		init_skill_info.select_ = false;
		skill_info_[3] = init_skill_info;
		user_info_.exp_ = 0;
		user_info_.exp_next_ = 2147483647;
		user_info_.lv_ = 123;
		warning_sound_pair_.first = false;
		warning_string_pair_.first = false;
		NyaString::SettingFont("design_exp_font", 18, 2);
		NyaString::SettingFont("design_fps_font", 14, 2);
		NyaString::SettingFont("design_lv_font", 60, 6);
		NyaString::SettingFont("design_skill_font", 30, 2);
		NyaString::SettingFont("design_input_font", 50, 2);
		NyaString::SettingFont("design_warning_font", 64, 4);

		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{
	delete nya_sound_;
}

void NyaDesign::AddEXP(int x)
{
	user_info_.exp_ += x;
	for (int skill_type = eSKILL::NUM::Q; skill_type != eSKILL::NUM::sizeof_enum; skill_type++)
	{
		if (skill_info_[skill_type].select_)
			skill_info_[skill_type].exp_ += x;
	}
}

void NyaDesign::Run(void)
{
	switch(process_)
	{
	case ePROCESS::NUM::MISSION_LOAD:
		count_mission_frame_ = 0;
		break;
	case ePROCESS::NUM::MISSION_RUN:
	case ePROCESS::NUM::MISSION_STOP:
		if (warning_string_pair_.first)
			DrawWarning();
		count_mission_frame_++;
		break;
	}

	DrawBlack(850, 0, 1279, 719);
	DrawSkill(875, 110);
	DrawLv(875, 515);
	DrawInput(875, 600);
	UpdateFPS(1180, 660);
}

void NyaDesign::Warning(int grid_x, int grid_y, int draw_time_sec)
{
	warning_string_pair_.first = true;
	warning_string_pair_.second.draw_start_frame_ = count_mission_frame_;
	warning_string_pair_.second.draw_end_frame_ = count_mission_frame_ + FPS_MAX * draw_time_sec;
	warning_string_pair_.second.grid_x_ = grid_x;
	warning_string_pair_.second.grid_y_ = grid_y;
}




void NyaDesign::DrawBlack(int x, int y, int x2, int y2) 
{
	static int color = GetColor(16, 16, 16);

	DrawBox(x, y, x2, y2, color , true) ;
}

void NyaDesign::DrawInput(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);
	static tuple<int, int, int> red = make_tuple(255, 0, 0);

	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::Q))
		NyaString::Write("design_input_font", red, x, y, "■");
	NyaString::Write("design_input_font", white, x, y, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::W))
		NyaString::Write("design_input_font", red, x + 50, y, "■");
	NyaString::Write("design_input_font", white, x + 50, y, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::E))
		NyaString::Write("design_input_font", red, x + 100, y, "■");
	NyaString::Write("design_input_font", white, x + 100, y, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::R))
		NyaString::Write("design_input_font", red, x + 150, y, "■");
	NyaString::Write("design_input_font", white, x + 150, y, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::SPACE))
		NyaString::Write("design_input_font", red, x + 200, y, "■");
	NyaString::Write("design_input_font", white, x + 200, y, "□");

	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::UP))
		NyaString::Write("design_input_font", red, x + 275, y -120, "■");
	NyaString::Write("design_input_font", white, x + 275, y - 120, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::RIGHT))
		NyaString::Write("design_input_font", red, x + 325, y - 70, "■");
	NyaString::Write("design_input_font", white, x + 325, y - 70, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::DOWN))
		NyaString::Write("design_input_font", red, x + 275, y - 20, "■");
	NyaString::Write("design_input_font", white, x + 275, y -20, "□");
	if (NyaInput::GetKeyFlagNow(eINPUT::NUM::LEFT))
		NyaString::Write("design_input_font", red, x + 225, y - 70, "■");
	NyaString::Write("design_input_font", white, x + 225, y - 70, "□");
}

void NyaDesign::DrawLv(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	NyaString::Write("design_lv_font", white, x, y, "Lv.%d", user_info_.lv_);
}

void NyaDesign::DrawSkill(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i, "☆");
		NyaString::Write("design_skill_font", white, x + 50, y + 90 * i, skill_info_[i].name_);
	}
	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i + 45, "□□□□");
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 40, "Exp : %d pt", skill_info_[i].exp_);
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 60, "Next: %d pt", skill_info_[i].exp_next_[skill_info_[i].lv_]);
	}
}

void NyaDesign::DrawWarning(void)
{
	int x = warning_string_pair_.second.grid_x_;
	int y = warning_string_pair_.second.grid_y_;
	static int black = GetColor(0, 0, 0);
	static tuple<int, int, int> red = make_tuple(255, 0, 0);
	static SoundPropertyX spx;

	if (count_mission_frame_ == warning_string_pair_.second.draw_start_frame_)
	{
		if (warning_sound_pair_.first)
		{
			spx.file_id_ = warning_sound_pair_.second;
			nya_sound_->Play(&spx);
		}
	}

	if (count_mission_frame_ == warning_string_pair_.second.draw_end_frame_ - 1)
		warning_string_pair_.first = false;

	DrawBox(x, y, x + 400, y + 150, black, true);
	NyaString::Write("design_warning_font", red, x + 90, y + 25, "WARNING");
}

/**
@param FPS更新関数
**/
void NyaDesign::UpdateFPS(int x, int y)
{

	static	int frame_ave_ = 0;					//フレームレート平均
	static	int wtime_ave_ = 0;					//wait時間平均
	static	int ltime_ave_ = 0;					//loop時間平均
	static	int frame_[FPS_MAX] = {};			//フレームレート
	static	int ltime_[FPS_MAX] = {};			//loop時間
	static	int wtime_[FPS_MAX] = {};			//wait時間
	static	int prev_time_ = 0;					//1フレーム前の時間
	static	int frame_count_ = 0;				//現在のフレーム(0～FPS_MAX-1)
	static unsigned int all_frame_count_ = 0;	//フレーム数をカウントし続ける変数
	static tuple<int, int, int> white = make_tuple(255, 255, 255);



#ifdef __DEBUG__
	if (frame_ave_ != 0) {
		NyaString::Write("design_fps_font", white, x, y, "fps[%.1f fps]", 1000.0 / (double)frame_ave_);
		NyaString::Write("design_fps_font", white, x, y + 20, "loop[%d ms]", ltime_ave_);
		NyaString::Write("design_fps_font", white, x, y + 40, "wait[%d ms]", wtime_ave_);
	}
#else
	if (frame_ave_ != 0)
		DebugPrint::SetData(1200, 700, "fps[%.1f]", 1000.0 / (double)frame_ave_);
#endif


	frame_count_ = ++all_frame_count_ % FPS_MAX;
	/*平均算出*/
	if (frame_count_ == FPS_MAX - 1)
	{
		frame_ave_ = 0;
		ltime_ave_ = 0;
		wtime_ave_ = 0;
		for (int i = 0; i < FPS_MAX; i++)
		{
			frame_ave_ += frame_[i];
			ltime_ave_ += ltime_[i];
			wtime_ave_ += wtime_[i];
		}
		frame_ave_ = frame_ave_ / FPS_MAX;
		ltime_ave_ = ltime_ave_ / FPS_MAX;
		wtime_ave_ = wtime_ave_ / FPS_MAX;
	}

	ltime_[frame_count_] = GetNowCount() - prev_time_;
	/*wait処理*/
	wtime_[frame_count_] = (1000 / FPS_MAX) - ltime_[frame_count_];
	if (0 < wtime_[frame_count_])
		Sleep(wtime_[frame_count_]);
	frame_[frame_count_] = GetNowCount() - prev_time_;
	prev_time_ = GetNowCount();
}
