#include <bits/stdc++.h>
using namespace std;


void print_board(vector<string>board)
{

    cout<<"-------------------"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"|  "<<board[0]<<"  |  "<<board[1]<<"  |  "<<board[2]<<"  |"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"-------------------"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"|  "<<board[3]<<"  |  "<<board[4]<<"  |  "<<board[5]<<"  |"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"-------------------"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"|  "<<board[6]<<"  |  "<<board[7]<<"  |  "<<board[8]<<"  |"<<endl;
    cout<<"|     |     |     |"<<endl;
    cout<<"-------------------"<<endl;

    return;
}

vector<int> empty(vector<string> &board)
{
    vector<int>empty_cells;
    for(int i = 0;i < 9;i++)
    {
        if(board[i] == " ")
            empty_cells.push_back(i);
    }
    return empty_cells;
}

void insert_piece(vector<string> &board, int move, string symbol)
{
    board[move] = symbol;
    return;
}


int get_score(int depth)
{
    int score = 1;
    for(int i = 10 - depth;i > 0;i--)
    {
        score *= i;
    }
    return score;
}

bool board_win(string symbol, vector<string> &board)
{
    for(int i = 0;i < 3;i++)
    {
        if(board[0 + i * 3] == symbol and board[1 + i * 3] == symbol and board[2 + i * 3] == symbol)
            return true;
    }
    for(int j = 0;j < 3;j++)
    {
        if (board[0 + j] == symbol and board[3 + j] == symbol and board[6 + j] == symbol)
            return true;
    }
    if(board[4] == symbol)
    {
        if (board[0] == symbol and board[8] == symbol)
            return true;
        else if (board[2] == symbol and board[6] == symbol)
            return true;
    }
    return false;
}


int minimax(vector<string> state, int initial, int depth, string symbol, int alpha, int beta, string comp_token, string player_token)
{
    if(board_win(comp_token, state))
        return get_score(depth);
    if(board_win(player_token, state))
        return (-get_score(depth));
    if(depth == 9)
        return 0;
    
    if(symbol == comp_token)
        symbol = player_token;
    else
        symbol = comp_token;
    int ideal_path = 0;
    int max_eval = INT_MIN;
    int min_eval = INT_MAX;

    if(symbol == comp_token)
    {
        for (auto cell:empty(state))
        {
            vector<string> newState = state;
            insert_piece(newState, cell, comp_token);
            int eval = minimax(newState, initial, depth + 1, comp_token, alpha, beta, comp_token, player_token);
            if(depth == initial)
            {
                if(eval > max_eval)
                    ideal_path = cell;
            }
            max_eval = max(max_eval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha)
                break;
        }
        if (depth == initial)
            return ideal_path;
        else
            return max_eval;
    }

    else
    {
        for (auto cell : empty(state))
        {
            vector<string> newState = state;
            insert_piece(newState, cell, player_token);
            int eval = minimax(newState, initial ,depth + 1, player_token, alpha, beta, comp_token, player_token);
            min_eval = min(min_eval,eval);
            beta = min(beta,eval);
            if (beta <= alpha)
                break;
        }
        return min_eval;
    }
}

void comp_move(vector<string> &board, string comp_token, string player_token)
{
    int depth = empty(board).size();
    int initial_layer = 9 - depth;
    if(depth == 0)
    {
        return;
    }

    int comp_move = minimax(board, initial_layer, initial_layer, player_token, INT_MIN, INT_MAX, comp_token, player_token);

    insert_piece(board, comp_move, comp_token);
    system("cls");
    cout<<"Computers's Move"<<endl;
    print_board(board);
    return;
}


void player_move(vector<string> &board, string comp_token, string player_token)
{
    vector<int> empty_cells = empty(board);
    int pl_move;
    while(1)
    {
        cout<<"Please Enter a move: "<<endl;
        cin>>pl_move;
        pl_move--;
        if(find(empty_cells.begin(), empty_cells.end(), pl_move) == empty_cells.end())
        {
            cout<<"Please Enter a Valid Move!"<<endl;
        }
        else
        {
            break;
        }
    }
    insert_piece(board, pl_move, player_token);
    system("cls");
    cout<<"Human's Move"<<endl;
    print_board(board);
    return;
}


int main()
{
    system("cls");
    cout<<"Do you want to play Tic-Tac-Toe game with me? (Yes/No): ";
    string s;
    cin>>s;
    auto change_case = [&](string s)
    {
        for(int i = 0;i < s.size();i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    };
    s = change_case(s);

    /* If in starting only the user says NO*/

    if(s == "no")
    {
        cout<<"Ok! No problem :)";
        return 0;
    }

    // -------------- //

    int human_points = 0;
    int computer_points = 0;

    cout<<"Use your Num-pad to enter your move\n";

    print_board({"1", "2", "3", "4", "5", "6", "7", "8", "9"});
    cout<<endl;
    while(s == "yes")
    {
        cout<<"Select your token: ('X'/'O')"<<endl;
        string player_token;
        string comp_token;
        cin>>player_token;
        system("cls");
        if(player_token == "X")
            comp_token = "O";
        else
            comp_token = "X";
        vector<string>board = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
        print_board(board);
        while((empty(board)).size())
        {
            player_move(board, comp_token, player_token);
            comp_move(board, comp_token, player_token);
            if(board_win(player_token, board))
            {
                cout<<"Human Won!"<<endl;
                human_points++;
                break;
            }
            else if(board_win(comp_token, board))
            {
                cout<<"Computer Won!"<<endl;
                cout<<"Better Luck Next Time ;)"<<endl;
                computer_points++;
                break;
            }
            else if(empty(board).size() == 0)
            {
                cout<<"Tie"<<endl;
                break;
            }
        }
        cout<<"Computer Wins: "<<computer_points<<endl;
        cout<<"Human Wins: "<<human_points<<endl;
        cout<<"Do you want to play again? (Yes/No): ";
        cin>>s;
        s = change_case(s);
    }
    cout<<"Hope you enjoyed!"<<endl;
    cout<<"Thanks for trying to beat me!"<<endl;
    return 0;
}