#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <functional>
#include <ctime>
#include <cstdlib>

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
                        return false;
                    }
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

vector<bool**> successor2(int** table, bool** state, int row, int col)
{
    vector<bool**> result;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (state[i][j])
            {
                bool** tmpState = CopyState(state, row, col);
                bool flagRepeated = false;

                for (int k = 0; k < col; k++)
                {
                    if (k != j && state[i][k])
                    {
                        if (table[i][j] == table[i][k])
                        {
                            flagRepeated = true;
                            break;
                        }
                    }
                }
                if (!flagRepeated)
                {
                    for (int k = 0; k < row; k++)
                    {
                        if (k != i && state[k][j])
                        {
                            if (table[i][j] == table[k][j])
                            {
                                flagRepeated = true;
                                break;
                            }
                        }
                    }
                }

                if (flagRepeated)
                {
                    if ( (i-1 >= 0 && !tmpState[i-1][j]) || 
                        (i+1 < row && !tmpState[i+1][j]) ||
                        (j-1 >= 0 && !tmpState[i][j-1]) ||
                        (j+1 < col && !tmpState[i][j+1]) ||
                        (
                            ( (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (i+2 < row && !tmpState[i+2][j]) && (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) ) ||
                            ( (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (j+2 < col && !tmpState[i][j+2]) && (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) ) ||
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (i-2 >= 0 && !tmpState[i-2][j]) && (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) ) ||
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (j-2 >= 0 && !tmpState[i][j-2]) && (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) ) ||
                            
                            ( (i-2 >= 0 && !tmpState[i-2][j]) && (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (j+1 == col) ) ||
                            ( (i+2 < row && !tmpState[i+2][j]) && (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (j+1 == col) ) ||
                            ( (j+2 < col && !tmpState[i][j+2]) && (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (i == 0) ) ||
                            ( (j+2 < col && !tmpState[i][j+2]) && (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (i+1 == row) ) ||
                            ( (i-2 >= 0 && !tmpState[i-2][j]) && (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (j == 0) ) ||
                            ( (i+2 < row && !tmpState[i+2][j]) && (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (j == 0) ) ||
                            ( (j-2 >= 0 && !tmpState[i][j-2]) && (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (i == 0) ) ||
                            ( (j-2 >= 0 && !tmpState[i][j-2]) && (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (i+1 == row) ) ||
                            
                            ( (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (i+2 == row) ) ||
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (i-1 == 0) ) ||
                            ( (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (j+2 == col) ) ||
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (j-1 == 0) ) ||
                            
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (j+1 == col) && (i-1 == 0) ) ||
                            ( (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (j+1 == col) && (i+2 == row) ) ||
                            ( (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (j == 0) && (i-1 == 0) ) ||
                            ( (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (j == 0) && (i+2 == row) ) ||
                            ( (i-1 >= 0 && j+1 < col && !tmpState[i-1][j+1]) && (j+2 == col) && (i+1 == row) ) ||
                            ( (i-1 >= 0 && j-1 >= 0 && !tmpState[i-1][j-1]) && (j-1 == 0) && (i+1 == row) ) ||
                            ( (i+1 < row && j+1 < col && !tmpState[i+1][j+1]) && (j+2 == col) && (i == 0) ) ||
                            ( (i+1 < row && j-1 >= 0 && !tmpState[i+1][j-1]) && (j-1 == 0) && (i == 0) )
                        )
                        )
                    {
                        DeleteState(tmpState, row, col);
                    }
                    else
                    {
                        tmpState[i][j] = false;
                        result.push_back(tmpState);
                    }
                }
                else
                {
                    DeleteState(tmpState, row, col);
                }
                
            }
        }
    }
    return result;
}

vector<bool**> successor(int** table, bool** state, int row, int col)
{
    vector<bool**> result;
    int counter = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (state[i][j])
            {
                bool** tmpState = CopyState(state, row, col);
                bool twoWhites = false;
                bool repeated = false;

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
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (k-2 >= 0 && !tmpState[i][k-2]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) ) ||
                                    
                                    ( (i-2 >= 0 && !tmpState[i-2][k]) && (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (k+1 == col) ) ||
                                    ( (i+2 < row && !tmpState[i+2][k]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (k+1 == col) ) ||
                                    ( (k+2 < col && !tmpState[i][k+2]) && (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (i == 0) ) ||
                                    ( (k+2 < col && !tmpState[i][k+2]) && (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (i+1 == row) ) ||
                                    ( (i-2 >= 0 && !tmpState[i-2][k]) && (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (k == 0) ) ||
                                    ( (i+2 < row && !tmpState[i+2][k]) && (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (k == 0) ) ||
                                    ( (k-2 >= 0 && !tmpState[i][k-2]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (i == 0) ) ||
                                    ( (k-2 >= 0 && !tmpState[i][k-2]) && (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (i+1 == row) ) ||

                                    ( (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (i+2 == row) ) ||
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (i-1 == 0) ) ||
                                    ( (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (k+2 == col) ) ||
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (k-1 == 0) ) ||
                                    
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (k+1 == col) && (i-1 == 0) ) ||
                                    ( (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (k+1 == col) && (i+2 == row) ) ||
                                    ( (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (k == 0) && (i-1 == 0) ) ||
                                    ( (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (k == 0) && (i+2 == row) ) ||
                                    ( (i-1 >= 0 && k+1 < col && !tmpState[i-1][k+1]) && (k+2 == col) && (i+1 == row) ) ||
                                    ( (i-1 >= 0 && k-1 >= 0 && !tmpState[i-1][k-1]) && (k-1 == 0) && (i+1 == row) ) ||
                                    ( (i+1 < row && k+1 < col && !tmpState[i+1][k+1]) && (k+2 == col) && (i == 0) ) ||
                                    ( (i+1 < row && k-1 >= 0 && !tmpState[i+1][k-1]) && (k-1 == 0) && (i == 0) )
                                )
                                )
                            {
                                twoWhites = true;
                                break;
                            }
                            repeated = true;
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
                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (k+2 < row && !tmpState[k+2][j]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) ) ||
                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j+2 < col && !tmpState[k][j+2]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (k-2 >= 0 && !tmpState[k-2][j]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (j-2 >= 0 && !tmpState[k][j-2]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) ) ||
                                    
                                        ( (k-2 >= 0 && !tmpState[k-2][j]) && (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (j+1 == col) ) ||
                                        ( (k+2 < row && !tmpState[k+2][j]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (j+1 == col) ) ||
                                        ( (j+2 < col && !tmpState[k][j+2]) && (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (k == 0) ) ||
                                        ( (j+2 < col && !tmpState[k][j+2]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (k+1 == row) ) ||
                                        ( (k-2 >= 0 && !tmpState[k-2][j]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (j == 0) ) ||
                                        ( (k+2 < row && !tmpState[k+2][j]) && (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j == 0) ) ||
                                        ( (j-2 >= 0 && !tmpState[k][j-2]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (k == 0) ) ||
                                        ( (j-2 >= 0 && !tmpState[k][j-2]) && (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (k+1 == row) ) ||
                                        
                                        ( (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (k+2 == row) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (k-1 == 0) ) ||
                                        ( (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j+2 == col) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (j-1 == 0) ) ||
                                    
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (j+1 == col) && (k-1 == 0) ) ||
                                        ( (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (j+1 == col) && (k+2 == row) ) ||
                                        ( (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (j == 0) && (k-1 == 0) ) ||
                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j == 0) && (k+2 == row) ) ||
                                        ( (k-1 >= 0 && j+1 < col && !tmpState[k-1][j+1]) && (j+2 == col) && (k+1 == row) ) ||
                                        ( (k-1 >= 0 && j-1 >= 0 && !tmpState[k-1][j-1]) && (j-1 == 0) && (k+1 == row) ) ||
                                        ( (k+1 < row && j+1 < col && !tmpState[k+1][j+1]) && (j+2 == col) && (k == 0) ) ||
                                        ( (k+1 < row && j-1 >= 0 && !tmpState[k+1][j-1]) && (j-1 == 0) && (k == 0) )
                                    )
                                    ) 
                                
                                {
                                    twoWhites = true;
                                    break;
                                }
                                repeated = true;
                                tmpState[k][j] = false;
                            }

                        }
                    }
                }

                if (!twoWhites && repeated)
                {   
                    cout << endl;
                    printState(tmpState, row, col);
                    result.push_back(tmpState);
                }
                
                if (twoWhites || !repeated)
                {   
                    DeleteState(tmpState, row, col);
                }
            }
        }
    }
    return result;
}

bool** heuristic1(vector<bool**> current_state_childs, int row, int col) 
{
    // cout << "heuristic size: " << current_state_childs.size() << endl;

    
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

class state_with_depth
{
public:
    bool** state;
    int row;
    int col;
    int depth;

    state_with_depth(bool** state, int row, int col, int depth)
    {
        this->state = state;
        this->row = row;
        this->col = col;
        this->depth = depth;
    }
};

bool heuristic1_comprator_a_star(state_with_depth state1, state_with_depth state2)
{
    int state1_counter = 0;
    int state2_counter = 0;
    for (int i = 0; i < state1.row; i++)
    {
        for (int j = 0; j < state1.col; j++)
        {
            if (state1.state[i][j])
            {
                state1_counter++;
            }
            if (state2.state[i][j])
            {
                state2_counter++;
            }
        }
    }

    // g(n)
    state1_counter += state1.depth;
    state2_counter += state2.depth;

    if (state1_counter >= state2_counter)
    {
        return true;
    }
    return false;
}

// bool** heuristic2(vector<bool**> current_state_childs, int row, int col)
// {

// }

int tRow, tCol;
bool heuristic1_comprator(bool** state1, bool** state2)
{
    int state1_counter = 0;
    int state2_counter = 0;
    for (int i = 0; i < tRow; i++)
    {
        for (int j = 0; j < tCol; j++)
        {
            if (!state1[i][j])
            {
                state1_counter++;
            }
            if (!state2[i][j])
            {
                state2_counter++;
            }
        }
    }

    if (state1_counter < state2_counter)
    {
        return true;
    }
    return false;
}


// bool heuristic2_compartor(bool** state1, bool** state2)
// {
//     int repeat1_counter = 0;
//     int repaet2_counter = 0;
// }

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

    vector<bool**> current_state_childs;
    current_state_childs = successor(table, current_state, row, col);

    tRow = row;
    tCol = col;
    priority_queue<bool**, vector<bool**>, function<bool(bool**, bool**)> > pq(heuristic1_comprator);

    for (int i = 0; i < current_state_childs.size(); i++ )
    {
        pq.push(current_state_childs[i]);
    }

    while (!pq.empty())
    {
        cout << endl;
        current_state = pq.top();
        printState(current_state, row, col);
        // cin.get();
        pq.pop();

        if (is_goal(table, current_state, row, col))
        {
            cout << "we have reached the goal" << endl;
            printState(current_state, row, col);
            break;
        }
        else
        {
            vector<bool**> new_state_childs;
            new_state_childs = successor(table, current_state, row, col);
            for (int i = 0; i < new_state_childs.size(); i++ )
            {
                pq.push(new_state_childs[i]);
            }
            new_state_childs.clear();
        }
    }
}

bool CompareStates(bool** state1, bool** state2, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (state1[i][j] != state2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

void bfs(int** table, int row, int col)
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

    vector<bool**> current_state_childs;
    current_state_childs = successor(table, current_state, row, col);
    // for (int i = 0; i < current_state_childs.size(); i++)
    // {
    //      cout << endl;
    //      printState(current_state_childs[i], row, col);
    //      cin.get();
    // }

    // priority_queue<state_with_depth, vector<state_with_depth>, function<bool(state_with_depth, state_with_depth)> > pq(heuristic1_comprator_a_star);
    stack<bool**> pq;
    for (int i = 0; i < current_state_childs.size(); i++ )
    {
        pq.push(current_state_childs.at(i));
    }
    vector<bool**> visited;
    // int current_state_depth = 0;

    int debug_count = 0;
    while (!pq.empty())
    {
        current_state = pq.top();
        // current_state_depth = pq.top().depth;
        pq.pop();

        
        bool visi = false;
        for (auto v : visited)
        {
            if (CompareStates(v, current_state, row, col))
            {
                visi = true;
                break;
            }
        }
        if (visi)
        {
            continue;
        }
        
        visited.push_back(current_state);
        
        debug_count++;

        // // if (debug_count % 1000 == 0)
        // // {
        //     cout << endl;
        //     printState(current_state, row, col);
        //     cout << debug_count;
        //     // cout << current_state_depth;
        //     cin.get();
        // // }
        
        // cout << "Hello" << endl;
        

        if (is_goal(table, current_state, row, col))
        {
            cout << "we have reached the goal" << endl;
            printState(current_state, row, col);
            break;
        }

        else
        {
            vector<bool**> new_state_childs;
            new_state_childs = successor(table, current_state, row, col);
            for (int i = 0; i < new_state_childs.size(); i++ )
            {
                pq.push(new_state_childs[i]);
            }
            // new_state_childs.clear();
        }
    }
}


void a_star(int** table, int row, int col)
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

    vector<bool**> current_state_childs;
    current_state_childs = successor(table, current_state, row, col);

    priority_queue<state_with_depth, vector<state_with_depth>, function<bool(state_with_depth, state_with_depth)> > pq(heuristic1_comprator_a_star);

    for (int i = 0; i < current_state_childs.size(); i++ )
    {
        pq.push(state_with_depth(current_state_childs[i],row, col, 0));
    }

    int current_state_depth = 0;

    int debug_count = 0;
    while (!pq.empty())
    {
        current_state = pq.top().state;
        current_state_depth = pq.top().depth;
        pq.pop();
        debug_count++;
        // if (debug_count % 100 == 0)
        // {
            // cout << endl;
            // printState(current_state, row, col);
            // cout << current_state_depth;
            // cin.get();
        // }

        if (is_goal(table, current_state, row, col))
        {
            cout << "we have reached the goal" << endl;
            printState(current_state, row, col);
            break;
        }

        else
        {
            vector<bool**> new_state_childs;
            new_state_childs = successor(table, current_state, row, col);
            for (int i = 0; i < new_state_childs.size(); i++ )
            {
                pq.push(state_with_depth(new_state_childs[i], row, col, current_state_depth+1));
            }
            new_state_childs.clear();
        }
    }
}

int heuristic1_calc(bool** state, int row, int col)
{
    int counter = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (!state[i][j])
            {
                counter++;
            }
        }
    }
    return counter;
}

void hill_climbing(int** table, int row, int col)
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

    vector<bool**> current_state_childs;

    while (!is_goal(table, current_state, row, col))
    {
        current_state_childs = successor(table, current_state, row, col);

        if (current_state_childs.size() > 0)
        {           
            current_state = heuristic1(current_state_childs, row, col);
        }
        else
        {
            cout << "goal not found" << endl;
            printState(current_state, row, col);
            return;
        }
        
        current_state_childs.clear();
        // printState(current_state, row, col);
        // cout << endl;
        // cin.get();
    }
    cout << "we have reached the goal" << endl;
    printState(current_state, row, col);
}

vector<int> heuristic1_random(vector<bool**> current_state_childs, int row, int col) 
{
    vector<int> black_num;
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
        black_num.push_back(counter);
    }

    return black_num;
}

void random_hill_climbing(int** table, int row, int col)
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

    vector<bool**> current_state_childs;

    while (!is_goal(table, current_state, row, col))
    {
        current_state_childs = successor(table, current_state, row, col);

        if (current_state_childs.size() > 0)
        {
            // bool** current_state_childs_heuristic = heuristic1(current_state_childs, row, col);
            vector<int> current_state_childs_heuristic = heuristic1_random(current_state_childs, row, col);
            int childs_heuristic_sum = 0;
            for (int i = 0; i < current_state_childs_heuristic.size(); i++)
            {
                childs_heuristic_sum += current_state_childs_heuristic.at(i);
            }
            float random_number = rand() / (float) RAND_MAX;
            float tmp_rand = 0;
            int index = 0;
            cout << random_number << endl;

            while(tmp_rand < random_number)
            {
                tmp_rand += (float) current_state_childs_heuristic.at(index) / (float) childs_heuristic_sum;
                index++;
            }
            index -= 1;

            current_state = current_state_childs.at(index);
        }
        else
        {
            cout << "goal not found" << endl;
            printState(current_state, row, col);
            return;
        }
        
        current_state_childs.clear();
        // printState(current_state, row, col);
        // cout << endl;
        // cin.get();
    }
    cout << "we have reached the goal" << endl;
    printState(current_state, row, col);    
}


int main(int argc, char** argv)
{
    srand(time(NULL));

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
    // printState(current_state, row, col);

    successor(table, current_state, row, col);
    // if (newArgv == "greedy")
    // {
    //     // successor(table, current_state, row, col);
    //     greedy(table, row, col);
    // }
    // else if (newArgv == "a_star")
    // {
    //     a_star(table, row, col);
    // }
    // else if (newArgv == "hc")
    // {
    //     hill_climbing(table, row, col);
    // }
    // else if (newArgv == "hcr")
    // {
    //     random_hill_climbing(table, row, col);
    // }
    // else if (newArgv == "bfs")
    // {
    //     bfs(table, row, col);
    // }
}