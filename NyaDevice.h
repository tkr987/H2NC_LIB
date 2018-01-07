#pragma once

#include <list>
#include "NyaDefine.h"

using namespace std;


namespace H2NLIB {


	// 弾オブジェクトを生成するクラス

	struct ShotToken {

		//未完成

		//bool hit_effect_;
		//double img_angle_;
		//int img_id_;
		//double img_rotate_;
		//double plus_x_;
		//double plus_y_;
		//double pos_range_;
		//int wait_frames_;
		//EffectParam1 *eparam_;
		//PosParam1 *pparam_;
	};

	struct DevicePropertyX {
		double img_angle_;						//!< 画像角度(ラジアン, 初期値0)
		int img_id_;							//!< 画像ID(初期値不定)
		double img_rotate_;						//!< 画像回転角度(初期値0)
		double shot_angle_;						//!< 角度(初期値不定)
		double shot_pow_;						//!< 攻撃力(初期値0)
		double shot_range_;						//!< 当たり判定の範囲(初期値0)
		double shot_speed_;						//!< 速度(初期値不定)
		unsigned int shot_wait_;				//!< 待機フレーム数(初期値0)
		double shot_x_;							//!< 生成x座標(初期値不定)
		double shot_y_;							//!< 生成y座標(初期値不定)
		bool hit_effect_;						//!< ヒットエフェクト(true = on, false = off, 初期値false)
		int hit_effect_img_divmax_;				//!< ヒットエフェクト画像分割最大値(初期値不定)
		int hit_effect_img_divmin_;				//!< ヒットエフェクト画像分割最小値(初期値0)
		int hit_effect_img_id_;					//!< ヒットエフェクト画像ID(初期値不定)
		int hit_effect_img_interval_;			//!< ヒットエフェクト画像切り替えインターバル時間(初期値不定)
		double hit_effect_img_extend_rate_;		//!< ヒットエフェクト画像拡大率(初期値1.0倍)
		DevicePropertyX(){
			img_angle_ = 0.0;
			img_rotate_ = 0.0;
			shot_pow_ = 0.0;
			shot_range_ = 0.0;
			shot_wait_ = 0;
			hit_effect_ = false;
			hit_effect_img_divmin_ = 0;
			hit_effect_img_extend_rate_ = 1.0;
		}
	};

	class Device {
	public:
		Device();
		~Device();
		void Run(void);
	private:
		static std::list<ShotToken> list_unused_;
		static std::list<ShotToken> list_used_[eOBJECT::GROUP::sizeof_enum];
		static std::list<ShotToken> list_wait_[eOBJECT::GROUP::sizeof_enum];
		int UserAttack(DevicePropertyX *dpx);
	};

}
