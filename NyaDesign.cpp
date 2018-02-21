#include <tuple>
#include "DxLib.h"
#include "NyaDesign.h"
#include "NyaInput.h"
#include "NyaString.h"
#include "NyaTarget.h"

#define FPS_MAX 60
#define __DEBUG__

using namespace std;
using namespace H2NLIB;

int NyaDesign::count_mission_frame_;
int NyaDesign::user_exp_;
int NyaDesign::user_lv_;
int NyaDesign::skill_exp_[4] = {};
int NyaDesign::skill_exp_next_[4][4] = {
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
	{2147483647, 2147483647, 2147483647, 2147483647},
};
unsigned int NyaDesign::skill_lv_[4] = {};
string NyaDesign::skill_name_[4];
unsigned int NyaDesign::skill_select_;
ePROCESS::NUM NyaDesign::process_;


NyaDesign::NyaDesign()
{
	static bool first_call = true;

	// 初期化するのは1回だけ
	if (first_call) {
		user_exp_ = 0;
		user_lv_ = 123;
		skill_name_[0] = "Skill Z";
		skill_name_[1] = "Skill X";
		skill_name_[2] = "Skill C";
		skill_name_[3] = "Skill V";
		skill_select_ = 0;
		NyaString::SettingFont("design_exp_font", 18, 2);
		NyaString::SettingFont("design_fps_font", 14, 2);
		NyaString::SettingFont("design_lv_font", 60, 6);
		NyaString::SettingFont("design_skill_font", 30, 2);
		NyaString::SettingFont("design_input_font", 50, 2);

		first_call = false;
	}
}


NyaDesign::~NyaDesign()
{

}

void NyaDesign::AddEXP(int x)
{
	user_exp_ += x;
	skill_exp_[skill_select_] += x;
}

ePROCESS::NUM NyaDesign::GetProcess(void)
{
	return process_;
}

void NyaDesign::SetProcess(ePROCESS::NUM set)
{
	process_ = set;
}

void NyaDesign::Run(void)
{
	DrawBlack(850, 0, 1279, 719);
	DrawSkill(875, 110);
	DrawLv(875, 515);
	DrawInput(875, 600);
	UpdateFPS(1180, 660);
}

void NyaDesign::SetSkillSelect(int n)
{
	skill_select_ = n;
}

void NyaDesign::SetSkillName(int x, string name)
{
	skill_name_[x] = name;
}

void NyaDesign::DrawBlack(int x, int y, int x2, int y2) {
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

	NyaString::Write("design_lv_font", white, x, y, "Lv.%d", user_lv_);
}

void NyaDesign::DrawSkill(int x, int y)
{
	static tuple<int, int, int> white = make_tuple(255, 255, 255);

	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i, "☆");
		NyaString::Write("design_skill_font", white, x + 50, y + 90 * i, skill_name_[i]);
	}
	for (int i = 0; i < 4; i++) {
		NyaString::Write("design_skill_font", white, x, y + 90 * i + 45, "□□□□");
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 40, "Exp : %d pt", skill_exp_[i]);
		NyaString::Write("design_exp_font", white, x + 150, y + 90 * i + 60, "Next: %d pt", skill_exp_next_[i][0]);
	}
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
