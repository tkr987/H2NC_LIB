#pragma once


namespace H2NLIB {

	class NyaGraphic;
	class NyaPosition;
	struct PositionPropertyX;

	class NyaUser {
	public:
		NyaUser();
		~NyaUser();
		void Run(void);
	private:
		NyaPosition *nya_position_;
		PositionPropertyX* ppx;
	};

}