




class chess_piece {

public:

    ~chess_piece();
     void executeMove(int new_location[2]);

private:

    bool checkValidMove(int new_location[2]);




};
