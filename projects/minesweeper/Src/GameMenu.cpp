/****************************************
GameMenu.cpp
Author: Root
Date: 2019/12/09
Description:
�����˳���˵�����Ⱦ/����ģ�飬��GameMenu�����ռ��ֹͬ����Ⱦ
*****************************************/
#include "GameMenu.h"

namespace GameMenu {
	// �������������ռ�
	using namespace Graphic;
	using namespace Controller;

	size_t frame = 0;                  // ��������Ⱦ��֡�� 
	COORD pos = { 0 }, hitPos = { 0 }; // ������굱ǰ�������������������
	int choice = 0, oldChoice = 0;     // ����ѡ�еĲ˵���
	bool isChosen = false;             // �����Ƿ�����ѡ��
	char key = '\0';                   // ���嵱ǰ���̵İ���
	clock_t tic = clock();             // ���������һ֡��Ⱦ��ʱ��
	

	/****************************************
	Function:  renderMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	�������Ҵ�ӡ�������ز˵�ѡ��
	*****************************************/
	void renderMenu() {

		ClearScreen();  // ����
		MovePos(47, 6); // �ƶ����굽 14,2

		//���Ʋ˵�
		PutString("|��||��|ɨ�״���ս|��||��|"); 
		MovePos(54, 10);
		PutString("����ʼս��<");
		MovePos(54, 12);
		PutString("���鿴˵��<");
		MovePos(54, 14);
		PutString("���˳���Ϸ<");
		Update();
	}

	/****************************************
	Function:  InitMenu()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ʼ���˵���ͬʱ��ʼ��ͼ�ο�ܺͿ��������
	*****************************************/
	void InitMenu() {
		InitGraphic(130, 40); // ��ʼ���µĴ��ڴ�С
		InitController();    // ��ʼ��������
		renderMenu();        // ���Ʋ˵�
	}

	/****************************************
	Function:  randerChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	����ǰѡ�еĲ˵���(int choice)������Ⱦһ��������ʧ�İ�ɫ
	*****************************************/
	void randerChoiceBackground(int choice) {
		size_t y = 0;  // ���嵱ǰѡ�еĲ˵����ʵ��y����
		const BYTE alpha = 255 - (BYTE)((frame % 50) * 5);  // ���屳����ɫ��ǰ����ɫֵ��ͨ������Ⱦ��֡���������㣨�˴�Ҳ���Ըĳ�ʹ��ʱ�䣩
		switch (choice) {
		case 0:
			y = 10;
			break;
		case 1:
			y = 12;
			break;
		case 2:
			y = 14;
			break;
		}
		for (size_t x = 50; x < 70; x++) {
			MovePos((SHORT)x, (SHORT)y); // �������Ƶ�Ŀ���
			ModColor(2, 255, 255, 255, alpha, alpha, alpha); // �޸ı���ɫ
		}
		Update();  // ���½���
	}

	/****************************************
	Function:  clearChoiceBackground(int choice)
	Parameter: int choice
	Return:    None(void)
	Description:
	���ϴ�ѡ�еĲ˵���(int choice)�����ָ�Ϊ��ɫ�����ݴ��º���һ������һ�£�����������
	*****************************************/
	void clearChoiceBackground(int choice) {
		size_t y = 0;
		switch (choice) {
		case 0:
			y = 10;
			break;
		case 1:
			y = 12;
			break;
		case 2:
			y = 14;
			break;
		}
		for (size_t x = 50; x < 70; x++) {
			MovePos((SHORT)x, (SHORT)y);
			ModColor(2, 255, 255, 255, 0, 0, 0);
		}
	}


	/****************************************
	Function:  checkChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	������/������룬������ѡ�еĲ˵���
	*****************************************/
	void checkChoice() {
		FlushInput();           // ˢ�����뻺����
		pos = GetCursorPos();   // ��ȡ�������
		key = GetKeyHit();		// ��ȡ��������
		hitPos = GetCursorHitPos();  // ��ȡ��굥������
		isChosen = false;		// ����ѡ��״̬

		// ������λ�ã�����ѡ����
		if (!(pos.Y != 10 || pos.X < 50 || pos.X > 70)) {
			choice = 0;
		}
		else if (!(pos.Y != 12 || pos.X < 50 || pos.X > 70)) {
			choice = 1;
		}
		else if (!(pos.Y != 14|| pos.X < 50 || pos.X > 70)) {
			choice = 2;
		}

		// �����̰���������ѡ����
		switch (key) {
		case VK_UP:
			// �Ϸ����
			if (choice > 0)choice--;
			break;
		case VK_DOWN:
			// �·����
			if (choice < 2)choice++;
			break;
		case VK_RETURN:
			// �س�������ѡ��
			isChosen = true;
			break;
		}

		// ����������λ���Ƿ��ڲ˵����У�����ǣ�����ѡ��
		if (!(hitPos.Y != 10 || hitPos.X < 50 || hitPos.X > 70)) {
			isChosen = true;
		}
		else if (!(hitPos.Y != 12 || hitPos.X < 50 || hitPos.X > 70)) {
			isChosen = true;
		}
		else if (!(hitPos.Y != 14 || hitPos.X < 50 || hitPos.X > 70)) {
			isChosen = true;
		}
	}

	/****************************************
	Function:  WaitChoice()
	Parameter: None(void)
	Return:    None(void)
	Description:
	��ѭ���������˳���һֱ��Ⱦ��ȥ
	*****************************************/
	void WaitChoice() {
		bool runFlag = true;
		while (runFlag) {
			checkChoice();  // �������

			if (choice != oldChoice) {
				// ���µ�ѡ�����ѡ��һ�£�����ѡ��ı������
				clearChoiceBackground(oldChoice);
				oldChoice = choice;
			}
			randerChoiceBackground(choice); // ����ѡ����ı���

			// ���ѡ�в˵���ִ�в���
			if (isChosen) {
				switch (choice) {
				case 0:
					// ��ʼ��Ϸ
					GameEngine::InitGame();
					GameEngine::Play();
					GameEngine::DestroyGame();
					renderMenu();
					break;
				case 1:
					// ����˵��
					GameEngine::RenderIntro();
					renderMenu();
					break;
				case 2:
					// ��Flag�÷����˳�ѭ��
					runFlag = false;
					break;
				}
			}

			// ����ÿ֡������
			frame++;  // ��Ⱦ֡������
			clock_t elapsed = 25 - (clock() - tic); // �����һ֡��Ⱦʱ�䣬��������25�Ĳ�ֵ
			Sleep(elapsed > 0 ? elapsed : 0);       // ����ֵ�����㣬�����߸ò�ֵ�ĺ���������ȷ��ÿ֡��Ⱦ������50֡
			tic = clock();							// ������һ�μ�¼��ʱ��
		}
	}
}