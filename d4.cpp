#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <map>
#include <set>

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
    vector<string> drawn;
    string d;
    // multimap: repeating values in a board
    vector<multimap<string, pair<int, int> > > rev_index;

    getline(fin, item);
    stringstream ss(item);
    while (getline(ss, d, ','))
    {
        drawn.push_back(d);
    }
    getline(fin, item);
    while (getline(fin, item))
    {
        string temp;
        multimap<string, pair<int, int> > index;
        for (int i = 0; i < 5; i++)
        {
            stringstream ss(item);

            for (int j = 0; j < 5; j++)
            {
                ss >> temp;
                index.insert(make_pair(temp, make_pair(i, j)));
            }

            getline(fin, item);
        }
        rev_index.push_back(index);
    }

    int res = 0, n = rev_index.size();
    vector<vector<int> > lines(n, vector<int>(10, 0));
    set<string> s;

    switch (stoi(argv[2]))
    {
    case 0:
    {
        for (int i = 0; i < drawn.size(); i++)
        {
            s.insert(drawn[i]);
            for (int j = 0; j < n; j++)
            {
                if (rev_index[j].find(drawn[i]) != rev_index[j].end())
                {
                    pair<multimap<string, pair<int, int> >::iterator, multimap<string, pair<int, int> >::iterator> ptr = rev_index[j].equal_range(drawn[i]);
                    for (multimap<string, pair<int, int> >::iterator item = ptr.first; item != ptr.second; ++item)
                    {
                        pair<int, int> p = item->second;
                        lines[j][p.first]++;
                        lines[j][5 + p.second]++;
                        if (lines[j][p.first] == 5 || lines[j][5 + p.second] == 5)
                        {
                            for (multimap<string, pair<int, int> >::iterator k = rev_index[j].begin(); k != rev_index[j].end(); ++k)
                            {
                                pair<int, int> coord = k->second;
                                if (s.find(k->first) == s.end())
                                {
                                    res += stoi(k->first);
                                }
                            }
                            res *= stoi(item->first);
                            std::cout << res << std::endl;
                            return 0;
                        }
                    }
                }
            }
        }
        break;
    }
    case 1:
    {
        map<int, int> score;
        for (int i = 0; i < drawn.size(); i++)
        {
            s.insert(drawn[i]);
            for (int j = 0; j < n; j++)
            {
                if (rev_index[j].find(drawn[i]) != rev_index[j].end() && score.find(j) == score.end())
                {
                    pair<multimap<string, pair<int, int> >::iterator, multimap<string, pair<int, int> >::iterator> ptr = rev_index[j].equal_range(drawn[i]);
                    for (multimap<string, pair<int, int> >::iterator item = ptr.first; item != ptr.second; ++item)
                    {
                        pair<int, int> p = item->second;
                        lines[j][p.first]++;
                        lines[j][5 + p.second]++;
                        if (lines[j][p.first] == 5 || lines[j][5 + p.second] == 5)
                        {
                            res = 0;
                            for (multimap<string, pair<int, int> >::iterator k = rev_index[j].begin(); k != rev_index[j].end(); ++k)
                            {
                                pair<int, int> coord = k->second;
                                if (s.find(k->first) == s.end())
                                {
                                    res += stoi(k->first);
                                }
                            }
                            res *= stoi(item->first);

                            score.insert(make_pair(j, res));
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
    default:
        break;
    }

    std::cout << res << std::endl;
    return 0;
}