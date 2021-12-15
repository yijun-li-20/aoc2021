#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

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
        int hor, dep = 0;
        for (int i = 0; i < input.size(); i++)
        {
            istringstream ss(input[i]);
            string op, operand;
            ss >> op >> operand;
            if (op == "forward")
            {
                hor += stoi(operand);
            }
            else if (op == "down")
            {
                dep += stoi(operand);
            }
            else if (op == "up")
            {
                dep -= stoi(operand);
            }
        }
        res = hor * dep;
        break;
    }
    case 1:
    {
        int hor, aim, dep = 0;
        for (int i = 0; i < input.size(); i++)
        {
            istringstream ss(input[i]);
            string op, operand;
            ss >> op >> operand;
            if (op == "forward")
            {
                hor += stoi(operand);
                dep += aim * stoi(operand);
            }
            else if (op == "down")
            {
                aim += stoi(operand);
            }
            else if (op == "up")
            {
                aim -= stoi(operand);
            }
        }
        res = hor * dep;
        break;
    }
        // default:
        //     break;
    }

    std::cout << res << std::endl;
    return 0;
}