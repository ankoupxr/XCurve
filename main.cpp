#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Core>
using namespace std;

int main()
{
	//����2��3�о��󣬲�Ϊ����ֵ
	Eigen::Matrix<float, 2, 3> matrix_23;
	matrix_23 << 1, 2, 3, 4, 5, 6;
	cout << matrix_23 << endl;
	//���ʾ����е�Ԫ��
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++)
			cout << matrix_23(i, j) << "\t";
		cout << endl;
	}
	system("pause");
}