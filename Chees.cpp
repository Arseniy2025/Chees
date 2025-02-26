#include <iostream>
using namespace std;

class fig {
protected:
    string name;
    int x;
    int y;
    bool Ismoved = false;
public:
    fig() {
        name = "";
        x = 0;
        y = 0;
    }
};

class hor : fig {
private:

public:
    void Go(int os) {
        switch (os) {
        case 1:
            y += 2;
            x++;
        case 2:
            x += 2;
            y++;
        case 3:
            x += 2;
            y--;
        case 4:
            y -= 2;
            x++;
        case 5:
            y -= 2;
            x++;
        case 6:
            x -= 2;
            y--;
        case 7:
            x -= 2;
            y++;
        case 8:
            y += 2;
            x--;
        }
    }
};

class que :fig {
public:
    void Go(int num, int os) {
        if (x < y)
            y = x;
        else x = y;
        switch (os) {
        case 1:
            x += num;
        case 2:
            x += num;
            y -= num;
        case 3:
            y -= num;
        case 4:
            x -= num;
            y -= num;
        case 5:
            x -= num;
        case 6:
            x -= num;
            y += num;
        case 7:
            y += num;
        case 8:
            x += num;
            y += num;
        }
    }
};
class kin : fig {
public:
    void Go(int os) {
        switch (os) {
        case 1:
            x++;
        case 2:
            x++;
            y--;
        case 3:
            y--;
        case 4:
            x--;
            y--;
        case 5:
            x--;
        case 6:
            x--;
            y++;
        case 7:
            y++;
        case 8:
            x++;
            y++;
        }
    }
};

class lad :fig {
private:

public:
    void Go(int num, int os) {
        switch (os) {
        case 1:
            x += num;
        case 2:
            x -= num;
        case 3:
            y += num;
        case 4:
            y -= num;
        }
    }
};

class elep : fig {
private:
    void Go(int x1, int y1, int num) {
        if (x < y)
            y = x;
        else x = y;
        switch (num) {
        case 1:
            x += x1;
            y += y1;
        case 2:
            x -= x1;
            y += y1;
        case 3:
            x += x1;
            y -= y1;
        case 4:
            x -= x1;
            y -= y1;
        }
    }
};

class pesh : fig {
private:

    bool Ismoved = false;
public:
    pesh() {
        name = "";
        x = 0;
        y = 0;
    }
    void Go() {
        if (Ismoved)
            y++;
        else y += 2;
        if (y = 8)
            ;
    }


};
struct Piece {
    char symbol;
    bool isWhite;
};

class ChessBoard {
private:
    static const int size = 8;
    Piece board[size][size];

public:
    ChessBoard() {

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j] = { '.', false };
            }
        }
    }

    void placePiece(int row, int col, char symbol, bool isWhite) {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            board[row][col] = { symbol, isWhite };
        }
    }

    void printBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if ((i + j) % 2 == 0) {
                    std::cout << "#";
                }
                else {
                    std::cout << " ";
                }


                std::cout << board[i][j].symbol;
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ChessBoard chessBoard;
    chessBoard.placePiece(0, 4, 'K', true);

    chessBoard.placePiece(7, 3, 'Q', false);

    chessBoard.printBoard();

    return 0;
}

