#include <iostream>
#include <cmath>
using namespace std;


class Result {
public:
	int* S;
	Result(){
		S = {};
	}
	//int** S_path;
};


int* plan_dijkstar(int** map, const int size, int start[2], int end[2]){

	// map[i][0/1] 状态和代价；
	// size 地图大小；
	// start 起点坐标；
	// end 终点坐标；
		
	int side = sqrt(size);

	int* S = new int [size]; // 代价	
	//int** S_path = new int* [size]; // 路径

	int* U = new int [size];
	//int** U_path = new int* [size];

	// 初始化
	if (map[start[0]+side*start[1]-1][0] == -1 ||
 	    start[0]+side*start[1] < 0 ||
	    start[0]+size*start[1] >= size || 
	    map[end[0]+side*end[1]][0] == -1 ||
	    end[0]+side*end[1] < 0 ||
	    end[0]+side*end[1] >= size ) {
		cout << "START OR END INVLID ! \n";
		Result error;

//		return error;
	}
	
	for (int i=0; i<size; i++) {
		S[i] = 65535;
		U[i] = 65535;
	}

	S[start[0]+side*start[1]-1] = 0;
	//S_path[start[0]+side*start[1]-1][0] = start[0]+side*start[1];
	
	for (int i=0; i<size; i++) { 	
		int arround[4] = {start[0]+side*start[1]-1,
	 			  start[0]+side*start[1]-1-side,
				  start[0]+side*start[1]-1+side,
				  start[0]+side*start[1] };

		int min = arround[0];
		for (int j=0; j<4; j++) {
			if (arround[j] < 0 || map[arround[j]][0]==-1) continue;
			U[arround[j]] = map[arround[j]][1];
	
			if (min <= U[j]) {
				min = arround[j];
				cout <<U[j]<<"\n";
			}
		}
	S[min] = U[min];
	start[0] = min % side;
	start[1] = min / side;
	}
	


	

	// 输出
//	Result result;
//	result.S = S;
	return S;



}


int main(){


	cout << "dijkstar start! \n";
	
	int row1[] = {0, 0, 0, 0};
	int row2[] = {0, 0,-1, 0};
	int row3[] = {0,-1, 0, 0};
	int row4[] = {0, 0, 0, 0};

	int* map[] = {row1, row2, row3, row4};
	cout << "===1=== \n" ;
	int start[2] = {0, 0};
	int end[2] = {3, 3};
	cout << "===2=== \n" ;
	cout << "===3=== \n" ;

	int* res = plan_dijkstar(map, 16, start, end);

	cout <<"hello" ;

	for (int i=0; i<16; i++) {
		cout << res[i] << "\n" ;
	}

	cout <<"over" ;



	return 0;
}
