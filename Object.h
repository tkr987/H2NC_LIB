#ifndef __OBJECT__
#define __OBJECT__

#include <string>
#include "DefineNH.h"

namespace NH2 {
	struct ImgParam4;
	class PosParam1;
}

namespace NH2 {

	class Object {
	public:
		Object(void);
		~Object(void);
		double Collision(double extension, PosParam1 *pparam);
		void CollisionImg(int imgfile, int imgdiv, int interval, PosParam1 *pparam, ImgParam4 *iparam);
		void CollisionSound(int soundfile, int interval, PosParam1 *pparam);
		void Draw(unsigned int imgfile, unsigned int imgdiv, PosParam1 *pparam, ImgParam4 *iparam);
		void GetPos(int *x, int *y, PosParam1 *pparam);
		void GetPos(double *x, double *y, PosParam1 *pparam);
		bool InsideDisplayWindow(double extension, PosParam1 *pparam);
	private:
		int collision_interval_img_;
		int collision_interval_sound_;
	};

}

#endif
