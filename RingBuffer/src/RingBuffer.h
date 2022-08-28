/*
Simple RingBuffer template class.
*/
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <Arduino.h>

typedef std::function<void(void*)> OnPushToBufferCb;

template <typename T>
class RingBuffer
{
protected:
	T* buffer;
	int bufferSize;

	int dataCount;
	int readIndex;
	int writeIndex;

	OnPushToBufferCb ptrOnPushToBufferCb;

	RingBuffer()
	{
		this->clear();
		this->bufferSize = 0;
		this->buffer = NULL;
		this->ptrOnPushToBufferCb = NULL;
	}

	void releaseBuffer()
	{
		if (this->buffer != NULL) {
			free(this->buffer);
			this->buffer = NULL;
			this->bufferSize = 0;
		}
	}

	void allocBuffer(int bufsize)
	{
		this->releaseBuffer();

		this->buffer = (T*)malloc(sizeof(T) * bufsize);
		this->bufferSize = bufsize;
		this->clear();
	}

public:
	RingBuffer(int initialSize) : RingBuffer()
	{
		this->allocBuffer(initialSize);
	}

	~RingBuffer()
	{
	}

	int available()
	{
		this->onPushToBuffer();
		return this->dataCount;
	}

	bool isEmpty()
	{
		this->onPushToBuffer();

		return (this->dataCount == 0);
	}

	bool isFull()
	{
		return (this->dataCount >= bufferSize);
	}

	T read()
	{
		T item = this->buffer[this->readIndex++];
		this->readIndex = this->readIndex % this->bufferSize;
		this->dataCount--;
		return item;
	}

	void write(T item)
	{
		this->buffer[this->writeIndex++] = item;
		this->writeIndex = this->writeIndex % this->bufferSize;
		this->dataCount++;
	}

	T peek()
	{
		return this->buffer[this->readIndex];
	}

	void clear()
	{
		this->dataCount = 0;
		this->readIndex = 0;
		this->writeIndex = 0;
	}

	void setBufferSize(int newSize)
	{
		this->allocBuffer(newSize);
	}

	int getBufferSize()
	{
		return this->bufferSize;
	}

	virtual void onPushToBuffer()
	{
		if (this->ptrOnPushToBufferCb != NULL) {
			if (!this->isFull()) {
				this->ptrOnPushToBufferCb(this);
			}
		}
	}

	virtual void setOnPushToBufferCb(OnPushToBufferCb callback)
	{
		this->ptrOnPushToBufferCb = callback;
	}
};

class ByteRingBuffer : public RingBuffer<byte>, public Stream
{
public:
	ByteRingBuffer(const int size) :RingBuffer<byte>(size)
	{
	}

	virtual int available() override
	{
		return RingBuffer<byte>::available();
	}

	virtual int read() override
	{
		if (RingBuffer<byte>::available() > 0) {
			return this->read();
		}
		return -1;
	}

	virtual int peek() override
	{
		return RingBuffer<byte>::peek();
	}

	virtual size_t write(uint8_t data) override
	{
		if (!RingBuffer<byte>::isFull()) {
			RingBuffer<byte>::write(data);
			return 1;
		}
		return 0;
	}
};

#endif
