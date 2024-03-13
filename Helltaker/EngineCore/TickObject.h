#pragma once
#include <EngineBase\EngineDebug.h>

// 설명 :
class UTickObject
{

public:
	// constrcuter destructer
	UTickObject();
	virtual ~UTickObject();

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	void ActiveOn()
	{
		IsActiveValue = true;
	}

	void ActiveOff()
	{
		IsActiveValue = false;
	}

	virtual void SetActive(bool _Active, float _ActiveTime = 0.0f)
	{
		ActiveTime = _ActiveTime;

		if (true == _Active && 0.0f == ActiveTime)
		{
			IsActiveValue = _Active;
			return;
		}

		if (true == _Active && 0.0f != ActiveTime)
		{
			IsActiveUpdate = true;
		}
		IsActiveValue = false;
	}

	bool IsActive()
	{
		// 내가 켜져있고         죽지도 않았다면
		return IsActiveValue && IsDestroyValue == false;
	}


	virtual void Destroy(float _DestroyTime = 0.0f)
	{
		IsDestroyUpdate = true;
		DestroyTime = _DestroyTime;
		if (0.0f >= _DestroyTime)
		{
			this->IsDestroyValue = true;
		}
	}

	int GetOrder()
	{
		return Order;
	}

	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	virtual void ActiveUpdate(float _DeltaTime)
	{
		ActiveTime -= _DeltaTime;

		if (true == IsActiveUpdate)
		{
			if (0.0f >= ActiveTime)
			{
				IsActiveUpdate = false;
				IsActiveValue = true;
				return;
			}
		}
	}

	virtual void DestroyUpdate(float _DeltaTime)
	{
		if (false == IsDestroyUpdate)
		{
			return;
		}

		DestroyTime -= _DeltaTime;
		if (0.0f >= DestroyTime)
		{
			Destroy(0.0f);
		}
	}

	bool IsDestroy()
	{
		return IsDestroyValue;
	}

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
	virtual void End();

	void DebugCheckOn()
	{
		IsDebugCheck = true;
	}

	void DebugCheck()
	{
		if (true == IsDebugCheck)
		{
			int a = 0;
		}
	}

protected:

private:
	bool IsDebugCheck = false;
	int Order = 0;

	bool IsDestroyUpdate = false;
	float DestroyTime = 0.0f;
	bool IsDestroyValue = false;

	bool IsActiveUpdate = false;
	float ActiveTime = 0.0f;
	bool IsActiveValue = true;
};

