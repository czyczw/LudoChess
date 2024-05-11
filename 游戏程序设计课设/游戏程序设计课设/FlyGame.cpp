#include"FlyGame.h";
Event event;

Game::Game()
{
	Window_Width = 1080;
	Window_Height = 720;
	window.create(sf::VideoMode(Window_Width, Window_Height), L"恋与飞行棋");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			QiziA[i][j].game = this;
		}
	}
}

void Game::Initial()
{
	window.setFramerateLimit(60);

	isChange = false;
	gameQuit = false;//游戏未退出
	gameOver = false;//游戏未结束
	GameStart = true;//游戏在初始场景
	GamePlay = false; //不在游戏场景
	GameEnd = false;//不在结束场景
	touziNum = 0;
	touziNuml = 0;
	LeftCoener.x = 612;
	LeftCoener.y = 395;
	touziTime = true;
	touziInitial = false;
	qiziBuxingTime = false;
	qizibuxingCount = 0;
	PlayerNum = 0;
	touziHomeNum = 0;
	touzinumPrex = 0;
	diezi = 0;
	endNum = 0;
	SoundVolume = 50;

	QiziDianjiLock = false;
	for (int i = 0; i < 4; i++)
	{
		PlayerWin[i] = false;
		WinPai[i] = -1;
	}
	///开始界面
	if (!tBackBegin.loadFromFile("data/images/bg3.jpg")) { cout << "初始背景素材没有找到" << endl; }
	if (!tBeginButton1.loadFromFile("data/images/Begin1.png")) { cout << "开始按钮1没有找到" << endl; }
	if (!tBeginButton2.loadFromFile("data/images/Begin2.png")) { cout << "开始按钮2没有找到" << endl; }

	///游戏进行界面
	if (!tBackPlay.loadFromFile("data/images/PlayBK08.jpg")) cout << "游戏场景素材没有找到" << endl;
	if (!tToziBut.loadFromFile("data/images/QIZI4.png")) cout << "骰子素材没有找到" << endl;
	if (!tQizi1.loadFromFile("data/images/QZxm.png")) cout << "棋子1素材没有找到" << endl;
	if (!tQizi2.loadFromFile("data/images/QZlzy.png")) cout << "棋子2素材没有找到" << endl;
	if (!tQizi3.loadFromFile("data/images/QZzql.png")) cout << "棋子3素材没有找到" << endl;
	if (!tQizi4.loadFromFile("data/images/QZbq.png")) cout << "棋子4素材没有找到" << endl;
	if (!t_touzi.loadFromFile("data/images/tou1.jpg")) cout << "16骰子素材没有找到" << endl;
	if (!t_touzi2.loadFromFile("data/images/tou2.jpg")) cout << "旋转棋子素材没有找到" << endl;
	if (!ttouyin.loadFromFile("data/images/touyin.png")) cout << "投影素材没有找到" << endl;
	if (!sbtouzi.loadFromFile("data/Audios/TZ.wav")) { cout << "骰子音乐声没有找到" << endl; }
	if (!sbyeah.loadFromFile("data/Audios/yeah.wav")) { cout << "棋子结束回家音乐声没有找到" << endl; }
	if (!bkMusic.openFromFile("data/Audios/ly68.wav")) { cout << "背景音乐声没有找到" << endl; }
	if (!font.loadFromFile("data/Fonts/simsun.ttc")) cout << "字体没有找到" << endl;
	if (!tEventBingLiang.loadFromFile("data/images/Map/bingliang.png")) cout << "兵粮素材没有找到" << endl;
	if (!tEventShan.loadFromFile("data/images/Map/shan.png")) cout << "闪素材没有找到" << endl;
	if (!tEventShanDian.loadFromFile("data/images/Map/shandian.png")) cout << "闪电素材没有找到" << endl;
	if (!tEventLeBu.loadFromFile("data/images/Map/lebu.png")) cout << "乐不思蜀素材没有找到" << endl;
	if (!tEventChiTu.loadFromFile("data/images/Map/chitu.png")) cout << "赤兔素材没有找到" << endl;
	if (!tEventWuZhong.loadFromFile("data/images/Map/wuzhong.png")) cout << "无中生有素材没有找到" << endl;
	text.setFont(font);

	//结束场景
	if (!tPaiHang.loadFromFile("data/images/PH.png")) { cout << "排行榜素材没有找到" << endl; }

	sBackBegin.setTexture(tBackBegin);
	sBeginButton.setTexture(tBeginButton1);
	sBackPlay.setTexture(tBackPlay);
	sQizi1.setTexture(tQizi1);   sQizi2.setTexture(tQizi2);   sQizi3.setTexture(tQizi3);   sQizi4.setTexture(tQizi4);
	stouyin.setTexture(ttouyin);
	s_touzi.setTexture(t_touzi);   s_touzi2.setTexture(t_touzi2);
	sPaiHang.setTexture(tPaiHang);

	sEventBingLiang.setTexture(tEventBingLiang);
	sEventShan.setTexture(tEventShan);
	sEventShanDian.setTexture(tEventShanDian);
	sEventLeBu.setTexture(tEventLeBu);
	sEventChiTu.setTexture(tEventChiTu);
	sEventWuZhong.setTexture(tEventWuZhong);

	sQizi[0] = sQizi1;	sQizi[1] = sQizi2;	sQizi[2] = sQizi3;	sQizi[3] = sQizi4;//方便

	stouyin.setOrigin(10, 10);//设置投影初始位置偏移量

	soundfly.setBuffer(sbfly);
	soundjump.setBuffer(sbjump);
	soundzhuang.setBuffer(sbzhuang);
	soundyeah.setBuffer(sbyeah);
	soundtouzi.setBuffer(sbtouzi);

	//格子位置定义初始化偏移（因为窗口坐标与图片不一定符合）
	for (int i = 0; i < 56 + 28 + 1; i++)
	{
		DPosition[i][0] -= 20;
		DPosition[i][1] -= 20;
	}
}

void Game::QiziBuxing()
{
	for (int k = 0; k < 80; k++)//数值不固定，只是让它循环一下，不一定好用，可改
	{

		//当棋子前进结束
		//if (qizibuxingCount >= touziNum + touzinumPrex + 1)//棋子前进步数等于骰子数与跳棋飞棋数
		if (qizibuxingCount >= touziNum + 1)//棋子前进步数等于骰子数
		{
			//如果棋子刚刚好到达终点
			if (QiziA[PlayerNum][qiziDianji].GePos == DITUSIZE + 7 * (PlayerNum)+6)
			{
				QiziA[PlayerNum][qiziDianji].isend = true;
				QiziA[PlayerNum][qiziDianji].isHome = true;
				soundyeah.setVolume(60);
				soundyeah.play();

				cout << "一棋子成功" << endl;

				//判断阵营结束
				int wincount = 0;
				for (int j = 0; j < 4; j++)
				{
					if (QiziA[PlayerNum][j].isend == true)
						wincount++;
				}
				if (wincount == 4)//如果整个阵营四个棋子都结束
				{
					PlayerWin[PlayerNum] = true; //此阵营结束
					cout << PlayerNum << "结束" << endl;//测试
					WinPai[PlayerNum] = endNum; //此阵营排行
					cout << "winpai" << PlayerNum << WinPai[PlayerNum] << "endnum" << endNum << endl;//测试
					endNum++;
					cout << "endnum" << endNum << endl;//测试
				}
				if (endNum == 3)//如果3个阵营结束
				{
					for (int i = 0; i < 4; i++)
					{
						if (WinPai[i] == -1)//则剩下一个为最后一名
							WinPai[i] = 3;
					}
					GameEnd = true;//游戏进入结束界面
				}
			}
			//判断叠子
			for (int k = 0; k < 4; k++)
				if (QiziA[PlayerNum][k].GePos == QiziA[PlayerNum][qiziDianji].GePos || k != qiziDianji)
					diezi++;
			QiziA[PlayerNum][qiziDianji].diezishu = diezi;//此棋子叠子高度
			diezi = 0;
			QiziDianjiLock = false;//可点击下一个
			touzinumPrex = 0;//跳棋飞棋偏移还原置为0
			qiziBuxingTime = false;//棋子步行时间结束
			qizibuxingCount = 0;//棋子前进数还原置为0

			
			touziTime = true;//骰子时间
			if (touziNum != 5)//骰子数不为6则进入下一玩家
			{
				do
				{
					if (PlayerNum == 3)
						PlayerNum = 0;
					else
						PlayerNum++;
				} while (PlayerWin[PlayerNum] == true);//若有玩家结束则跳过该玩家
			}
		}
		if (k == 49)
		{
			//若棋子到达终点骰子数还没走完，则返回剩下的步数
			if (QiziA[PlayerNum][qiziDianji].GePos == DITUSIZE + 7 * (PlayerNum)+6)
			{
				QiziA[PlayerNum][qiziDianji].GePos -= (touziNum + 1 - qizibuxingCount);
				qizibuxingCount = touziNum + 1;
			}
			else
			{
				//棋子在骰子数中前进单个单个前进
				if (qizibuxingCount < touziNum + 1)
				{
					//进入终点路线
					if (QiziA[PlayerNum][qiziDianji].GePos == QiziA[PlayerNum][qiziDianji].prex - 3)
					{
						QiziA[PlayerNum][qiziDianji].GePos = DITUSIZE + 7 * (PlayerNum);
					}
					//到棋盘55时则让其回到0；
					if (QiziA[PlayerNum][qiziDianji].GePos == 55)
						QiziA[PlayerNum][qiziDianji].GePos = 0;
					//2号格闪电事件
					else if (QiziA[PlayerNum][qiziDianji].GePos == 2 && qizibuxingCount==touziNum)
						//QiziA[PlayerNum][qiziDianji].AdvanceEvent(10);
						//QiziA[PlayerNum][qiziDianji].GePos = 55;
					{
						QiziA[PlayerNum][qiziDianji].GePos += 1;
						this->touziTime = true;
						QiziA[PlayerNum][qiziDianji].DisasterEvent();
						PlayerNum++;
						qiziBuxingTime = false;
						break;
					}
					//3号格乐不思蜀事件
					else if (QiziA[PlayerNum][qiziDianji].GePos == 3 && qizibuxingCount == touziNum)
					{
						QiziA[PlayerNum][qiziDianji].GePos += 1;
						this->touziTime = true;
						QiziA[PlayerNum][qiziDianji].StopEvent();
						PlayerNum++;
						qiziBuxingTime = false;
						break;
					}
					//4号格兵粮寸断事件
					else if (QiziA[PlayerNum][qiziDianji].GePos == 4 && qizibuxingCount == touziNum)
					{
						QiziA[PlayerNum][qiziDianji].GePos += 1;
						QiziA[PlayerNum][qiziDianji].ReduceNextPointEvent();
						PlayerNum++;
						qiziBuxingTime = false;
						break;
					}
					else
						QiziA[PlayerNum][qiziDianji].GePos += 1;
					qizibuxingCount++;
					//将经过的棋子打回(跳棋飞棋不打回)（在测试的时候可以注释，容易拖慢测试速度）
					for (int m = 0; m < 4; m++)
						for (int n = 0; n < 4; n++)
						{
							if (QiziA[m][n].GePos == QiziA[PlayerNum][qiziDianji].GePos && m != PlayerNum && QiziA[m][n].isDoor == false)
							{
								QiziA[m][n].isHome = true;
								soundzhuang.setVolume(60);
								soundzhuang.play();
							}
						}
				}
				//棋子跳棋或飞棋直接前进剩下步数
				/*else
				{
					for (qizibuxingCount = touziNum + 1; qizibuxingCount < touziNum + 1 + touzinumPrex; qizibuxingCount++)
					{
						if (QiziA[PlayerNum][qiziDianji].GePos == QiziA[PlayerNum][qiziDianji].prex - 3)
						{
							QiziA[PlayerNum][qiziDianji].GePos = DITUSIZE + 7 * (PlayerNum);
						}
						if (QiziA[PlayerNum][qiziDianji].GePos == 55)
							QiziA[PlayerNum][qiziDianji].GePos = 0;
						else
							QiziA[PlayerNum][qiziDianji].GePos += 1;
					}
				}*/
			}
		}
	}
	//绘制投影和棋子
	stouyin.setPosition(DPosition[QiziA[PlayerNum][qiziDianji].GePos][0], DPosition[QiziA[PlayerNum][qiziDianji].GePos][1]);
	window.draw(stouyin);
	sQizi[PlayerNum].setPosition(DPosition[QiziA[PlayerNum][qiziDianji].GePos][0], DPosition[QiziA[PlayerNum][qiziDianji].GePos][1]);
	window.draw(sQizi[PlayerNum]);
}

void Game::Input()
{	
	if (!IsPlayerTurn())
	{
		goto AITURNGOTO;
	}
	while (window.pollEvent(event))
	{
		AITURNGOTO://AI回合先执行一遍，在处理event事件。
		if (event.type == Event::Closed) {
			window.close();
			gameQuit = true;
		}
		if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Escape) {
			window.close();
			gameQuit = true;
		}
		//背景音量控制
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Up)
		{
			SoundVolume += 5;
			bkMusic.setVolume(SoundVolume);
		}
		else if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Down)
		{
			SoundVolume -= 5;
			bkMusic.setVolume(SoundVolume);
		}
		// 背景音乐开关
		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::P)
		{
			if (MusicOn == true)
			{
				bkMusic.pause();
				MusicOn = false;
			}
			else
			{
				bkMusic.play();
				MusicOn = true;
			}
		}
		/*if (event.type == sf::Event::MouseMoved)
		{

			if (BeginButton.contains(event.mouseMove.x, event.mouseMove.y))
			{
				std::cout << "按键经‘开始’上移动" << std::endl;
			}

		}*/

		if (BeginButton.contains(event.mouseMove.x, event.mouseMove.y))
		{
			//std::cout << "按键停留在按键‘开始’上" << std::endl;
			isChange = true;
		}
		else
		{
			isChange = false;
		}


		if (GameStart == true)//初始界面输入模块
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				if (sf::Mouse::getPosition(window).x > 500 && sf::Mouse::getPosition(window).x < 600
					&& sf::Mouse::getPosition(window).y >500 && sf::Mouse::getPosition(window).y < 620)
				{
					GameStart = false;//跳出初始界面
					GamePlay = true;//进入游戏界面
					MusicOn = true;//判断音乐开始（暂时没用）
					bkMusic.setVolume(SoundVolume);//调节音乐声大小
					bkMusic.play();//背景音乐播放
					bkMusic.setLoop(true);//背景音乐循环
				}
		}

		if (GamePlay == true)//游戏界面输入模块
		{
			//骰子时间
			if (touziTime == true && touziInitial == false)
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && TouziPosClicked() || !IsPlayerTurn())//左键单击骰子位置 
				{
					touzi();//进行骰子数值初始化及动画
					soundtouzi.setVolume(40);
					soundtouzi.play();
					//cout << "chg" << endl;
				}
			}

			if (touziTime == false && qiziBuxingTime == false)//不为骰子时间，可选择棋子进行步行
			{
				int AiChoice;
				if (!IsPlayerTurn()) {
					AiChoice = AiDoChoice();
				}
				for (int i = 0; i < 4; i++)//本环节四个棋子可选择
				{
					//如果是AI的回合，判断AI的选择是否是该棋子，不是的话continue;
					if (!IsPlayerTurn() && AiChoice != i) {
						continue;
					}

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left || !IsPlayerTurn())//左键单击 
					{
						//在家且该棋子未结束且骰子数为6
						if (QiziA[PlayerNum][i].isHome == true && QiziA[PlayerNum][i].isend == false && touziNum == 5)
						{
							if (sf::Mouse::getPosition(window).x > QiziHomePos1[PlayerNum][i][0] - 20 + 20 //点击在家位置
								&& sf::Mouse::getPosition(window).x < QiziHomePos1[PlayerNum][i][0] + 20 + 20
								&& sf::Mouse::getPosition(window).y > QiziHomePos1[PlayerNum][i][1] - 20 + 20
								&& sf::Mouse::getPosition(window).y < QiziHomePos1[PlayerNum][i][1] + 20 + 20
								|| !IsPlayerTurn())
							{

								QiziA[PlayerNum][i].isHome = false;//在家状态变为不在
								QiziA[PlayerNum][i].isDoor = true;//门口状态变为在门口
								touziTime = true;//可再投一次骰子（因为刚刚为6）
								QiziA[PlayerNum][i].GePos = QiziA[PlayerNum][i].prex;//将该棋子的格子位置变为门口第一个位置
								//cout << "chg" << i << endl;
							}
						}
						else
						{
							//棋子在家门口
							if (QiziA[PlayerNum][i].isDoor == true && QiziDianjiLock == false)
							{
								if (sf::Mouse::getPosition(window).x > DPosition[QiziA[PlayerNum][i].prex][0] + QiziA[PlayerNum][i].prex2[0] - 20 + 20 //棋子在家门口位置
									&& sf::Mouse::getPosition(window).x < DPosition[QiziA[PlayerNum][i].prex][0] + QiziA[PlayerNum][i].prex2[0] + 20 + 20//(即家门第一格加偏移量)
									&& sf::Mouse::getPosition(window).y > DPosition[QiziA[PlayerNum][i].prex][1] + QiziA[PlayerNum][i].prex2[1] - 20 + 20
									&& sf::Mouse::getPosition(window).y < DPosition[QiziA[PlayerNum][i].prex][1] + QiziA[PlayerNum][i].prex2[1] + 20 + 20
									||!IsPlayerTurn())

								{
									//qiziDianji = i;
									for (int k = 0; k < 4; k++)//判断叠棋
									{
										if (QiziA[PlayerNum][k].GePos == QiziA[PlayerNum][i].GePos || k != i)
											diezi++;
									}
									QiziA[PlayerNum][i].diezishu = diezi;
									diezi = 0;
									int n = i;
									for (int m = i; m < 4; m++)
									{
										if (QiziA[PlayerNum][m].diezishu > QiziA[PlayerNum][n].diezishu)
										{
											n = m;
										}
									}
									qiziDianji = n;//叠棋最上方一个棋子可进入步行状态

									QiziDianjiLock = true;//（不设定的话其他同时在门口的棋子也会出门）
									QiziA[PlayerNum][qiziDianji].isDoor = false;//门口状态变为出门
									QiziA[PlayerNum][qiziDianji].GePos = QiziA[PlayerNum][qiziDianji].prex;//将该棋子的格子位置变为门口第一个位置（第二次）
									//跨越第55格的跳棋
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55  //如果加上骰子数后在55之后，则需要减去56才是正常棋子跳棋判断，否则会用终点路线的棋子颜色数值判断
										&& QiziA[PlayerNum][qiziDianji].GePos < 56)//忘了为什么要这么设置了
									{
										//if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum)//判断是否跳棋
										//{
										//	touzinumPrex += 4;
										//	soundjump.setVolume(40);
										//	soundjump.play();
										//}
									}
									else//不跨越55格的跳棋
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum)//判断是否跳棋
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
											for (int k = touziNum + 2; k < touziNum + touzinumPrex + 2; k++)//跳棋路上是否有白格，有就加一格
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + k] == 9)
													touzinumPrex++;
											}
										}
									}
									qiziBuxingTime = true;//进入步行时间
								}
							}
							//正常路上棋子，不在家也不在门口（许多解析可根据上方门口的输出逻辑，大部分一样）
							else
							{
								if (sf::Mouse::getPosition(window).x > DPosition[QiziA[PlayerNum][i].GePos][0] - 20 + 20//以棋子为中心上下左右分别20为点击有效范围
									&& sf::Mouse::getPosition(window).x < DPosition[QiziA[PlayerNum][i].GePos][0] + 20 + 20
									&& sf::Mouse::getPosition(window).y > DPosition[QiziA[PlayerNum][i].GePos][1] - 20 + 20
									&& sf::Mouse::getPosition(window).y < DPosition[QiziA[PlayerNum][i].GePos][1] + 20 + 20
									||!IsPlayerTurn())
								{
									touzinumPrex = 0;
									int n = i;
									for (int m = i; m < 4; m++)//判断叠棋
									{
										if (QiziA[PlayerNum][m].diezishu > QiziA[PlayerNum][n].diezishu)
										{
											n = m;
										}
									}
									qiziDianji = n;
									//跨越55格的跳棋
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55 && QiziA[PlayerNum][qiziDianji].GePos < 56)
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum)//判断跳棋
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
											for (int k = touziNum + 2; k < touziNum + touzinumPrex + 2; k++)
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + k] == 9)
													touzinumPrex++;
											}
											if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 + touzinumPrex - 56] == PlayerNum + 4)
											{
												touzinumPrex += 12;
												soundfly.setVolume(40);
												soundfly.play();
											}
										}
									}
									else//不跨越55格的跳棋
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum &&  //判断跳棋
											(QiziA[PlayerNum][qiziDianji].GePos< QiziA[PlayerNum][qiziDianji].prex - 6 || //这里的判断是为了避免终点入口附近加了touzinum后用终点另一边的颜色数值
												QiziA[PlayerNum][qiziDianji].GePos > QiziA[PlayerNum][qiziDianji].prex - 2))//因为以棋盘为一圈而不是直接连上终点所以需要这样设置
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
											for (int k = touziNum + 2; k < touziNum + touzinumPrex + 2; k++)
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + k] == 9)
													touzinumPrex++;
											}
											//判断飞棋格是否跨越55格
											if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 + touzinumPrex > 55 && QiziA[PlayerNum][qiziDianji].GePos < 56)
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 + touzinumPrex - 56] == PlayerNum + 4)
												{
													touzinumPrex += 12;
													soundfly.setVolume(40);
													soundfly.play();
												}
											}
											else
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 + touzinumPrex] == PlayerNum + 4)
												{
													touzinumPrex += 12;
													soundfly.setVolume(40);
													soundfly.play();
												}
											}
										}
									}
									//跨越55格的飞棋（因为出门没有飞棋所以出门输出模块没有设置）
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55 && QiziA[PlayerNum][qiziDianji].GePos < 56)
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum + 4)//判断飞棋
										{
											touzinumPrex += 17;
											soundfly.setVolume(40);
											soundfly.play();
											soundjump.setVolume(40);
											soundjump.play();
										}
									}
									else//不跨越55格的飞棋
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum + 4)//判断飞棋
										{
											touzinumPrex += 17;
											soundfly.play();
											soundjump.setVolume(40);
											soundjump.play();
										}
									}
									qiziBuxingTime = true;
									//cout << "chh" << n << endl;
								}
							}
						}
					}
				}
			}
		}

	}
}

void Game::Draw()
{
	//想输出现在轮回的文字，未成功（问题）
	text.setCharacterSize(120);
	text.setString(L"现在轮回");
	text.setFillColor(Color(255, 255, 0, 255));
	text.setOrigin(100, 25);
	text.setPosition(300, 50);
	window.draw(text);

	if (GameStart == true)
	{
		window.clear();

		sBackBegin.setTexture(tBackBegin);
		sBackBegin.setPosition(0, 0);
		window.draw(sBackBegin);//绘制背景

		if (isChange == false) {
			sBeginButton.setTexture(tBeginButton1);//绘制开始按钮
		}
		else
		{
			sBeginButton.setTexture(tBeginButton2);
		}
		sBeginButton.setPosition(513, 513);

		BeginButton.left = 500;
		BeginButton.top = 500;
		BeginButton.width = 100;
		BeginButton.height = 100;

		window.draw(sBeginButton);
	}

	///游戏进行界面
	if (GamePlay == true)
	{
		DrawPlay();
		if (touziTime == true && touziInitial == true)//骰子时间并且骰子已初始化
		{
			touziDraw();//绘制骰子帧动画
		}
		else//不是骰子时间，画静止的就可
		{
			s_touzi.setTextureRect(IntRect(touziNum * ButtonWidth, 0, ButtonWidth, ButtonHeight));
			s_touzi.setPosition(530, 330);
			window.draw(s_touzi);
		}
	}

	if (GameEnd == true)
	{
		sPaiHang.setPosition(436, 160);//绘制排行榜图片
		window.draw(sPaiHang);

		for (int i = 0; i < 4; i++)
		{
			sQizi[i].setScale(1.4, 1.4);//放大
			sQizi[i].setOrigin(0, 0);//还原初始偏移（因为drawplay中绘制棋子会有初始偏移）
			sQizi[i].setPosition(570, 275 + WinPai[i] * 60);//根据排名绘制不同y值的位置

			window.draw(sQizi[i]);
		}
	}
	window.display();
}

void Game::touzi()//初始化骰子数
{
	//遍历玩家的四个棋子,检测isStop
	/*for (int i = 0; i < 4; i++)
	{
		if (QiziA[PlayerNum][i].isStop == true)
		{
			QiziA[PlayerNum][i].isStop = false;
			PlayerNum++;
			qiziBuxingTime = false;
			return;
		}
	}*/
	touziNuml = touziNum;
	touziNum = rand() % 6;
	while (IsPlayerTurn())
	{
		if (Keyboard::isKeyPressed(Keyboard::Num1))
		{
			touziNum = 0;
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2))
		{
			touziNum = 1;
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3))
		{
			touziNum = 2;
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4))
		{
			touziNum = 3;
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5))
		{
			touziNum = 4;
			break;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6))
		{
			touziNum = 5;
			break;
		}
	}
	//if (touziReduce != 0)
	//{
	//	touziNum -= touziReduce;
	//	if (touziNum<1)
	//	{
	//		touziNum = 0;
	//	}
	//	touziReduce = 0;
	//}
	TouziFlash_n = 0;
	TouziFlash[0] = touziNuml;
	TouziFlash[19] = touziNum;
	for (int i = 0; i < 20; i++)
	{
		TouziFlash[i] = rand() % 6;
	}
	touziInitial = true;
}
void Game::touziDraw()//绘制骰子

{
	if (TouziFlash_n == 0 || TouziFlash_n == 20)//开始一帧和结束一帧
	{
		if (TouziFlash_n == 0)
		{
			s_touzi.setTextureRect(IntRect(touziNuml * ButtonWidth, 0, ButtonWidth, ButtonHeight));
			TouziFlash_n++;
		}
		else
		{
			s_touzi.setTextureRect(IntRect(touziNum * ButtonWidth, 0, ButtonWidth, ButtonHeight));
			touziTime = false;
			if (touziTime == false && touziNum != 5 && QiziA[PlayerNum][0].isHome == true && QiziA[PlayerNum][1].isHome == true && QiziA[PlayerNum][2].isHome == true && QiziA[PlayerNum][3].isHome == true)
			{
				touziTime = true;
				do
				{
					if (PlayerNum == 3)
						PlayerNum = 0;
					else
						PlayerNum++;
				} while (PlayerWin[PlayerNum] == true);//若有玩家结束则跳过该玩家
			}
			touziInitial = false;
		}
		s_touzi.setPosition(530, 330);
		if (TouziFlash_n == 20)
		{
			window.draw(s_touzi);
			window.display();
			Sleep(500);
		}

	}
	else//过程旋转效果过渡帧
	{
		s_touzi2.setTextureRect(IntRect(0, TouziFlash[TouziFlash_n] * ButtonWidth, ButtonWidth, ButtonHeight));
		s_touzi2.setPosition(530, 330);
		window.draw(s_touzi2);
		TouziFlash_n++;
	}
}
void Game::DrawPlay()
{
	window.clear();
	sBackPlay.setTexture(tBackPlay);
	sBackPlay.setPosition(0, 0);
	window.draw(sBackPlay);//绘制游戏场景

	//sEventBingLiang.setTexture(tEventBingLiang);
	//sEventBingLiang.setScale(0.5, 0.5);
	////sEventBingLiang.setOrigin(sEventBingLiang.getTextureRect().width / 2, sEventBingLiang.getTextureRect().height / 2);
	//sEventBingLiang.setOrigin(sEventBingLiang.getTextureRect().width/2 , sEventBingLiang.getTextureRect().height/2);
	//sEventBingLiang.setPosition(440, 220);
	//window.draw(sEventBingLiang);

	//sEventChiTu.setTexture(tEventChiTu);
	//sEventChiTu.setScale(0.5, 0.5);
	////sEventChiTu.setOrigin(sEventChiTu.getTextureRect().width, sEventChiTu.getTextureRect().height/2);
	//sEventChiTu.setPosition(290, 20);
	//window.draw(sEventChiTu);

	//画棋子
	for (int i = 0; i < 4; i++)
	{
		if (i == PlayerNum && touziTime == false)//将该轮回玩家的棋子放大
		{
			sQizi[PlayerNum].setOrigin(7, 7);//放大会有偏移，设置初始位置偏移修正
			sQizi[PlayerNum].setScale(1.3, 1.3);
		}
		else
		{
			sQizi[i].setScale(1, 1);//该轮回结束还原
			sQizi[i].setOrigin(0, 0);
		}
		for (int j = 0; j < 4; j++)
		{
			if (QiziA[i][j].isHome == true || QiziA[i][j].isDoor == true)//在家或在门口
			{
				if (QiziA[i][j].isHome == true)//在家
				{
					if (i == PlayerNum && QiziA[i][j].isend == false && touziTime == false)
					{
						stouyin.setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);//当前玩家棋子加投影
						window.draw(stouyin);
					}
					sQizi[i].setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);
					window.draw(sQizi[i]);
				}
				else//在门口
				{
					if (i == PlayerNum && touziTime == false)
					{
						stouyin.setPosition(DPosition[QiziA[i][j].prex][0] + QiziA[i][j].prex2[0], DPosition[QiziA[i][j].prex][1] + QiziA[i][j].prex2[1]);
						window.draw(stouyin);//当前玩家棋子加投影
					}
					sQizi[i].setPosition(DPosition[QiziA[i][j].prex][0] + QiziA[i][j].prex2[0], DPosition[QiziA[i][j].prex][1] + QiziA[i][j].prex2[1]);
					window.draw(sQizi[i]);
				}
			}

			else//路上或者结束回家
			{
				if (i == PlayerNum && j == qiziDianji && qiziBuxingTime == true)//只对选择的一个棋子在步行时间进行绘制调整，避免其他棋子出现闪烁现象
					QiziBuxing();
				else
				{
					if (QiziA[i][j].isend == false)//棋子未结束绘制在路上
					{
						if (i == PlayerNum && touziTime == false)
						{
							stouyin.setPosition(DPosition[QiziA[i][j].GePos][0], DPosition[QiziA[i][j].GePos][1]);
							window.draw(stouyin);//当前玩家棋子加投影
						}
						sQizi[i].setPosition(DPosition[QiziA[i][j].GePos][0], DPosition[QiziA[i][j].GePos][1]);
						window.draw(sQizi[i]);
					}
					else
					{
						sQizi[i].setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);
						window.draw(sQizi[i]);//玩家只有结束后棋子不给予投影，表示棋子任务已结束且不可点击操作
					}
				}
			}
		}
	}
}

void Game::Run()
{
	do {
		Initial();
		while (window.isOpen() && gameOver == false) {
			Input();
			Draw();
		}
	} while (!gameQuit);
}

bool Game::TouziPosClicked() {
	return (sf::Mouse::getPosition(window).x > 500 && sf::Mouse::getPosition(window).x < 580
		&& sf::Mouse::getPosition(window).y >320 && sf::Mouse::getPosition(window).y < 380);
	
}
bool Game::IsPlayerTurn() {
	if (PlayerNum == 0)
		return true;
	else
		return false;
}
int Game::AiDoChoice() {
	if (touziNum == 5) {
		for (int i = 0; i < 4; i++) {
			if (!QiziA[PlayerNum][i].isend)
				return i;
		}
	}
	for (int i = 0; i < 4; i++) {
		if (!QiziA[PlayerNum][i].isend && !QiziA[PlayerNum][i].isHome)
			return i;
	}
	return -1;
}