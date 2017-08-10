#ifndef InputEnums_H
#define InputEnums_H

namespace Key
{
	enum Code
	{
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		Num0 = 48,
		Num1 = 49,
		Num2 = 50,
		Num3 = 51,
		Num4 = 52,
		Num5 = 53,
		Num6 = 54,
		Num7 = 55,
		Num8 = 56,
		Num9 = 57,
		Escape = 256,
		LControl,
		LShift,
		LAlt,
		LSystem,      ///< OS specific key (left side) : windows (Win and Linux), apple (MacOS), ...
		RControl,
		RShift,
		RAlt,
		RSystem,      ///< OS specific key (right side) : windows (Win and Linux), apple (MacOS), ...
		Menu,
		LBracket,     ///< [
		RBracket,     ///< ]
		SemiColon,    ///< ;
		Comma,        ///< ,
		Period,       ///< .
		Quote,        ///< '
		Slash,        ///< /
		BackSlash,
		Tilde,        ///< ~
		Equal,        ///< =
		Dash,         ///< -
		Space = 32,
		Return = 257,
		Back,
		Tab,
		PageUp,
		PageDown,
		End,
		Home,
		Insert,
		Delete,
		Add,          ///< +
		Subtract,     ///< -
		Multiply,     ///< *
		Divide,       ///< /
		Left = 263,         ///< Left arrow
		Right = 262,        ///< Right arrow
		Up = 265,           ///< Up arrow
		Down = 264,         ///< Down arrow
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		Pause,

		Count // Keep last -- total number of keyboard keys
	};
}

namespace Mouse
{
	enum Button
	{
		Left = 0,
		Right = 1,
		Middle = 3,

		Count // Keep last -- total number
	};
}

namespace Gamepad
{
	enum Button
	{
		Left,
		Right,
		Up,
		Down,
		Triangle,
		Square,
		Circle,
		Cross,
		LTrigger,
		RTrigger,
		Select,
		Start,

		Count // Keep last -- total number
	};
}

#endif
