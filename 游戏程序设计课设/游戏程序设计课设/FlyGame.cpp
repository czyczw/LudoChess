#include"FlyGame.h";
Event event;

Game::Game()
{
	Window_Width = 1080;
	Window_Height = 720;
	window.create(sf::VideoMode(Window_Width, Window_Height), L"���������");
}

Game::~Game()
{

}


void Game::Initial()
{
	window.setFramerateLimit(60);

	isChange = false;
	gameQuit = false;//��Ϸδ�˳�
	gameOver = false;//��Ϸδ����
	GameStart = true;//��Ϸ�ڳ�ʼ����
	GamePlay = false; //������Ϸ����
	GameEnd = false;//���ڽ�������
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

	///��ʼ����
	if (!tBackBegin.loadFromFile("data/images/bg3.jpg")) { cout << "��ʼ�����ز�û���ҵ�" << endl; }
	if (!tBeginButton1.loadFromFile("data/images/Begin1.png")) { cout << "��ʼ��ť1û���ҵ�" << endl; }
	if (!tBeginButton2.loadFromFile("data/images/Begin2.png")) { cout << "��ʼ��ť2û���ҵ�" << endl; }

	///��Ϸ���н���
	if (!tBackPlay.loadFromFile("data/images/PlayBK08.jpg")) cout << "��Ϸ�����ز�û���ҵ�" << endl;
	if (!tToziBut.loadFromFile("data/images/QIZI4.png")) cout << "�����ز�û���ҵ�" << endl;
	if (!tQizi1.loadFromFile("data/images/QZxm.png")) cout << "����1�ز�û���ҵ�" << endl;
	if (!tQizi2.loadFromFile("data/images/QZlzy.png")) cout << "����2�ز�û���ҵ�" << endl;
	if (!tQizi3.loadFromFile("data/images/QZzql.png")) cout << "����3�ز�û���ҵ�" << endl;
	if (!tQizi4.loadFromFile("data/images/QZbq.png")) cout << "����4�ز�û���ҵ�" << endl;
	if (!t_touzi.loadFromFile("data/images/tou1.jpg")) cout << "16�����ز�û���ҵ�" << endl;
	if (!t_touzi2.loadFromFile("data/images/tou2.jpg")) cout << "��ת�����ز�û���ҵ�" << endl;
	if (!ttouyin.loadFromFile("data/images/touyin.png")) cout << "ͶӰ�ز�û���ҵ�" << endl;
	if (!sbtouzi.loadFromFile("data/Audios/TZ.wav")) { cout << "����������û���ҵ�" << endl; }
	if (!sbyeah.loadFromFile("data/Audios/yeah.wav")) { cout << "���ӽ����ؼ�������û���ҵ�" << endl; }
	if (!bkMusic.openFromFile("data/Audios/ly68.wav")) { cout << "����������û���ҵ�" << endl; }
	if (!font.loadFromFile("data/Fonts/simsun.ttc")) cout << "����û���ҵ�" << endl;
	text.setFont(font);

	//��������
	if (!tPaiHang.loadFromFile("data/images/PH.png")) { cout << "���а��ز�û���ҵ�" << endl; }

	sBackBegin.setTexture(tBackBegin);
	sBeginButton.setTexture(tBeginButton1);
	sBackPlay.setTexture(tBackPlay);
	sQizi1.setTexture(tQizi1);   sQizi2.setTexture(tQizi2);   sQizi3.setTexture(tQizi3);   sQizi4.setTexture(tQizi4);
	stouyin.setTexture(ttouyin);
	s_touzi.setTexture(t_touzi);   s_touzi2.setTexture(t_touzi2);
	sPaiHang.setTexture(tPaiHang);
	sQizi[0] = sQizi1;	sQizi[1] = sQizi2;	sQizi[2] = sQizi3;	sQizi[3] = sQizi4;//����

	stouyin.setOrigin(10, 10);//����ͶӰ��ʼλ��ƫ����

	soundfly.setBuffer(sbfly);
	soundjump.setBuffer(sbjump);
	soundzhuang.setBuffer(sbzhuang);
	soundyeah.setBuffer(sbyeah);
	soundtouzi.setBuffer(sbtouzi);

	//����λ�ö����ʼ��ƫ�ƣ���Ϊ����������ͼƬ��һ�����ϣ�
	for (int i = 0; i < 56 + 28 + 1; i++)
	{
		DPosition[i][0] -= 20;
		DPosition[i][1] -= 20;
	}
}

void Game::QiziBuxing()
{
	for (int k = 0; k < 80; k++)//��ֵ���̶���ֻ������ѭ��һ�£���һ�����ã��ɸ�
	{

		//������ǰ������
		if (qizibuxingCount >= touziNum + touzinumPrex + 1)//����ǰ���������������������������
		{
			//������Ӹոպõ����յ�
			if (QiziA[PlayerNum][qiziDianji].GePos == DITUSIZE + 7 * (PlayerNum)+6)
			{
				QiziA[PlayerNum][qiziDianji].isend = true;
				QiziA[PlayerNum][qiziDianji].isHome = true;
				soundyeah.setVolume(60);
				soundyeah.play();

				cout << "һ���ӳɹ�" << endl;

				//�ж���Ӫ����
				int wincount = 0;
				for (int j = 0; j < 4; j++)
				{
					if (QiziA[PlayerNum][j].isend == true)
						wincount++;
				}
				if (wincount == 4)//���������Ӫ�ĸ����Ӷ�����
				{
					PlayerWin[PlayerNum] = true; //����Ӫ����
					cout << PlayerNum << "����" << endl;//����
					WinPai[PlayerNum] = endNum; //����Ӫ����
					cout << "winpai" << PlayerNum << WinPai[PlayerNum] << "endnum" << endNum << endl;//����
					endNum++;
					cout << "endnum" << endNum << endl;//����
				}
				if (endNum == 3)//���3����Ӫ����
				{
					for (int i = 0; i < 4; i++)
					{
						if (WinPai[i] == -1)//��ʣ��һ��Ϊ���һ��
							WinPai[i] = 3;
					}
					GameEnd = true;//��Ϸ�����������
				}
			}
			//�жϵ���
			for (int k = 0; k < 4; k++)
				if (QiziA[PlayerNum][k].GePos == QiziA[PlayerNum][qiziDianji].GePos || k != qiziDianji)
					diezi++;
			QiziA[PlayerNum][qiziDianji].diezishu = diezi;//�����ӵ��Ӹ߶�
			diezi = 0;
			QiziDianjiLock = false;//�ɵ����һ��
			touzinumPrex = 0;//�������ƫ�ƻ�ԭ��Ϊ0
			qiziBuxingTime = false;//���Ӳ���ʱ�����
			qizibuxingCount = 0;//����ǰ������ԭ��Ϊ0
			touziTime = true;//����ʱ��
			if (touziNum != 5)//��������Ϊ6�������һ���
			{
				do
				{
					if (PlayerNum == 3)
						PlayerNum = 0;
					else
						PlayerNum++;
				} while (PlayerWin[PlayerNum] == true);//������ҽ��������������
			}
		}
		if (k == 49)
		{
			//�����ӵ����յ���������û���꣬�򷵻�ʣ�µĲ���
			if (QiziA[PlayerNum][qiziDianji].GePos == DITUSIZE + 7 * (PlayerNum)+6)
			{
				QiziA[PlayerNum][qiziDianji].GePos -= (touziNum + 1 - qizibuxingCount);
				qizibuxingCount = touziNum + 1;
			}
			else
			{
				//��������������ǰ����������ǰ��
				if (qizibuxingCount < touziNum + 1)
				{
					//�����յ�·��
					if (QiziA[PlayerNum][qiziDianji].GePos == QiziA[PlayerNum][qiziDianji].prex - 3)
					{
						QiziA[PlayerNum][qiziDianji].GePos = DITUSIZE + 7 * (PlayerNum);
					}
					//������55ʱ������ص�0��
					if (QiziA[PlayerNum][qiziDianji].GePos == 55)
						QiziA[PlayerNum][qiziDianji].GePos = 0;
					else
						QiziA[PlayerNum][qiziDianji].GePos += 1;
					qizibuxingCount++;
					//�����������Ӵ��(������岻���)���ڲ��Ե�ʱ�����ע�ͣ��������������ٶȣ�
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
				//������������ֱ��ǰ��ʣ�²���
				else
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
				}
			}
		}
	}
	//����ͶӰ������
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
		AITURNGOTO:
		if (event.type == Event::Closed) {
			window.close();
			gameQuit = true;
		}
		if (event.type == Event::EventType::KeyReleased && event.key.code == Keyboard::Escape) {
			window.close();
			gameQuit = true;
		}
		//������������
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
		// �������ֿ���
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
				std::cout << "����������ʼ�����ƶ�" << std::endl;
			}

		}*/

		if (BeginButton.contains(event.mouseMove.x, event.mouseMove.y))
		{
			//std::cout << "����ͣ���ڰ�������ʼ����" << std::endl;
			isChange = true;
		}
		else
		{
			isChange = false;
		}


		if (GameStart == true)//��ʼ��������ģ��
		{
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
				if (sf::Mouse::getPosition(window).x > 500 && sf::Mouse::getPosition(window).x < 600
					&& sf::Mouse::getPosition(window).y >500 && sf::Mouse::getPosition(window).y < 620)
				{
					GameStart = false;//������ʼ����
					GamePlay = true;//������Ϸ����
					MusicOn = true;//�ж����ֿ�ʼ����ʱû�ã�
					bkMusic.setVolume(SoundVolume);//������������С
					bkMusic.play();//�������ֲ���
					bkMusic.setLoop(true);//��������ѭ��
				}
		}

		if (GamePlay == true)//��Ϸ��������ģ��
		{
			if (touziTime == true && touziInitial == false)//����ʱ��
			{
				if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && TouziPosClicked() || !IsPlayerTurn())//�����������λ�� 
				{
					touzi();//����������ֵ��ʼ��������
					soundtouzi.setVolume(40);
					soundtouzi.play();
					//cout << "chg" << endl;
				}
			}
			if (touziTime == false)//��Ϊ����ʱ�䣬��ѡ�����ӽ��в���
			{
				int AiChoice;
				if (!IsPlayerTurn()) {
					AiChoice = AiDoChoice();
				}
				for (int i = 0; i < 4; i++)//�������ĸ����ӿ�ѡ��
				{
					//�����AI�Ļغϣ��ж�AI��ѡ���Ƿ��Ǹ����ӣ����ǵĻ�continue;
					if (!IsPlayerTurn() && AiChoice != i) {
						continue;
					}

					if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left || !IsPlayerTurn())//������� 
					{
						//�ڼ��Ҹ�����δ������������Ϊ6
						if (QiziA[PlayerNum][i].isHome == true && QiziA[PlayerNum][i].isend == false && touziNum == 5)
						{
							if (sf::Mouse::getPosition(window).x > QiziHomePos1[PlayerNum][i][0] - 20 + 20 //����ڼ�λ��
								&& sf::Mouse::getPosition(window).x < QiziHomePos1[PlayerNum][i][0] + 20 + 20
								&& sf::Mouse::getPosition(window).y > QiziHomePos1[PlayerNum][i][1] - 20 + 20
								&& sf::Mouse::getPosition(window).y < QiziHomePos1[PlayerNum][i][1] + 20 + 20
								|| !IsPlayerTurn())
							{

								QiziA[PlayerNum][i].isHome = false;//�ڼ�״̬��Ϊ����
								QiziA[PlayerNum][i].isDoor = true;//�ſ�״̬��Ϊ���ſ�
								touziTime = true;//����Ͷһ�����ӣ���Ϊ�ո�Ϊ6��
								QiziA[PlayerNum][i].GePos = QiziA[PlayerNum][i].prex;//�������ӵĸ���λ�ñ�Ϊ�ſڵ�һ��λ��
								//cout << "chg" << i << endl;
							}
						}
						else
						{
							//�����ڼ��ſ�
							if (QiziA[PlayerNum][i].isDoor == true && QiziDianjiLock == false)
							{
								if (sf::Mouse::getPosition(window).x > DPosition[QiziA[PlayerNum][i].prex][0] + QiziA[PlayerNum][i].prex2[0] - 20 + 20 //�����ڼ��ſ�λ��
									&& sf::Mouse::getPosition(window).x < DPosition[QiziA[PlayerNum][i].prex][0] + QiziA[PlayerNum][i].prex2[0] + 20 + 20//(�����ŵ�һ���ƫ����)
									&& sf::Mouse::getPosition(window).y > DPosition[QiziA[PlayerNum][i].prex][1] + QiziA[PlayerNum][i].prex2[1] - 20 + 20
									&& sf::Mouse::getPosition(window).y < DPosition[QiziA[PlayerNum][i].prex][1] + QiziA[PlayerNum][i].prex2[1] + 20 + 20
									||!IsPlayerTurn())

								{
									//qiziDianji = i;
									for (int k = 0; k < 4; k++)//�жϵ���
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
									qiziDianji = n;//�������Ϸ�һ�����ӿɽ��벽��״̬

									QiziDianjiLock = true;//�����趨�Ļ�����ͬʱ���ſڵ�����Ҳ����ţ�
									QiziA[PlayerNum][qiziDianji].isDoor = false;//�ſ�״̬��Ϊ����
									QiziA[PlayerNum][qiziDianji].GePos = QiziA[PlayerNum][qiziDianji].prex;//�������ӵĸ���λ�ñ�Ϊ�ſڵ�һ��λ�ã��ڶ��Σ�
									//��Խ��55�������
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55  //�����������������55֮������Ҫ��ȥ56�����������������жϣ���������յ�·�ߵ�������ɫ��ֵ�ж�
										&& QiziA[PlayerNum][qiziDianji].GePos < 56)//����ΪʲôҪ��ô������
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum)//�ж��Ƿ�����
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
										}
									}
									else//����Խ55�������
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum)//�ж��Ƿ�����
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
											for (int k = touziNum + 2; k < touziNum + touzinumPrex + 2; k++)//����·���Ƿ��а׸��оͼ�һ��
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + k] == 9)
													touzinumPrex++;
											}
										}
									}
									qiziBuxingTime = true;//���벽��ʱ��
								}
							}
							//����·�����ӣ����ڼ�Ҳ�����ſڣ��������ɸ����Ϸ��ſڵ�����߼����󲿷�һ����
							else
							{
								if (sf::Mouse::getPosition(window).x > DPosition[QiziA[PlayerNum][i].GePos][0] - 20 + 20//������Ϊ�����������ҷֱ�20Ϊ�����Ч��Χ
									&& sf::Mouse::getPosition(window).x < DPosition[QiziA[PlayerNum][i].GePos][0] + 20 + 20
									&& sf::Mouse::getPosition(window).y > DPosition[QiziA[PlayerNum][i].GePos][1] - 20 + 20
									&& sf::Mouse::getPosition(window).y < DPosition[QiziA[PlayerNum][i].GePos][1] + 20 + 20
									||!IsPlayerTurn())
								{
									touzinumPrex = 0;
									int n = i;
									for (int m = i; m < 4; m++)//�жϵ���
									{
										if (QiziA[PlayerNum][m].diezishu > QiziA[PlayerNum][n].diezishu)
										{
											n = m;
										}
									}
									qiziDianji = n;
									//��Խ55�������
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55 && QiziA[PlayerNum][qiziDianji].GePos < 56)
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum)//�ж�����
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
									else//����Խ55�������
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum &&  //�ж�����
											(QiziA[PlayerNum][qiziDianji].GePos< QiziA[PlayerNum][qiziDianji].prex - 6 || //������ж���Ϊ�˱����յ���ڸ�������touzinum�����յ���һ�ߵ���ɫ��ֵ
												QiziA[PlayerNum][qiziDianji].GePos > QiziA[PlayerNum][qiziDianji].prex - 2))//��Ϊ������ΪһȦ������ֱ�������յ�������Ҫ��������
										{
											touzinumPrex += 4;
											soundjump.setVolume(40);
											soundjump.play();
											for (int k = touziNum + 2; k < touziNum + touzinumPrex + 2; k++)
											{
												if (DColor[QiziA[PlayerNum][qiziDianji].GePos + k] == 9)
													touzinumPrex++;
											}
											//�жϷ�����Ƿ��Խ55��
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
									//��Խ55��ķ��壨��Ϊ����û�з������Գ������ģ��û�����ã�
									if (QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 > 55 && QiziA[PlayerNum][qiziDianji].GePos < 56)
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1 - 56] == PlayerNum + 4)//�жϷ���
										{
											touzinumPrex += 17;
											soundfly.setVolume(40);
											soundfly.play();
											soundjump.setVolume(40);
											soundjump.play();
										}
									}
									else//����Խ55��ķ���
									{
										if (DColor[QiziA[PlayerNum][qiziDianji].GePos + touziNum + 1] == PlayerNum + 4)//�жϷ���
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
	//����������ֻص����֣�δ�ɹ������⣩
	text.setCharacterSize(120);
	text.setString(L"�����ֻ�");
	text.setFillColor(Color(255, 255, 0, 255));
	text.setOrigin(100, 25);
	text.setPosition(300, 50);
	window.draw(text);

	if (GameStart == true)
	{
		window.clear();

		sBackBegin.setTexture(tBackBegin);
		sBackBegin.setPosition(0, 0);
		window.draw(sBackBegin);//���Ʊ���



		if (isChange == false) {
			sBeginButton.setTexture(tBeginButton1);//���ƿ�ʼ��ť
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

	///��Ϸ���н���
	if (GamePlay == true)
	{

		DrawPlay();
		if (touziTime == true && touziInitial == true)//����ʱ�䲢�������ѳ�ʼ��
		{
			touziDraw();//��������֡����
		}
		else//��������ʱ�䣬����ֹ�ľͿ�
		{
			s_touzi.setTextureRect(IntRect(touziNum * ButtonWidth, 0, ButtonWidth, ButtonHeight));
			s_touzi.setPosition(530, 330);
			window.draw(s_touzi);
		}
	}

	if (GameEnd == true)
	{
		sPaiHang.setPosition(436, 160);//�������а�ͼƬ
		window.draw(sPaiHang);

		for (int i = 0; i < 4; i++)
		{
			sQizi[i].setScale(1.4, 1.4);//�Ŵ�
			sQizi[i].setOrigin(0, 0);//��ԭ��ʼƫ�ƣ���Ϊdrawplay�л������ӻ��г�ʼƫ�ƣ�
			sQizi[i].setPosition(570, 275 + WinPai[i] * 60);//�����������Ʋ�ͬyֵ��λ��

			window.draw(sQizi[i]);
		}
	}
	window.display();
}

void Game::touzi()//��ʼ��������
{
	srand(time(NULL));
	touziNuml = touziNum;
	touziNum = rand() % 6;
	TouziFlash_n = 0;
	TouziFlash[0] = touziNuml;
	TouziFlash[19] = touziNum;
	for (int i = 0; i < 20; i++)
	{
		TouziFlash[i] = rand() % 6;
	}
	touziInitial = true;
}
void Game::touziDraw()//��������

{
	if (TouziFlash_n == 0 || TouziFlash_n == 20)//��ʼһ֡�ͽ���һ֡
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
				} while (PlayerWin[PlayerNum] == true);//������ҽ��������������
			}
			touziInitial = false;
		}
		s_touzi.setPosition(530, 330);
		window.draw(s_touzi);
	}
	else//������תЧ������֡
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
	window.draw(sBackPlay);//������Ϸ����

	//������
	for (int i = 0; i < 4; i++)
	{
		if (i == PlayerNum && touziTime == false)//�����ֻ���ҵ����ӷŴ�
		{
			sQizi[PlayerNum].setOrigin(7, 7);//�Ŵ����ƫ�ƣ����ó�ʼλ��ƫ������
			sQizi[PlayerNum].setScale(1.3, 1.3);
		}
		else
		{
			sQizi[i].setScale(1, 1);//���ֻؽ�����ԭ
			sQizi[i].setOrigin(0, 0);
		}
		for (int j = 0; j < 4; j++)
		{
			if (QiziA[i][j].isHome == true || QiziA[i][j].isDoor == true)//�ڼһ����ſ�
			{
				if (QiziA[i][j].isHome == true)//�ڼ�
				{
					if (i == PlayerNum && QiziA[i][j].isend == false && touziTime == false)
					{
						stouyin.setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);//��ǰ������Ӽ�ͶӰ
						window.draw(stouyin);
					}
					sQizi[i].setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);
					window.draw(sQizi[i]);

				}
				else//���ſ�
				{
					if (i == PlayerNum && touziTime == false)
					{
						stouyin.setPosition(DPosition[QiziA[i][j].prex][0] + QiziA[i][j].prex2[0], DPosition[QiziA[i][j].prex][1] + QiziA[i][j].prex2[1]);
						window.draw(stouyin);//��ǰ������Ӽ�ͶӰ
					}
					sQizi[i].setPosition(DPosition[QiziA[i][j].prex][0] + QiziA[i][j].prex2[0], DPosition[QiziA[i][j].prex][1] + QiziA[i][j].prex2[1]);
					window.draw(sQizi[i]);
				}
			}

			else//·�ϻ��߽����ؼ�
			{
				if (i == PlayerNum && j == qiziDianji && qiziBuxingTime == true)//ֻ��ѡ���һ�������ڲ���ʱ����л��Ƶ����������������ӳ�����˸����
					QiziBuxing();
				else
				{
					if (QiziA[i][j].isend == false)//����δ����������·��
					{
						if (i == PlayerNum && touziTime == false)
						{
							stouyin.setPosition(DPosition[QiziA[i][j].GePos][0], DPosition[QiziA[i][j].GePos][1]);
							window.draw(stouyin);//��ǰ������Ӽ�ͶӰ
						}
						sQizi[i].setPosition(DPosition[QiziA[i][j].GePos][0], DPosition[QiziA[i][j].GePos][1]);
						window.draw(sQizi[i]);
					}
					else
					{

						sQizi[i].setPosition(QiziHomePos1[i][j][0], QiziHomePos1[i][j][1]);
						window.draw(sQizi[i]);//���ֻ�н��������Ӳ�����ͶӰ����ʾ���������ѽ����Ҳ��ɵ������
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