#include<stdio.h>
#include<iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n = 5;//5��������
int fn = 6;//6���ļ�
int m = 2;//��������
int r = 3;//����3����
int cloud_lat[6];//�������ص�cost�ӳ�
int netlat[5][5];//�����ӳ�
int lam[5][6];//�����滻
double p[5][6];//���ж�
double q[5][6];//����Ƶ��
int lalimit[5];//ÿ���������ڵ������ӳ�
double limit_theta[5];//�ۼ��ӳ�
double lyapunov = 0;//L
double lyapunov_delta = 0;//delta L
bool file_satis[5][6];
double cost_1;//δ�Ż�
double cost_2;//�Ż�
double b_limit = 0;//B����
double cost_all;
double cost_new;
double benefit;

int edgefile[5][6];//��ĳ���ڵ���� ��ȡȫ���ļ��������ӳ�

//�������
bool satis(int x,int y) {
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

//ȫ�ּ��� ��������� 
bool satis_all() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (file_satis[i][j] == false&&q[i][j]!=0) return false;
		}
	}
	return true;
}

// ����cost
int getcost() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cost_1 += p[i][j] * edgefile[i][j];
		}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (q[i][j] != 0) {
				b_limit += lalimit[i] * lalimit[i];
			}
		}
	}
	b_limit = b_limit / 2;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			if (q[i][j] != 0) {
				cost_2 += limit_theta[i] * (edgefile[i][j] - lalimit[i]);
			}
		}
	}
	return  cost_1 + b_limit + cost_2;

}
//�滻����
void eccr(int edge,int file) {
	cost_new = 0;
	for (int a = 0; a < 5; a++) {
		for (int b = 0; b < 6; b++) {
			if (lam[a][b] == 1 && a != edge && b != file) {
				lam[a][b] = 0;
				lam[a][file] = 1;
				cost_new = getcost();
				benefit = cost_all - cost_new;
				if (benefit > 0) {
					file_satis[a][file] = satis(a, file);
					file_satis[a][b] = satis(a, b);
					return;
				}
				else {
					lam[a][file] = 0;
					lam[a][b] = 1;
					return;
				}
			}
		}
	}
}

// ʵ��ECCR-lzk�㷨

int main() {
	int t = 1;
	int T = 0;
	cout << "����T�ִ�" << endl;
	cin >> T;
	cout << "������������ӳ�" << endl;//�˴�����ͨ�����������紫��ֻ����Ҫ��Ҫ��������ӳټ��� ��˱����ϲ����ڲ���ͨ����
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> netlat[i][j];
		}
	}
	cout << "��ʼ���" << endl;//�˴�����ͨ�����������紫��ֻ����Ҫ��Ҫ��������ӳټ��� ��˱����ϲ����ڲ���ͨ����
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			cin >> lam[i][j];
		}
	}

	while (t <= T) {
		cout << "ʱ��t= " << t << endl;
		//��������
		cout << "ÿ���ڵ��������" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "�Խڵ�" << i + 1 << "�ļ�1~6�����������" << endl;
			for (int j = 0; j < 6; j++) {
				cin >> q[i][j];
			}
		}
		cout << "ʱ��t=" << t << "����������" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				cout << q[i][j] << " ";
				if (j == 5) cout << endl;
			}
		}

		//����pi,x
		cout << "ʱ��t=" << t << "�������жȣ�" << endl;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				p[i][j] = 0.5 * p[i][j] + 0.5 * q[i][j];
			}
		}

		//���Ƚ���ȫ�ּ���
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				file_satis[i][j] = satis(i, j);
			}
		}


		//���򻯴����� ����ֻ�������������ڵ� ÿ���ļ���Ҫ���鼴�ɻָ�
		//��ֻ��������� �����������1��������� ���������������������ռ�
		//����ÿ���������ռ�Ϊ3�������ĸ��ļ��鲻����ͬʱ��һ���������ϳ���


		//����li,x
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				if (q[i][j] != 0) {
					for (int t = 0; t < 3; t++) {
						edgefile[i][j] = max(edgefile[i][j], lam[t][j] * netlat[i][t]);
					}
				}
			}
		}


		//�����ۼ��ӳ�
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 6; j++) {
				limit_theta[i] += max(0, edgefile[i][j] - lalimit[i]);
			}
		}
		//����Lyapunov����
		int lyapunov_temp = 0;
		for (int i = 0; i < 3; i++) {
			lyapunov_temp += limit_theta[i] * limit_theta[i] / 2;
		}
		lyapunov_delta = lyapunov_temp - lyapunov;
		lyapunov = lyapunov_temp;

		//lyapunov�Ż���cost
		cost_all = getcost();
		//benifit��ʼ
		int benefit = 0;
		while (!satis_all()) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 6; j++) {
					if (file_satis[i][j] == false) {//��ʼ�滻
						eccr(i, j);
					}
				}
			}
		}
	}
	//�����滻����ʾÿ���ڵ㱣���ļ���
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 6; j++) {
			cout << lam[i][j] << " ";
			if (j == 5) cout << endl;
		}
	}
	return 0;

}
