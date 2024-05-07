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

	// mouse
	int mouse_x;
	int mouse_y;
	bool mouse_left;
	bool mouse_right;

	short wheel_pos;
	short last_wheel_pos;
};
