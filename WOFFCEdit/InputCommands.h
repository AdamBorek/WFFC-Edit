#pragma once

struct InputCommands
{
	// keyboard
	bool forward;
	bool back;
	bool right;
	bool left;
	bool up;
	bool down;
	bool rotRight;
	bool rotLeft;
	bool rotUp;
	bool rotDown;
	bool lCtrl;

	bool copy;
	bool cut;
	bool paste;
	bool deleteObj;

	// mouse
	int mouse_x;
	int mouse_y;
	bool mouse_left;
	bool mouse_right;

	bool mouse_left_hold;

	short wheel_pos;
	short last_wheel_pos;
};
