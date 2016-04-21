#pragma once

#define MAX_KEYS	1024
#define MAX_BUTTONS	32


#define MOUSE_LEFT	  0x00
#define MOUSE_MIDDLE	  0x01
#define MOUSE_RIGHT    0x02

#define MOUSE_NO_CURSOR	  NULL

#define KB_MODIFIER_LEFT_CONTROL	1 << 2
#define KB_MODIFIER_LEFT_ALT		1 << 3
#define KB_MODIFIER_LEFT_SHIFT		1 << 4
#define KB_MODIFIER_RIGHT_CONTROL	1 << 5
#define KB_MODIFIER_RIGHT_ALT		1 << 6
#define KB_MODIFIER_RIGHT_SHIFT		1 << 7

#define KB_KEY_TAB			  0x09

#define KB_KEY_0			  0x30
#define KB_KEY_1			  0x31
#define KB_KEY_2			  0x32
#define KB_KEY_3			  0x33
#define KB_KEY_4			  0x34
#define KB_KEY_5			  0x35
#define KB_KEY_6			  0x36
#define KB_KEY_7			  0x37
#define KB_KEY_8			  0x38
#define KB_KEY_9			  0x39

#define KB_KEY_A			  0x41
#define KB_KEY_B			  0x42
#define KB_KEY_C			  0x43
#define KB_KEY_D			  0x44
#define KB_KEY_E			  0x45
#define KB_KEY_F			  0x46
#define KB_KEY_G			  0x47
#define KB_KEY_H			  0x48
#define KB_KEY_I			  0x49
#define KB_KEY_J			  0x4A
#define KB_KEY_K			  0x4B
#define KB_KEY_L			  0x4C
#define KB_KEY_M			  0x4D
#define KB_KEY_N			  0x4E
#define KB_KEY_O			  0x4F
#define KB_KEY_P			  0x50
#define KB_KEY_Q			  0x51
#define KB_KEY_R			  0x52
#define KB_KEY_S			  0x53
#define KB_KEY_T			  0x54
#define KB_KEY_U			  0x55
#define KB_KEY_V			  0x56
#define KB_KEY_W			  0x57
#define KB_KEY_X			  0x58
#define KB_KEY_Y			  0x59
#define KB_KEY_Z			  0x5A

#define KB_KEY_LBUTTON        0x01
#define KB_KEY_RBUTTON        0x02
#define KB_KEY_CANCEL         0x03
#define KB_KEY_MBUTTON        0x04

#define KB_KEY_ESCAPE         0x1B
#define KB_KEY_SHIFT          0x10
#define KB_KEY_CONTROL        0x11
#define KB_KEY_MENU           0x12
#define KB_KEY_ALT	          KB_KEY_MENU
#define KB_KEY_PAUSE          0x13
#define KB_KEY_CAPITAL        0x14

#define KB_KEY_KBACE          0x20
#define KB_KEY_PRIOR          0x21
#define KB_KEY_NEXT           0x22
#define KB_KEY_END            0x23
#define KB_KEY_HOME           0x24
#define KB_KEY_LEFT           0x25
#define KB_KEY_UP             0x26
#define KB_KEY_RIGHT          0x27
#define KB_KEY_DOWN           0x28
#define KB_KEY_SELECT         0x29
#define KB_KEY_PRINT          0x2A
#define KB_KEY_EXECUTE        0x2B
#define KB_KEY_SNAPSHOT       0x2C
#define KB_KEY_INSERT         0x2D
#define KB_KEY_DELETE         0x2E
#define KB_KEY_HELP           0x2F

#define KB_KEY_NUMPAD0        0x60
#define KB_KEY_NUMPAD1        0x61
#define KB_KEY_NUMPAD2        0x62
#define KB_KEY_NUMPAD3        0x63
#define KB_KEY_NUMPAD4        0x64
#define KB_KEY_NUMPAD5        0x65
#define KB_KEY_NUMPAD6        0x66
#define KB_KEY_NUMPAD7        0x67
#define KB_KEY_NUMPAD8        0x68
#define KB_KEY_NUMPAD9        0x69
#define KB_KEY_MULTIPLY       0x6A
#define KB_KEY_ADD            0x6B
#define KB_KEY_SEPARATOR      0x6C
#define KB_KEY_SUBTRACT       0x6D
#define KB_KEY_DECIMAL        0x6E
#define KB_KEY_DIVIDE         0x6F
#define KB_KEY_F1             0x70
#define KB_KEY_F2             0x71
#define KB_KEY_F3             0x72
#define KB_KEY_F4             0x73
#define KB_KEY_F5             0x74
#define KB_KEY_F6             0x75
#define KB_KEY_F7             0x76
#define KB_KEY_F8             0x77
#define KB_KEY_F9             0x78
#define KB_KEY_F10            0x79
#define KB_KEY_F11            0x7A
#define KB_KEY_F12            0x7B
#define KB_KEY_F13            0x7C
#define KB_KEY_F14            0x7D
#define KB_KEY_F15            0x7E
#define KB_KEY_F16            0x7F
#define KB_KEY_F17            0x80
#define KB_KEY_F18            0x81
#define KB_KEY_F19            0x82
#define KB_KEY_F20            0x83
#define KB_KEY_F21            0x84
#define KB_KEY_F22            0x85
#define KB_KEY_F23            0x86
#define KB_KEY_F24            0x87

#define KB_KEY_NUMLOCK        0x90
#define KB_KEY_SCROLL         0x91

#define KB_KEY_LSHIFT         0xA0
#define KB_KEY_RSHIFT         0xA1
#define KB_KEY_LCONTROL       0xA2
#define KB_KEY_RCONTROL       0xA3
#define KB_KEY_LMENU          0xA4
#define KB_KEY_RMENU          0xA5