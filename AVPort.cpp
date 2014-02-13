#include <cstring>
#include <iostream>

#include "ConferenceManager.h"
#include "ConferenceMixer.h"
#include "AVPort.h"

namespace ConferenceManager {

using std::cout;

AudioPort::AudioPort(ConferenceMixer *parent, string source):
  AVPort(parent, source, AVPORT_AUDIO_BUFFER_SIZE) {
}
VideoPort::VideoPort(ConferenceMixer *parent, string source):
  AVPort(parent, source, AVPORT_VIDEO_BUFFER_SIZE) {
}


DummyVideoPort::DummyVideoPort(ConferenceMixer *parent):
  VideoPort(parent, (string) "dummy"), allow(true) {
	master = true;
}
int DummyVideoPort::read(char *data, int size) {
	int ret = -2;
	if (allow) {
		memcpy(data, ConferenceManager::blankScreen, AVPORT_VIDEO_FRAME_SIZE);
		ret = size;
	}
	allow = !allow;
	return ret;
}
DummyAudioPort::DummyAudioPort(ConferenceMixer *parent):
  AudioPort(parent, (string) "dummy"), allow(true) {
	master = true;
}
int DummyAudioPort::read(char *data, int size) {
	int ret = -2;
	if (allow) {
		memset(data, 0xff, size);
		ret = size;
	}
	allow = !allow;
	return ret;
}



AVPort::AVPort(ConferenceMixer *parent, string source, int size):
  CircularBuffer(size), parentMixer(parent),
  active(true),master(false) {
	this->source = source;
}
void AVPort::takeover() {
	parentMixer->setActiveVideo((VideoPort*)this);
}



CircularBuffer::CircularBuffer(int size):
  bufferSize(size),
  bufferHead(0), bufferTail(0) {
	bufferData = (char *) malloc(size + 1);
	
	if (!bufferData) {
		bufferSize = 0;
	}
}
CircularBuffer::~CircularBuffer() {
	free(bufferData);
	bufferData = 0;
	bufferSize = 0;
}

int CircularBuffer::write(char *data, int size) {
	if (data == 0) {
		return -1;
	}
	if (size > spaceFree()) {
		return -2;
	}

	// TODO: switch to one or two memcpy() calls
	// for now, use a 1-byte loop
	for (int i = 0; i  < size; i++) {
		bufferData[bufferTail++] = data[i];
		if (bufferTail > bufferSize) {
			bufferTail = 0;
		}
	}
	
	return size;
}
int CircularBuffer::read(char *data, int size) {
	if (data == 0) {
		return -1;
	}
	if (size > dataSize()) {
		return -2;
	}
	if (size == 0) {
		size = dataSize();
	}

	// TODO: switch to one or two memcpy() calls
	// for now, use a 1-byte loop
	for (int i = 0; i < size; i++) {
		data[i] = bufferData[bufferHead++];
		if (bufferHead > bufferSize) {
			bufferHead = 0;
		}
	}

	return size;
}
void CircularBuffer::clear() {
	bufferHead = bufferTail;
}

int CircularBuffer::dataSize() {
	if (bufferHead == bufferTail) {
		return 0;
	}
	int size = bufferTail - bufferHead;
	if (size > 0) {
		return size;
	}
	return size + bufferSize;
}
int CircularBuffer::spaceFree() {
	return bufferSize - 1 - dataSize();
}

} // namespace
