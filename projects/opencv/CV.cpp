// ����ҵ����QAQ....
// ��־��
// 11/30 2:15 �򿪲�ϲ���õ�VS2019 Ȼ�������������ɫ������һ��Сʱqaq 
// 11/30 2:41 ���˸����˵�qaq
// 11/20 14:53 д���˲˵����˳�������ϵͳqaq  ׼���ѡ��򵥡��ļӼ��˳�д��qaq
// 12/01 0:29 ��Ϊ�ļ�������QAQ...��ʼ����  ���ظո�д�ò˵�
// 12/01 1:24 ��Ȼ�����˶�ջ���⣬զ����˵��,д���˼ӷ�������Ӧ�ü򵥵��
// 12/01 1:36 д��������
// 12/01 2:01 д����ת�� Ȼ��˯��QAQ
// 12/01 10:07 ͻȻ����һ���Ż������ȡ�Ķ�����������һά����Ҫ��...)���Ҽ�ֱ���ܸ����˹�����
// 12/01 10:26 д���˳˷���H���������˻�,ֻʣ�����ee
// 12/01 11:04 �������Ż��Ĵ���ӽ�ȥ����Ϊ������ĸ���
// 12/01 11:32 �Ż���ɣ�׼��д���
// 12/01 11:48 �Ҹо�������˾��֮ǰ���������飬��ʼд���QAQ
// 12/02 17:10 ��ɵľ���ĺ��Ĵ��� Ҳ����˶�ջ���������
// 12/02 18:06 ���ú���opencv�����������˴���ע�ͣ����Ҳд���ˣ������о������ڶ�дһ���Զ���ĺ�����Ҫ��Ȼ�����Ӧ�û�Ƚ��鷳QAQ
// 12/02 19:08  �ҷ����ˣ�demo������ֱ���ĵ�һ��
// 12/03 23:15 д���˾��Ӧ�ù�������
// 12/05 1:30 ѧϰ��һ��opencv QAQ������һ��èè��ôд��Ȼ����д�����QAQ
// 12/12 ���������־��QAQ


//����ͷ�ļ�
#include <iostream>
#include <conio.h>
#include <opencv2/opencv.hpp>
#include <cmath>

//�����ռ�Ԥ����
using namespace cv;
using namespace std;
#define sizeL 256

//����ȫ�ֱ���
int matrixA[sizeL * sizeL] = { 0 }, matrixB[sizeL * sizeL] = { 0 }, matrixC[sizeL * sizeL] = { 0 }, matrixAPad[(sizeL + 2) * (sizeL + 2)] = { 0 }, convD[sizeL * sizeL];

//��������
void tip();
void matriplus();
void nummulti();
void matritrans();
void matrimulti();
void hadamulti();
void conv_padding(int A[], int APad[], int row, int col);
void conv_ope(int APad[], int B[], int conv[], int row, int col);
int conv_sum(int array[], int row, int col);
void conv();
void wait_for_enter();
void menu();
void demo();
void otsu();
Mat extract_ope(Mat src);
void extract();

 //������
int main()
{
	// ������ر���
	char choice = 0, ch = 0;

	wait_for_enter();
	while (true)
	{
		system("cls"); //����
		menu(); //���ò˵���ʾ����
		choice = _getch();//ѡ��
		if (choice == '0') //ѡ���˳�
		{
			cout << "\n\t\t\t\t��ȷ��Ҫ�˳���? (�� \"Y\" �˳�)" << endl;
			ch = _getch();
			if (ch == 'y' || ch == 'Y')
				break;
			else
				continue;
		}

		switch (choice)
		{
		case '1':matriplus(); break;//����ӷ�
		case '2':nummulti(); break;//��������
		case '3':matritrans(); break;//����ת��
		case '4':matrimulti(); break;//����˷�
		case '5':hadamulti(); break;//Hadamard�˻�
		case '6':conv(); break;//������
		case '7':demo(); break;//���Ӧ��
		case '8':otsu(); break;//��ֵ��
		case '9':extract(); break;//ͼ��Ŀ����ȡ
		default:
			cout << "\n\t\t\t\t   �����������������QAQ..." << endl;
			wait_for_enter();
		}
	}
	return 0;
}

//�������ȴ�����
void wait_for_enter()
{
	cout << endl << "\t\t\t\t\t���س�����...";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

//�˵�����
void menu() {
	cout << "\t\t************************��ӭ�������������************************\n";
	cout << "\t\t******************************************************************\n";
	cout << "\t\t**                           --�˵�--                           **\n";
	cout << "\t\t**    1.����ӷ�             2.��������         3.����ת��      **\n";
	cout << "\t\t**    4.����˷�             5.Hadamard�˻�     6.������      **\n";
	cout << "\t\t**    7.���Ӧ��             8.OTSU�㷨��ֵ��   9.ͼ��Ŀ����ȡ  **\n";
	cout << "\t\t**    0.�������ҿ���Ͱ�0                                     **\n";
	cout << "\t\t******************************************************************\n";
	cout << "\t\t**************************��ѡ����<0~9>*************************\n";
}

//��ʾ����
void tip() {
	cout << "\n(ע:�������ʱ,��ʹ��Ӣ�����뷨,ÿ��Ԫ��֮���Զ���','����,�Էֺ�';'Ϊ���еı�־,ĩ�н�β����Ҫ�ֺš�)\n����2,3,1;4,3,2;3,6,8\n";
}

//����ӷ�����
void matriplus() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************����ӷ�************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back, c;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}

	//�����������ж���������������������������
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n���������A��" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t����A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "���������B��" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowA == rowB && colA == colB) break;
		cout << "\t����A�����B�������QAQ\n\t��������������ͬ�;���...\n";
	}
	cout << "\t����B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//���㲢���������֮��
	cout << "\n\t����A����B֮��Ϊ��\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] + matrixB[i];
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//������ز˵���ʾ
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//�������˺���
void nummulti() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************��������************\n";
	tip();
	int rowA = 0, colA = 0;
	int i = 0, n = 0;
	char back, c;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	i = 0;

	//�������
	cout << "\n���������A��" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t����A\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//��������
	cout << "����������B��\n";
	cin >> n;

	//�����������
	cout << "\t����A������B�ĳ˻�Ϊ��\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] * n;
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//������ز˵���ʾ
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//ת�ú���
void matritrans() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************����ת��************\n";
	tip();
	int rowA = 0, colA = 0;
	int i = 0, n = 0, j = 0, k = 0;
	char back, c;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	i = 0;

	//�������
	cout << "\n���������A��" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t����A\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//���ת�ú�Ľ��
	cout << "\n\t����Aת��֮��ľ���Ϊ��\n";
	for (i = 0, n = 0; j < colA; j++, n++) {
		for (k = 0, i = n; k < rowA; i = i + colA, k++) {
			cout << "\t" << matrixA[i];
		}
		cout << endl;
	}

	//������ز˵���ʾ
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//����˷�����
void matrimulti() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************����˷�************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back;
	char c;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixC[i] = 0;
	}

	//�����������ж���������������������������
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n���������A��" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t����A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "���������B��" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (colA == rowB) break;
		cout << "\t����A�����B�������QAQ\n\t������������������,��֤����A����������B������...\n";
	}
	cout << "\t����B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//���г˷����㲢������
	cout << "\n\t����A����B���Ϊ��\n";
	for (i = 0; i < rowA; i++) {
		for (j = 0; j < colB; j++) {
			for (int a = 0; a < colA; a++) {
				matrixC[colB * i + j] += matrixA[i * colA + a] * matrixB[a * colB + j];
			}
		}
	}
	for (i = 0; i < rowA * colB; i++) {
		cout << "\t" << matrixC[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//������ز˵���ʾ
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//����Hadamard�˻�����
void hadamulti() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************����Hadamard�˻�************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0;
	int i = 0, j = 0;
	char back;
	char c;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}

	//�����������ж���������������������������
	while (true) {
		for (i = 0; i < rowA * colA; i++) {
			matrixA[i] = 0;
		}
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowA = 0; colA = 0; rowB = 0; colB = 0; i = 0; j = 0;
		cout << "\n���������A��" << endl;
		cin >> matrixA[i];
		while ((c = getchar()) != '\n') {
			cin >> matrixA[++i];
			if (c == ';') rowA++;
		}
		rowA++;
		i++;
		colA = i / rowA;
		cout << "\t����A\n";
		for (i = 0; i < rowA * colA; i++) {
			cout << "\t" << matrixA[i];
			if ((i + 1) % colA == 0) cout << endl;
		}
		cout << "���������B��" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowA == rowB && colA == colB) break;
		cout << "\t����A�����B���ܽ���Hadamard���QAQ\n\t��������������ͬ�;���...\n";
	}
	cout << "\t����B\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//Hadamard�˻����㲢������
	cout << "\n\t����A����B��Hadamard�˻�Ϊ��\n";
	for (i = 0; i < rowA * colA; i++) {
		matrixA[i] = matrixA[i] * matrixB[i];
	}
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//��ʾ���ز˵�
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//�����亯��
void conv_padding(int A[], int APad[], int row, int col) {
	int colAPad, rowAPad, i;
	colAPad = col + 2;
	rowAPad = row + 2;
	for (i = 0; i < row * col; i++) {
		APad[i + col + 3 + 2 * int(i / col)] = A[i];
	}
}

//�����������
void conv_ope(int APad[], int B[], int conv[], int row, int col) {
	int i, colAPad, con_i;
	colAPad = col + 2;
	for (i = 0; i < row * col; i++) {
		con_i = i + col + 3 + 2 * int(i / col);
		conv[i] = B[0] * APad[con_i - colAPad - 1] + B[1] * APad[con_i - colAPad] + B[2] * APad[con_i - colAPad + 1]
			+ B[3] * APad[con_i - 1] + B[4] * APad[con_i] + B[5] * APad[con_i + 1]
			+ B[6] * APad[con_i + colAPad - 1] + B[7] * APad[con_i + colAPad] + B[8] * APad[con_i + colAPad + 1];
	}
}

//�������
void conv() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************������************\n";
	tip();
	int rowA = 0, colA = 0, rowB = 0, colB = 0, colAPad = 0, rowAPad = 0, con_i = 0;
	int const kernelSize = 3;
	int i = 0, j = 0;
	char c, back;

	//����ȫ�ֱ�����ֵ
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < (sizeL + 2) * (sizeL + 2); i++) {
		matrixAPad[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		convD[i] = 0;
	}
	i = 0;

	//���뱻������� 
	cout << "\n�����뱻�������A��" << endl;
	cin >> matrixA[i];
	while ((c = getchar()) != '\n') {
		cin >> matrixA[++i];
		if (c == ';') rowA++;
	}
	rowA++;
	i++;
	colA = i / rowA;
	cout << "\t���������\n";

	//������������ 
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << matrixA[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//�������˾��� 
	while (true) {
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowB = 0; colB = 0; j = 0;
		cout << "���������˷���B��3�ף���" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowB == 3 && colB == 3) break; //�жϾ�����Ƿ�Ϊ���׷��� 
		cout << "\t������Ĳ���3�׷�������������...\n";
	}

	//�������� 
	cout << "\t�����\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//������
	conv_padding(matrixA, matrixAPad, rowA, colA);
	rowAPad = rowA + 2;
	colAPad = colA + 2;

	//�������
	conv_ope(matrixAPad, matrixB, convD, rowA, colA);

	//��������ľ���
	cout << "\n\tAB������Ϊ��\n";
	for (i = 0; i < rowA * colA; i++) {
		cout << "\t" << convD[i];
		if ((i + 1) % colA == 0) cout << endl;
	}

	//��ʾ���ز˵�
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//�����Ԫ��֮��
int conv_sum(int array[],int row,int col) {
	int sum=0,i=0;
	for (; i < row * col;i++) {
		sum = sum + array[i];
	}
	return sum;
}

//�����Ӧ�á���ͼ����
void demo() {

	//�����ʾ��������ر���
	cout << "\n\t\t\t\t************��������Ӧ��************\n";
	tip();
	cout << "\n���������3�׵��Զ������˶�Lenaͼ����в���\n";
	int rowA = 0, colA = 0, rowB = 0, colB = 0, colAPad = 0, rowAPad = 0, con_i = 0,i=0,j=0;
	char c,back;
	Mat image = imread("demolena.jpg",0);//ͼ��ĻҶ�ֵ����ڸ�ʽΪMat�ı���image��

	
	//����ȫ�ֱ���
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixA[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		matrixB[i] = 0;
	}
	for (i = 0; i < (sizeL + 2) * (sizeL + 2); i++) {
		matrixAPad[i] = 0;
	}
	for (i = 0; i < sizeL * sizeL; i++) {
		convD[i] = 0;
	}

	

	//��Mat����ת��Ϊһά����
	int* array = new int[sizeL * sizeL];
	for (i = 0; i < sizeL * sizeL; i++) {
		array[i] = 0;
	}
	for (i = 0; i < image.rows * image.cols; i++) {
		array[i] = image.at<uchar>(i / image.cols, i % image.cols);
	}
	rowA = image.rows;
	colA= image.cols;
	
	//�������˾��� 
	while (true) {
		for (j = 0; j < rowB * colB; j++) {
			matrixB[j] = 0;
		}
		rowB = 0; colB = 0; j = 0;
		cout << "\n����������B��3�ף���" << endl;
		cin >> matrixB[j];
		while ((c = getchar()) != '\n') {
			cin >> matrixB[++j];
			if (c == ';') rowB++;
		}
		rowB++;
		j++;
		colB = j / rowB;
		if (rowB == 3 && colB == 3) break; //�жϾ�����Ƿ�Ϊ���׷��� 
		cout << "\t������Ĳ���3�׷�������������...\n";
	}

	//�������� 
	cout << "\t�����\n";
	for (i = 0; i < rowB * colB; i++) {
		cout << "\t" << matrixB[i];
		if ((i + 1) % colB == 0) cout << endl;
	}

	//������
	conv_padding(array, matrixAPad, rowA, colA);
	rowAPad = rowA + 2;
	colAPad = colA + 2;

	//�������
	conv_ope(matrixAPad, matrixB, convD, rowA, colA);

	//���Ծ����
	if (conv_sum(matrixB, rowB, colB) != 0) {
		for (i = 0; i < rowA * colA; i++) {
			convD[i] = convD[i] / conv_sum(matrixB, rowB, colB);
		}
	}

	//����Խ������
	for (i = 0; i < image.rows * image.cols; i++) {
		if (convD[i] < 0) convD[i] = 0;
		if (convD[i] > 255) convD[i] = 255;
	}

	//����תMat����
	Mat result = Mat(image.rows, image.cols, CV_8UC1, Scalar::all(0));
	for (i = 0; i < image.rows * image.cols; i++) {
		result.at<uchar>(i / image.cols, i % image.cols) = convD[i];
	}

	//��ʾԭͼ
	namedWindow("original", WINDOW_AUTOSIZE);
	imshow("original", image);

	//��ʾ�����ͼ��
	namedWindow("result", WINDOW_AUTOSIZE);
	imshow("result", result);
	waitKey(0);
	delete[] array;

	//��ʾ���ز˵�
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//OTSU�㷨��ֵ��
void otsu() {

	//�����ʾ
	char  begin,back;
	cout << "\n\t\t\t\t************OTSU�㷨��ֵ��************\n";
	cout << "\n�㽫��OTSU�㷨��ͼ����ж�ֵ��\n���������ʾ���...\n";
	begin = _getch();

	//����ͼƬ
	Mat src = imread("demolena.jpg");

	//�ж϶���ͼƬ�Ƿ�ɹ�
	if (src.empty()) {
		printf("could not load image...\n");
	}

	//��ʾԭͼ
	namedWindow("input");
	imshow("input", src);

	//��ֵ������(δʹ��openCV�Ķ�ֵ����ֵ����)
	int t = 127;
	Mat gray, binary;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	Scalar m = mean(src);
	t = int(m[0]);
	binary = Mat::zeros(src.size(), CV_8UC1);
	int height = src.rows;
	int width = src.cols;// ֱ�Ӷ�ȡͼ������
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int pv = gray.at<uchar>(row, col);
			if (pv > t) {
				binary.at<uchar>(row, col) = 255;
			}
			else {
			binary.at<uchar>(row, col) = 0;
			}
		}
	}


	//��ʾ��ֵ���������ͼƬ
	imshow("result", binary);
	waitKey(0);


	//��ʾ���ز˵�
	cout << "\n\t����������ز˵�...";
	back = _getch();

}

//ͼ��ָ���ȡ
void extract() {

	//�����ʾ
	char  begin, back;
	cout << "\n\t\t\t\t************openCV�ļ�Ӧ��************\n";
	cout << "\n�㽫��openCV��ͼ����зָ���ȡ����\n���������ʾ���...\n";
	begin = _getch();

	//����ͼƬ��������Mat����
	Mat src1 = imread("brain.jpg");
	Mat src2 = imread("ship.jpg");
	Mat src3 = imread("snowball.jpg");
	Mat src4 = imread("polyhedrosis.jpg");
	Mat result1, result2, result3, result4;

	//��ʾԭͼ
	namedWindow("input1", CV_WINDOW_AUTOSIZE);
	imshow("input1", src1);
	namedWindow("input2", CV_WINDOW_AUTOSIZE);
	imshow("input2", src2);
	namedWindow("input3", CV_WINDOW_AUTOSIZE);
	imshow("input3", src3);
	namedWindow("input4", CV_WINDOW_AUTOSIZE);
	imshow("input4", src4);
	
	//Ŀ����ȡ����
	result1 = extract_ope(src1);
	result2 = extract_ope(src2);
	result3 = extract_ope(src3);
	result4 = extract_ope(src4);

	//��ʾ���
	namedWindow("result1", CV_WINDOW_AUTOSIZE);
	imshow("result1", result1);
	namedWindow("result2", CV_WINDOW_AUTOSIZE);
	imshow("result2", result2);
	namedWindow("result3", CV_WINDOW_AUTOSIZE);
	imshow("result3", result3);
	namedWindow("result4", CV_WINDOW_AUTOSIZE);
	imshow("result4", result4);

	waitKey(0);

	//��ʾ���ز˵�
	cout << "\n\t����������ز˵�...";
	back = _getch();
}

//ͼ��ָ���ȡ��������
Mat extract_ope(Mat src) {

	/*������ر���*/
	Mat src_br;

	/*��ֵ��*/
	cvtColor(src, src_br, COLOR_BGRA2GRAY);
	threshold(src_br, src_br, 0, 255, THRESH_OTSU | THRESH_BINARY);

	/*��ȡ���������*/
	vector<vector<Point>>contours;
	findContours(src_br, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	vector<vector<Point> >::const_iterator it = contours.begin();
	while (it != contours.end())
	{
		if (it->size() < 100)
			it = contours.erase(it);
		else
			++it;
	}
	Mat dst(src.size(), CV_8U, Scalar(0));
	drawContours(dst, contours, -1, Scalar(255), CV_FILLED);
	cvtColor(dst, dst, CV_GRAY2RGB);

	/*����������Ĩȥ*/
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < 3 * src.cols; j++) {
			if (dst.at<uchar>(i, j) == 0) {
				src.at<uchar>(i, j) = 0;
			}
		}
	}

	/*���ؽ��ͼ��*/
	return src;
}
