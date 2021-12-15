#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, char *argv[]){
    string filename = argv[1];
	ifstream fin;
	fin.open(filename.c_str());
	if (!fin)
	{
		cout << "Error opening " << filename << endl;
		exit(1);
	}

    string d;
	vector<int> depth;

	while (getline(fin, d))
	{
		depth.push_back(stoi(d));
	}

    int inc = 0;
    switch (stoi(argv[2]))
    {
    case 0:
        for(int i=1;i<depth.size();i++){
            if (depth[i] > depth[i-1]){
                inc ++;
            }
        }
        break;
    case 1:
        for(int i=1;i<depth.size()-2;i++){
            if(depth[i+2]>depth[i-1]) inc++;
        }
        break;
    default:
        break;
    }

    std::cout << inc << std::endl;
    return 0;
}