#include<iostream>
#include<vector>
using namespace std;
#define il long long int

il sum(vector<vector<vector<il>>>&mat, int x, int y, int z) {
	il sum = 0;

	for(;x > 0; x -= (x&(-x))) 
		for(;y > 0; y -= (y&(-y)))
			for(;z > 0; z -= (z&(-z)))
				sum += mat[x][y][z];
	
	return sum;
} 

int query(vector<vector<vector<il>>>&mat, int x1,int y1,int z1,int x2, int y2, int z2){
    int j4 = sum(mat,x1-1, y1-1, z1-1);
    int j1 = sum(mat,x2, y1-1, z1-1) - j4;
    int j2 = sum(mat,x1-1, y2, z1-1) - j4;
    int j3 = sum(mat,x1-1, y1-1, z2) - j4;

    return sum(mat,x2, y2, z2) - sum(mat,x2, y1-1, z2) - sum(mat,x1-1, y2, z2) - sum(mat,x2, y2, z1-1) + 2*j4 + j1 + j2 + j3;

}

void update(vector<vector<vector<il>>>&mat, int x, int y, int z, il newVal) {
	il delta = newVal - mat[x][y][z];
	for(;x < mat.size(); x += (x&(-x))) 
		for(;y < mat.size(); y += (y&(-y)))
			for(;z < mat.size(); z += (z&(-z)))
				mat[x][y][z] += newVal;
}

int main(int argc,char** argv) {
	int t;
	cin >> t;
	while(t-->0) {
		int n,q;
		cin >> n >> q;
		vector<vector<vector<il>>> mat(n+1,vector<vector<il>>(n+1,vector<il>(n+1, 0))); 
		while(q-->0) {
			string s;
			cin >> s;
			if(s == "QUERY") {
				vector<int> k(6, 0);
				for(int i = 0; i < k.size(); i++) {
                    cin >> k[i];
                }

				cout << query(mat,k[0],k[1],k[2],k[3],k[4],k[5]) << endl;
			}

			else {
				vector<il> k(4, 0);
				for(int i = 0; i < k.size(); i++) {
                    cin >> k[i];
                }
				update(mat,k[0],k[1],k[2],k[3]);
			}
		}
	}
}