#include "NyaEnum.h"

using namespace H2NLIB;

// ‚È‚º‚©using namespace‚ª‹@”\‚µ‚È‚¢
eOBJECT& H2NLIB::operator++(eOBJECT& enum_object)
{
	if (enum_object != eOBJECT::sizeof_enum)
		enum_object = static_cast<eOBJECT>(static_cast<int>(enum_object) + 1);
		
	return enum_object;
}

eSKILL& H2NLIB::operator++(eSKILL& enum_skill)
{
	if (enum_skill != eSKILL::sizeof_enum)
		enum_skill = static_cast<eSKILL>(static_cast<int>(enum_skill) + 1);
		
	return enum_skill;
}

