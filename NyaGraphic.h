#pragma once

#include <array>
#include <deque>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include "NyaEnum.h"


namespace HNLIB
{

	class GraphicFile 
	{	// 画像ファイル構造体
	public:
		std::vector<int> div_collection_;
		int div_total_;
		int div_x_;
		int div_y_;
		std::string pass_;
		int size_x_;
		int size_y_;
	};

	//*********************************
	// ここからgraphic propertyの定義
	//*********************************

	// DXLIB 通常描画関数に対応
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX1 
	{
	public:
		double draw_grid_x_;
		double draw_grid_y_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		GraphicPropertyX1();
	};

	// DXLIB LR反転描画関数に対応
	// int DXLIB::DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ; に対応
	class GraphicPropertyX2 
	{
	public:
		double draw_grid_x_;
		double draw_grid_y_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		GraphicPropertyX2();
	};

	// DXLIB 拡大縮小描画関数に対応
	// int DXLIB::DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicPropertyX3 
	{
	public:
		double draw_grid_x1_;
		double draw_grid_x2_;
		double draw_grid_y1_;
		double draw_grid_y2_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		GraphicPropertyX3();
	};

	// DXLIB 回転描画関数に対応
	// int DXLIB::DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicPropertyX4 
	{
	public:
		double draw_angle_deg_;
		double draw_grid_cx_;
		double draw_grid_cy_;
		double extend_rate_;
		GraphicFile file_;
		int file_div_;
		bool flag_turn_;
		bool flag_trans_;
		GraphicPropertyX4();
	};

	// DXLIB 回転描画関数IIに対応
	// int DXLIB::DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX5 
	{
	public:
		double draw_grid_x_;
		double draw_grid_y_;
		double draw_grid_cx_;
		double draw_grid_cy_;
		double draw_angle_deg_;
		double extend_rate_;
		GraphicFile file_;
		int file_div_;
		bool flag_turn_;
		bool flag_trans_;
		GraphicPropertyX5();
	};

	// DXLIB 回転描画関数IIIに対応
	// int DXLIB::DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX6
	{
	public:
		double draw_grid_x_;
		double draw_grid_y_;
		double draw_grid_cx_;
		double draw_grid_cy_;
		double draw_angle_deg_;
		double extend_ratex_;
		double extend_ratey_;
		GraphicFile file_;
		int file_div_;
		bool flag_turn_;
		bool flag_trans_;
		GraphicPropertyX6();
	};

	// DXLIB 自由変形描画関数に対応
	// int DXLIB::DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicPropertyX7 
	{
	public:
		double draw_grid_x1_;
		double draw_grid_x2_;
		double draw_grid_x3_;
		double draw_grid_x4_;
		double draw_grid_y1_;
		double draw_grid_y2_;
		double draw_grid_y3_;
		double draw_grid_y4_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		GraphicPropertyX7();
	};

	// DXLIB 指定矩形描画関数に対応
	// int DXLIB::DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX8 
	{
	public:
		double draw_grid_dx_;
		double draw_grid_dy_;
		double draw_grid_sx_;
		double draw_grid_sy_;
		GraphicFile file_;
		int file_div_;
		bool flag_turn_;
		bool flag_trans_;
		int size_width_;
		int size_height_;
		GraphicPropertyX8();
	};

	// DXLIB 通常描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX1b 
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		GraphicPropertyX1b();
	};

	// DXLIB LR反転描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicPropertyX2b 
	{
	public:
		int blend_alpha_;
		int blend_mode_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		int grid_x_;
		int grid_y_;
		GraphicPropertyX2b();
	};

	// DXLIB 拡大縮小描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicPropertyX3b 
	{
	public:
		int blend_alpha_;
		int blend_mode_;
		GraphicFile file_;
		int file_div_;
		bool flag_trans_;
		int grid_x1_;
		int grid_y1_;
		int grid_x2_;
		int grid_y2_;
		GraphicPropertyX3b();
	};

	// DXLIB 回転描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicPropertyX4b 
	{
	public:
		int blend_alpha_;
		int blend_mode_;
		double draw_angle_deg_;
		double extend_rate_;
		GraphicFile file_;
		bool flag_turn_;
		bool flag_trans_;
		int file_div_;
		int grid_cx_;
		int grid_cy_;
		GraphicPropertyX4b();
	};

	// DXLIB 回転描画関数IIに対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX5b 
	{
	public:
		GraphicFile file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_deg_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
		GraphicPropertyX5b();
	};

	// DXLIB 回転描画関数IIIに対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX6b 
	{
	public:
		GraphicFile file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_deg_;
		double extend_ratex_;
		double extend_ratey_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
	};

	// DXLIB 自由変形描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicPropertyX7b 
	{
	public:
		GraphicFile file_;
		int file_div_;
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
	};

	// DXLIB 指定矩形描画関数に対応
	// int DXLIB::SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DXLIB::DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicPropertyX8b 
	{
	public:
		GraphicFile file_;
		int file_div_;
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
	};

	class GraphicDrawSet {
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
		void Clear(void)
		{
			gpx1_deque_.clear();
			gpx2_deque_.clear();
			gpx3_deque_.clear();
			gpx4_deque_.clear();
			gpx5_deque_.clear();
			gpx6_deque_.clear();
			gpx7_deque_.clear();
			gpx8_deque_.clear();
			gpx1b_deque_.clear();
			gpx2b_deque_.clear();
			gpx3b_deque_.clear();
			gpx4b_deque_.clear();
			gpx5b_deque_.clear();
			gpx6b_deque_.clear();
			gpx7b_deque_.clear();
			gpx8b_deque_.clear();
		}
	};

	class GraphicSwing
	{	// 振動を表現するクラス
	public:
		unsigned int count_;
		int grid_x_;
		GraphicSwing();
	};

	class NyaGraphic {
	public:
		NyaGraphic();
		~NyaGraphic();
		static void Clear(void);
		static void Delete(GraphicFile* file);
		static void Draw(const GraphicPropertyX1* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX2* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX3* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX4* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX5* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX6* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX7* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX8* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX1b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX2b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX3b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX4b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX5b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX6b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX7b* gpx, eOBJECT layer);
		static void Draw(const GraphicPropertyX8b* gpx, eOBJECT layer);
		static void Init(void);
		static void Load(std::string file_pass, GraphicFile* file);
		static void Load(int div_x, int div_y, std::string file_pass, GraphicFile* file);
		static void Run(void);
		static void Swing(void);
	private:
		static std::list<GraphicFile> file_collection_;
		static std::array<GraphicDrawSet, static_cast<int>(eOBJECT::sizeof_enum)> layer_collection_;
		static GraphicSwing swing_;
		static void CalculateSwing(void);
		static void DrawAll(eOBJECT layer);
	};

}
