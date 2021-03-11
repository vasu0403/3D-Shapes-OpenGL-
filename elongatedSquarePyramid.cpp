#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"
#include "colors.h"
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

struct coordinate {
	double x, y, z;
	coordinate(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
double dx[] = {-1, 1, 1, -1};
double dy[] = {-1, -1, 1, 1};

void print_vertex(coordinate v, int color_ind) {
	cout << "\t" << v.x << ", " << v.y << ", " << v.z << ", " << color[color_ind][0] << ", " << color[color_ind][1] << ", " << color[color_ind][2] << ",\n";
}

void print_triangle(coordinate v1, coordinate v2, coordinate v3, int color_ind) {
	print_vertex(v1, color_ind);
	print_vertex(v2, color_ind);
	print_vertex(v3, color_ind);
}
int main(void)
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    vector<coordinate> upper_square;
    vector<coordinate> lower_square;
    double length = 1.0;
    for(int i = 0; i < 4; i++) {
    	double x = (dx[i] * length) / 2;
    	double y = (dy[i] * length) / 2;
    	coordinate upper = coordinate(x, y, length / 2);
    	coordinate lower = coordinate(x, y, -length / 2);
    	upper_square.push_back(upper);
    	lower_square.push_back(lower);
    }
    coordinate upper_vertex = coordinate(0, 0, 0.5 + (sqrt(2.0) / 4));
    coordinate lower_vertex = coordinate(0, 0, -0.5 - (sqrt(2.0) / 4));

    cout << "float vertices[] = {\n";

    // upper pyramid
    print_triangle(upper_square[0], upper_square[1], upper_vertex, ACID_GREEN);
    print_triangle(upper_square[1], upper_square[2], upper_vertex, ARCTIC_LIME);
    print_triangle(upper_square[2], upper_square[3], upper_vertex, CHINESE_YELLOW);
    print_triangle(upper_square[3], upper_square[0], upper_vertex, CHARTREUSE);

    // lower pyramid
    print_triangle(lower_square[0], lower_square[1], lower_vertex, GREEN);
    print_triangle(lower_square[1], lower_square[2], lower_vertex, DARK_YELLOW);
    print_triangle(lower_square[2], lower_square[3], lower_vertex, YELLOW);
    print_triangle(lower_square[3], lower_square[0], lower_vertex, DARK_GREEN);

    // square faces
    print_triangle(upper_square[0], lower_square[0], lower_square[1], RED);
    print_triangle(upper_square[0], upper_square[1], lower_square[1], RED);

    print_triangle(upper_square[1], lower_square[1], lower_square[2], WHITE);
    print_triangle(upper_square[1], upper_square[2], lower_square[2], WHITE);

    print_triangle(upper_square[2], lower_square[2], lower_square[3], RED);
    print_triangle(upper_square[2], upper_square[3], lower_square[3], RED);

    print_triangle(upper_square[3], lower_square[3], lower_square[0], WHITE);
    print_triangle(upper_square[3], upper_square[0], lower_square[0], WHITE);

    cout << "};\n";
}