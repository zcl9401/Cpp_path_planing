#include <opencv2/opencv.hpp>
#include<iostream>

using namespace std;


class Cell{
        public:
                Cell(int S=0, float V=1){
                        STATA = S;
                        VALUE = V;
                }
                void set(){
                        switch(STATA){
                                case -1:
                                        bgr(0, 0, 0);
                                        break;
                                case 0:
                                        bgr(128, 128, 128);
                                        break;
                                case 1:
                                        bgr(50, 50, 255);
                                        break;
                                case 2:
                                        bgr(50, 255, 50);
                                        break;
                                case 3:
                                        bgr(255, 50, 50);
                                }
                        }

                void bgr(int b, int g, int r){
                        B = b;
                        G = g;
                        R = r;
                }
                int LOCAL_X;
                int LOCAL_Y;
                int B;
                int G;
                int R;
                int STATA;// -1 障碍物;  0 未入列;  1 入列表;  2 出列表;  3标记点  
                float VALUE;

};

class Map{
        public:
                Map(int l, int n, int ambient_B=0,int ambient_G=0,int ambient_R=0)
                : LENGTH(l), SIZE(n), AMBIENT_B(ambient_B), AMBIENT_G(ambient_G), AMBIENT_R(ambient_R)
                {}

                void createWorld(){
                        cv::Mat world(LENGTH, LENGTH, CV_8UC3, cv::Scalar(AMBIENT_B, AMBIENT_G, AMBIENT_R));
                        MAP_IMAGE = world;
                }

                void showMap(const Map& m){
                        cv::namedWindow(m.NAME, cv::WINDOW_NORMAL);
                        cv::imshow(m.NAME, MAP_IMAGE);
                        cv::waitKey(0);
                        cv::destroyAllWindows();
        }

                void makeMap(){
                        for (int i=0; i<SIZE*SIZE; i++) {
                                int x = (i % SIZE) * (LENGTH / SIZE);
                                int y = (i / SIZE) * (LENGTH / SIZE);
                                cv::Rect rect(x, y, LENGTH/SIZE, LENGTH/SIZE);
                                cv::rectangle(MAP_IMAGE, rect, cv::Scalar(cells[i].B, cells[i].G, cells[i].R), -1);
                                cv::rectangle(MAP_IMAGE, rect, cv::Scalar(255, 255, 255), 0.03*SIZE);
                        }
                        delete[] cells;
                }

                int** packCells(int num, int distribution[][2]){
                        cells = new Cell[SIZE*SIZE];
                        for (int j=0; j<num; j++) {
                                cells[distribution[j][0]].STATA = distribution[j][1];
                        }

                        int** STATA_LIST = new int*[SIZE*SIZE];

                        for (int k=0; k<SIZE*SIZE; k++) {
                                cells[k].set();
                                if (cells[k].STATA == -1) {
                                        cells[k].VALUE = -1;
                                }
                                STATA_LIST[k][0] = cells[k].STATA;
                                STATA_LIST[k][1] = cells[k].VALUE;
                        }
                        return STATA_LIST;
                }

                int reduceDimension(int x, int y){
                        return x + y * SIZE;
                }

                ~Map(){
                }


        private:
                std::string NAME;
                const int LENGTH;
                const int SIZE;
                int AMBIENT_B;
                int AMBIENT_G;
                int AMBIENT_R;
                cv::Mat MAP_IMAGE;
                Cell* cells;
};


int main(){

	return 0;
}
