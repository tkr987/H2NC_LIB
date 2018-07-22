#include "TeemoOpening.h"
#include "NyaGraphic.h"

using namespace HNLIB;

TeemoOpening::TeemoOpening()
{
	gpx_ = new GraphicPropertyX1;
}

TeemoOpening::~TeemoOpening()
{
	delete gpx_;
	gpx_ = nullptr;
}

void TeemoOpening::Load(void)
{
	NyaGraphic::Load("img/back/opening.png", &gpx_->file_);
}

void TeemoOpening::Run(void)
{
	NyaGraphic::Draw(gpx_, eOBJECT::BACK_MAP1);
}

void TeemoOpening::Delete(void)
{
	NyaGraphic::Delete(&gpx_->file_);
}
