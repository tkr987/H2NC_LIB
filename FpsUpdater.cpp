#include "DxLib.h"
#include "FpsUpdater.h"
#include "DebugPrint.h"

#define __DEBUG__
using namespace NH3;

static int fpsall = 0;

FpsUpdater::FpsUpdater()
{
	ave_frame_ = ave_wtime_ = ave_ltime_ = 0;
	for (int i = 0; i < FPS_MAX; i++)
		frame_[i] = ltime_[i] = wtime_[i] = 0;
	frame_count_ = 0;
	all_frame_count_ = 0;
	prev_time_ = 0;
}

FpsUpdater::~FpsUpdater()
{

}


void FpsUpdater::Run(void)
{
#ifdef __DEBUG__
	DebugPrint::SetData(615, 220, "frames_: %d", fpsall++);
	if (ave_frame_ != 0) {
		DebugPrint::SetData(690, 535, "fps[%.1f]", 1000.0 / (double)ave_frame_);
		DebugPrint::SetData(690, 555, "loop[%dms]", ave_ltime_);
		DebugPrint::SetData(690, 575, "wait[%dms]", ave_wtime_);
	}
#else
	if (ave_frame_ != 0)
		DebugPrint::SetData(700, 550, "fps[%.1f]", 1000.0 / (double)ave_frame_);
#endif


	frame_count_ = ++all_frame_count_ % FPS_MAX;
	/*•½‹ÏŽZo*/
	if (frame_count_ == FPS_MAX - 1)
	{
		ave_frame_ = 0;
		ave_ltime_ = 0;
		ave_wtime_ = 0;
		for (int i = 0; i < FPS_MAX; i++)
		{
			ave_frame_ += frame_[i];
			ave_ltime_ += ltime_[i];
			ave_wtime_ += wtime_[i];
		}
		ave_frame_ = ave_frame_ / FPS_MAX;
		ave_ltime_ = ave_ltime_ / FPS_MAX;
		ave_wtime_ = ave_wtime_ / FPS_MAX;
	}

	ltime_[frame_count_] = GetNowCount() - prev_time_;
	/*waitˆ—*/
	wtime_[frame_count_] = (1000 / FPS_MAX) - ltime_[frame_count_];
	if (0 < wtime_[frame_count_])
		Sleep(wtime_[frame_count_]);
	frame_[frame_count_] = GetNowCount() - prev_time_;
	prev_time_ = GetNowCount();
}
