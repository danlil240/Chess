#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <vector>

class board 
{
public:
    board();
	~board();
	bool isTaken(std::vector<int> square);
	bool threaten;
    void updateSquares(std::vector<int> from,std::vector<int> to);

private:
    void init();

};
