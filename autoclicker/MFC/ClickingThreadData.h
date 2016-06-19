#pragma once

#include "afxwin.h"
#include <vector>

typedef struct PayloadStruct
{
	bool issequence;
	std::vector<INPUT> KeySqeuence;
	long waittime;
} Payload;

typedef struct TwoBytesStruct
{
	BYTE vkey, modifiers;
} TwoBytes;

typedef struct ClickingThreadDataStruct
{
	int threadnumber;
	volatile bool isRunning;
	volatile bool isClicking;
	std::vector<TwoBytes> StartkeyCombo;
	std::vector<TwoBytes> StopkeyCombo;
	std::vector<Payload> Sequence;
} ClickingThreadData;