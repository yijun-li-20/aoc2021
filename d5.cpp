#include<bits/stdc++.h>
#define MP make_pair
using namespace std;

int main(int argc, char *argv[])
{
    string filename = argv[1];
    ifstream fin;
    fin.open(filename.c_str());
    if (!fin)
    {
        cout << "Error opening " << filename << endl;
        exit(1);
    }

    string item, temp;
    vector<vector<int> > input;
    while (getline(fin, item))
    {
        vector<int> v(4);
        stringstream ss(item);
        getline(ss, temp, ',');
        v[0] = stoi(temp);
        ss >> temp;
        v[1] = stoi(temp);
        ss >> temp;
        getline(ss, temp, ',');
        v[2] = stoi(temp);
        ss >> temp;
        v[3] = stoi(temp);
        input.push_back(v);
    }

    int res = 0;
    int res2 = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        multimap<int, pair<int, int> > mx, my;
        map<pair<int, int>, int> c;
        for(int i=0;i<input.size();i++){
            if(input[i][0] == input[i][2]){
                // parallel to y axis
                my.insert(make_pair(input[i][0], make_pair(min(input[i][1], input[i][3]), max(input[i][1], input[i][3]))));
            }
            else if (input[i][1] == input[i][3])
            {
                // parallel to x axis
                mx.insert(make_pair(input[i][1], make_pair(min(input[i][0], input[i][2]), max(input[i][0], input[i][2]))));
            }
        }
        // horizontal lines: same y
        for(auto iter=my.begin(); iter!=my.end(); iter++){
            for(int x=iter->second.first; x!=iter->second.second+1;x++){
                if(c.count(MP(x, iter->first))){
                    if(c[MP(x, iter->first)] == 1) res++;
                    c[MP(x, iter->first)] ++;
                    
                }
                else{
                    c[MP(x, iter->first)] = 1;
                }
            }

        }
        // vertical lines: same x
        for(auto iter=mx.begin(); iter!=mx.end(); iter++){
            for(int y=iter->second.first; y!=iter->second.second+1;y++){
                if(c.count(MP(iter->first,y))){
                    if(c[MP(iter->first,y)] == 1) res++;
                    c[MP(iter->first,y)] ++;
                }
                else{
                    c[MP(iter->first,y)] = 1;
                }
            }

        }
        break;
    }
    case 1:
    {
        res = 0;
        
        multimap<int, pair<int, int> > mx, my, mbl, mtl;
        map<pair<int, int>, int> c;
        for(int i=0;i<input.size();i++){
            if(input[i][0] == input[i][2]){
                // parallel to y axis
                my.insert(MP(input[i][0], MP(min(input[i][1], input[i][3]), max(input[i][1], input[i][3]))));
            }
            else if (input[i][1] == input[i][3])
            {
                // parallel to x axis
                mx.insert(MP(input[i][1], MP(min(input[i][0], input[i][2]), max(input[i][0], input[i][2]))));
            }
            else if (input[i][3] - input[i][1] == input[i][2]-input[i][0]){
                // k=1
                mbl.insert(MP(min(input[i][0], input[i][2]), MP(min(input[i][1], input[i][3]), max(input[i][1], input[i][3]))));
            }   
            else if (input[i][3] - input[i][1] == -input[i][2]+input[i][0]){
                // k=-1
                mtl.insert(MP(min(input[i][0], input[i][2]), MP(max(input[i][1], input[i][3]), min(input[i][1], input[i][3]))));
            }
        }
        // horizontal lines: same y
        for(auto iter=my.begin(); iter!=my.end(); iter++){
            for(int x=iter->second.first; x!=iter->second.second+1;x++){
                if(c.count(MP(x, iter->first))){
                    if(c[MP(x, iter->first)] == 1){ res++;}
                    c[MP(x, iter->first)] ++;
                    
                }
                else{
                    c[MP(x, iter->first)] = 1;
                }
            }

        }
        // vertical lines: same x
        for(auto iter=mx.begin(); iter!=mx.end(); iter++){
            for(int y=iter->second.first; y!=iter->second.second+1;y++){
                if(c.count(MP(iter->first,y))){
                    if(c[MP(iter->first,y)] == 1){ res++;}
                    c[MP(iter->first,y)] ++;
                }
                else{
                    c[MP(iter->first,y)] = 1;
                }
            }

        }
        
        for(auto iter=mtl.begin(); iter!=mtl.end(); iter++){
            int step = iter->second.first - iter->second.second+1;
            // if(iter->first == 70){
            //     cout << iter->second.first << "\t" << iter->second.second << "\n";
            // }
            for(int y=0; y!=step;y++){
                // if(iter->first == 70){
                //     cout << iter->first+y << ", " << iter->second.first-y << ";";
                // }
                if(c.count(MP(iter->first+y,iter->second.first-y))){
                    if(c[MP(iter->first+y,iter->second.first-y)] == 1){ res++;}
                    c[MP(iter->first+y,iter->second.first-y)] ++;
                }
                else{
                    c[MP(iter->first+y,iter->second.first-y)] = 1;
                }
            }
        }
        for(auto iter=mbl.begin(); iter!=mbl.end(); iter++){
            // if(iter->first == 70){
            //     cout << iter->second.first << "\t" << iter->second.second << "\n";
            // }
            int step = iter->second.second - iter->second.first+1;
            for(int y=0; y!=step;y++){
                // if(iter->first == 70){
                //     cout << iter->first+y << ", " << iter->second.first+y << ";";
                // }
                if(c.count(MP(iter->first+y,iter->second.first+y))){
                    if(c[MP(iter->first+y,iter->second.first+y)] == 1){ res++;}
                    c[MP(iter->first+y,iter->second.first+y)] ++;
                }
                else{
                    c[MP(iter->first+y,iter->second.first+y)] = 1;
                }
            }
        }
        
        for(auto iter: c){
            if (c[iter.first]>1) res2++; 
        }
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}