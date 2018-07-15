#include "NyaGraphic.h"
#include "NyaBack.h"
#include "TeemoEnum.h"

namespace HNLIB
{
	class GraphicPropertyX1;
}

class TeemoBack3 : public HNLIB::NyaBack
{
public:
	TeemoBack3();
	~TeemoBack3();
private:
	HNLIB::GraphicPropertyX1* gpx_;
	void Act(void);
	void Draw(void);
};

