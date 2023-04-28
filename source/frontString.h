#pragma once
#include"libs/object.h"

/// <summary>
/// ��ʂɕ������ʂ��N���X
/// ��{�I�ɕ`��D����Ō���ɂ���
/// </summary>
class FrontString :public Object {
public:
	FrontString(Scene* sc);
	~FrontString()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void DrawFrontString(int x,int y,std::string str,unsigned int col);
	void DrawCreateFont(int x,int y,std::string str,unsigned int col, char* fontName=NULL, int size=-1, int thick=-1, int fontType= DX_FONTTYPE_NORMAL);
	void DeleteFont(std::string str);
private:
	struct StrTemple {
		unsigned int color=0;
		int font;
		int x=0, y=0;
		std::string string="";

		StrTemple():font(-1) 
		{
			string.clear();
		}
	};

	std::list<StrTemple>fontList;


public:
	StrTemple GetFont(std::string str) {
		for (StrTemple& temp : fontList) {
			if (temp.string != str)continue;
			return temp;
		}
		
		return StrTemple();
	}

};