#include <iostream>
#include <string>
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
    fig(int x1, int y1, string name1) {
        name = name1;
        x = x1;
        y = y1;
    }

    virtual char getSymbol() const = 0;
};

class hor : public fig {
public:
    hor(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'H';
    }

    void Go(int os) {
        switch (os) {
        case 1:
            y += 2;
            x++;
            break;
        case 2:
            x += 2;
            y++;
            break;
        case 3:
            x += 2;
            y--;
            break;
        case 4:
            y -= 2;
            x++;
            break;
        case 5:
            y -= 2;
            x++;
            break;
        case 6:
            x -= 2;
            y--;
            break;
        case 7:
            x -= 2;
            y++;
            break;
        case 8:
            y += 2;
            x--;
            break;
        }
    }
};

class que : public fig {
public:
    que(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'Q';
    }

    void Go(int num, int os) {
        if (x < y)
            y = x;
        else x = y;
        switch (os) {
        case 1:
            x += num;
            break;
        case 2:
            x += num;
            y -= num;
            break;
        case 3:
            y -= num;
            break;
        case 4:
            x -= num;
            y -= num;
            break;
        case 5:
            x -= num;
            break;
        case 6:
            x -= num;
            y += num;
            break;
        case 7:
            y += num;
            break;
        case 8:
            x += num;
            y += num;
            break;
        }
    }
};

class kin : public fig {
public:
    kin(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'K';
    }

    void Go(int os) {
        switch (os) {
        case 1:
            x++;
            break;
        case 2:
            x++;
            y--;
            break;
        case 3:
            y--;
            break;
        case 4:
            x--;
            y--;
            break;
        case 5:
            x--;
            break;
        case 6:
            x--;
            y++;
            break;
        case 7:
            y++;
            break;
        case 8:
            x++;
            y++;
            break;
        }
    }
};

class lad : public fig {
public:
    lad(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'L';
    }

    void Go(int num, int os) {
        switch (os) {
        case 1:
            x += num;
            break;
        case 2:
            x -= num;
            break;
        case 3:
            y += num;
            break;
        case 4:
            y -= num;
            break;
        }
    }
};

class elep : public fig {
public:
    elep(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'E';
    }

    void Go(int x1, int y1, int num) {
        if (x < y)
            y = x;
        else x = y;
        switch (num) {
        case 1:
            x += x1;
            y += y1;
            break;
        case 2:
            x -= x1;
            y += y1;
            break;
        case 3:
            x += x1;
            y -= y1;
            break;
        case 4:
            x -= x1;
            y -= y1;
            break;
        }
    }
};

class pesh : public fig {
public:
    pesh(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'P';
    }
    void Go() {
        if (Ismoved)
            y++;
        else y += 2;
        if (y == 8) {

        }
    }
};

struct Piece {
    fig* figura;
    bool isWhite;
};

class ChessBoard {
private:
    int size;
    Piece** board;

public:
    ChessBoard(int boardSize = 8) : size(boardSize) {
        board = new Piece * [size];
        for (int i = 0; i < size; ++i) {
            board[i] = new Piece[size];
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j] = { nullptr, false };
            }
        }
    }

    ~ChessBoard() {
        for (int i = 0; i < size; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    void placePiece(int row, int col, fig* piece, bool isWhite) {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            board[row][col] = { piece, isWhite };
        }
    }

    void printBoard() {
        cout << "  ";
        for (int j = 0; j < size; ++j) {
            cout << " " << char('A' + j) << " ";
        }
        cout << endl;

        for (int i = 0; i < size; ++i) {
            cout << size - i << " ";

            for (int j = 0; j < size; ++j) {
                if ((i + j) % 2 == 0) {
                    cout << "\033[100m";
                }
                else {
                    cout << "\033[40m";
                }

                if (board[i][j].figura) {
                    cout << " " << board[i][j].figura->getSymbol() << " ";
                }
                else {
                    cout << " . ";
                }
            }

            cout << "\033[0m" << " " << size - i << endl;
        }

        cout << "  ";
        for (int j = 0; j < size; ++j) {
            cout << " " << char('A' + j) << " ";
        }
        cout << endl;
    }
};


ChessBoard CreateFullPole() {

    ChessBoard chessBoard(8);

    //hor b1(1, 2, "Knight");

    hor* z1 = new hor(8, 2, "Knight");  hor* z2 = new hor(8, 7, "Knight");
    lad* z3 = new lad(8, 1, "Knight");  lad* z4 = new lad(8, 8, "Knight");
    elep* z5 = new elep(8, 3, "Knight");  elep* z6 = new elep(8, 6, "Knight");
    kin* z7 = new kin(8, 5, "Knight");  que* z8 = new que(8, 4, "Knight");
    pesh* z9 = new pesh(7, 1, "Knight");  pesh* z0 = new pesh(7, 2, "Knight");
    pesh* z11 = new pesh(7, 3, "Knight");  pesh* z12 = new pesh(7, 4, "Knight");
    pesh* z13 = new pesh(7, 5, "Knight");  pesh* z14 = new pesh(7, 6, "Knight");
    pesh* z15 = new pesh(7, 7, "Knight");  pesh* z16 = new pesh(7, 8, "Knight");
    chessBoard.placePiece(7, 1, z1, true);
    chessBoard.placePiece(7, 6, z2, true);  chessBoard.placePiece(7, 0, z3, true);
    chessBoard.placePiece(7, 7, z4, true);  chessBoard.placePiece(7, 2, z5, true);
    chessBoard.placePiece(7, 5, z6, true);  chessBoard.placePiece(7, 4, z7, true);
    chessBoard.placePiece(7, 3, z8, true);  chessBoard.placePiece(6, 0, z9, true);
    chessBoard.placePiece(6, 1, z0, true);  chessBoard.placePiece(6, 2, z11, true);
    chessBoard.placePiece(6, 3, z12, true);  chessBoard.placePiece(6, 4, z13, true);
    chessBoard.placePiece(6, 5, z14, true);  chessBoard.placePiece(6, 6, z15, true);
    chessBoard.placePiece(6, 7, z16, false);  

    hor* b1 = new hor(1, 2, "Knight");
    hor* b2 = new hor(1, 7, "Knight");
    lad* b3 = new lad(1, 1, "Knight");
    lad* b4 = new lad(1, 8, "Knight");
    elep* b5 = new elep(1, 3, "Knight");
    elep* b6 = new elep(1, 6, "Knight");
    kin*  b7 = new kin(1, 5, "Knight");
    que* b8 = new que(1, 4, "Knight");
    pesh* b9 = new pesh(2, 1, "Knight");
    pesh* b0 = new pesh(2, 2, "Knight");
    pesh* b11 = new pesh(2, 3, "Knight");
    pesh* b12 = new pesh(2, 4, "Knight");
    pesh* b13 = new pesh(2, 5, "Knight");
    pesh* b14 = new pesh(2, 6, "Knight");
    pesh* b15 = new pesh(2, 7, "Knight");
    pesh* b16 = new pesh(2, 8, "Knight");

    chessBoard.placePiece(0, 1, b1, true);
    chessBoard.placePiece(0, 6, b2, true);
    chessBoard.placePiece(0, 0, b3, true);
    chessBoard.placePiece(0, 7, b4, true);
    chessBoard.placePiece(0, 2, b5, true);
    chessBoard.placePiece(0, 5, b6, true);
    chessBoard.placePiece(0, 4, b7, true);
    chessBoard.placePiece(0, 3, b8, true);
    chessBoard.placePiece(1, 0, b9, true);
    chessBoard.placePiece(1, 1, b0, true);
    chessBoard.placePiece(1, 2, b11, true);
    chessBoard.placePiece(1, 3, b12, true);
    chessBoard.placePiece(1, 4, b13, true);
    chessBoard.placePiece(1, 5, b14, true);
    chessBoard.placePiece(1, 6, b15, true);
    chessBoard.placePiece(1, 7, b16, false);
    return chessBoard;

}


int main() {
    
    ChessBoard chessBoard =  CreateFullPole();

    chessBoard.printBoard();

    return 0;
}
