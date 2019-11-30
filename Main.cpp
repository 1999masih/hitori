#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool is_goal(int** table, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int k = j + 1; k < col; k++)
            {
                if (table[i][j] == table[i][k])
                {
                    return false;
                }
            }
        }
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            for (int k = j + 1; k < row; k++)
            {
                if (table[j][i] == table[k][j])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

vector<int**> successor(int** table, int row, int col)
{

}

void greedy(int** table, int row, int col)
{
    int** current_state = table;
    vector<int**> current_state_childs;

    while (!is_goal(current_state, row, col))
    {

        current_state_childs = successor(current_state, row, col);

        current_state = heuristic(current_state_childs, row, col);

    }
}

int main(int argc, char** argv)
{
    vector<vector<int>> table_vec;

    ifstream input_file("samples/sample" + (string) argv[2] + ".txt");

    char tmp = ' ';
    vector<int> tmp_vec;
    while(!input_file.eof())
    {
        input_file.get(tmp);
        if (tmp == '\n')
        {
            table_vec.push_back(tmp_vec);
            tmp_vec.clear();
        }
        else if (tmp <= '9' && tmp >= '0')
        {
            tmp_vec.push_back(tmp - '0');
        }
    }
    table_vec.push_back(tmp_vec);

    int** table = new int*[table_vec.size()];
    for (int i = 0; i < table_vec.size(); i++)
    {
        table[i] = new int[table_vec[0].size()];
        for (int j = 0; j < table_vec[0].size(); j++)
        {
            table[i][j] = table_vec[i][j];
        }
    }
    
    for (int i = 0; i < table_vec.size(); i++)
    {
        for (int j = 0; j < table_vec[0].size(); j++)
        {
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }

    // which algorithm
    if (argv[1] == "greedy")
    {
        greedy(table, table_vec.size(); table_vec[0].size());
    }
}