#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

constexpr int BOARD_SIZE = 9;
constexpr int X = -1;
constexpr int O = 1;
constexpr int BLANK = 0;

int Board[9] =
{
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};

vector<int> Free_Space;

bool Human_Turn = true;

default_random_engine rand_engine(time(0));

void init() {
    for(int i = 0; i < BOARD_SIZE; ++i) {
        Free_Space.push_back(i);
    }
}

void print_board() {
    for(size_t i = 0; i < BOARD_SIZE; ++i) {
        if(i%3 == 0) {
            cout << endl << "| ";
        }
        cout << ((Board[i] < 0) ? 'X' : ((Board[i] > 0) ? 'O' : '-')) << " | ";
    }
    cout << endl;
}

void insert_choice(int choice) {
	if(Human_Turn) {
        Board[choice] = X;
        Human_Turn = false;
    }
    else {
        Board[choice] = O;
        Human_Turn = true;
    }

	Free_Space.erase(find(Free_Space.begin(), Free_Space.end(), choice));
}

void get_user_choice() {
    size_t choice;
    vector<int>::iterator iter;
    do {
        cout << "Enter your choice: ";
        cin >> ws >> choice;

		cin.sync();
		cout.flush();

        if(choice >= BOARD_SIZE || choice < 0) {
            cout << "Please enter a value between 0 and " << BOARD_SIZE - 1 << '!' << endl;
			continue;
		}

        iter = find(Free_Space.begin(), Free_Space.end(), choice);
        if(iter == Free_Space.end()) {
            cout << "That location is already taken!" << endl;
		}

    } while(choice >= BOARD_SIZE || choice < 0 || iter == Free_Space.end());

	insert_choice(choice);
}

void get_robot_choice() {
	uniform_int_distribution<int> dist(0, Free_Space.size());
	int choice = dist(rand_engine);
	std::cout << "Robot choice: " << Free_Space[choice] << endl;
	insert_choice(Free_Space[choice]);
}

bool check_diagonal() {
	return (Board[0] != BLANK && Board[0] == Board[4] && Board[4] == Board[8]) || (Board[2] != BLANK && Board[2] == Board[4] && Board[4] == Board[6]);
}

bool check_horizontal() {
	bool ret = false;
	for(size_t i = 0; i < 3; ++i)
		ret = ret || (Board[0 + i] != BLANK && Board[0 + i] == Board[3 + i] && Board[3 + i] == Board[6 + i]);
	return ret;
}

bool check_vertical() {
	bool ret = false;
	for(size_t i = 0; i < 3; ++i)
		ret = ret || (Board[0 + (i*3)] != BLANK && Board[0 + (i*3)] == Board[1 + (i*3)] && Board[1 + (i*3)] == Board[2 + (i*3)]);
	return ret;
}

int main() {
    cout << "TicTacToe game in C++!" << endl;

    init();
    print_board();

    while(!Free_Space.empty()) {
		if(Human_Turn)
        	get_user_choice();
		else
			get_robot_choice();
		
        print_board();

		if(check_diagonal() || check_horizontal() || check_vertical()) {
			cout << "Congratulations! " << (Human_Turn ? "Robot" : "Human") << " won the round!" << endl;
			break;
		}
        cout << "Next turn!" << endl;
    }

    cout << "Game Over!" << endl;

    return 0;
}
