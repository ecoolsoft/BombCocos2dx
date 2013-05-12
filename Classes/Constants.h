/*
 * Constants.h
 *
 *  Created on: 2012-12-26
 *      Author: sky
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

namespace ecoolsoft {

class Constants {
public:
	Constants();
	virtual ~Constants();
	static const float SPRITE_MOVE_DURATION = 20;

	static const float SPRITE_RIGHT_POSITION_X = 270;
	static const float SPRITE_RIGHT_POSITION_Y = 60;
	static const float SPRITE_LEFT_POSITION_X = 0;
	static const float SPRITE_LEFT_POSITION_Y = 0;

	static const float BK_POSITION_X = 0;
	static const float BK_POSITION_Y = 0;

	static const float BTN_CLOSE_POSITION_X = 0;
	static const float BTN_CLOSE_POSITION_Y = 0;

	static const float MAIN_BOARD_POSITION_X = 15;
	static const float MAIN_BOARD_POSITION_Y = 35;
	static const float MAIN_TILE_LEN = 22;

	static const float SUB_BOARD_POSITION_X = 277;
	static const float SUB_BOARD_POSITION_Y = 83;
	static const float SUB_TILE_LEN = 18;

	static const float FONT_SIZE = 14;
	static const float TEXT_MARGIN = 3;

	static const float ROW_COUNT = 10;
	static const float COLUMN_COUNT = 10;

	static const float NORTH_SOURTH_LIMIT_POSITION_X = 6;
	static const float NORTH_SOURTH_LIMIT_POSITION_Y = 7;
	static const float WEST_EAST_LIMIT_POSITION_X = 7;
	static const float WEST_EAST_LIMIT_POSITION_Y = 6;
};

} /* namespace ecoolsoft */
#endif /* CONSTANTS_H_ */
