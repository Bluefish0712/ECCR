//5�������� 6���ļ� ÿ������������Ϊ3 ÿ���ļ���Ҫ3��ָ�
//ÿ������������1���ļ���1���� 
//�滻����Ϊ �ھ������ƻ������Ե�ǰ���� ����̰��
//������ò��ƻ������� ���ϸ���̰��
//���ƻ������Ե��ļ�ѡ����ƶ�����

#include<stdio.h>
#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int servern = 5;
int fn = 6;
int n = 6;
int m = 3;
int r = 3;

int lij[5][5];
int lix[5][6];
int llimit = 300;
int pix[5][6] = { 0 };
int qix[5][6] = { 0 };
int lambda[5][6] = { 0 };
int VD[5] = {0};

void request() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> qix[i][j];
		}
	}
	return;
}
void calculate_pq() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			pix[i][j] = qix[i][j] + pix[i][j];
		}
	}
	return;
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



bool checkforfile(int x) {
	int cnt = 0;
	for (int i = 0; i < 5; i++) {
		if (lambda[i][x] == 1) cnt += 1;
	}
	if (cnt >= m) return true;
	else return false;
}

bool checkforserver(int v) {
	int cnt = 0;
	for (int i = 0; i < 6; i++) {
		if (lambda[v][i] == 1) cnt += 1;
	}
	if (cnt > r) return false;
	else return true;
}

int calculate_cost() {
	int cost = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (checkforfile(j)) {
				cost += pix[i][j] * lix[i][j];
			}
			else {
				cost += 10000;
			}
		}
	}
	return cost;
}

void showout() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << lambda[i][j] << " ";
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
	//ÿ���ļ��������ҵ�3��
	for (int i = 0; i < 6; i++) {

		//ͳ�ƶԵ�i���ļ��ȶ���ߵ����������� 
		int vx = 0, vy = 0;
		calculate_pq();


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


		for (int a = 0; a < 5; a++) VD[a] = 0;
		for (int j = 0; j < 5; j++) {
			if (lix[j][i] < llimit) {
				VD[i] = 1;
			}
		}

		int loss[5][6] = { 0 };
		//��ʼ�滻 
		for (int j = 0; j < 5; j++) {
			if (VD[j]) {
				for (int t = 0; t < 6; t++) {
					if (lambda[j][t] == 1) {
						calculate_lix();
						double cost1 = calculate_cost();
						lambda[j][i] = 1;
						lambda[j][t] = 0;
						calculate_lix();
						double cost2 = calculate_cost();
						loss[j][t] = cost2 - cost1;
						lambda[j][i] = 0;
						lambda[j][t] = 1;
					}
				}
			}
		}
		//�ҵ���ʧ��С������
		//�Ȱ�����ʧ��С�����������
		//����ʧ��С������ 
		//ÿ����Ҫ���������� ���������ĳ���ļ�
		//�����滻�ÿ���ƻ��������� ���һ�����Ǵ��ƶ����غͻ��������ʧ��С
		//�����ƻ�������������ϸ�ʱ �����滻

		int v1=0, v2=0, v3=0;
		int x1=0, x2=0, x3=0;
		for (int j = 0; j < 5; j++) {
			for (int t = 0; t < 6; t++) {
				if (lambda[j][t]) {
					if (loss[j][t] <= loss[v1][x1]) {
						v3 = v2;
						x3 = x2;
						v2 = v1;
						x2 = x1;
						v1 = j;
						x1 = t;
					}
					else if (loss[j][t] > loss[v1][x1]&& loss[j][t] <= loss[v2][x2]) {
						v3 = v2;
						x3 = x2;
						v2 = j;
						x2 = t;

					}
					else if (loss[j][t] > loss[v1][x1] && loss[j][t] > loss[v2][x2]&& loss[j][t] <= loss[v3][x3]) {
						v3 = j;
						x3 = t;
					}
				}
			}
		}
		lambda[v1][x1] = 0;
		lambda[v2][x2] = 0;
		lambda[v3][x3] = 0;
		lambda[v1][i] = 1;
		lambda[v2][i] = 1;
		lambda[v3][i] = 1;
	}
	cout << "ȫ���滻��" << endl;
	showout();
	int costend = calculate_cost();
	cout << "eccr�滻���ܳɱ�Ϊ��" << costend << endl;
	return 0;
}
