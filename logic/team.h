#pragma once

#include "chess_piece.h"

class team
{
public:
    team(team_color color,int up_down);
	~team();

private:
	std::shared_ptr<chess_piece> pieces[16];
	team_color color_;
    int dir_;
    int up_down_;
};

