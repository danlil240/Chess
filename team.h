#pragma once

#include "chess_piece.h"

class team
{
public:
    team(team_color color,std::shared_ptr<board> board_);
	~team();

private:
	std::shared_ptr<chess_piece> pieces[16];
	team_color color_;
};

