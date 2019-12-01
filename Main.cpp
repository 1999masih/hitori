#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool is_goal(int** table, bool** state, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            for (int k = j + 1; k < col; k++)
            {
                if (table[i][j] == table[i][k] && state[i][j] && state[i][k])
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
                if (table[j][i] == table[k][j] && state[j][i] && state[k][j])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool** CopyState(bool** state, int row, int col)
{
    bool** new_state = new bool*[row];
    for (int i = 0; i < row; i++)
    {
        new_state[i] = new bool[col];
        for (int j = 0; j < col; j++)
        {
            new_state[i][j] = state[i][j];
        }
    }
    return new_state;
}

void DeleteState(bool** state, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        delete[] state[i];
    }
    delete[] state;
}

// void printStates(vector<vector<bool>> a) 
// {
//     for (int i; i<a.size(); i++)
//     {
//         for(int j; j<a[0].size(); j++) 
//         {
//             cout << a[i][j] << endl;
//         }
//     }

// }

void printState(bool** state, int row, int col) 
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << state[i][j] << ' ';
        }
        cout << endl;
    }

}

vector<bool**> successor(int** table, bool** state, int row, int col)
{
    vector<bool**> result;
    int counter = 0;
    for (int i = 0; i < row; i++)
    {
        // vector<int> repeateds;
        for (int j = 0; j < col; j++)
        {
            
            // if (!(find(repeateds.begin(), repeateds.end(), table[i][j]) != repeateds.end()))
            // {
            //     bool flag = false;
                bool** tmpState = CopyState(state, row, col);
                bool twoWhites = false;
                bool repeated = false;
                // if (!(!table[i][j-1] && !table[i][j+1] && !table[i-1][j] && !table[i+1][j]))

                for (int k = 0; k < col; k++)
                {
                    if (k != j)
                    {

                        if (table[i][j] == table[i][k])
                        {
                            if ( (i-1 >= 0 && !tmpState[i-1][k]) || 
                                (i+1 < row && !tmpState[i+1][k]) ||
                                (k-1 >= 0 && !tmpState[i][k-1]) ||
                                (k+1 < col && !tmpState[i][k+1]) ||
                                
                                (
                                    ( (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (i+2 < row && !tmpState[i+2][k]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) ) ||
                                    ( (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (k+2 < col && !tmpState[i][k+2]) && (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) ) ||
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (i-2 >= 0 && !tmpState[i-2][k]) && (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) ) ||
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (k-2 >= 0 && !tmpState[i][k-2]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) )
                                )
                                
                                )
                            {
                                // cout << "test1" << endl;
                                twoWhites = true;
                                break;
                            }
                            
                            repeated = true;
                            // cout << "test2" << endl;
                            tmpState[i][k] = false;
                        }

                    }
                }



                if (!twoWhites)
                {
                    for (int k = 0; k < row; k++)
                    {
                        if (k != i)
                        {
                            if (table[i][j] == table[k][j])
                            {
                                if ( (k-1 >= 0 && !tmpState[k-1][j]) || 
                                    (k+1 < row && !tmpState[k+1][j]) ||
                                    (j-1 >= 0 && !tmpState[k][j-1]) ||
                                    (j+1 < col && !tmpState[k][j+1]) ||
                                    (
                                        // ( (j+1 < col && k-1 >= 0 && !tmpState[k-1][j+1]) && (j+2 < col && !tmpState[k][j+2]) && (j+1 < col && k+1 < row && !tmpState[k+1][j+1]) ) || //Checkong right side of node
                                        // ( (j-1 >= 0 && k-1 >= 0 && !tmpState[k-1][j-1]) && (j-2 >= 0 && !tmpState[k][j-2]) && (j-1 >= 0  && k+1 < row && !tmpState[k+1][j-1] ) )|| //Checking left side of node
                                        // ( (j-1 >= 0 && k+1 < row && !tmpState[k+1][j-1]) && (k+2 < row && !tmpState[k+2][j]) && (j+1 < col && k+1 < row && !tmpState[k+1][j+1]) ) || //checking bottom side of node
                                        // ( (k-1 >= 0  && j+1 < col &&  !tmpState[k+1][j+1]) && (k-2 >= 0 && !tmpState[k-2][j]) && (k-1 >= 0 && j-1 >= 0 &&  !tmpState[k-1][j-1] )) //Checking topside of node   

                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (k+2 < row && !tmpState[k+2][j]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) ) ||
                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j+2 < col && !tmpState[k][j+2]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (k-2 >= 0 && !tmpState[k-2][j]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (j-2 >= 0 && !tmpState[k][j-2]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) )

                                    )
                                    ) 
                                
                                {
                                    // cout << "test3" << endl;
                                    twoWhites = true;
                                    break;
                                }
                                // cout << "test4" << endl;
                                repeated = true;
                                tmpState[k][j] = false;
                            }

                        }
                    }
                }

                // cout << "heeloo" << endl;


                if (!twoWhites && repeated)
                {
                    // cout << "pushing" << endl;
                    result.push_back(tmpState);
                    // printState(tmpState, row, col);
                    counter++;
                    // cout << counter << endl;
                    // cin.get();
                }
                
                if (twoWhites || !repeated)
                {   
                    // cout << "deletion" << endl;
                    // printState(tmpState, row, col);
                    DeleteState(tmpState, row, col);
                    counter++;
                    // cout << counter << endl;
                    // cin.get();
                }
                
            //     if (flag)
            //     {
            //         bool** tmpState = CopyState(state, row, col);
            //         tmpState[i][j] = false;
            //         result.push_back(tmpState);
            //         repeateds.push_back(table[i][j]);
            //     }
            // }
        }
    }
    cout << counter << endl;
    return result;
}

void greedy(int** table, int row, int col)
{
    bool** current_state = new bool*[row];
    for (int i = 0; i < row; i++)
    {
        current_state[i] = new bool[col];
        for (int j = 0; j < col; j++)
        {
            current_state[i][j] = true;
        }
    }

    // int** current_state = table;
    vector<bool**> current_state_childs;

    while (!is_goal(table, current_state, row, col))
    {

        current_state_childs = successor(table, current_state, row, col);

        //current_state = heuristic(current_state_childs, row, col);

    }
}

int main(int argc, char** argv)
{
    vector<vector<int>> table_vec;

    ifstream input_file("samples/sample" + (string) argv[2] + ".txt");
    string newArgv;
    newArgv = string(argv[1]);
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

    int row = table_vec.size();
    int col = table_vec[0].size();
    
    for (int i = 0; i < table_vec.size(); i++)
    {
        for (int j = 0; j < table_vec[0].size(); j++)
        {
            cout << table[i][j] << ' ';
        }
        cout << endl;
    }

    bool** current_state = new bool*[row];
    for (int i = 0; i < row; i++)
    {
        current_state[i] = new bool[col];
        for (int j = 0; j < col; j++)
        {
            current_state[i][j] = true;
        }
    }

    //successor(table, current_state, row, col);
    //which algorithm
    cout << "fckNazi" << endl;
    // printState(current_state, row, col);

    // successor(table, current_state, row, col);
    if (newArgv == "greedy")
    {
        successor(table, current_state, row, col);
        cout << "wtf" << endl;
    }
}