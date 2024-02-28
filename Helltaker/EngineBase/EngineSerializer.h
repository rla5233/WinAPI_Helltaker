#pragma once
#include <vector>
#include <string>

// 직렬화
// 
// 설명 :
class UEngineFile;
class UEngineSerializer
{
	friend UEngineFile;

public:
	// constrcuter destructer
	UEngineSerializer();
	~UEngineSerializer();

	// delete Function
	UEngineSerializer(const UEngineSerializer& _Other) = delete;
	UEngineSerializer(UEngineSerializer&& _Other) noexcept = delete;
	UEngineSerializer& operator=(const UEngineSerializer& _Other) = delete;
	UEngineSerializer& operator=(UEngineSerializer&& _Other) noexcept = delete;

	void Write(void* _Data, unsigned int _Size);

	void operator<<(int& _Data)
	{
		Write(&_Data, sizeof(int));
	}
	void operator<<(bool& _Data)
	{
		Write(&_Data, sizeof(bool));
	}
	void operator<<(std::string& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		operator<<(Size);
		Write(&_Data[0], Size);
	}

	void Read(void* _Data, unsigned int _Size);

	void operator>>(int& _Data)
	{
		Read(&_Data, sizeof(int));
	}

	void operator>>(std::string& _Data)
	{
		int Size = 0;
		operator>>(Size);

		if (Size == 0)
		{
			return;
		}
		_Data.resize(Size);
		Read(&_Data[0], Size);
	}


	void BufferResize(int _Size);

protected:

private:
	unsigned int WriteOffset = 0;
	unsigned int ReadOffset = 0;

	std::vector<char> Data;
};

