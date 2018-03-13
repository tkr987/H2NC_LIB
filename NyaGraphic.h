#pragma once

#include <deque>
#include <string>
#include <vector>
#include "NyaDefine.h"



namespace H2NLIB
{
	///////////////////////////////////
	// ここからパラメータ設定用構造体
	///////////////////////////////////

	// DXLIB 通常描画関数に対応
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX1 {
	public:
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB LR反転描画関数に対応
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX2 {
	public:
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 拡大縮小描画関数に対応
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicPropertyX3 {
	public:
		int file_div_;
		int file_id_;
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 回転描画関数に対応
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicPropertyX4 {
	public:
		int file_div_;
		int file_id_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		eOBJECT::NUM object_group_;
		~GraphicPropertyX4(){}
	};

	// DXLIB 回転描画関数IIに対応
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX5 {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 回転描画関数IIIに対応
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX6 {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 自由変形描画関数に対応
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicPropertyX7 {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 指定矩形描画関数に対応
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX8 {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 通常描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX1b {
	public:
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB LR反転描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX2b {
	public:
		int file_div_;
		int file_id_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 拡大縮小描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicPropertyX3b {
	public:
		int file_div_;
		int file_id_;
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 回転描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicPropertyX4b {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 回転描画関数IIに対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX5b {
	public:
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
		eOBJECT::NUM object_group_;
	};

	// DXLIB 回転描画関数IIIに対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX6b {
	public:
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
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 自由変形描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicPropertyX7b {
	public:
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
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	// DXLIB 指定矩形描画関数に対応
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX8b {
	public:
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
		int blend_alpha_;
		int blend_mode_;
		eOBJECT::NUM object_group_;
	};

	class GraphicFileSet {
	public:
		int div_max_;
		int div_x_;
		int div_y_;
		int size_x_;
		int size_y_;
		std::string file_pass_;
		std::vector<int> div_vector_;
	};

	class DrawDequeSet {
	public:
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
		std::deque<GraphicPropertyX6b> gpx6b_deque_;
		std::deque<GraphicPropertyX7b> gpx7b_deque_;
		std::deque<GraphicPropertyX8b> gpx8b_deque_;
	};

	class NyaGraphic {
	public:
		NyaGraphic();
		~NyaGraphic();
		void Draw(GraphicPropertyX1* gpx);
		void Draw(GraphicPropertyX2* gpx);
		void Draw(GraphicPropertyX3* gpx);
		void Draw(GraphicPropertyX4* gpx);
		void Draw(GraphicPropertyX5* gpx);
		void Draw(GraphicPropertyX6* gpx);
		void Draw(GraphicPropertyX1b* gpx);
		void Draw(GraphicPropertyX2b* gpx);
		int LoadFile(std::string file_pass);
		int LoadFile(int div_x, int div_y, std::string file_pass);
		void Run(void);
	private:
		static int swing_x_;
		static int swing_y_;
		static std::vector<GraphicFileSet> file_vector_;
		static std::vector<DrawDequeSet> layer_vector_;
		static std::vector<bool> swing_vector_;
		void DrawAll(eOBJECT::NUM layer, int swing_x, int swing_y);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159); }
		double AngleToRad(double x) { return (x * 3.14159 / 180.0); }
	};

}
