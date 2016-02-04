//Credits to Hans Henrik for writing this data structure so everyone can use it

struct VKeyStruct {
	CString Name;
	UINT VKey;
	CString Description;
};

const VKeyStruct VKeyList[178] = {
	{ _T("VK_LBUTTON"), 0x01, _T("Left mouse button") },
	{ _T("VK_RBUTTON"), 0x02, _T("Right mouse button") },
	{ _T("VK_CANCEL"), 0x03, _T("Control-break processing") },
	{ _T("VK_MBUTTON"), 0x04, _T("Middle mouse button") },
	{ _T("VK_XBUTTON1"), 0x05, _T("X1 mouse button") },
	{ _T("VK_XBUTTON2"), 0x06, _T("X2 mouse button") },
	{ _T("-"), 0x07, _T("Undefined") },
	{ _T("VK_BACK"), 0x08, _T("BACKSPACE key") },
	{ _T("VK_TAB"), 0x09, _T("TAB key") },
	//{ _T("-"), 0x0A - 0B, _T("Reserved") },
	{ _T("VK_CLEAR"), 0x0C, _T("CLEAR key") },
	{ _T("VK_RETURN"), 0x0D, _T("ENTER key") },
	//{ _T("-"), 0x0E - 0F, _T("Undefined") },
	{ _T("VK_SHIFT"), 0x10, _T("SHIFT key") },
	{ _T("VK_CONTROL"), 0x11, _T("CTRL key") },
	{ _T("VK_MENU"), 0x12, _T("ALT key") },
	{ _T("VK_PAUSE"), 0x13, _T("PAUSE key") },
	{ _T("VK_CAPITAL"), 0x14, _T("CAPS LOCK key") },
	{ _T("VK_KANA"), 0x15, _T("IME Kana mode") },
	{ _T("VK_HANGUEL"), 0x15, _T("IME Hanguel mode") },
	{ _T("VK_HANGUL"), 0x15, _T("IME Hangul mode") },
	//{ _T("-"), 0x16, _T("Undefined") },
	{ _T("VK_JUNJA"), 0x17, _T("IME Junja mode") },
	{ _T("VK_FINAL"), 0x18, _T("IME final mode") },
	{ _T("VK_HANJA"), 0x19, _T("IME Hanja mode") },
	{ _T("VK_KANJI"), 0x19, _T("IME Kanji mode") },
	//{ _T("-"), 0x1A, _T("Undefined") },
	{ _T("VK_ESCAPE"), 0x1B, _T("ESC key") },
	{ _T("VK_CONVERT"), 0x1C, _T("IME convert") },
	{ _T("VK_NONCONVERT"), 0x1D, _T("IME nonconvert") },
	{ _T("VK_ACCEPT"), 0x1E, _T("IME accept") },
	{ _T("VK_MODECHANGE"), 0x1F, _T("IME mode change request") },
	{ _T("VK_SPACE"), 0x20, _T("SPACEBAR") },
	{ _T("VK_PRIOR"), 0x21, _T("PAGE UP key") },
	{ _T("VK_NEXT"), 0x22, _T("PAGE DOWN key") },
	{ _T("VK_END"), 0x23, _T("END key") },
	{ _T("VK_HOME"), 0x24, _T("HOME key") },
	{ _T("VK_LEFT"), 0x25, _T("LEFT ARROW key") },
	{ _T("VK_UP"), 0x26, _T("UP ARROW key") },
	{ _T("VK_RIGHT"), 0x27, _T("RIGHT ARROW key") },
	{ _T("VK_DOWN"), 0x28, _T("DOWN ARROW key") },
	{ _T("VK_SELECT"), 0x29, _T("SELECT key") },
	{ _T("VK_PRINT"), 0x2A, _T("PRINT key") },
	{ _T("VK_EXECUTE"), 0x2B, _T("EXECUTE key") },
	{ _T("VK_SNAPSHOT"), 0x2C, _T("PRINT SCREEN key") },
	{ _T("VK_INSERT"), 0x2D, _T("INS key") },
	{ _T("VK_DELETE"), 0x2E, _T("DEL key") },
	{ _T("VK_HELP"), 0x2F, _T("HELP key") },
	{ _T("0 key"), 0x30, _T("0 key") },
	{ _T("1 key"), 0x31, _T("1 key") },
	{ _T("2 key"), 0x32, _T("2 key") },
	{ _T("3 key"), 0x33, _T("3 key") },
	{ _T("4 key"), 0x34, _T("4 key") },
	{ _T("5 key"), 0x35, _T("5 key") },
	{ _T("6 key"), 0x36, _T("6 key") },
	{ _T("7 key"), 0x37, _T("7 key") },
	{ _T("8 key"), 0x38, _T("8 key") },
	{ _T("9 key"), 0x39, _T("9 key") },
	//{ _T("undefined"), 0x3A - 40, _T("undefined") },
	{ _T("A key"), 0x41, _T("A key") },
	{ _T("B key"), 0x42, _T("B key") },
	{ _T("C key"), 0x43, _T("C key") },
	{ _T("D key"), 0x44, _T("D key") },
	{ _T("E key"), 0x45, _T("E key") },
	{ _T("F key"), 0x46, _T("F key") },
	{ _T("G key"), 0x47, _T("G key") },
	{ _T("H key"), 0x48, _T("H key") },
	{ _T("I key"), 0x49, _T("I key") },
	{ _T("J key"), 0x4A, _T("J key") },
	{ _T("K key"), 0x4B, _T("K key") },
	{ _T("L key"), 0x4C, _T("L key") },
	{ _T("M key"), 0x4D, _T("M key") },
	{ _T("N key"), 0x4E, _T("N key") },
	{ _T("O key"), 0x4F, _T("O key") },
	{ _T("P key"), 0x50, _T("P key") },
	{ _T("Q key"), 0x51, _T("Q key") },
	{ _T("R key"), 0x52, _T("R key") },
	{ _T("S key"), 0x53, _T("S key") },
	{ _T("T key"), 0x54, _T("T key") },
	{ _T("U key"), 0x55, _T("U key") },
	{ _T("V key"), 0x56, _T("V key") },
	{ _T("W key"), 0x57, _T("W key") },
	{ _T("X key"), 0x58, _T("X key") },
	{ _T("Y key"), 0x59, _T("Y key") },
	{ _T("Z key"), 0x5A, _T("Z key") },
	{ _T("VK_LWIN"), 0x5B, _T("Left Windows key") },
	{ _T("VK_RWIN"), 0x5C, _T("Right Windows key") },
	{ _T("VK_APPS"), 0x5D, _T("Applications key") },
	//{ _T("-"), 0x5E, _T("Reserved") },
	{ _T("VK_SLEEP"), 0x5F, _T("Computer Sleep key") },
	{ _T("VK_NUMPAD0"), 0x60, _T("Numpad 0 key") },
	{ _T("VK_NUMPAD1"), 0x61, _T("Numpad 1 key") },
	{ _T("VK_NUMPAD2"), 0x62, _T("Numpad 2 key") },
	{ _T("VK_NUMPAD3"), 0x63, _T("Numpad 3 key") },
	{ _T("VK_NUMPAD4"), 0x64, _T("Numpad 4 key") },
	{ _T("VK_NUMPAD5"), 0x65, _T("Numpad 5 key") },
	{ _T("VK_NUMPAD6"), 0x66, _T("Numpad 6 key") },
	{ _T("VK_NUMPAD7"), 0x67, _T("Numpad 7 key") },
	{ _T("VK_NUMPAD8"), 0x68, _T("Numpad 8 key") },
	{ _T("VK_NUMPAD9"), 0x69, _T("Numpad 9 key") },
	{ _T("VK_MULTIPLY"), 0x6A, _T("Multiply key") },
	{ _T("VK_ADD"), 0x6B, _T("Add key") },
	{ _T("VK_SEPARATOR"), 0x6C, _T("Separator key") },
	{ _T("VK_SUBTRACT"), 0x6D, _T("Subtract key") },
	{ _T("VK_DECIMAL"), 0x6E, _T("Decimal key") },
	{ _T("VK_DIVIDE"), 0x6F, _T("Divide key") },
	{ _T("VK_F1"), 0x70, _T("F1 key") },
	{ _T("VK_F2"), 0x71, _T("F2 key") },
	{ _T("VK_F3"), 0x72, _T("F3 key") },
	{ _T("VK_F4"), 0x73, _T("F4 key") },
	{ _T("VK_F5"), 0x74, _T("F5 key") },
	{ _T("VK_F6"), 0x75, _T("F6 key") },
	{ _T("VK_F7"), 0x76, _T("F7 key") },
	{ _T("VK_F8"), 0x77, _T("F8 key") },
	{ _T("VK_F9"), 0x78, _T("F9 key") },
	{ _T("VK_F10"), 0x79, _T("F10 key") },
	{ _T("VK_F11"), 0x7A, _T("F11 key") },
	{ _T("VK_F12"), 0x7B, _T("F12 key") },
	{ _T("VK_F13"), 0x7C, _T("F13 key") },
	{ _T("VK_F14"), 0x7D, _T("F14 key") },
	{ _T("VK_F15"), 0x7E, _T("F15 key") },
	{ _T("VK_F16"), 0x7F, _T("F16 key") },
	{ _T("VK_F17"), 0x80, _T("F17 key") },
	{ _T("VK_F18"), 0x81, _T("F18 key") },
	{ _T("VK_F19"), 0x82, _T("F19 key") },
	{ _T("VK_F20"), 0x83, _T("F20 key") },
	{ _T("VK_F21"), 0x84, _T("F21 key") },
	{ _T("VK_F22"), 0x85, _T("F22 key") },
	{ _T("VK_F23"), 0x86, _T("F23 key") },
	{ _T("VK_F24"), 0x87, _T("F24 key") },
	//{ _T("-"), 0x88 - 8F, _T("Unassigned") },
	{ _T("VK_NUMLOCK"), 0x90, _T("NUM LOCK key") },
	{ _T("VK_SCROLL"), 0x91, _T("SCROLL LOCK key") },
	//{ _T("-"), 0x88 - 8F, _T("Unassigned") },
	{ _T("VK_NUMLOCK"), 0x90, _T("NUM LOCK key") },
	{ _T("VK_SCROLL"), 0x91, _T("SCROLL LOCK key") },
	//{"-"), 0x92-96,"OEM specific"},
	//{ _T("-"), 0x97 - 9F, _T("Unassigned") },
	{ _T("VK_LSHIFT"), 0xA0, _T("Left SHIFT key") },
	{ _T("VK_RSHIFT"), 0xA1, _T("Right SHIFT key") },
	{ _T("VK_LCONTROL"), 0xA2, _T("Left CONTROL key") },
	{ _T("VK_RCONTROL"), 0xA3, _T("Right CONTROL key") },
	{ _T("VK_LMENU"), 0xA4, _T("Left MENU key") },
	{ _T("VK_RMENU"), 0xA5, _T("Right MENU key") },
	{ _T("VK_BROWSER_BACK"), 0xA6, _T("Browser Back key") },
	{ _T("VK_BROWSER_FORWARD"), 0xA7, _T("Browser Forward key") },
	{ _T("VK_BROWSER_REFRESH"), 0xA8, _T("Browser Refresh key") },
	{ _T("VK_BROWSER_STOP"), 0xA9, _T("Browser Stop key") },
	{ _T("VK_BROWSER_SEARCH"), 0xAA, _T("Browser Search key") },
	{ _T("VK_BROWSER_FAVORITES"), 0xAB, _T("Browser Favorites key") },
	{ _T("VK_BROWSER_HOME"), 0xAC, _T("Browser Start and Home key") },
	{ _T("VK_VOLUME_MUTE"), 0xAD, _T("Volume Mute key") },
	{ _T("VK_VOLUME_DOWN"), 0xAE, _T("Volume Down key") },
	{ _T("VK_VOLUME_UP"), 0xAF, _T("Volume Up key") },
	{ _T("VK_MEDIA_NEXT_TRACK"), 0xB0, _T("Next Track key") },
	{ _T("VK_MEDIA_PREV_TRACK"), 0xB1, _T("Previous Track key") },
	{ _T("VK_MEDIA_STOP"), 0xB2, _T("Stop Media key") },
	{ _T("VK_MEDIA_PLAY_PAUSE"), 0xB3, _T("Play/Pause Media key") },
	{ _T("VK_LAUNCH_MAIL"), 0xB4, _T("Start Mail key") },
	{ _T("VK_LAUNCH_MEDIA_SELECT"), 0xB5, _T("Select Media key") },
	{ _T("VK_LAUNCH_APP1"), 0xB6, _T("Start Application 1 key") },
	{ _T("VK_LAUNCH_APP2"), 0xB7, _T("Start Application 2 key") },
	//{ _T("-"), 0xB8 - B9, _T("Reserved") },
	{ _T("VK_OEM_1"), 0xBA, _T("';:' keyS") },
	{ _T("VK_OEM_PLUS"), 0xBB, _T("'+' key") },
	{ _T("VK_OEM_COMMA"), 0xBC, _T("',' key") },
	{ _T("VK_OEM_MINUS"), 0xBD, _T("'-' key") },
	{ _T("VK_OEM_PERIOD"), 0xBE, _T("'.' key") },
	{ _T("VK_OEM_2"), 0xBF, _T("'/?' key") },
	{ _T("VK_OEM_3"), 0xC0, _T("'`~' key") },
	//{ _T("-"), 0xC1 - D7, _T("Reserved") },
	//{ _T("-"), 0xD8 - DA, _T("Unassigned") },
	{ _T("VK_OEM_4"), 0xDB, _T("'[{' key") },
	{ _T("VK_OEM_5"), 0xDC, _T("'\\|' key") },
	{ _T("VK_OEM_6"), 0xDD, _T("']}' key") },
	{ _T("VK_OEM_7"), 0xDE, _T("'/\") key") },
	{ _T("VK_OEM_8"), 0xDF, _T("Undefined") },
	//{ _T("-"), 0xE0, _T("Reserved") },
	//{ _T("-"), 0xE1, _T("OEM specific") },
	{ _T("VK_OEM_102"), 0xE2, _T("</> key") },
	//{ _T("-"), 0xE3 - E4, _T("OEM specific") },
	{ _T("VK_PROCESSKEY"), 0xE5, _T("IME PROCESS key") },
	//{ _T("-"), 0xE6, _T("OEM specific") },
	{ _T("VK_PACKET"), 0xE7, _T("Undefined") },
	//{ _T("-"), 0xE8, _T("Unassigned") },
	//  {"-"),0xE6,"OEM specific"},
	{ _T("VK_PACKET"),0xE7, _T("Undefined") },
	//  {"-"),0xE8,"Unassigned"},
	//{ _T("-"), 0xE9 - F5, _T("OEM specific") },
	{ _T("VK_ATTN"), 0xF6, _T("Attn key") },
	{ _T("VK_CRSEL"), 0xF7, _T("CrSel key") },
	{ _T("VK_EXSEL"), 0xF8, _T("ExSel key") },
	{ _T("VK_EREOF"), 0xF9, _T("Erase EOF key") },
	{ _T("VK_PLAY"), 0xFA, _T("Play key") },
	{ _T("VK_ZOOM"), 0xFB, _T("Zoom key") },
	{ _T("VK_NONAME"), 0xFC, _T("Reserved") },
	{ _T("VK_PA1"), 0xFD, _T("PA1 key") },
	{ _T("VK_OEM_CLEAR"), 0xFE, _T("Clear key") }
};