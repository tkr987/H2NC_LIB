#pragma once


namespace H2NLIB
{
	enum class eEVENT;

	// �w�i�摜�Ɣw�i���y�̊��N���X
	class NyaBackground
	{
	public:
		NyaBackground(){}
		virtual ~NyaBackground(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(const eEVENT check_event);
	};
}
