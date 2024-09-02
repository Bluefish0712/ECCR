//��ʽ̰�ģ��ڲ��ò��滻���������ļ���ʱ���滻����������ʱ�̶������ܲ��滻�����Ŀ飬��ʹ�����
#include<stdio.h>
#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int n = 5;//5��������
int fn = 6;//�����ļ�
int m = 2;//��������
int r = 3;///ÿ���������Ļ���ռ�Ϊ3��

int lij[5][5];//������֮��
int lix[5][6];//������������
int llimit=200;//�������
int pix[5][6];//�ȶ�popularity
int qix[5][6];//Ƶ��
int lambda[5][6];//�滻����

void request() {
	for (int i = 0; i < 5; i++) {
		/*cout << "�ڷ�����" << i + 1 << "�������ļ�1-6��";*/
		for (int j = 0; j < 6; j++) {
			cin >> qix[i][j];
		}
	}
	return ;
}
void calculate_lix() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			for (int t = 0; t < 5; t++) {
				lix[i][j] = max(lix[i][j], lambda[t][j] * lij[t][j]);
			}
		}
	}
	return ;
}
double calculate_cost() {
	double cost = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cost += pix[i][j] * lix[i][j];
		}
	}
	return cost;
}

void show1() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << lambda[i][j] << " ";
			if (j == 5) cout << endl;
		}
	}
	return ;
}

void show2() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << pix[i][j] << " ";
			if (j == 5) cout << endl;
		}
	}
	return;
}
int main() {
	//Ϊ�˼��㷽�� �ȶԷ������������ӳ��������һ���ֶ�����
	cout << "�ֶ������ӳ����" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> lij[i][j];
		}
	}
	//Ϊ�˼��㷽�� �ȶԷ������ϵ��ļ������������һ���ֶ�����
	cout << "�ֶ������ʼ�������" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> lambda[i][j];
		}
	}



	//Ϊ�˼��㷽�� �ȶԷ������ϵ��ļ��ȶ��������һ���ֶ�����
	cout << "�ֶ������ʼ�ȶ����" << endl;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> pix[i][j];
		}
	}


	//����Ҫ��
	cout << "��������" << endl;
	request();


	//��ÿ���ļ������� for each file xn do
	for (int i = 0; i < 6; i++) {

		//ͳ�ƶԵ�i���ļ��ȶ���ߵ����������� 
		int vx = 0, vy = 0;
		for (int j = 0; j < 5; j++) {
			pix[j][i] = pix[j][i]  + qix[j][i] ;
		}
		for (int j = 0; j < 5; j++) {
			if (pix[j][i] > pix[vx][i] && pix[j][i] > pix[vy][i]) {
				vy = vx;
				vx = j;

			}
			else if (pix[j][i] > pix[vx][i] && pix[j][i] <= pix[vy][i]) {
				vy = j;
			}
		}
		//��������������Ϊ����ȥ��ʱ�������ڿɷ��ļ���ķ�������ΪĿ�������
		calculate_lix();
		int VD[5] = { 0 };
		for (int j = 0; j < 5; j++) {
			if (lix[j][i] < llimit) {
				VD[i] = 1;
			}
		}
		double loss[5][6] = { 0 };
		//��ʼ�滻
		for (int j = 0; j < 5; j++) {
			if (VD[j]) {
				for (int t = 0; t < 6; t++) {
					calculate_lix();
					double cost1= calculate_cost();
					lambda[j][i] = 1;
					lambda[j][t] = 0;
					calculate_lix();
					double cost2 = calculate_cost();
					loss[j][t] = cost2-cost1;
					lambda[j][i] = 0;
					lambda[j][t] = 1;
				}
			}
		}
		//�ҵ���ʧ��С���ǿ�
		int vi=0,xi = 0;
		for (int j = 0;j < 5; j++) {
			for (int t = 0; t < 6; t++) {
				if (loss[vi][xi] > loss[j][t]) {
					vi = j;
					xi = t;
				}
			}
		}
		//�滻
		lambda[vi][xi] = 0;
		lambda[vi][i] = 1;
	}
	cout << "ȫ���滻��" << endl;
	show1();
	return 0;
}
