#pragma once
#include<DxLib.h>

class KeyState {
public:
	KeyState(int key);
	bool Down();//�������u��
	bool Up();//�������u��
	bool Get();//���

	void Update();//�g��Update���̉��̕��ɒu���Ă�������
private:
	int myKey;
	bool keystop;
};