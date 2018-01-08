#pragma once

namespace H2NLIB {

	// ****************************************************
	//  class PosToken
	//  実際の座標データが格納されるクラス
	//  class PosManager は Postoken データ集合を管理する
	// ****************************************************
	struct PosToken {
		bool flag_collision_;
		double hit_;
		double move_x_;
		double move_y_;
		double pow_;
		double range_;
		double x_;
		double y_;
	};


	class NyaPosision
	{
	public:
		NyaPosision();
		~NyaPosision();
	};

}