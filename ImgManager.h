#pragma once

#include <vector>
#include <deque>
#include "DefineNH.h"

namespace NH2 {

	namespace eIMG {
		enum DRAW {
			TYPE1, TYPE2, TYPE3, TYPE4, TYPE5, TYPE6, TYPE7, TYPE8,
			TYPE1B, TYPE2B, TYPE3B, TYPE4B, TYPE5B, TYPE6B, TYPE7B, TYPE8B,
		};
		enum RET { OK, OUT_OF_RANGE, STILL_USED };
	};


	///////////////////////////////////
	// ‚±‚±‚©‚çƒpƒ‰ƒ[ƒ^İ’è—p\‘¢‘Ì
	///////////////////////////////////

	// DXLIB ’Êí•`‰æŠÖ”‚ğ—˜—p
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct ImgParam1 {
		int x_;
		int y_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct ImgParam2 {
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚ğ—˜—p
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	struct ImgParam3 {
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	struct ImgParam4 {
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚ğ—˜—p
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct ImgParam5 {
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”III‚ğ—˜—p
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct ImgParam6 {
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_ratex_;
		double extend_ratey_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ©—R•ÏŒ`•`‰æŠÖ”‚ğ—˜—p
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	struct ImgParam7 {
		int pos_x1_;
		int pos_x2_;
		int pos_x3_;
		int pos_x4_;
		int pos_y1_;
		int pos_y2_;
		int pos_y3_;
		int pos_y4_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB w’è‹éŒ`•`‰æŠÖ”‚ğ—˜—p
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	struct ImgParam8 {
		int pos_dx_;
		int pos_dy_;
		int pos_sx_;
		int pos_sy_;
		int val_width_;
		int val_height_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ’Êí•`‰æŠÖ”‚ğ—˜—p
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct ImgParam1b {
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct ImgParam2b {
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚ğ—˜—p
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	struct ImgParam3b {
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	struct ImgParam4b {
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP group_type_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚ğ—˜—p
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct ImgParam5b {
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP group_type_;
	};

	struct ImgToken {
		eIMG::DRAW draw_type_;
		unsigned int id_;
		unsigned int div_;
		ImgParam1 param1_;
		ImgParam2 param2_;
		ImgParam3 param3_;
		ImgParam4 param4_;
		ImgParam5 param5_;
		ImgParam6 param6_;
		ImgParam7 param7_;
		ImgParam8 param8_;
		ImgParam1b param1b_;
		ImgParam2b param2b_;
		ImgParam3b param3b_;
		ImgParam4b param4b_;
		ImgParam5b param5b_;
	};

	struct ImgLoad {
		int xnum_;
		int ynum_;
		int xsize_;
		int ysize_;
		int divmax_;
		int file_[64];
		std::string filename_;
	};

	class ImgManager {
	public:
		ImgManager() {}
		virtual ~ImgManager() {}
		// ‰Šú‰»ŠÖ˜A
		static void Clear(void);
		static void End(void);
		static void Init(void);
		// ‰æ‘œ“Ç‚İ‚İŠÖ”
		static int LoadImg(std::string filename);
		static int LoadImg(int xnum, int ynum, int xsize, int ysize, std::string filename);
		// •`‰æŠÖ”
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam1 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam2 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam3 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam4 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam5 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam6 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam7 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam8 *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam1b *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam2b *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam3b *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam4b *);
		static void Draw(unsigned int imgfile_id, unsigned int imgfile_div, ImgParam5b *);
		// ‚»‚Ì‘¼
		static int GetDivMax(unsigned int id) { return vec_iload_[id].divmax_; }
		static bool SwingX(unsigned int scale, unsigned int time);
		static bool SwingY(unsigned int scale, unsigned int time);
		eIMG::RET CheckFileTableRange(unsigned int id);
		eIMG::RET CheckTokenTableRange(eOBJECT::GROUP group, long id);
	protected:
		static unsigned int id_draw_[eOBJECT::GROUP::sizeof_enum];		// ImgManager::Draw()‚ğŒÄ‚Ño‚·‚Æ+1, ImgUpdate::Run()‚Å0‚ÉƒNƒŠƒA‚³‚ê‚é
		static unsigned int id_load_;									// ImgManager::LoadImg()‚ğŒÄ‚Ño‚·‚Æ+1‚³‚ê‚é
		static int swing_scale_y_;
		static int swing_time_y_;
		// ƒ[ƒh‚³‚ê‚½‰æ‘œ‚ğŠi”[‚µ‚Ä‚¨‚­”z—ñ
		static std::vector<ImgLoad> vec_iload_;
//		static unsigned int itoken_size_[eOBJECT::GROUP::sizeof_enum];
		// Imgƒg[ƒNƒ“ŠÖ˜A
		static std::vector<ImgToken> vec_itoken_[eOBJECT::GROUP::sizeof_enum];			// Imgƒg[ƒNƒ“‚ğŠi”[‚·‚é”z—ñ
		// •Ö—˜‚»‚¤‚ÈŠÖ”
		static double CalcAngle(double x) { return (x * 180.0 / 3.1415); }
		static double CalcRAD(double x) { return (x * 3.1415 / 180.0); }
	};

}
