#pragma once


namespace HNLIB
{
	enum class eEVENT;

	// �w�i�摜�Ɣw�i���y�̊��N���X
	class NyaBack
	{
	public:
		NyaBack(){}
		virtual ~NyaBack(){}
		virtual void Act(void) = 0;
		virtual void Draw(void) = 0;
		void Run(const eEVENT check_event);
	};
}
