#ifndef __emptyExample__ofxAvUtils__
#define __emptyExample__ofxAvUtils__

#include <map>
#include <string>

extern "C"{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include <libavutil/channel_layout.h>
#include <libavutil/samplefmt.h>
#include <libswresample/swresample.h>
}

class AvUtils
{
public:
	
	// make sure ffmpeg is initialized
	static void init(); 
	
	// read metadata of a file
	static std::map<std::string,std::string> readMetadata( std::string filename );
	
	// updates the metadata.
	// the entire file has to be read and written during the process, so this is not fast!
	// however, the file will not be reencoded, so there is no quality loss.
	static bool updateMetadata( std::string filename, std::map<std::string,std::string> newMetadata );
	
	static std::map<std::string,std::string> read( std::string filename );
	static bool update( std::string filename, std::map<std::string,std::string> newMetadata );
	
	// file duration in seconds
	static double duration( std::string filename );
};

#endif /* defined(__emptyExample__ofxAvUtils__) */
