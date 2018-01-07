#ifndef __TARGET__
#define __TARGET__

#include "DefineNH.h"

namespace NH2 {
	struct ImgParam4;
	struct PosParam;
}

namespace NH2T {

	class Target {
	public:
		Target(double x, double y, double range);
		~Target(void);
		double Collision(double extension);
		void CollisionImg(int imgfile, int imgdiv, int interval);
		void CollisionSound(int soundfile, int interval);
		void DeleteData(double add_alv);
		void DeleteData(double add_alv, double add_rank);
		void DeleteData(double add_alv, double add_exarms, double add_rank, long add_score);
		void Draw(unsigned int imgfile, double angle);
		void Draw(unsigned int imgfile, unsigned int imgdiv, double angle);
		void Draw(unsigned int imgfile, unsigned int imgdiv, double exrate, double angle);
		double GetAtan(eOBJECT::GROUP group, std::string name, double angle = 0.0);
		void GetPos(int *x, int *y);
		void GetPos(double *x, double *y);
		bool InsidePanel(double extension = 0);
		void MoveA(double *px, double *py);
		void MoveB(double angle, double dist);
		void SetGroup(eOBJECT::GROUP group);
		void SetPos(double *x, double *y);
	private:
		int collision_interval_img_;
		int collision_interval_sound_;
		unsigned int posid_;
		double hit_;
		NH2::ImgParam4* iparam_;
		NH2::ImgParam4* iparam_collision_;
		NH2::PosParam1* pparam_;
		Target(void) {}
		double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
		double CalcAngle(double x) { return (x * 180.0) / 3.1415; }
	};

}

#endif
