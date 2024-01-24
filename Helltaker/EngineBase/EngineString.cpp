#include "EngineString.h"

EngineString::EngineString()
{}

EngineString::~EngineString()
{}

std::string EngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}