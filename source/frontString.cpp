#include "frontString.h"

namespace {

}

FrontString::FrontString(Scene* sc)
	:Object(sc)
{
}

FrontString::~FrontString(){
	for(StrTemple& temp:fontList)
	if(temp.font>0)
		DeleteFontToHandle(temp.font);
}

void FrontString::Init(){
	fontList.clear();
	
	//DrawCreateFont(SCREEN_WIDTH / 3 * 2, SCREEN_HEIGHT / 2, "frontString‚ÌƒeƒXƒg", 0xffffff, NULL, 64, -1);
}

void FrontString::Update(){

}

void FrontString::Draw(){
	for (StrTemple& disp : fontList) {
		DrawStringToHandle(disp.x,disp.y,disp.string.c_str(),disp.color,disp.font,0x0);
	}
}

void FrontString::DrawFrontString(int x, int y, std::string str, unsigned int col){
	StrTemple in;
	in.x = x;
	in.y = y;
	in.string = str;
	in.color = col;
	fontList.emplace_back(in);
}

void FrontString::DrawCreateFont(int x, int y, std::string str, unsigned int col, char* fontName, int size, int thick, int fontType){
	StrTemple in;
	in.x = x;
	in.y = y;
	in.string = str;
	in.color = col;
	in.font= CreateFontToHandle(fontName,size,thick,fontType);
	fontList.emplace_back(in);
}

void FrontString::DeleteFont(std::string str){
	for (auto it = fontList.begin(); it != fontList.end();) {
		StrTemple& temp = *it;

		if (str != temp.string) {
			it++;
			continue;
		}

		if (temp.font > 0) {
			DeleteFontToHandle(temp.font);
		}
			it=fontList.erase(it);
	}
}
