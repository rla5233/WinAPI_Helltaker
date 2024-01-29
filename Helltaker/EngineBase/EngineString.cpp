#include "EngineString.h"

UEngineString::UEngineString()
{}

UEngineString::~UEngineString()
{}

std::string UEngineString::ToUpper(std::string_view View)
{
	std::string Name = View.data();

	for (char& _Ch : Name)
	{
		_Ch = std::toupper(_Ch);
	}

	return Name;
}