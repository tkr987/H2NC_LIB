#pragma once

class Stage
{
public:
	Stage();
	~Stage();
	virtual void Load(int lv, int rand, long frame = 0) = 0;
	virtual void Run(void) = 0;
protected:
	long frame_;
	int phase_;
};

