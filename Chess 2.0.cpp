#include <iostream>
#include <string>
using namespace std;

class ChessBoard; 

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
    virtual bool canMove(int newX, int newY, ChessBoard& board) = 0;
    int getX() const { return x; }
    int getY() const { return y; }
    virtual void setPosition(int newX, int newY) { 
        x = newX;
        y = newY;
    }
};

class ChessBoard {
public:
    int size;
    struct Piece {
        fig* figura;
        bool isWhite;
    };
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
            for (int j = 0; j < size; ++j) {
                if (board[i][j].figura) {
                    delete board[i][j].figura;
                }
            }
            delete[] board[i];
        }
        delete[] board;
    }

    void placePiece(int row, int col, fig* piece, bool isWhite) {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            board[row][col] = { piece, isWhite };
        }
    }

    Piece getPiece(int row, int col) const {
        if (row >= 0 && row < size && col >= 0 && col < size) {
            return board[row][col];
        }
        return { nullptr, false };
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

                
                ChessBoard::Piece piece = board[i][j];

                if (piece.figura) {
                    if (!piece.isWhite) {
                        cout << "\033[31m"; 
                    }
                    else {
                        cout << "\033[97m"; 
                    }
                    cout << " " << piece.figura->getSymbol() << " ";
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

    bool movePiece(int startX, int startY, int endX, int endY, bool isWhite) {
        if (startX < 0 || startX >= size || startY < 0 || startY >= size ||
            endX < 0 || endX >= size || endY < 0 || endY >= size) {
            return false;
        }

        Piece& startPiece = board[startX][startY];
        Piece& endPiece = board[endX][endY];

        if (!startPiece.figura || startPiece.isWhite != isWhite) {
            return false;
        }

        if (endPiece.figura && endPiece.isWhite == isWhite) {
            return false;
        }

        if (!startPiece.figura->canMove(endX, endY, *this)) {
            return false;
        }

        if (endPiece.figura) {
            delete endPiece.figura;
        }

        endPiece = startPiece;
        startPiece = { nullptr, false };
        endPiece.figura->setPosition(endX, endY);

        return true;
    }
};

class hor : public fig {
public:
    hor(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'H';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        int dx = (newX > x) ? (newX - x) : (x - newX); 
        int dy = (newY > y) ? (newY - y) : (y - newY); 
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
};

class que : public fig {
public:
    que(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'Q';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        int dx = (newX > x) ? (newX - x) : (x - newX);
        int dy = (newY > y) ? (newY - y) : (y - newY);

        if (dx == dy) {
            int stepX = (newX > x) ? 1 : -1;
            int stepY = (newY > y) ? 1 : -1;

            int currentX = x + stepX;
            int currentY = y + stepY;

            while (currentX != newX && currentY != newY) {
                if (board.getPiece(currentX, currentY).figura) {
                    return false;
                }
                currentX += stepX;
                currentY += stepY;
            }
            return true;
        }

      
        if (x == newX || y == newY) {
            int stepX = (newX > x) ? 1 : (newX < x) ? -1 : 0;
            int stepY = (newY > y) ? 1 : (newY < y) ? -1 : 0;

            int currentX = x + stepX;
            int currentY = y + stepY;

            while (currentX != newX || currentY != newY) {
                if (board.getPiece(currentX, currentY).figura) {
                    return false;
                }
                currentX += stepX;
                currentY += stepY;
            }
            return true;
        }

        return false;
    }
};

class kin : public fig {
public:
    kin(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'K';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        int dx = (newX > x) ? (newX - x) : (x - newX); 
        int dy = (newY > y) ? (newY - y) : (y - newY); 
        return (dx <= 1 && dy <= 1);
    }
};

class lad : public fig {
public:
    lad(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'L';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        if (x != newX && y != newY) {
            return false;
        }

        int dx = (newX > x) ? 1 : -1;
        int dy = (newY > y) ? 1 : -1;

        if (x == newX) {
            for (int i = y + dy; i != newY; i += dy) {
                if (board.getPiece(x, i).figura) {
                    return false;
                }
            }
        }
        else {
            for (int i = x + dx; i != newX; i += dx) {
                if (board.getPiece(i, y).figura) {
                    return false; 
                }
            }
        }

        return true;
    }
};

class elep : public fig {
public:
    elep(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'E';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        int dx = (newX > x) ? (newX - x) : (x - newX);
        int dy = (newY > y) ? (newY - y) : (y - newY);

        if (dx != dy) {
            return false;
        }

        int stepX = (newX > x) ? 1 : -1;
        int stepY = (newY > y) ? 1 : -1;

        int currentX = x + stepX;
        int currentY = y + stepY;
        while (currentX != newX && currentY != newY) {
            if (board.getPiece(currentX, currentY).figura) {
                return false; 
            }
            currentX += stepX;
            currentY += stepY;
        }

        return true;
    }
};

class pesh : public fig {
public:
    pesh(int x1, int y1, string name1) : fig(x1, y1, name1) {}

    char getSymbol() const override {
        return 'P';
    }

    bool canMove(int newX, int newY, ChessBoard& board) override {
        int dx = newX - x;
        int dy = newY - y;

        
        if (board.getPiece(x, y).isWhite) {
            
            if (dx > 0) return false;
        }
        else {
          
            if (dx < 0) return false;
        }

     
        if (dy == 0 && abs(dx) == 1) {
            
            return !board.getPiece(newX, newY).figura;
        }

        
        if (dy == 0 && abs(dx) == 2 && !Ismoved) {
            
            int middleX = x + (newX - x) / 2;
            return !board.getPiece(middleX, newY).figura && !board.getPiece(newX, newY).figura;
        }

        
        if (abs(dy) == 1 && abs(dx) == 1) {
            
            ChessBoard::Piece targetPiece = board.getPiece(newX, newY);
            return targetPiece.figura && targetPiece.isWhite != board.getPiece(x, y).isWhite;
        }

        return false;
    }

    void setPosition(int newX, int newY) override {
        if (!Ismoved) {
            Ismoved = true;
        }
        x = newX;
        y = newY;
    }
};

ChessBoard CreateFullPole() {
    ChessBoard chessBoard(8);

    // Белые фигуры
    chessBoard.placePiece(7, 1, new hor(7, 1, "Knight"), true);
    chessBoard.placePiece(7, 6, new hor(7, 6, "Knight"), true);
    chessBoard.placePiece(7, 0, new lad(7, 0, "Rook"), true);
    chessBoard.placePiece(7, 7, new lad(7, 7, "Rook"), true);
    chessBoard.placePiece(7, 2, new elep(7, 2, "Bishop"), true);
    chessBoard.placePiece(7, 5, new elep(7, 5, "Bishop"), true);
    chessBoard.placePiece(7, 4, new kin(7, 4, "King"), true);
    chessBoard.placePiece(7, 3, new que(7, 3, "Queen"), true);
    for (int i = 0; i < 8; ++i) {
        chessBoard.placePiece(6, i, new pesh(6, i, "Pawn"), true);
    }

    // Черные фигуры
    chessBoard.placePiece(0, 1, new hor(0, 1, "Knight"), false);
    chessBoard.placePiece(0, 6, new hor(0, 6, "Knight"), false);
    chessBoard.placePiece(0, 0, new lad(0, 0, "Rook"), false);
    chessBoard.placePiece(0, 7, new lad(0, 7, "Rook"), false);
    chessBoard.placePiece(0, 2, new elep(0, 2, "Bishop"), false);
    chessBoard.placePiece(0, 5, new elep(0, 5, "Bishop"), false);
    chessBoard.placePiece(0, 4, new kin(0, 4, "King"), false);
    chessBoard.placePiece(0, 3, new que(0, 3, "Queen"), false);
    for (int i = 0; i < 8; ++i) {
        chessBoard.placePiece(1, i, new pesh(1, i, "Pawn"), false);
    }

    return chessBoard;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ChessBoard chessBoard = CreateFullPole();
    bool isWhiteTurn = true;

    while (true) {
        chessBoard.printBoard();
        cout << (isWhiteTurn ? "Белые" : "Черные") << ", ваш ход. Введите ход (например, e2 e4): ";
        string move;
        getline(cin, move);

        if (move.length() != 5 || move[2] != ' ') {
            cout << "Неправильный формат хода. Попробуйте снова." << endl;
            continue;
        }

        int startX = 8 - (move[1] - '0');
        int startY = move[0] - 'a';
        int endX = 8 - (move[4] - '0');
        int endY = move[3] - 'a';

        if (chessBoard.movePiece(startX, startY, endX, endY, isWhiteTurn)) {
            isWhiteTurn = !isWhiteTurn;
        }
        else {
            cout << "Недопустимый ход. Попробуйте снова." << endl;
        }
    }

    return 0;
}
