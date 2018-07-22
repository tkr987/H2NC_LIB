#include "TeemoEnding.h"
#include "NyaGraphic.h"

using namespace HNLIB;

TeemoEnding::TeemoEnding()
{
	gpx_ = new GraphicPropertyX1;
}

TeemoEnding::~TeemoEnding()
{
	delete gpx_;
	gpx_ = nullptr;
}

void TeemoEnding::Load(void)
{
	NyaGraphic::Load("img/back/ending.png", &gpx_->file_);
}

void TeemoEnding::Run(void)
{
	NyaGraphic::Draw(gpx_, eOBJECT::BACK_MAP1);
}

void TeemoEnding::Delete(void)
{
	NyaGraphic::Delete(&gpx_->file_);
}

