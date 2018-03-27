#pragma once

#include <deque>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include "NyaDefine.h"


namespace H2NLIB
{
	class GraphicFile 
	{
	public:
		int div_total_;
		std::vector<int> div_vector_;
		int div_x_;
		int div_y_;
		std::string pass_;
		GraphicFile& operator=(const GraphicFile& file)
		{
			div_total_ = file.div_total_;
			std::copy(file.div_vector_.begin(), file.div_vector_.end(), back_inserter(div_vector_));
			div_x_ = file.div_x_;
			div_y_ = file.div_y_;
			pass_ = file.pass_;
			return *this;
		}
	};

	// **********************
	// graphic property
	// **********************

	// DXLIB ’Êí•`‰æŠÖ”‚É‘Î‰
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicProperty1 
	{
	public:
		int draw_grid_x_;
		int draw_grid_y_;
		int file_div_;
		bool flag_trans_;
		GraphicFile graphic_file_;
		GraphicProperty1()
		{
			file_div_ = 0;
			flag_trans_ = true;
		}
		GraphicProperty1& operator=(const GraphicProperty1& gp)
		{
			draw_grid_x_ = gp.draw_grid_x_;
			draw_grid_y_ = gp.draw_grid_y_;
			file_div_ = gp.file_div_;
			graphic_file_ = gp.graphic_file_;
			flag_trans_ = gp.flag_trans_;
			return *this;
		}
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚É‘Î‰
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicProperty2 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int draw_grid_x_;
		int draw_grid_y_;
		bool flag_trans_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚É‘Î‰
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicProperty3 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int draw_grid_x1_;
		int draw_grid_y1_;
		int draw_grid_x2_;
		int draw_grid_y2_;
		bool flag_trans_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚É‘Î‰
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicProperty4 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int draw_grid_cx_;
		int draw_grid_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		GraphicProperty4()
		{
			file_div_ = 0;
			draw_angle_ = 0;
			extend_rate_ = 1.0;
			flag_turn_ = false;
			flag_trans_ = true;
		}
		GraphicProperty4& operator=(const GraphicProperty4& gpx4)
		{
			graphic_file_ = gpx4.graphic_file_;
			file_div_ = gpx4.file_div_;
			draw_grid_cx_ = gpx4.draw_grid_cx_;
			draw_grid_cy_ = gpx4.draw_grid_cy_;
			draw_angle_ = gpx4.draw_angle_;
			extend_rate_ = gpx4.extend_rate_;
			flag_turn_ = gpx4.flag_turn_;
			flag_trans_ = gpx4.flag_trans_;
			return *this;
		}

	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚É‘Î‰
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty5 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”III‚É‘Î‰
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty6 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_ratex_;
		double extend_ratey_;
		bool flag_turn_;
		bool flag_trans_;
	};

	// DXLIB ©—R•ÏŒ`•`‰æŠÖ”‚É‘Î‰
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicProperty7 
	{
	public:
		GraphicFile graphic_file_;
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
	};

	// DXLIB w’è‹éŒ`•`‰æŠÖ”‚É‘Î‰
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty8 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_dx_;
		int pos_dy_;
		int pos_sx_;
		int pos_sy_;
		int val_width_;
		int val_height_;
		bool flag_turn_;
		bool flag_trans_;
	};

	// DXLIB ’Êí•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicProperty1b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
	};

	// DXLIB LR”½“]•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawTurnGraph( int x, int y, int GrHandle, int TransFlag ) ;
	class GraphicProperty2b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_x_;
		int pos_y_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
	};

	// DXLIB Šg‘åk¬•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawExtendGraph( int x1, int y1, int x2, int y2, int GrHandle , int TransFlag ) ;
	class GraphicProperty3b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_x1_;
		int pos_y1_;
		int pos_x2_;
		int pos_y2_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph( int x, int y, double ExtRate, double Angle, int GrHandle , int TransFlag , int TurnFlag ) ;
	class GraphicProperty4b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
		int pos_cx_;
		int pos_cy_;
		double draw_angle_;
		double extend_rate_;
		bool flag_turn_;
		bool flag_trans_;
		int blend_alpha_;
		int blend_mode_;
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”II‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph2( int x, int y, int cx, int cy, double ExtRate, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty5b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
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
	};

	// DXLIB ‰ñ“]•`‰æŠÖ”III‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRotaGraph3(int x, int y,int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty6b 
	{
	public:
		GraphicFile graphic_file_;
		int file_div_;
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
	};

	// DXLIB ©—R•ÏŒ`•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawModiGraph( int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle , int TransFlag );
	class GraphicProperty7b 
	{
	public:
		GraphicFile graphic_file_;
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

	// DXLIB w’è‹éŒ`•`‰æŠÖ”‚É‘Î‰
	// int SetDrawBlendMode( int BlendMode , int Pal ) ;
	// int DrawRectGraph( int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GraphHandle, int TransFlag, int TurnFlag ) ;
	class GraphicProperty8b 
	{
	public:
		GraphicFile graphic_file_;
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

	class DrawDequeSet {
	public:
		std::deque<GraphicProperty1> gp1_deque_;
		std::deque<GraphicProperty2> gpx2_deque_;
		std::deque<GraphicProperty3> gpx3_deque_;
		std::deque<GraphicProperty4> gpx4_deque_;
		std::deque<GraphicProperty5> gpx5_deque_;
		std::deque<GraphicProperty6> gpx6_deque_;
		std::deque<GraphicProperty7> gpx7_deque_;
		std::deque<GraphicProperty8> gpx8_deque_;
		std::deque<GraphicProperty1b> gpx1b_deque_;
		std::deque<GraphicProperty2b> gpx2b_deque_;
		std::deque<GraphicProperty3b> gpx3b_deque_;
		std::deque<GraphicProperty4b> gpx4b_deque_;
		std::deque<GraphicProperty5b> gpx5b_deque_;
		std::deque<GraphicProperty6b> gpx6b_deque_;
		std::deque<GraphicProperty7b> gpx7b_deque_;
		std::deque<GraphicProperty8b> gpx8b_deque_;
	};

	class NyaGraphic {
	public:
		NyaGraphic();
		~NyaGraphic();
		void DeleteGraphicFile(GraphicFile file);
		void Draw(GraphicProperty1* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty2* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty3* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty4* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty5* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty6* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty1b* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty2b* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty3b* gp, eOBJECT::NUM layer);
		void Draw(GraphicProperty4b* gp, eOBJECT::NUM layer);
		void LoadGraphicFile(std::string file_pass, GraphicFile* file);
		void LoadGraphicFile(int div_x, int div_y, std::string file_pass, GraphicFile* file);
		void Run(void);
	private:
		static int swing_x_;
		static int swing_y_;
		static std::list<GraphicFile> file_list_;
		static std::vector<DrawDequeSet> layer_vector_;
		static std::vector<bool> swing_vector_;
		void DrawAll(eOBJECT::NUM layer, int swing_x, int swing_y);
		double RadToAngle(double x) { return (x * 180.0 / 3.14159265359); }
		double AngleToRad(double x) { return (x * 3.14159265359 / 180.0); }
	};

}
