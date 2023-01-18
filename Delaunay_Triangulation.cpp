#include <bits/stdc++.h>
using namespace std;

struct Point2D{
	double x;
	double y;
};

queue<Point2D> center;
vector<pair<Point2D,Point2D> > lines;

int point_num = 500;
Point2D point[500];

Point2D GetCenter(Point2D pt1, Point2D pt2, Point2D pt3){
	double A = pt2.x - pt1.x;
	double B = pt2.y - pt1.y;
	double C = pt3.x - pt1.x;
	double D = pt3.y - pt1.y;
	double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
	double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
	double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));
	if (G == 0)
		return pt1;

	Point2D ptCenter;
	ptCenter.x = (D * E - B * F) / G;
	ptCenter.y = (A * F - C * E) / G;

	return ptCenter;
}

void make_points(){
    for(int i = 0; i < point_num; i++){
        point[i].x = rand();
        point[i].y = rand();
    }
}

double calcdis(Point2D pt1, Point2D pt2){
    return sqrt(pow(pt2.x - pt1.x,2)+pow(pt2.y - pt1.y,2));
}

bool is_center(Point2D pre_center, Point2D pt1, Point2D pt2, Point2D pt3){
    double dis1 = calcdis(pre_center, pt1);
    for(int i = 0; i < point_num; i++){
        if ((pt1.x == point[i].x && pt1.y == point[i].y) || (pt2.x == point[i].x && pt2.y == point[i].y) || (pt3.x == point[i].x && pt3.y == point[i].y)) continue;
        double dis2 = calcdis(pre_center,point[i]);
        if(dis1 > dis2) return false;
    }
    center.push(pre_center);
    return true;
}

int main(){

    double start = time(NULL);
    srand((unsigned int)time(NULL));
    make_points();

    for( int i = 0; i < point_num; i++){
        for( int j = i; j < point_num; j++){
            for( int k = j; k < point_num; k++){
                Point2D pre_center = GetCenter(point[i],point[j],point[k]);
                bool _is = is_center(pre_center,point[i],point[j],point[k]);
                if(_is){
                    lines.push_back(pair<Point2D,Point2D> (point[i],point[j]));
                    lines.push_back(pair<Point2D,Point2D> (point[j],point[k]));
                    lines.push_back(pair<Point2D,Point2D> (point[k],point[i]));
                }
            }
        }
    }

    printf("%lf",time(NULL)-start);

    return 0;
}