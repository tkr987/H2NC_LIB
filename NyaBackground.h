#pragma once


namespace H2NLIB
{
	// �w�i�摜�Ɣw�i���y�̊��N���X
	class NyaBackground
	{
	public:
		NyaBackground(){}
		virtual ~NyaBackground(){}
		virtual void Act(void){}
		virtual void Draw(void) = 0;
	};
}
