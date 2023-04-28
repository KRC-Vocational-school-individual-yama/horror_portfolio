#include "skybox.h"
#include"libs/scene.h"
#include"camera/camera.h"
#include"graphDraw.h"
#include"keystate.h"
#include"switchbutton.h"

namespace {
	static VECTOR fastPos = {1000,0,1000};
	static float radius = 100000;
	static const int FAST_DIV = 36;
	unsigned int color[] = {0xff0000,0x00ff00,0x0000ff};

	KeyState* key		=nullptr;
	KeyState* divminKey	=nullptr;
	SwitchButton* button=nullptr;
	SwitchButton* graph	=nullptr;
	
}

SkyBox::SkyBox(Scene* sc)
	:Object(sc)
	,sphereList()
	,divNum(FAST_DIV)
	,Light(-1)
{
	sphereList.clear();

	if(key==nullptr)
		key = new KeyState(KEY_INPUT_K);
	if (divminKey == nullptr)
		divminKey = new KeyState(KEY_INPUT_H);
	if (button == nullptr)
		button = new SwitchButton(KEY_INPUT_O);
	if (graph == nullptr)
		graph = new SwitchButton(KEY_INPUT_J);
}

SkyBox::~SkyBox() {
	DeleteLightHandle(Light);

	if (key			!= nullptr)
		delete key		,
		key		= nullptr;

	if (divminKey	!= nullptr)
		delete divminKey,
		divminKey	= nullptr;

	if (button		!= nullptr)
		delete button	,
		button		= nullptr;

	if (graph		!= nullptr)
		delete graph	,
		graph		= nullptr;
}

void SkyBox::Init(){
	//fastPos = VGet(0,0,0);
	button->On();
	graph->On();


	std::vector<VECTOR>radiusLine;
	radiusLine.reserve(360);

	//���a�̈��
	for (float i = 0; i < 361.f/2.f ; i+=180.f/(divNum)) {
		//float num= 360.f / divNum;
		
		//��
		float rad = DX_PI_F / 180 * (i/**num*/);
		MATRIX rotZ= MGetRotZ(rad);
		VECTOR ans = VTransform(VGet(0, radius,0),rotZ);
		
		
		//�ꖇ�G
		//VECTOR ans = VTransform(VGet(1,0,0),MGetTranslate(VGet(0,i*5,0)));
		
		radiusLine.emplace_back(ans);
	}
	radiusLine.shrink_to_fit();

	//sphereList.emplace_back(radiusLine);

	//������ƈ��
	for (int i = 0; i < divNum; i++) {
		float num = 360.f / divNum;
		float rad = DX_PI_F / 180 * (i * num);
		MATRIX rotY = MGetRotY(rad);
		
		std::vector<VECTOR>nextLine;
		nextLine.clear();
		
		for (VECTOR& vertex : radiusLine) {
			VECTOR vec= VTransform(vertex, rotY);
		
			//�ꖇ�G
			//VECTOR vec = VTransform(vertex,MGetTranslate(VGet(i*5*(180.f / (divNum)),0,0)));
			nextLine.emplace_back(vec);
		}
		sphereList.emplace_back(nextLine);
	}
	
	dispSphereList = sphereList;

	//�J�����̈ʒu
	Camera* cp= GetScene()->Invoke<Camera>();
	VECTOR cameraPos= cp->GetPos();
	
	//�J�����̏ꏊ�Ɉړ�
	for (std::vector<VECTOR>& vertexList : dispSphereList)
		for (VECTOR& ver : vertexList) {
			MATRIX move = MGetTranslate(cameraPos);
			ver = VTransform(ver, move);
		}


	////�C�ӂ̏ꏊ�Ɉړ�
	//for (std::vector<VECTOR>& vertexList : dispSphereList)
	//	for (VECTOR& ver : vertexList) {
	//		MATRIX move = MGetTranslate(fastPos);
	//		ver = VTransform(ver, move);
	//	}

	// // ���f���̏㑤�Ƀ|�C���g�^�C�v�̃��C�g���쐬
	//Light= CreateSpotLightHandle(
	//	cameraPos,
	//	VGet(0.0f, -1.0f, 0.0f),
	//	3600,
	//	DX_PI_F / 180*0,
	//	2000.0f,
	//	0.0f,
	//	0.001f,
	//	0.0f);
	//GetScene()->Create<GraphDraw>();
}

void SkyBox::Update() {
	GraphDraw* gp = GetScene()->Invoke<GraphDraw>();


	//Kkey�������ƈʒu��␳
	if (key->Get()) {
	
		Camera* cp = GetScene()->Invoke<Camera>();
		if (cp != nullptr) {
			VECTOR cameraPos = cp->GetPos();
			std::vector<std::vector<VECTOR>>ans;
	
			for (std::vector<VECTOR>& vertexList : sphereList) {
				std::vector<VECTOR>temp;
				for (VECTOR& ver : vertexList) {
					MATRIX move = MGetTranslate(cameraPos);
					temp.emplace_back(VTransform(ver, move));
				}
				ans.emplace_back(temp);
			}
			dispSphereList = ans;
			
		}

		if(gp !=nullptr)
			gp->Init();
	}

	//Hkey�@�������Ɓ@�������̑���
	if (divminKey->Down()) {
		sphereList.clear();
		dispSphereList.clear();
	
		if (CheckHitKey(KEY_INPUT_LSHIFT)) 
			divNum = min(divNum+1,360);		
		else 
			divNum = max(divNum-1,0);
	
		Init();
	}
	
	//Jkey	�������Ɓ@�O���t�̏o��
	if (graph->Get()) {
		if (gp==nullptr) {
		GraphDraw* gp=static_cast<GraphDraw*>(GetScene()->Create<GraphDraw>());
		GetScene()->ChangeDispRank(gp,50);
		}
	}
	else {
		if (gp != nullptr) {
			GetScene()->Destroy(gp);
		}
	}

	//�L�[�̍X�V
	key->Update();
	divminKey->Update();
	graph->Update();
	if(CheckHitKey(KEY_INPUT_RSHIFT))
		button->Update();


	if (CheckHitKey(KEY_INPUT_M)) {

	//��]�������������@�d��
	for (std::vector<VECTOR>& vertexList : sphereList)
	for (VECTOR& vertex:vertexList) {
		vertex = VTransform(vertex, MGetRotY(DX_PI_F / 180 * 0.01f));
	}
	dispSphereList = sphereList;
	}

}

void SkyBox::Draw(){
	//printfDx("Okey && RSHIFT ��������skybox�̃K�C�h���\���ؑ�\n");
	if (button->Get())return;

	//printfDx("skyBox divNum = %d",divNum);

	int count = 0;
	for(const std::vector<VECTOR>& vertexList: dispSphereList)
		for (const VECTOR& ver : vertexList) {
			DrawPixel3D(ver, color[count % 3]);
			count++;
		}

	for (const std::vector<VECTOR>& vertexList : dispSphereList)
	for (int i = 0; i < vertexList.size(); i++) {
		int index = i + 1;
		if (index >= vertexList.size())continue;

		DrawLine3D(vertexList.at(i), vertexList.at(index%vertexList.size()), color[i % 3]);
	}

	
}

void SkyBox::GetDivNum(int& x, int& y){
	x = dispSphereList.size();
	y = dispSphereList.at(0).size();

}