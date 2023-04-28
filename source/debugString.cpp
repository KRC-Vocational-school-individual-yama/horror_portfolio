#include "debugString.h"

DebugString::DebugString(Scene* sc)
	:Object(sc)
{
	strings.clear();
}

DebugString::~DebugString()
{
}

void DebugString::Init()
{
}

void DebugString::Update()
{
}

void DebugString::Draw()
{
	for(const StringParam& str:strings)
		DrawString(SCREEN_WIDTH/3*2,0+str.number*96,str.str.c_str(),str.color);
}

void DebugString::SetString(std::string _str, unsigned int _col){

	StringParam param;

	param.str = _str;
	param.color = _col;
	if( !strings.empty())
		param.number = strings.back().number+1;

	strings.emplace_back(param);
}
