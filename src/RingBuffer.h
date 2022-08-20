/*
Simple RingBuffer template class.
*/
#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <Arduino.h>
template <typename T>
class RingBuffer
{
private:
	T *buffer;
	int bufferSize;

	int dataCount;
	int readIndex;
	int writeIndex;

	RingBuffer()
	{
		this->clear();
		this->bufferSize = 0;
		this->buffer = NULL;
	}

	void releaseBuffer()
	{
		if (this->buffer != NULL)
		{
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
		return this->dataCount;
	}

	bool isEmpty()
	{
		return (this->dataCount == 0);
	}

	bool isFull()
	{
		return (this->dataCount >= bufferSize);
	}

	T pull()
	{
		T item = this->buffer[this->readIndex++];
		this->readIndex = this->readIndex % this->bufferSize;
		this->dataCount--;
		return item;
	}

	void push(T item)
	{
		this->buffer[this->writeIndex++] = item;
		this->writeIndex = this->writeIndex % this->bufferSize;
		this->dataCount++;
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
};

#endif
