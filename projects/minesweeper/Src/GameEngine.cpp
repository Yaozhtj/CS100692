/****************************************
GameEngine.cpp
Author: Root
Date: 2019/12/09
Description:
�����˳�����Ϸģ�飬��GameEngine�����ռ��ֹͬ����Ⱦ��������Ҫ��Ҫ�޸ĵ��ļ�
*****************************************/
#include "GameEngine.h"

namespace GameEngine {

	// �������������ռ�
	using namespace Graphic;
	using namespace Controller;

	//Ԥ�ñ���
	size_t mapWidth = 0, mapHeight = 0;				 // ��ͼ��Ⱥ͸߶�
	UCHAR* mapCanvas = nullptr;						 // ��ͼ����ָ�룬�����������벻Ҫֱ�ӳ��Բ������ָ��
	COORD pos = { 0 }, posOld = { 0 };				 // ����λ��
	COORD posChoice = { 0 }, posChoiceOld = { 0 };	 // ѡ�е�ͼ�����λ��
	char key = '\0';								 // ���̵İ���
	bool gameFlag = false;							 // ��Ϸ����״̬
	size_t frame = 0;								 // ����Ⱦ֡��
	clock_t tic = clock();							 // ��Ϸ��ʼʱ��
	int operation = 0;								 // ִ�еĲ���
	bool isFirst = true;							 // �Ƿ�Ϊ��һ��
	UCHAR **mapArray=nullptr;						 // ��ͼ����
	// �¼ӱ���
	UCHAR **mapArrayPadding=nullptr;				 //Ϊ����߽����չ�ĵ�ͼ����
	short flagNum = 0;                               //�ѱ����
	UCHAR stepNum = 0;                               //���߲���
	bool isWin=true;                                 //��Ϸ��Ӯ
	bool isLose = false;                             //��Ϸ��Ӯ
	clock_t timeStart;                               //��ʼ��ʱ
	clock_t timeEnd;                                 //ֹͣ��ʱ
	short mineNum = 0;								 //���׸���

	/****************************************
	Function:  renderMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	���Ƶ�ǰ��ͼ
	*****************************************/
	void renderMap() {

		// ���п�ʼ����
		for (size_t i = 0; i < mapHeight + 1; i++) {
			// �ƶ����������� ���������׵��ַ�
			MovePos(0, (SHORT)i * 2 + 3);
			if (i == 0) {
				PutString("�X");
			}
			else if (i == mapHeight) {
				PutString("�^");
			}
			else {
				PutString("�d");
			}

			// �����У����Ʊ߽�
			for (size_t j = 0; j < mapWidth; j++) {
				// �ƶ���ȷ�е����꣬���Ʒ���ı߽�
				MovePos(2 + (SHORT)j * 8, (SHORT)i * 2 + 3);
				if (i == 0) {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�j");
					}
					else {
						PutString("�T�T�T�[");
					}
				}
				else if (i == mapHeight) {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�m");
					}
					else {
						PutString("�T�T�T�a");
					}
				}
				else {
					if (j < mapWidth - 1) {
						PutString("�T�T�T�p");
					}
					else {
						PutString("�T�T�T�g");
					}
				}
			}

			// ���Ƶ�ͼ
			if (i > 0 && i < mapHeight + 1) {
				// �ƶ������ף����Ʊ߽��ַ�
				MovePos(0, (SHORT)i * 2 + 2);
				PutString("�U");
				// ������ ���Ƶ���
				for (size_t j = 0; j < mapWidth; j++) {
					MovePos(2 + (SHORT)j * 5, (SHORT)i * 2 + 2);    // �ƶ���ȷ������
					const size_t mapIndex = (i - 1) * mapWidth + j; // ȷ����ͼ������±�
					char numMap[8] = "   ";							// ȷ�������ַ���
					numMap[1] = '0' + mapCanvas[mapIndex];			// ��mapCanvas[mapIndex]Ϊ1��8ʱ������ת�����ַ���
					switch (mapCanvas[mapIndex]) {
					case 0:
						// 0��ʱ����ÿհ�
						PutString("   ");
						break;
					case 1:
						// ��1��ʼ��������
						PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
						break;
					case 2:
						PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
						break;
					case 3:
						PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
						break;
					case 4:
						PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
						break;
					case 5:
						PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
						break;
					case 6:
						PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
						break;
					case 7:
						PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
						break;
					case 8:
						PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
						break;
					case 9:
						// 9Ϊ����
						PutStringWithColor(" ��", 255, 215, 0, 0, 0, 0);
						break;
						//����20Ϊ���
					case 20:
					case 21:
					case 22:
					case 23:
					case 24:
					case 25:
					case 26:
					case 27:
					case 28:
					case 29:
						PutStringWithColor(" ��", 178, 34, 34, 0, 0, 0);
						//����Ϊδ����
					default:
						PutString(" �~");
					}

					MovePos(5 + (SHORT)j * 5, (SHORT)i * 2 + 2);
					PutString("�U");
				}
			}
		}

		// ����ͼ���µ���Ļ
		Update();
	}

	/****************************************
	Function:  updateMap()
	Parameter: None(void)
	Return:    None(void)
	Description:
	����ά��������ݸ��Ƶ�һά������
	*****************************************/
	void updateMap() {
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapCanvas[j + i * mapWidth] = mapArray[i][j];
			}
		}
	}

	/****************************************
	Function:  patternCust()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�õ��û��Զ����ͼ�Ĵ�С���׵ĸ���
	*****************************************/
	void patternCust() {
		//��ر���
		char ch='0';
		size_t n=0;
		size_t i = 0;

		//����˵��
		ClearScreen();							//����
		MovePos(55, 2);
		PutStringWithColor("�Զ���ģʽ", 30, 144, 255, 0, 0, 0);
		MovePos(30, 4);
		PutString("����������Լ������ͼ��С���׵ĸ���������Ҫ��һ����Χ�ڣ���ͼ����");
		MovePos(30, 6);
		PutString("8-30֮�䣬��ͼ����8-16֮�䣬���׵ĸ������ݵ�ͼ�Ĵ�С����ѡ��");
		MovePos(30, 8);
		PutStringWithColor("ע��:�뱣֤�������ȷ�ԣ����Ҳ���ɾ��������󰴡��س���ȷ��", 178, 34, 34, 0, 0, 0);
		Update();


		//��õ�ͼ���
		MovePos(46, 10);
		PutString("�������ͼ��ȣ�8-30����");
		Update();
		MovePos(46, 11);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46+i, 11);
		}
		mapWidth = n;
		ch = '0'; n = 0; i = 0;

		//��õ�ͼ�߶�
		MovePos(46, 12);
		PutString("�������ͼ�߶ȣ�8-16����");
		Update();
		MovePos(46, 13);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46 + i, 13);
		}
		mapHeight = n;
		ch = '0'; n = 0; i = 0;

		//��õ��׸���
		MovePos(46, 14);
		PutString("��������׸�������������ͼ��С����");
		Update();
		MovePos(46, 15);
		while (ch != 13) {
			n = n * 10 + ch - '0';
			while (true) {
				ch = _getch(); if (ch >= '0' && ch <= '9' || ch == 13) break;
			}
			PutChar(ch);
			Update();
			i++;
			MovePos(46 + i, 15);
		}
		mineNum = n;
		
	}


	/****************************************
	Function:  patternChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʾģʽѡ�񣬸���ѡ������ѳ̶�ȷ����ͼ�Ĵ�С���׵ĸ���
	*****************************************/
	void patternChoice() {

		//����˵��
		ClearScreen();//����
		MovePos(62, 2);
		PutStringWithColor("���ѳ̶�", 30, 144, 255, 0, 0, 0);
		MovePos(38, 4);
		PutString("|��ģʽ|    ��ͼ��С��10x10 �ף�10       (����1��)");
		MovePos(38, 6);
		PutString("|һ��ģʽ|    ��ͼ��С��16x16 �ף�30       (����2��)");
		MovePos(38, 8);
		PutString("|����ģʽ|    ��ͼ��С��16x30 �ף�99       (����3��)");
		MovePos(38, 10);
		PutString("|�Զ���ģʽ|  ��ͼ��8-30 ��ͼ�ߣ�8-16    (����4��)");
		Update();

		//�������
		char choice;
		while (true) {
			choice = _getch();
			if (choice == '1' || choice == '2' || choice == '3'||choice=='4') break;
		}

		//��������ȷ�����ѳ̶�
		switch (choice) {
		case '1': 
			//��ģʽ
			mapWidth = 10;
			mapHeight = 10;
			mineNum = 10;
			break;
		case '2':
			//һ��ģʽ
			mapWidth = 16;
			mapHeight = 16;
			mineNum = 30;
			break;
		case '3':
			//����ģʽ
			mapWidth = 30;
			mapHeight = 16;
			mineNum = 99;
			break;
		case '4':
			//�Զ����Ѷ�
			patternCust();
		}
		ClearScreen();//����
	}

	/****************************************
	Function:  InitGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ����Ϸ
	*****************************************/
	void InitGame() {

		// ����
		ClearScreen();	

		// ȷ�����ѳ̶�
		patternChoice();

		// �����ͼ����ռ�
		mapArray = new UCHAR * [mapHeight];
		mapArray[0] = new UCHAR[mapWidth * mapHeight];
		for (size_t i = 1; i < mapHeight; i++) mapArray[i] = mapArray[i - 1] + mapWidth;
		mapArrayPadding = new UCHAR * [mapHeight+2];
		mapArrayPadding[0] = new UCHAR[(mapWidth+2) * (mapHeight+2)];
		for (size_t i = 1; i < mapHeight+2; i++) mapArrayPadding[i] = mapArrayPadding[i - 1] + mapWidth+2;
		mapCanvas = new UCHAR[mapWidth * mapHeight];

		// ��ʼ����ͼ����
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArray[i][j] = 10;
			}
		}

		// ���²����Ƶ�ͼ
		updateMap();	
		renderMap();	
	}

	/****************************************
	Function:  renderChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	����ѡ�еĵؿ�ı���
	*****************************************/
	void renderChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);        // ���屳����ɫ��ǰ����ɫֵ��ͨ������Ⱦ��֡���������㣨�˴�Ҳ���Ըĳ�ʹ��ʱ�䣩
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x; // ȷ����ͼ�±�

		MovePos(2 + x * 4, y * 2 + 3);

		// ��������ͬrenderMap�л�������Ԫ�ض�Ӧͼ��������ͬ
		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, alpha, alpha, alpha);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, alpha, alpha, alpha);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, alpha, alpha, alpha);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, alpha, alpha, alpha);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, alpha, alpha, alpha);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, alpha, alpha, alpha);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, alpha, alpha, alpha);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, alpha, alpha, alpha);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, alpha, alpha, alpha);
			break;
		case 9:
			PutStringWithColor("��", 255, 215, 0, alpha, alpha, alpha);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			PutStringWithColor("��", 178, 34, 34, alpha, alpha, alpha);
			break;
		default:
			PutStringWithColor("�~", 255, 255, 255, alpha, alpha, alpha);
		}
	}

	/****************************************
	Function:  clearChoiceBackground(COORD choice)
	Parameter: COORD choice
	Return:    None(void)
	Description:
	���choice��ָʾλ�õı���������ͬ��
	*****************************************/
	void clearChoiceBackground(COORD choice) {
		const SHORT x = choice.X, y = choice.Y;
		const size_t mapIndex = (size_t)y * mapWidth + (size_t)x;

		MovePos(2 + x * 4, y * 2 + 3);

		char numMap[8] = "  ";
		numMap[0] = '0' + mapCanvas[mapIndex];
		switch (mapCanvas[mapIndex]) {
		case 0:
			PutStringWithColor("  ", 255, 255, 255, 0, 0, 0);
			break;
		case 1:
			PutStringWithColor(numMap, 30, 144, 255, 0, 0, 0);
			break;
		case 2:
			PutStringWithColor(numMap, 0, 255, 127, 0, 0, 0);
			break;
		case 3:
			PutStringWithColor(numMap, 255, 48, 48, 0, 0, 0);
			break;
		case 4:
			PutStringWithColor(numMap, 72, 61, 139, 0, 0, 0);
			break;
		case 5:
			PutStringWithColor(numMap, 255, 105, 180, 0, 0, 0);
			break;
		case 6:
			PutStringWithColor(numMap, 148, 0, 211, 0, 0, 0);
			break;
		case 7:
			PutStringWithColor(numMap, 139, 0, 0, 0, 0, 0);
			break;
		case 8:
			PutStringWithColor(numMap, 139, 34, 82, 0, 0, 0);
			break;
		case 9:
			PutStringWithColor("��", 255, 215, 0, 0, 0, 0);
			break;
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 28:
		case 29:
			PutStringWithColor("��", 178, 34, 34, 0, 0, 0);
			break;
		default:
			PutStringWithColor("�~", 255, 255, 255, 0, 0, 0);
		}
	}

	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�������Ͳ�������������ر���
	*****************************************/
	void checkChoice() {
		FlushInput();							// ˢ�����뻺����
		pos = GetCursorPos();					// ��ȡ�������
		COORD hitLeftPos = GetCursorHitPos();	// ��ȡ�����������
		COORD hitRightPos = GetCursorHitPos(2);	// ��ȡ�Ҽ���������
		key = GetKeyHit();						// ��ȡ��������
		operation = 0;							// ��ǰ���� (0�޲�����1Ϊ�ڿ��ؿ飬2Ϊ��ֵ���ģ������Լ�ָ��)

		// ����������
		switch (key) {
		case VK_ESCAPE:
			// ESC��������Ϸ����״̬�÷����˳���Ϸ
			gameFlag = false;
			break;

		// �������Ҽ��ƶ�ѡ�е�����
		case VK_UP:
			if (posChoice.Y > 0)posChoice.Y--;
			break;
		case VK_RIGHT:
			if (posChoice.X < (SHORT)mapWidth - 1)posChoice.X++;
			break;
		case VK_DOWN:
			if (posChoice.Y < (SHORT)mapHeight - 1)posChoice.Y++;
			break;
		case VK_LEFT:
			if (posChoice.X > 0)posChoice.X--;
			break;

		// �س��Ϳո�ֱ��Ӧ����1��2
		case VK_RETURN:
			operation = 1;
			break;
		case VK_SPACE:
			operation = 2;
			break;
		}

		// ��������̨�������������ͼ����
		const size_t mouseY = (size_t)(pos.Y + 1) / 2 - 2;
		const size_t mouseX = (size_t)(pos.X - 1) / 4;
		if (mouseY < mapHeight && mouseX < mapWidth) {
			// ��û�г��߽磬����ѡ�������
			posChoice.X = (SHORT)mouseX;
			posChoice.Y = (SHORT)mouseY;
		}

		// ������Ҽ��ֱ��Ӧ����1��2
		if (hitLeftPos.X == pos.X && hitLeftPos.Y == pos.Y) {
			operation = 1;
		}
		else if (hitRightPos.X == pos.X && hitRightPos.Y == pos.Y) {
			operation = 2;
		}
	}

	/****************************************
	Fuction: loadingMap()
	Parameter:
	Return:	  
	Description:
	�����ؿ鲢�����õݹ���������չ
	*****************************************/
	void loadingMap(size_t x,size_t y) {

		//���ȷ����հ�
		mapArray[x][y] = mapArray[x][y] - 10;

		//������ֵ
		for (size_t i = 0; i < mapHeight+2; i++) {
			for (size_t j = 0; j < mapWidth+2; j++) {
				mapArrayPadding[i][j] = 100;
			}
		}
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArrayPadding[i + 1][j + 1] = mapArray[i][j];
			}
		}

		//��չ�հ�
		for (size_t i = x; i <= x + 2; i++) {
			for (size_t j = y; j <= y + 2; j++) {
				if (mapArrayPadding[i][j] >= 11 && mapArrayPadding[i][j] <= 18) {
					mapArrayPadding[i][j] = mapArrayPadding[i][j] - 10;
					for (size_t i = 0; i < mapHeight; i++) {
						for (size_t j = 0; j < mapWidth; j++) {
							mapArray[i][j] = mapArrayPadding[i + 1][j + 1];
						}
					}
				}
				else if (mapArrayPadding[i][j] == 10) {
					loadingMap(i - 1, j - 1);
				}
			}
		}

	}

	/****************************************
	Function:  renderFailTip
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʾʧ����ʾ
	*****************************************/
	void renderLoseTip() {
		
		//��ʾ��
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] == 19|| mapArray[i][j] == 29) mapArray[i][j] = 9;
			}
		}

		// ���²����Ƶ�ͼ
		updateMap();	
		renderMap();

		//��ʾʧ����ʾ
		MovePos(2,2*mapHeight+3);
		PutStringWithColor("!!!BOOM YOU LOST!!!", 178, 34, 34, 0, 0, 0);
		MovePos(2, 2 * mapHeight + 4);
		PutString("|�����ˣ������Ļ���»س��Լ���|");
		Update();
	}

	/****************************************
	Function:  renderWinTip
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʾ�ɹ���ʾ
	*****************************************/
	void renderWinTip() {

		//��ʾ����������ʱ��
		MovePos(12, 1);
		char strStep[32] = "";
		sprintf_s(strStep, "Step:%u   ", stepNum);
		PutString(strStep);
		char strTime[32] = "";
		sprintf_s(strTime, "Time:%ds  ", (int)(timeEnd - timeStart) / CLOCKS_PER_SEC);
		PutStringWithColor(strTime, 30, 144, 255, 0, 0, 0);
		
		//��ʾ�ɹ���ʾ
		MovePos(2, 2 * mapHeight + 3);
		PutStringWithColor("!!!! YOU  WIN !!!!", 30, 144, 255, 0, 0, 0);
		MovePos(2, 2 * mapHeight + 4);
		PutString("|��Ӯ�ˣ������Ļ���»س�����|");
		Update();
	}

	/****************************************
	Function:  initMap(COORD pos)
	Parameter: COORD pos
	Return:    None(void)
	Description:
	���ײ�������ʼ����ͼ
	*****************************************/
	void initMap(COORD pos) {

		// �������
		srand((unsigned)time(NULL));
		int mineX, mineY;
		for (size_t i = 0; i < mineNum;) {
			mineX = rand() % mapHeight;
			mineY = rand() % mapWidth;
			if (mineX != pos.Y && mineY != pos.X && mapArray[mineX][mineY] != 19) {
				mapArray[mineX][mineY] = 19;
				i++;
			}
		}

		//������ֵ
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArrayPadding[i + 1][j + 1] = mapArray[i][j];
			}
		}

		// ȷ������
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] >= 19) {
					mapArrayPadding[i ][j ]++;
					mapArrayPadding[i ][j+1]++;
					mapArrayPadding[i ][j + 2]++;
					mapArrayPadding[i+1][j ]++;
					mapArrayPadding[i+1][j + 2]++;
					mapArrayPadding[i + 2][j  ]++;
					mapArrayPadding[i + 2][j+1]++;
					mapArrayPadding[i + 2][j + 2]++;
				}
			}
		}

		// �����׵�ֵ
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				mapArray[i][j] = mapArrayPadding[i + 1][j + 1];
				if (mapArray[i][j] > 19) mapArray[i][j] = 19;
			}
		}

		// ���²����Ƶ�ͼ
		updateMap();	
		renderMap();	
	}

	/****************************************
	Function:  digBlock()
	Parameter: COORD(pos)
	Return:    None(void)
	Description:
	�����ؿ飬���ж��Ƿ�Ϊ��
	*****************************************/
	void digBlock(COORD pos) {

		if (isFirst) {
			// ����ǵ�һ���ߣ����ȳ�ʼ����ͼ
			initMap(pos);
			isFirst = false; // ����һ������Ϊ��
		}

		// ��ȡ�����ĵؿ�����
		size_t x = pos.Y;
		size_t y = pos.X;

		// ������������ף���ʧ��
		if (mapArray[x][y] == 19) {
			isLose = true;
		}

		// ��������֣�ֱ�ӷ���
		else if (mapArray[x][y] >= 11 && mapArray[x][y] <= 18) {
			mapArray[x][y] = mapArray[x][y] - 10;
			stepNum++;
			// ���²����Ƶ�ͼ
			updateMap();
			renderMap();
		}

		// ����ǿհף�����ɢ
		else if (mapArray[x][y] == 10) {
			loadingMap(x, y);
			stepNum++;
			// ���²����Ƶ�ͼ
			updateMap();
			renderMap();
		}
	}

	/****************************************
	Function:  flagBlock(COORD pos)
	Parameter: COORD pos
	Return:    None(void)
	Description:
	��ǻ�������
	*****************************************/
	void flagBlock(COORD pos) {

		// ���
		if (mapArray[pos.Y][pos.X] >= 10 && mapArray[pos.Y][pos.X] <= 19) {
			mapArray[pos.Y][pos.X] = mapArray[pos.Y][pos.X] + 10;
			flagNum++;
		}

		// ������
		else if(mapArray[pos.Y][pos.X] >= 20 && mapArray[pos.Y][pos.X] <= 29) {
			mapArray[pos.Y][pos.X] = mapArray[pos.Y][pos.X] - 10;
			flagNum--;
		}

		// ���²����Ƶ�ͼ
		updateMap();
		renderMap();
	}

	/****************************************
	Function:  judgeWin()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�ж��Ƿ�ɹ�
	*****************************************/
	void judgeWin() {
		//�ж��Ƿ�ʤ��
		for (size_t i = 0; i < mapHeight; i++) {
			for (size_t j = 0; j < mapWidth; j++) {
				if (mapArray[i][j] >= 9 && mapArray[i][j] <= 28) {
					isWin = false;
				}
			}
		}
	}

	/****************************************
	Function:  renderIntro()
	Parameter: None(void)
	Return:    None(void)
	Description:
	������Ϸ˵��
	*****************************************/
	void RenderIntro() {
		//����
		ClearScreen();

		//������Ϸ˵��
		MovePos(57, 3);
		PutStringWithColor("��Ϸ˵��", 178, 34, 34, 0, 0, 0);
		MovePos(41, 5);
		PutString("����ϷΪɨ����Ϸ������Ҫ�����㷭���ؿ��");
		MovePos(41, 6);
		PutString("������ʾ���ҵ���ͼ�����е��ײ����ñ�ǡ�");
		MovePos(41, 7);
		PutString("�����������£�");
		MovePos(41, 9);
		PutString("1.���������(���»س���)�����ؿ飬��");
		MovePos(41, 10);
		PutString("���������ǵ���(�׵�ͼ��Ϊ'��')����Ϸʧ��");
		MovePos(41, 11);
		PutString("�������ĵؿ�����ʾ�������Ǹõؿ��������");
		MovePos(41, 12);
		PutString("���ڵ��׵ĸ�����");
		MovePos(41, 14);
		PutString("2.�������Ҽ�(���¿ո��)�Եؿ���б�"); 
		MovePos(41, 15);
		PutString("�ǻ������(��ǵ�ͼ��Ϊ'��')");
		MovePos(41, 17);
		PutString("3.��������з��׵ؿ鷭�������������׳ɹ�");
		MovePos(41, 18);
		PutString("��ǣ�����Ϸʤ����");
		MovePos(46, 21);
		PutString("(�����Ļ���߰��»س����ز˵�)");
		Update();
		
		//�ȴ�����
		while (true) {
			checkChoice();
			if (operation == 1 || operation == 2) break;
		}
	}

	/****************************************
	Function:  Play()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ��Ϸ
	*****************************************/
	void Play() {
		timeStart = clock();							//��ʼ��ʱ
		flagNum = 0;									//��ʼ�������
		stepNum = 0;									//��ʼ������
		isFirst = true;									
		isLose = false;
		gameFlag = true;
		
		//����ѭ��
		while (gameFlag) {
			timeEnd = clock();
			isWin = true;
			checkChoice(); // �������

			// �鿴��ǰ�����Ƿ���Ҫ���±���
			if (posChoice.X != posChoiceOld.X || posChoice.Y != posChoiceOld.Y) {
				clearChoiceBackground(posChoiceOld);
				posChoiceOld = posChoice;
			}
			renderChoiceBackground(posChoice);

			// ���õ�ǰѡ��λ�õ��ַ�������ѡ��λ�á���������������ʣ���������,��ʱ�䡯
			MovePos(2, 0);
			char strChoice[32] = "";
			sprintf_s(strChoice, "Choice(%u, %u)  ", posChoice.X+1, posChoice.Y+1);
			PutString(strChoice);
			char strFlag[32] = "";
			sprintf_s(strFlag, "Mine:%d  ", mineNum-flagNum);
			PutString(strFlag);
			char strStep[32] = "";
			sprintf_s(strStep, "Step:%u  ", stepNum);
			PutString(strStep);
			char strTime[32] = "";
			sprintf_s(strTime, "Time:%ds  ", (int)(timeEnd-timeStart)/CLOCKS_PER_SEC);
			PutString(strTime);
			Update();

			// �������������Ϊִ����Ӧ����
			switch (operation) {
			case 1:
				// ����
				digBlock(posChoice);
				break;
			case 2:
				// ���
				flagBlock(posChoice);
				break;
			}

			//�ж��Ƿ�ʧ��
			if (isLose) {
				renderLoseTip();//����ʧ����ʾ
				// �ȴ�����
				while (true) {
					checkChoice(); 
					if (operation == 1 || operation == 2) break;
				}
				//��Ϸ����
				gameFlag = false;
			}

			//�ж��Ƿ�ʤ��
			if (operation ==1|| operation==2) {
				judgeWin();
				if (isWin) {
					renderWinTip();//���Ƴɹ���ʾ
					// �ȴ�����
					while (true) {
						checkChoice(); 
						if (operation == 1 || operation == 2) break;
					}
					//��Ϸ����
					gameFlag = false;
				}
			}

			//����ÿ֡������
			updateMap(); // ���µ�ͼ����
			Update();    // ���²�������Ļ

			frame++;  // ��Ⱦ֡������
			clock_t elapsed = 25 - (clock() - tic); // �����һ֡��Ⱦʱ�䣬��������25�Ĳ�ֵ
			Sleep(elapsed > 0 ? elapsed : 0);	    // ����ֵ�����㣬�����߸ò�ֵ�ĺ���������ȷ��ÿ֡��Ⱦ������50֡
			tic = clock();						    // ������һ�μ�¼��ʱ��
		}
	}

	/****************************************
	Function:  DestroytGame()
	Parameter: None(void)
	Return:    None(void)
	Description:
	������Ϸ�����ն�̬����ı���
	*****************************************/
	void DestroyGame() {
		delete[] mapCanvas;
		delete[] mapArray[0];
		delete[] mapArray;
		delete[] mapArrayPadding[0];
		delete[] mapArrayPadding;
	}
}