#include"app.h"

#include<DxLib.h>

#include"config.h"
#include"../libs/scenemanager.h"

namespace APP {
	void Init() {
		SceneManager::Init();
	}
	void Update() {
		SceneManager::Update();
	}
	void Draw() {
		SceneManager::Draw();
	}
	void Delete() {
		SceneManager::Delete();
	}

	bool GameEnd() {
		if (SceneManager::GameEnd()) 
			return true;
		return false;
	}
}
