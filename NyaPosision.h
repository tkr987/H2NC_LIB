#pragma once

namespace H2NLIB {

	// ****************************************************
	//  class PosToken
	//  ���ۂ̍��W�f�[�^���i�[�����N���X
	//  class PosManager �� Postoken �f�[�^�W�����Ǘ�����
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