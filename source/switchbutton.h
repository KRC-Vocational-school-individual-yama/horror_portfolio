#pragma once
class KeyState;

//�I���I�t�̐؂�ւ��p
class SwitchButton {
public:
	SwitchButton(int _key);
	~SwitchButton();
	void Update();
	bool Get() { return myflag; }
	void On() { myflag = true; }
	void Off() { myflag = false; }
private:
	int myKey;
	bool myflag;
	KeyState* key;
};