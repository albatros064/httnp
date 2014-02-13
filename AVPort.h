#ifndef AVPORT_H
#define AVPORT_H

#define AVPORT_AUDIO 1
#define AVPORT_VIDEO 2

#define AVPORT_AUDIO_BUFFER_SIZE    9600
#define AVPORT_VIDEO_BUFFER_SIZE 2304000

#define AVPORT_VIDEO_FRAME_SIZE 460800
#define AVPORT_VIDEO_LUMIN_SIZE 307200
#define AVPORT_VIDEO_CHROMA_SIZE 76800

#define AVPORT_AUDIO_CLIP_SIZE 400

#include <mutex>

namespace ConferenceManager {

using std::mutex;

class ConferenceMixer;

class CircularBuffer {
	public:
		CircularBuffer(int);
		virtual ~CircularBuffer();
		
		virtual void lock() { bufferMutex.lock(); }
		virtual void unlock() { bufferMutex.unlock(); }
		
		virtual int write(char*,int);
		virtual int read (char*,int);
		virtual void clear();
		
		int dataSize();
		int spaceFree();
		
	protected:
		int bufferSize;
		int bufferHead;
		int bufferTail;
		char *bufferData;
		
		mutex bufferMutex;
};

class AVPort : public CircularBuffer {
	public:
		AVPort(ConferenceMixer*,string,int);
		virtual ~AVPort() {}

		bool isActive() { return active; }
		void deactivate() { active = false; }

		bool isMaster() { return master; }
		void relinquish() { master = false; }
		void takeover();

	protected:
		
		ConferenceMixer *parentMixer;
		bool active;
		bool master;

		string source;

		friend class ConferenceMixer;
		
};

class AudioPort : public AVPort {
	public:
		AudioPort(ConferenceMixer*,string);
		virtual ~AudioPort() {}
	private:
	protected:
};

class VideoPort : public AVPort {
	public:
		VideoPort(ConferenceMixer*,string);
		virtual ~VideoPort() {}
		
	private:
	protected:
};

class DummyAudioPort : public AudioPort {
	public:
		DummyAudioPort(ConferenceMixer*);
		virtual ~DummyAudioPort() {}

		virtual void lock() {}
		virtual void unlock() {}
		virtual int write(char *a, int b) { return b; }
		virtual int read(char*,int);
		virtual void clear() {}
	private:
		bool allow;
};
class DummyVideoPort : public VideoPort {
	public:
		DummyVideoPort(ConferenceMixer*);
		virtual ~DummyVideoPort() {}

		virtual void lock() {}
		virtual void unlock() {}
		virtual int write(char *a, int b) { return b; }
		virtual int read(char*,int);
		virtual void clear() {}
	private:
		bool allow;
};

} // namespace

#endif
