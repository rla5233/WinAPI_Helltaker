#include "EngineMath.h"

const float4 float4::Zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Left = { -1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Right = { 1.0f, 0.0f, 0.0f, 0.0f };
const float4 float4::Up = { 0.0f, -1.0f, 0.0f, 0.0f };
const float4 float4::Down = { 0.0f, 1.0f, 0.0f, 0.0f };

const Color8Bit Color8Bit::Black = { 0, 0, 0, 255 };
const Color8Bit Color8Bit::Red = { 255, 0, 0, 255 };
const Color8Bit Color8Bit::Green = { 0, 255, 0, 255 };
const Color8Bit Color8Bit::Blue = { 0, 0, 255, 255 };
const Color8Bit Color8Bit::White = { 255, 255, 255, 255 };

EngineMath::EngineMath()
{}

EngineMath::~EngineMath()
{}

