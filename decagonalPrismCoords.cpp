#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

using namespace std;
using namespace __gnu_pbds;


#define ll long long int
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define all(a) a.begin(),a.end()

typedef tree <ll, null_type, less <ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// order_of_key(val): returns the number of values less than val
// find_by_order(k): returns an iterator to the kth largest element (0-based)
double PI = 3.141592653589793238;
double angle = PI / 5;
void print(vector<double> v, double r, double g, double b) {
	for(double d: v) {
		cout << d << ", ";
	}
	cout << r << ", " << g << ", " << b << ", \n";
}
int main(void)
{
	srand(time(NULL));
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    double length = (double)0.4;
    double x1 = 0, y1 = 0;
    double vx = length, vy = 0;
    vector<vector<double>> vertices;
    double up = (double) 0.2;
    vertices.pb({x1, y1, up});
    for(int i = 0; i < 9;i++) {
    	double x2 = x1 + vx, y2 = y1 + vy;
    	x1 = x2, y1 = y2;
    	double tx = vx*cos(angle) - vy*sin(angle);
    	double ty = vx*sin(angle) + vy*cos(angle);
    	vx = tx;
    	vy = ty; 
    	vertices.pb({x1, y1, up});
    }
    for(int i = 0; i < 10;i++) {
    	vertices.pb({vertices[i][0], vertices[i][1], -up});
    }
    cout << "float vertices[] = {\n";
    for(int i = 2; i < 10; i++) {\
		cout << "\t";print(vertices[0], 1, 0, 0);
		cout << "\t";print(vertices[i], 1, 0, 0);
		cout << "\t";print(vertices[i - 1], 1, 0, 0);
    }
    for(int i = 12; i < 20; i++) {
		cout << "\t";print(vertices[10], 1, 0, 0);
		cout << "\t";print(vertices[i], 1, 0, 0);
		cout << "\t";print(vertices[i - 1], 1, 0, 0);
    }
    double colors[10][3];
    colors[0][0] = 0.0, colors[0][1] = 1.0, colors[0][2] = 0.0;
    colors[1][0] = 0.0, colors[1][1] = 0.0, colors[1][2] = 0.5;
    colors[2][0] = 0.0, colors[2][1] = 1.0, colors[2][2] = 1.0;
    colors[3][0] = 0.0, colors[3][1] = 0.0, colors[3][2] = 1.0;
    colors[4][0] = 1.0, colors[4][1] = 0.0, colors[4][2] = 1.0;
    colors[5][0] = 1.0, colors[5][1] = 1.0, colors[5][2] = 1.0;
    colors[6][0] = 0.5, colors[6][1] = 0.0, colors[6][2] = 1.0;
    colors[7][0] = 0.8, colors[7][1] = 0.8, colors[7][2] = 0.8;
    colors[8][0] = 0.0, colors[8][1] = 0.5, colors[8][2] = 0.5;
    colors[9][0] = 0.5, colors[9][1] = 0.5, colors[9][2] = 0.0;

    for(int i = 0; i < 10; i++) {
    	int v1 = i, v2 = i + 1;
    	int v3 = v1 + 10, v4 = v2 + 10;
    	if(i == 9) {
    		v2 = 0, v4 = 10;
    	}
		double red, green, blue;
		red = colors[i][0], green = colors[i][1], blue = colors[i][2];
    	cout << "\t";print(vertices[v1], red, green, blue);
		cout << "\t";print(vertices[v3], red, green, blue);
		cout << "\t";print(vertices[v4], red, green, blue);
		cout << "\t";print(vertices[v1], red, green, blue);
		cout << "\t";print(vertices[v4], red, green, blue);
		cout << "\t";print(vertices[v2], red, green, blue);
    }
    cout << "};\n";
}