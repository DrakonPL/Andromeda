#ifndef SharedData_H
#define SharedData_H

#include <psp2/audioout.h>
#include <psp2/kernel/threadmgr.h>
#include <psp2/kernel/processmgr.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "audio_decoder.h"


#define BUFSIZE 8192 // Max dimension of audio buffer size
#define NSAMPLES 2048 // Number of samples for output
#define AUDIO_CHANNELS 8 // PSVITA has 8 available audio channels

// Music block struct
struct DecodedMusic
{
	volatile float volume;
	int audioPort;
	uint8_t* audiobuf;
	uint8_t* audiobuf2;
	uint8_t* cur_audiobuf;
	FILE* handle;
	volatile bool isPlaying;
	bool loop;
	volatile bool pauseTrigger;
	volatile bool closeTrigger;
	volatile uint8_t audioThread;
	char filepath[256];
	bool tempBlock;
};



#endif
