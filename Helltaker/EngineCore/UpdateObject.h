#pragma once

// Ό³Έν :
class UUpdateObject
{
public:
	// constrcuter destructer
	UUpdateObject();
	~UUpdateObject();

	// delete Function
	UUpdateObject(const UUpdateObject& _Other) = delete;
	UUpdateObject(UUpdateObject&& _Other) noexcept = delete;
	UUpdateObject& operator=(const UUpdateObject& _Other) = delete;
	UUpdateObject& operator=(UUpdateObject&& _Other) noexcept = delete;

	void On()
	{
		IsUpdateValue = true;
	}

	void Off()
	{
		IsUpdateValue = false;
	}

	bool IsOn()
	{
		return IsUpdateValue;
	}


	void Death()
	{
		IsDeathValue = true;
	}

	bool IsDeath()
	{
		return IsDeathValue;
	}

protected:

private:
	bool IsUpdateValue = true;
	bool IsDeathValue = false;

};

