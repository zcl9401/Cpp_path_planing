#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

struct GridNode {
    int x, y;  // 坐标
    int dist;  // 距离起点的距离

    GridNode(int _x, int _y, int _dist) : x(_x), y(_y), dist(_dist) {}

    bool operator<(const GridNode& other) const {
        return dist > other.dist;  // 用于优先队列的比较函数，按距离由小到大排列
    }
};

vector<vector<int>> astar(const vector<vector<int>>& grid, const pair<int, int>& start, const pair<int, int>& goal) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int, int>>> prev(rows, vector<pair<int, int>>(cols));

    priority_queue<GridNode> pq;
    pq.push(GridNode(start.second, start.first, 0));
    dist[start.second][start.first] = 0;

    while (!pq.empty()) {
        GridNode curr = pq.top();
        pq.pop();

        int x = curr.x;
        int y = curr.y;

        if (x == goal.second && y == goal.first) {
            break;
        }

        vector<pair<int, int>> neighbors = {{x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
        for (const auto& neighbor : neighbors) {
            int nx = neighbor.first;
            int ny = neighbor.second;

            if (nx >= 0 && nx < cols && ny >= 0 && ny < rows && grid[ny][nx] == 0) {
                int new_dist = dist[y][x] + 1;
                if (new_dist < dist[ny][nx]) {
                    dist[ny][nx] = new_dist;
                    prev[ny][nx] = {x, y};
                    pq.push(GridNode(nx, ny, new_dist));
                }
            }
        }
    }

    vector<vector<int>> path(rows, vector<int>(cols, 0));

    // 从终点回溯到起点，得到最短路径
    pair<int, int> curr = goal;
    while (curr != start) {
        path[curr.second][curr.first] = 1;
        curr = prev[curr.second][curr.first];
    }
    path[start.second][start.first] = 1;

    return path;
}

void visualizeGrid(const vector<vector<int>>& grid, const vector<vector<int>>& path) {
    Mat img(grid.size(), grid[0].size(), CV_8UC3);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (grid[i][j] == 0) {
                img.at<Vec3b>(i, j) = Vec3b(255, 255, 255);  // 白色表示可通行区域
            } else {
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 0);  // 黑色表示障碍物区域
            }

            if (path[i][j] == 1) {
                img.at<Vec3b>(i, j) = Vec3b(0, 0, 255);  // 蓝色表示最短路径
            }
        }
    }

    namedWindow("Grid Map", WINDOW_NORMAL);
    imshow("Grid Map", img);
    waitKey(0);
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
	{0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0} }; 

    pair<int, int> start = {0, 0};
    pair<int, int> goal = {19, 19};

    vector<vector<int>> path = astar(grid, start, goal);

    visualizeGrid(grid, path);

    return 0;
}

