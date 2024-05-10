#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include<SFML/Audio.hpp>
#include<sstream>
#include <time.h>
using namespace sf;
using namespace std;
#define  DITUSIZE 56  //��ͼһȦ�ĸ�����
#define  GZSIZE 40  //���Ӵ�С

//�����ඨ��
class Qizi {
public:
	int GePos;//���ڵĸ��ӣ�
	bool isHome; //�Ƿ��ڼ�
	bool isDoor;//�Ƿ��ڼ��ſ�
	int prex;//���ŵ�һ������ƫ����
	int prex2[2];//����ƫ��
	int diezishu;//������
	bool isend;//�Ƿ����
};

class Game
{
public:
	sf::RenderWindow window;
	Game();
	~Game();
	bool GameStart, GamePlay, GameEnd;//��ʼ��Ϸ���棬��Ϸ���н���,��Ϸ��������
	bool gameQuit, gameOver;  //��Ϸ�Ƿ����
	int Window_Width, Window_Height; //���ڴ�С
	Texture tBackBegin, tBeginButton1, tBeginButton2, tBackPlay, tToziBut, tQizi1, tQizi2, tQizi3, tQizi4, tPaiHang, ttouyin;//�����������
	Sprite sBackBegin, sBeginButton, sBackPlay, sToziBut, sQizi1, sQizi2, sQizi3, sQizi4, sPaiHang, stouyin;//�����������
	sf::IntRect BeginButton;
	Sprite sQizi[4] = { sQizi1,sQizi2,sQizi3,sQizi4 };
	Text text;
	Font font;
	SoundBuffer sbfly, sbjump, sbzhuang, sbyeah, sbtouzi;//����������Ч
	Sound soundfly, soundjump, soundzhuang, soundyeah, soundtouzi;
	Music bkMusic;// ��������
	int SoundVolume;//����������С
	bool MusicOn;//����������ͣ�����δʹ�ã�
	bool isChange;

	//�ֻؼ�ʤ������
	int PlayerNum, endNum, WinPai[4];
	bool PlayerWin[4];

	//���Ӳ��ֶ���
	int qizibuxingCount, diezi, qiziDianji;
	bool QiziDianjiLock, qiziBuxingTime;


	//���Ӳ��ֶ���
	int touziNuml, touziNum, touziHomeNum, touzinumPrex;
	bool touziTime, touziInitial;
	Texture t_touzi, t_touzi2;
	Sprite s_touzi, s_touzi2;
	int TouziFlash[20], TouziFlash_n;
	Vector2i LeftCoener;
	int ButtonWidth = 62;
	int ButtonHeight = 62;

	//��ͼ�ĸ�����ɫ
	int DColor[DITUSIZE + 28] =
	{
							  7,0,1,2,3,0,8,2,3,0,1,2,3,9,
							  4,1,2,3,0,1,8,3,0,1,2,3,0,9,
							  5,2,3,0,1,2,8,0,1,2,3,0,1,9,
							  6,3,0,1,2,3,8,1,2,3,0,1,2,9,
							  8,8,8,8,8,8,8,8,8,8,8,8,8,8,
							  8,8,8,8,8,8,8,8,8,8,8,8,8,8
	};

	//��ͼ���ӵ�x,y����
	int DPosition[DITUSIZE + 29][2] =
	{
		/*��1��2*/{440,200},{440,160},{440,120},{440,80},{480,80},{520,80},{560,80},{600,80},
		/*��3��4*/{640,80},{680,80},{680,120},{680,160},{680,200},{680,240},{720,240},{760,240},{800,240},
		/*��5��6*/{840,240},{840,280},{840,320},{840,360},{840,400},{840,440},{840,480},{800,480},
		/*��7��8*/{760,480},{720,480},{680,480},{680,520},{680,560},{680,600},{680,640},{640,640},{600,640},
		/*��9��10*/ {560,640},{520,640},{480,640},{440,640},{440,600},{440,560},{440,520},{440,480},{400,480},
		/*��11��12*/{360,480},{320,480},{280,480},{280,440},{280,400},{280,360},{280,320},{280,280},
		/*��13*/{280,240},{320,240},{360,240},{400,240},{440,240},
		{280,360},{320,360},{360,360},{400,360},{440,360},{480,360},{520,360},
		{560,80},{560,120},{560,160},{560,200},{560,240},{560,280},{560,320},
		{840,360},{800,360},{760,360},{720,360},{680,360},{640,360},{600,360},
		{560,640},{560,600},{560,560},{560,520},{560,480},{560,440},{560,400},{580,360}
	};

	//���Ӷ���
	Qizi QiziA[4][4] = { {{84,true,false,51,{0, -50 },0,false},{84,true,false,51,{0,-50},0 ,false}, {84,true,false,51,{0,-50},0,false },{84,true,false,51,{0,-50},0 ,false}, },
						 {{84,true,false,9,{50,0} ,0,false},{84,true,false,9,{50,0},0,false }, {84,true,false,9,{50,0},0 ,false},{84,true,false,9,{50,0},0 ,false}},
						 {{84,true,false,23,{0,50} ,0,false},{84,true,false,23,{0,50},0 ,false}, {84,true ,false,23,{0,50},0,false},{84,true,false,23 ,{0,50},0,false}},
						 { {84, true,false,37,{-50,0},0 ,false}, { 84,true,false,37,{-50,0},0 ,false}, { 84,true,false,37,{-50,0} ,0,false}, { 84,true,false,37,{-50,0},0,false }, } };//����

	//���Ӽ�λ��
	double QiziHomePos1[4][4][2] = { {{290,90},{335,90},{290,135},{335,135}},
	 { {750,90},{795,90},{750,135},{795,135} } ,
	 { {750,550},{795,550},{750,595},{795,595} } ,
	 { {290,550},{335,550},{290,595},{335,595} } };


	void Initial();
	void Input();
	void QiziBuxing();
	void touzi();
	void touziDraw();
	void Draw();
	void DrawPlay();
	void Run();

	bool TouziPosClicked();
	int AiDoChoice();
	bool IsPlayerTurn();

};


