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
	static const float SPRITE_LEFT_POSITION_X = 0;		//以左下角为基准点
	static const float SPRITE_LEFT_POSITION_Y = 0;

	static const float BK_POSITION_X = 0;
	static const float BK_POSITION_Y = 0;

	static const float BTN_CLOSE_POSITION_X = 445;
	static const float BTN_CLOSE_POSITION_Y = 285;
	static const float BTN_SETTING_POSITION_X = 405;
	static const float BTN_SETTING_POSITION_Y = 285;
	static const float BTN_ADD_POSITION_X = 284;
	static const float BTN_ADD_POSITION_Y = 32;
	static const float BTN_DELETE_POSITION_X = 322;
	static const float BTN_DELETE_POSITION_Y = 32;
	static const float BTN_START_POSITION_X = 435;
	static const float BTN_START_POSITION_Y = 0;
	static const float BTN_SOUND_POSITION_X = 360;
	static const float BTN_SOUND_POSITION_Y = 32;

	static const float MAIN_BOARD_POSITION_X = 15;		//左侧：270*280；边框：15；字母高度：20；数字宽度：20
	static const float MAIN_BOARD_POSITION_Y = 35;
	static const float MAIN_TILE_LEN = 22;				//每个格宽度

	static const float SUB_BOARD_POSITION_X = 277;		//右侧：210*220；边框：7；字母高度：16；数字宽度：16
	static const float SUB_BOARD_POSITION_Y = 83;
	static const float SUB_TILE_LEN = 18;				//每个格宽度

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
