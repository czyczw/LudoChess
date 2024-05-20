#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include<SFML/Audio.hpp>
#include<sstream>
#include <time.h>
using namespace sf;
using namespace std;
#define  DITUSIZE 56  //地图一圈的格子数
#define  GZSIZE 40  //棋子大小

class BaseClass
{
public:
	int touziNum;
	virtual void touzi() = 0;
};
//棋子类定义
class Qizi
{
public:
	int GePos;//处在的格子，
	bool isHome; //是否在家
	bool isDoor;//是否在家门口
	int prex;//家门第一个格子偏移量
	int prex2[2];//家门偏移
	int diezishu;//迭子数
	bool isend;//是否结束
	bool isStop;//是否停止
	bool isBingLiangCunDuan=false;//是否兵粮寸断
	int BingLiangCunDuanCount;//兵粮寸断数值

	BaseClass* game;
	void AdvanceEvent(int n)//前进事件
	{
		GePos += n;
	}
	void BackEvent(int n)//后退事件
	{
		GePos -= n;
	}
	//骰一次骰子，如果为偶数则回家
	void DisasterEvent()
	{
		game->touzi();
		if (game->touziNum%2==1)
		{
			GePos = 0;
			isHome = true;
			isDoor = false;
		}
	}
	//骰一次骰子，如果小于5，下回合不动
	void StopEvent()
	{
		game->touzi();
		if (game->touziNum < 5)
		{
			isStop = true;
		}
	}
	//下次骰子数-2
	void ReduceNextPointEvent()
	{
		isBingLiangCunDuan = true;
		BingLiangCunDuanCount = 2;
	}
};


class Game :public BaseClass
{
public:
	sf::RenderWindow window;
	Game();
	bool GameStart, GamePlay, GameEnd;//开始游戏界面，游戏进行界面,游戏结束界面
	bool Gamepick; //选人
	bool gameQuit, gameOver;  //游戏是否结束
	bool debugMode;
	int Window_Width, Window_Height; //窗口大小
	Texture tBackBegin, tBeginButton1, tBeginButton2, tBackPlay, tToziBut, tQizi1, tQizi2, tQizi3, tQizi4, tPaiHang, ttouyin;//创建纹理对象
	Sprite sBackBegin, sBeginButton, sBackPlay, sToziBut, sQizi1, sQizi2, sQizi3, sQizi4, sPaiHang, stouyin;//创建精灵对象
	Texture tEventShan, tEventWuZhong, tEventLeBu, tEventBingLiang, tEventShanDian, tEventChiTu;
	Sprite sEventShan, sEventWuZhong, sEventLeBu, sEventBingLiang, sEventShanDian, sEventChiTu;
	Texture tPickBackground,tyuanshao,tcaopi,tluanji,tfangzhu;
	Sprite sPickBackground,syuanshao,scaopi,sluanji,sfangzhu;

	sf::IntRect BeginButton;
	Sprite sQizi[4] = { sQizi1,sQizi2,sQizi3,sQizi4 };
	Text text;
	Font font;
	SoundBuffer sbfly, sbjump, sbzhuang, sbyeah, sbtouzi;//飞棋跳棋音效
	Sound soundfly, soundjump, soundzhuang, soundyeah, soundtouzi;
	Music bkMusic;// 背景音乐
	int SoundVolume;//设置音量大小
	bool MusicOn;//设置音乐暂停与否（暂未使用）
	bool isChange;

	//轮回及胜利定义
	int PlayerNum, endNum, WinPai[4];
	bool PlayerWin[4];

	//棋子部分定义
	int qizibuxingCount, diezi, qiziDianji;
	bool QiziDianjiLock, qiziBuxingTime;


	//骰子部分定义
	int touziNuml, touziHomeNum, touzinumPrex;
	bool touziTime, touziInitial;
	Texture t_touzi, t_touzi2;
	Sprite s_touzi, s_touzi2;
	int TouziFlash[20], TouziFlash_n;
	Vector2i LeftCoener;
	int ButtonWidth = 62;
	int ButtonHeight = 62;

	//地图的格子颜色
	int DColor[DITUSIZE + 28] =
	{
							  7,0,1,2,3,0,8,2,3,0,1,2,3,9,
							  4,1,2,3,0,1,8,3,0,1,2,3,0,9,
							  5,2,3,0,1,2,8,0,1,2,3,0,1,9,
							  6,3,0,1,2,3,8,1,2,3,0,1,2,9,
							  8,8,8,8,8,8,8,8,8,8,8,8,8,8,
							  8,8,8,8,8,8,8,8,8,8,8,8,8,8
	};

	//地图格子的x,y坐标
	int DPosition[DITUSIZE + 29][2] =
	{
		/*绿1绿2*/{440,200},{440,160},{440,120},{440,80},{480,80},{520,80},{560,80},{600,80},
		/*绿3绿4*/{640,80},{680,80},{680,120},{680,160},{680,200},{680,240},{720,240},{760,240},{800,240},
		/*绿5绿6*/{840,240},{840,280},{840,320},{840,360},{840,400},{840,440},{840,480},{800,480},
		/*绿7绿8*/{760,480},{720,480},{680,480},{680,520},{680,560},{680,600},{680,640},{640,640},{600,640},
		/*绿9绿10*/ {560,640},{520,640},{480,640},{440,640},{440,600},{440,560},{440,520},{440,480},{400,480},
		/*绿11绿12*/{360,480},{320,480},{280,480},{280,440},{280,400},{280,360},{280,320},{280,280},
		/*绿13*/{280,240},{320,240},{360,240},{400,240},{440,240},
		{280,360},{320,360},{360,360},{400,360},{440,360},{480,360},{520,360},
		{560,80},{560,120},{560,160},{560,200},{560,240},{560,280},{560,320},
		{840,360},{800,360},{760,360},{720,360},{680,360},{640,360},{600,360},
		{560,640},{560,600},{560,560},{560,520},{560,480},{560,440},{560,400},{580,360}
	};

	//棋子定义
	Qizi QiziA[4][4] = { {{84,true,false,51,{0, -50 },0,false},{84,true,false,51,{0,-50},0 ,false}, {84,true,false,51,{0,-50},0,false },{84,true,false,51,{0,-50},0 ,false}, },
						 {{84,true,false,9,{50,0} ,0,false},{84,true,false,9,{50,0},0,false }, {84,true,false,9,{50,0},0 ,false},{84,true,false,9,{50,0},0 ,false}},
						 {{84,true,false,23,{0,50} ,0,false},{84,true,false,23,{0,50},0 ,false}, {84,true ,false,23,{0,50},0,false},{84,true,false,23 ,{0,50},0,false}},
						 { {84, true,false,37,{-50,0},0 ,false}, { 84,true,false,37,{-50,0},0 ,false}, { 84,true,false,37,{-50,0} ,0,false}, { 84,true,false,37,{-50,0},0,false }, } };//棋子

	//棋子家位置
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
	void DrawDebug();
	int AiDoChoice();
	bool IsPlayerTurn();
};