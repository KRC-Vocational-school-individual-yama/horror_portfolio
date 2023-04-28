#pragma once

#include"myDxLib.h"
class Scene;


class Transform {
public:
	VECTOR position;
	VECTOR velocity;
	VECTOR rotation;
	VECTOR scale;
	MATRIX matrix;
	Transform()
		:position(VGet(0, 0, 0))
		, velocity(VGet(0, 0, 0))
		, rotation(VGet(0, 0, 0))
		, scale(VGet(1, 1, 1))
		, matrix(MGetIdent())
	{}
	void MakeMatrix() {
		matrix = MGetScale(scale);
		matrix = MMult(matrix, MGetRotX(rotation.x));
		matrix = MMult(matrix, MGetRotZ(rotation.z));
		matrix = MMult(matrix, MGetRotY(rotation.y));
		matrix = MMult(matrix, MGetTranslate(position));
	}
};

class Object {
public:
	Object(Scene* sc)
		:myScene	(sc) 
		,myDestroy	(false)
	{}
	virtual ~Object()		=default;
	virtual void Init()		=0;
	virtual void Update()	=0;
	virtual void Draw()		=0;


	/// <summary>
	/// 所属シーン取得
	/// </summary>
	/// <returns></returns>
	Scene* GetScene()			{ return myScene	;}

	/// <summary>
	/// 破棄フラグ　ゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetDestroy()		{ return myDestroy	;}

	/// <summary>
	/// 破棄フラグ　セッター
	/// </summary>
	/// <param name="_flag"></param>
	void MyDestroy()			{ myDestroy = true	;}

	/// <summary>
	/// Invokeの際  nullptr チェック用
	/// </summary>
	/// <typeparam name="C"></typeparam>
	/// <param name="true	">inClass</param>
	/// <param name="false	">nullptr</param>
	/// <returns></returns>
	template<class C>
	bool CheckClass();
private:
	Scene* myScene	;//所属シーン
	bool myDestroy	;//破棄フラグ
};

template<class C>
bool Object::CheckClass(){
	if (GetScene()->Invoke<C>() != nullptr)
		return true;

	return false;
};

