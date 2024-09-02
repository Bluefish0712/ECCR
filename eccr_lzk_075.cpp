//ECCR 0705
#include<stdio.h>
#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// ������ؽṹ��ͱ���

int edgenet[5][5];	 //li,j

int edgefile[5][6] = { 0 };  //li,x

int cloudfile[6];		

double p[5][6] = { 0 };
double q[5][6] = { 0 };

double a ;//pixϵ��
double b ;//costϵ��

int user_request[5][6] = { 0 };

int file_not[5][6] = { 0 };

int lam[5][6];		//answer

double latency[5] = { 0 };		//�ۼ��ӳ� Ư��

int latency_limit[5];

double lyapunov=0;
double lyapunov_delta = 0;

int cost_pl = 0;
int cost_last = 0;
int cost_all = 0;

double b_limit = 0;

// �������·������
//�˴�Ϊ�򻯼��� ֱ�Ӹ�����������·������

//�Խڵ��ĳ���ļ��Ƿ�����
bool satis(int x, int y) {
	if (q[x][y] != 0) {//���û����� ��ʼ����
		int cnt = 0;
		for (int t = 0; t < 3; t++) {
			if (lam[t][y] != 0) cnt++;
		}
		if (cnt >= 2) return true;
		else return false;
	}
	return true;
}

bool satisfied() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (file_not[i][j] == 1 && q[i][j] != 0) return false;
		}
	}
	return true;
}


// ����cost

int getcost() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cost_pl += p[i][j] * edgefile[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (user_request[i][j] != 0) {
				b_limit += latency_limit[i] * latency_limit[i];
			}
		}
	}
	b_limit = b_limit / 2;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (user_request[i][j] != 0) {
				cost_last += latency[i] * (edgefile[i][j] - latency_limit[i]);
			}
		}
	}
	return b * cost_pl + b_limit + cost_last;

}


// ʵ��ECCR-lzk�㷨

int main() {
	int t = 0;
	int T = 0;
	cout << "����T�ִ�" << endl;
	cin >> T;
	cout << "����pi,xϵ��a" << endl;
	cin >> a;
	cout << "����costϵ��b" << endl;
	cin >> b;
	cout << "������������ӳ�" <<endl;//�˴�����ͨ�����������紫��ֻ����Ҫ��Ҫ��������ӳټ��� ��˱����ϲ����ڲ���ͨ����
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> edgenet[i][j];
		}
	}
	

	while (t <= T) {
		cout << "ʱ��t= " << t << endl;
		//��������
		cout << "ÿ���ڵ��������" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "�Խڵ�" << i + 1 << "�ļ�1~6�����������" << endl;
			for (int j = 0; j < 6; j++) {
				cin >> user_request[i][j] ;
			}
		}
		cout << "ʱ��t=" << t << "����������" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				cout << user_request[i][j] << " ";
				if (j == 5) cout << endl;
			}
		}
		//����qi,x
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				q[i][j] = user_request[i][j];
			}
		}
		
		//����pi,x
		cout << "ʱ��t=" << t << "�������жȣ�" << endl;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				p[i][j] = a * p[i][j] + (1 - a) * q[i][j];
			}
		}
		
		//����li��x ������� ����n=3 room=3
		for (int i = 0; i < 5; i++) {
			int cnt = 0;
			for (int j = 0; j < 6; j++) {
				if (user_request[i][j] != 0) {
					for (int t = 0; t < 5; t++) {
						if (lam[t][j] != 0) {
							cnt++;
							if (t != i)
								edgefile[i][j] = max(edgefile[i][j], lam[t][j] * edgenet[i][t]);
						}
					}
					if (cnt < 3) {
						//�˴������� �������� edgefile���������-1
						edgefile[i][j] = -1;
						file_not[i][j] = 1;
					}
				}
			}
		}

		//�����ۼ��ӳ�
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 6; j++) {
				latency[i] += max(0, edgefile[i][j] - latency_limit[i]);
			}
		}
		//����Lyapunov����
		int lyapunov_temp = 0;
		for (int i = 0; i < 5; i++) {
			lyapunov_temp += latency[i] * latency[i] / 2;
		}
		lyapunov_delta = lyapunov_temp - lyapunov;
		lyapunov = lyapunov_temp;

		//lyapunov�Ż���cost
		cost_all = getcost();
		//benifit��ʼ
		int benefit = 0;

		//����ִ��
		for (int i = 0; i < 5; i++) {
			//���㵱������
			while (1) {
				for (int j = 0; j < 5; j++) {
					for (int k = 0; k < 6; k++) {
						for (int t = 0; t < 6; t++) {
							int cost_new = 0;//�滻
							if (file_not[t] && edgefile[j][k]) {
								lam[j][t] = 1;
								lam[j][k] = 0;
								cost_new = getcost();
								benefit = cost_all - cost_new;
								if (benefit > 0&&satisfied()) continue;
								else {
									lam[j][t] = 0;
									lam[j][k] = 1;
								}
							}
						}
					}
				}
			}
		}
		t = t + 1;
	}
	//�����滻����ʾÿ���ڵ㱣���ļ���
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cout << edgefile[i][j] << " ";
			if (j == 5) cout << endl;
		}
	}
	return 0;

}

