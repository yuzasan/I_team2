#include "Title.h"
#include "../Game/Game.h"
#include "../Base/Base.h"

Title::Title() : Base(eType_Scene),m_title_text("C:\\Windows\\Fonts\\msgothic.ttc",64) {
	m_img = COPY_RESOURCE("Title", CImage);
}

Title::~Title(){
	//�S�ẴI�u�W�F�N�g��j��
	Base::KillAll();
	//�Q�[���V�[����
	Base::Add(new Game());
}

void Title::Update(){
	//�{�^��1�Ń^�C�g���j��
	if (PUSH(CInput::eButton1)) {
		SetKill();
	}
}

void Title::Draw(){
	m_img.Draw();
	//�����\��
	m_title_text.Draw(64, 255, 0, 0, 0, "Title");
	m_title_text.Draw(64, 512, 0, 0, 0, "Push Z");
}
