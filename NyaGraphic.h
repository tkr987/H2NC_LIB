#pragma once

#include <deque>
#include <string>
#include <vector>
#include "NyaDefine.h"



namespace H2NLIB {

	///////////////////////////////////
	// ‚±‚±‚©‚çƒpƒ‰ƒ[ƒ^İ’è—p\‘¢‘Ì
	///////////////////////////////////

	// DXLIB ’Êí•`‰æŠÖ”‚ğ—˜—p
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct GraphicPropertyX1 {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct GraphicPropertyX2 {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚ğ—˜—p
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	struct GraphicPropertyX3 {
		int file_div_;
		int file_id_;
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	struct GraphicPropertyX4 {
		int file_div_;
		int file_id_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚ğ—˜—p
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct GraphicPropertyX5 {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”III‚ğ—˜—p
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct GraphicPropertyX6 {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_ratex_;
		double extend_ratey_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ©—R•ÏŒ`•`‰æŠÖ”‚ğ—˜—p
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	struct GraphicPropertyX7 {
		int file_div_;
		int file_id_;
		int pos_x1_;
		int pos_x2_;
		int pos_x3_;
		int pos_x4_;
		int pos_y1_;
		int pos_y2_;
		int pos_y3_;
		int pos_y4_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB w’è‹éŒ`•`‰æŠÖ”‚ğ—˜—p
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	struct GraphicPropertyX8 {
		int file_div_;
		int file_id_;
		int pos_dx_;
		int pos_dy_;
		int pos_sx_;
		int pos_sy_;
		int val_width_;
		int val_height_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ’Êí•`‰æŠÖ”‚ğ—˜—p
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct GraphicPropertyX1b {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	struct GraphicPropertyX2b {
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚ğ—˜—p
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	struct GraphicPropertyX3b {
		int file_div_;
		int file_id_;
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚ğ—˜—p
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	struct GraphicPropertyX4b {
		int file_div_;
		int file_id_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::GROUP object_group_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚ğ—˜—p
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	struct GraphicPropertyX5b {
		int file_div_;
		int file_id_;
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
		eOBJECT::GROUP object_group_;
	};

	struct GraphicFileSet {
		int div_max_;
		int div_x_;
		int div_y_;
		int size_x_;
		int size_y_;
		std::string file_pass_;
		std::vector<int> div_vector_;
	};

	struct DrawDequeSet {
		std::deque<GraphicPropertyX1> gpx1_deque_;
		std::deque<GraphicPropertyX2> gpx2_deque_;
		std::deque<GraphicPropertyX3> gpx3_deque_;
		std::deque<GraphicPropertyX4> gpx4_deque_;
		std::deque<GraphicPropertyX5> gpx5_deque_;
		std::deque<GraphicPropertyX6> gpx6_deque_;
		std::deque<GraphicPropertyX7> gpx7_deque_;
		std::deque<GraphicPropertyX8> gpx8_deque_;
		std::deque<GraphicPropertyX1b> gpx1b_deque_;
		std::deque<GraphicPropertyX2b> gpx2b_deque_;
		std::deque<GraphicPropertyX3b> gpx3b_deque_;
		std::deque<GraphicPropertyX4b> gpx4b_deque_;
		std::deque<GraphicPropertyX5b> gpx5b_deque_;
	};

	class NyaGraphic {
	public:
		NyaGraphic();
		~NyaGraphic();
		void Draw(GraphicPropertyX1*);
		void Draw(GraphicPropertyX2*);
		void Draw(GraphicPropertyX3*);
		void Draw(GraphicPropertyX4*);
		int LoadFile(std::string file_pass);
		int LoadFile(int, int, int, int, std::string);
		void Run(void);
	private:
		int count_;
		int swing_x_;
		int swing_y_;
		void DrawAll(eOBJECT::GROUP, bool);
		static std::vector<GraphicFileSet> file_vector_;
		static std::vector<DrawDequeSet> layer_vector_;
	};

}
