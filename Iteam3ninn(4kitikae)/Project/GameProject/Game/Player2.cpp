#include "Player2.h"
#include "Arrow.h"
#include "Bullet2.h"
#include "Enemy.h"
#include "Game.h"
#include "Map.h"

Player2::Player2(const CVector2D& pos, float ang, float speed, int a, bool flag) :Base(eType_Player) {
	m_img = COPY_RESOURCE("Player", CImage);
	m_pos_old = m_pos = pos;;
	//中心を設定
	m_img.SetCenter(16, 16);
	//矩形を設定	(左、上、右、下)
	m_rect = CRect(-16, -16, 16, 16);
	//半径
	m_rad = 16;
	m_ang = ang;
	m_cnt = 1;
	m_gen = -0.01;
	m_speed = speed;
	m_hp = 100;
	//ボールを管理する変数
	drag = 0;
	C = 0;
	m = a;
	m_flag = flag;
	m_state = eState_Stop;
}

void Player2::StateIdle() {
	CVector2D mouse;
	m_pos_old = m_pos;
	//switch (m) {
	//case 0:
		mouse = CInput::GetMousePoint();
		if (drag == 0) {
			if (C == 1) {
				if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60 && m_cnt == 1) {
					//if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60) {
					Base::Add(new Arrow(m_pos, m_ang));
					m_cnt -= 1;
					m_speed = 32;
					drag = 1;
					
					//printf("つかんでいる\n");
					CVector2D vec = CInput::GetMousePoint() - m_pos;
					m_ang = atan2(vec.x, vec.y);
					m_vec = CVector2D(sin(m_ang), cos(m_ang));
				}
			}
		}
		if (drag == 1) {
			//printf("引っ張っている\n");
			if (m_pos.x < mouse.x + 1200 && m_pos.x > mouse.x - 1200 && m_pos.y < mouse.y + 1200 && m_pos.y > mouse.y - 1200) {
				//if (m_pos.x < mouse.x + 60 && m_pos.x > mouse.x - 60 && m_pos.y < mouse.y + 60 && m_pos.y > mouse.y - 60) {
				drag = 0;
				//printf("やり直し\n");
			}
		}
		if (C == 0) {
			//printf("引っ張っている\n");
			if (m_speed > 0) {
				//m_state = eState_Move;
				m_cnt = 2;
				m_speed += m_gen;
				m_pos -= m_vec * m_speed;
			}
			if (m_speed <= 0) {
				m_state = eState_Stop;
				//m_cnt = 1;
			}
			drag = 0;
		}
		
		//break;
	//}
}

void Player2::StateMove() {
	//m_cnt = 2;
	//m_speed += m_gen;
	//m_pos -= m_vec * m_speed;
}

void Player2::StateStop() {
	m_cnt = 1;
}

void Player2::Update() {
	if (HOLD(CInput::eMouseL)) {
		if (m_cnt == 1)
			C = 1;
	}
	else {
		C = 0;
	}
	
	switch (m_state) {
		//通常状態
	case eState_Idle:
		StateIdle();
		break;
		//動く状態
	case eState_Move:
		StateMove();
		break;
		//止まる状態
	case eState_Stop:
		StateStop();
		break;
	}
	/*
	if (HOLD(CInput::eMouseL)) {
		if (m_cnt == 1)
			C = 1;
	}
	else {
		C = 0;
	}
	CVector2D mouse;
	m_pos_old = m_pos;
	switch (m) {
	case 0:
		mouse = CInput::GetMousePoint();
		if (drag == 0) {
			if (C == 1) {
				if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60 && m_cnt == 1) {
					//if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60) {
					Base::Add(new Arrow(m_pos, m_ang));
					m_cnt -= 1;
					m_speed = 32;
					drag = 1;
					//printf("つかんでいる\n");
					CVector2D vec = CInput::GetMousePoint() - m_pos;
					m_ang = atan2(vec.x, vec.y);
					m_vec = CVector2D(sin(m_ang), cos(m_ang));
				}
			}
		}
		if (drag == 1) {
			//printf("引っ張っている\n");
			if (m_pos.x < mouse.x + 1200 && m_pos.x > mouse.x - 1200 && m_pos.y < mouse.y + 1200 && m_pos.y > mouse.y - 1200) {
				//if (m_pos.x < mouse.x + 60 && m_pos.x > mouse.x - 60 && m_pos.y < mouse.y + 60 && m_pos.y > mouse.y - 60) {
				drag = 0;
				//printf("やり直し\n");
			}
		}
		if (C == 0) {
			//printf("引っ張っている\n");
			if (m_speed > 0) {
				m_cnt = 2;
				m_speed += m_gen;
				m_pos -= m_vec * m_speed;
			}
			if (m_speed <= 0) {
				m_cnt = 1;
			}
			drag = 0;
		}
	}*/
}

void Player2::Draw() {
	m_img.SetPos(m_pos);
	//m_img.SetAng(m_ang);
	m_img.SetSize(32,32);
	m_img.Draw();
}

void Player2::Collision(Base* b) {
	switch (b->m_type) {
	case eType_Field:
		if (Map* m = dynamic_cast<Map*>(b)) {
			/*
			int t = m->CollisionMap(m_pos);
			if (t != 0)
				m_pos = m_pos_old;
			*/
			int t = m->CollisionMap(CVector2D(m_pos.x, m_pos_old.y), m_rect);
			if (t == 1) {
				SOUND("kabeSE")->Play();
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 1.0;
				
			} else if (t == 2) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 2.0;
				//if (b->m_hp >= 0) {
				//	b->m_hp -= 20;
				//}
			}
			/*
			if (t != 0) {
				m_pos.x = m_pos_old.x;
				m_vec.x *= -1;
				m_speed -= 0.5;

			}
			*/
			t = m->CollisionMap(CVector2D(m_pos_old.x, m_pos.y), m_rect);
			if (t == 1) {
				SOUND("kabeSE")->Play();
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 1.0;

			} else if (t == 2) {
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 2.0;
				//if (b->m_hp >= 0) {
				//	b->m_hp -= 20;
				//}
			}
			/*
			if (t != 0) {
				m_pos.y = m_pos_old.y;
				m_vec.y *= -1;
				m_speed -= 0.5;
			}
			*/
		}
		break;
	case eType_Enemy:
		if (Base::CollisionRect(this, b)) {
			m_speed -= 3.0;
			/*
			CVector2D N = b->m_pos - m_pos;
			N.GetNormalize();
			CVector2D R=m_vec-(m_pos+N);
			m_vec += R;
			m_vec += m_vec * 2;
			m_vec += N;
			m_vec * -1;
			*/
		}
		break;
	}
}

/*
void Player2::Update() {
	if (HOLD(CInput::eMouseL)) {
		if (m_cnt == 1)
			C = 1;
	}
	else {
		C = 0;
	}
	CVector2D mouse;
	m_pos_old = m_pos;
	switch (m) {
	case 0:
		mouse = CInput::GetMousePoint();
		if (drag == 0) {
			if (C == 1) {
				if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60 && m_cnt == 1) {
					//if (HOLD(CInput::eMouseL) && m_pos.x < mouse.x + 60 || m_pos.x > mouse.x - 60 || m_pos.y < mouse.y + 60 || m_pos.y > mouse.y - 60) {
					Base::Add(new Arrow(m_pos, m_ang));
					m_cnt -= 1;
					m_speed = 32;
					drag = 1;
					//printf("つかんでいる\n");
					CVector2D vec = CInput::GetMousePoint() - m_pos;
					m_ang = atan2(vec.x, vec.y);
					m_vec = CVector2D(sin(m_ang), cos(m_ang));
				}
			}
		}
		if (drag == 1) {
			//printf("引っ張っている\n");
			if (m_pos.x < mouse.x + 1200 && m_pos.x > mouse.x - 1200 && m_pos.y < mouse.y + 1200 && m_pos.y > mouse.y - 1200) {
				//if (m_pos.x < mouse.x + 60 && m_pos.x > mouse.x - 60 && m_pos.y < mouse.y + 60 && m_pos.y > mouse.y - 60) {
				drag = 0;
				//printf("やり直し\n");
			}
			//else {
			//	if (C == 0) {
			//		printf("引っ張っている\n");
					//CVector2D vec = CInput::GetMousePoint() - m_pos;
					//m_ang = atan2(vec.x, vec.y);
					//m_vec = CVector2D(sin(m_ang), cos(m_ang));
			//		if (m_speed > 0) {
			//			m_speed += m_gen;
			//			m_pos += m_vec * m_speed;
			//		}
					//一瞬動く
			//		drag = 0;
			//	}
				//drag = 0;
			//}
		}
		if (C == 0) {
			//printf("引っ張っている\n");
			if (m_speed > 0) {
				m_cnt = 2;
				m_speed += m_gen;
				m_pos -= m_vec * m_speed;
			}
			if (m_speed <= 0) {
				m_cnt = 1;
			}
			drag = 0;
		}
		//printf("m_cnt:%d\n", m_cnt);

		//移動前の位置
		//m_pos_old = m_pos;
		//if (PUSH(CInput::eMouseR) && m_cnt==1) {
		//	m_cnt -= 1;
		//	m_speed = 32;
			//マウスへのベクトル
		//	CVector2D vec = CInput::GetMousePoint() - m_pos;
		//	m_ang = atan2(vec.x, vec.y);
			//跳ね返る　ピタッと止まる
		//	m_vec = CVector2D(sin(m_ang), cos(m_ang));
		//}
		//if (m_speed > 0) {
		//	m_speed += m_gen;
			//跳ね返らない　だんだん遅くなり止まる
			//m_vec = CVector2D(sin(m_ang), cos(m_ang)) * m_speed;
			//printf("%f\n", m_speed);
		//	m_pos += m_vec * m_speed;
		//}
		//if (m_speed <= 0) {
		//	m_cnt = 1;
		//}
	}
}
*/
