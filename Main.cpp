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
            for (int k = 0; k < col; k++)
            {
                if (j != k)
                {
                    if (table[i][j] == table[i][k] && state[i][j] && state[i][k])
                    {
                        // cout << "it's not goal" << endl;
                        return false;
                    }
                }
            }

            for (int k = 0; k < row; k++)
            {
                if (i != k)
                {
                    if (table[i][j] == table[k][j] && state[i][j] && state[k][j])
                    {
                        // cout << "it's not goal" << endl;
                        return false;
                    }
                }
            }
        }
    }

    // cout << "it's goal" << endl;

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
            if (state[i][j])
            {
                bool** tmpState = CopyState(state, row, col);
                bool twoWhites = false;
                bool repeated = false;
                // if (!(!table[i][j-1] && !table[i][j+1] && !table[i-1][j] && !table[i+1][j]))

                for (int k = 0; k < col; k++)
                {
                    if (k != j && state[i][k])
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
                        if (k != i && state[k][j])
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
                    // counter++;
                    // cout << counter << endl;
                    // cin.get();
                }
                
                if (twoWhites || !repeated)
                {   
                    // cout << "deletion" << endl;
                    // printState(tmpState, row, col);
                    DeleteState(tmpState, row, col);
                    // counter++;
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
    }
    // cout << counter << endl;
    return result;
}

bool** heuristic1(vector<bool**> current_state_childs, int row, int col) 
{
    cout << "heuristic size: " << current_state_childs.size() << endl;

    
    vector<pair<int, int>> black_num;
    for(int x = 0; x < current_state_childs.size(); x++)
    {
        int counter = 0;
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < col; j++)
            {
                if(current_state_childs[x][i][j] == false)
                {
                    counter++;
                }
            }
        }
        // cout << "this is counter "<< counter << endl;
        black_num.push_back(make_pair(counter, x));
    }

    int max_tmp = black_num.at(0).first;
    int max_tmp_index = black_num.at(0).second;
    for (int i = 0; i < black_num.size(); i++)
    {
        if (black_num.at(i).first > max_tmp)
        {
            max_tmp = black_num.at(i).first;
            max_tmp_index = black_num.at(i).second;
        }
    }
    // int max_black = *max_element(black_num.begin(), black_num.end());
    // cout << max_black << endl;
    
    // cin.get();
    return current_state_childs.at(max_tmp_index);
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

        if (current_state_childs.size() > 0)
        {
            current_state = heuristic1(current_state_childs, row, col);
        }
        // current_state = current_state_childs[0];
        current_state_childs.clear();
        cout << endl;
        // cout << "current state" << endl;
        // for (auto vv : current_state_childs)
        // {
            // printState(vv, row, col);
            // cin.get();
        // }
        printState(current_state, row, col);
        // cin.get();
    }
    cout << "we have reached the goal" << endl;
    printState(current_state, row, col);
}



// bool** heuristic2(vector<bool**> current_state_childs, int row, int col)
// {

// }

void greedy1(int** table, int row, int col)
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

    cout <<"test1" << endl;

    // int** current_state = table;
    vector<bool**> current_state_childs;
    current_state_childs = successor(table, current_state, row, col);

    priority_queue<bool**> pq;

    for (int i = 0; i < current_state_childs.size(); i++ )
    {
        pq.push(current_state_childs[i]);
        // printState(pq.top(), row, col);
        // cout<< endl;
    }

    // cout <<"test2" << endl;
    

    
    while (!pq.empty())
    {
        current_state = pq.top();
        printState(current_state, row, col);
        pq.pop();
        // cout <<"test3" << endl;

        if (is_goal(table, current_state, row, col))
        {
            cout << "we have reached the goal" << endl;
            printState(current_state, row, col);
            break;
        }

        else
        {
            cout <<"test4" << endl;
            vector<bool**> new_state_childs;
            cout << "test5" << endl;
            new_state_childs = successor(table, current_state, row, col);
            for (int i = 0; i < new_state_childs.size(); i++ )
            {
                pq.push(new_state_childs[i]);
            }
            cout <<"test6" << endl;
            new_state_childs.clear();
            
            
        }
     
        // printState(current_state, row, col);
        // cin.get();
    }
    
}

void a_star(int** table, int row, int col)
{
    // while (!)
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

    int test_row = 4;
    int test_col = 4;
    bool** test_state = new bool*[test_row];
    int** test_table = new int*[test_row];
    for (int i = 0; i < test_row; i++)
    {
        test_state[i] = new bool[test_col];
        test_table[i] = new int[test_col];
    }

    test_table[0][0] = 1;
    test_table[0][1] = 4;
    test_table[0][2] = 4;    
    test_table[0][3] = 2;    
    test_table[1][0] = 4;    
    test_table[1][1] = 1;    
    test_table[1][2] = 3;    
    test_table[1][3] = 2;    
    test_table[2][0] = 2;    
    test_table[2][1] = 1;    
    test_table[2][2] = 1;    
    test_table[2][3] = 2;
    test_table[3][0] = 1;    
    test_table[3][1] = 4;    
    test_table[3][2] = 2;    
    test_table[3][3] = 1;    

    test_state[0][0] = 1;
    test_state[0][1] = 0;
    test_state[0][2] = 1;
    test_state[0][3] = 1;
    test_state[1][0] = 1;
    test_state[1][1] = 1;
    test_state[1][2] = 1;
    test_state[1][3] = 1;
    test_state[2][0] = 1;
    test_state[2][1] = 0;
    test_state[2][2] = 1;
    test_state[2][3] = 0;
    test_state[3][0] = 0;
    test_state[3][1] = 1;
    test_state[3][2] = 1;
    test_state[3][3] = 1;

    // is_goal(test_table, test_state, test_row, test_col);
    // successor(test_table, test_state, test_row, test_col);
    //which algorithm
    cout << "fckNazi" << endl;
    // printState(current_state, row, col);

    // successor(table, current_state, row, col);
    if (newArgv == "greedy")
    {
        // successor(table, current_state, row, col);
        greedy1(table, row, col);
        cout << "wtf" << endl;
    }
}