#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

int filter(vector<string> input, vector<int> idx, int flag)
{
    vector<int> cand = idx;
    int iter = 0, res = 0;
    while (cand.size() > 1)
    {
        vector<int> ones;
        vector<int> zero;
        for (int i = 0; i < cand.size(); i++)
        {
            if (input[cand[i]].substr(iter, 1) == "1")
            {
                ones.push_back(cand[i]);
            }
            else
            {
                zero.push_back(cand[i]);
            }
        }
        if (flag == 1)
        {
            // get most frequent
            if (ones.size() >= zero.size())
                cand = ones;
            else
                cand = zero;
        }
        else
        {
            // get least frequent
            if (ones.size() < zero.size())
                cand = ones;
            else
                cand = zero;
        }
        iter++;
    }
    for (int i = 0; i < input[cand[0]].size(); i++)
    {
        if (input[cand[0]].substr(input[cand[0]].size() - 1 - i, 1) == "1")
        {
            res += 1 << i;
        }
    }
    return res;
}

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

    string item;
    vector<string> input;

    while (getline(fin, item))
    {
        input.push_back(item);
    }

    int res = 0;
    switch (stoi(argv[2]))
    {
    case 0:
    {
        int gamma = 0, epsilon = 0;
        int width = input[0].size();
        vector<int> freq(width, 0);
        for (int i = 0; i < input.size(); i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (input[i].substr(j, 1) == "1")
                {
                    freq[j] += 1;
                }
                else
                {
                    freq[j] -= 1;
                }
            }
        }
        for (int i = 0; i < width; i++)
        {
            if (freq[width - 1 - i] > 0)
            {
                gamma += 1 << i;
            }
        }
        epsilon = (1 << width) - 1 - gamma;
        res = gamma * epsilon;
        break;
    }
    case 1:
    {
        int oxygen = 0, co2 = 0;
        vector<int> idx(input.size());
        for (int i = 0; i < input.size(); i++)
            idx[i] = i;
        oxygen = filter(input, idx, 1);
        co2 = filter(input, idx, 0);
        res = oxygen * co2;
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}