#pragma once

struct float4
{
	// F구조체의 

public:
	static const float4 Zero;
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	float X; // 2D
	float Y; // 2D
	float Z;
	float W;

public:
	float hX()
	{
		return X * 0.5f;
	}

	float hY()
	{
		return Y * 0.5f;
	}


	int ihY()
	{
		return static_cast<int>(hY());
	}

	int ihX()
	{
		return static_cast<int>(hX());
	}

	float4 operator+(const float4& _Other)
	{
		float4 Result = *this;
		Result.X += _Other.X;
		Result.Y += _Other.Y;
		Result.Z += _Other.Z;
		return Result;
	}

	float4& operator+=(const float4& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
		Z += _Other.Z;

		return *this;
	}

	float4 operator*(float _Value) const
	{
		float4 Result = *this;
		Result.X *= _Value;
		Result.Y *= _Value;
		Result.Z *= _Value;
		return Result;
	}

	float4& operator*=(float _Value)
	{
		X *= _Value;
		Y *= _Value;
		Z *= _Value;

		return *this;
	}

	float4 operator*(const float4& _Other) const
	{
		float4 Result = *this;
		Result.X *= _Other.X;
		Result.Y *= _Other.Y;
		Result.Z *= _Other.Z;
		return Result;
	}

	float4& operator*=(const float4& _Other)
	{
		X *= _Other.X;
		Y *= _Other.Y;
		Z *= _Other.Z;

		return *this;
	}

	float4 operator-(const float4& _Other)
	{
		float4 Result = *this;
		Result.X -= _Other.X;
		Result.Y -= _Other.Y;
		Result.Z -= _Other.Z;
		return Result;
	}

	float4& operator-=(const float4& _Other)
	{
		X -= _Other.X;
		Y -= _Other.Y;
		Z -= _Other.Z;

		return *this;
	}
};

using FVector = float4;

// 설명 :
class EngineMath
{
public:
	// constrcuter destructer
	EngineMath();
	~EngineMath();

	// delete Function
	EngineMath(const EngineMath& _Other) = delete;
	EngineMath(EngineMath&& _Other) noexcept = delete;
	EngineMath& operator=(const EngineMath& _Other) = delete;
	EngineMath& operator=(EngineMath&& _Other) noexcept = delete;

protected:

private:

};

