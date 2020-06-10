#pragma once
#include <vector>
#include <wx/wx.h>
namespace Utils
{
	constexpr int field_width = 8;
	constexpr int field_height = 8;
	constexpr auto to_1d(int x, int y) { return x * Utils::field_width + y; }
	constexpr auto to_1d(const std::pair<int, int>& pair) { return pair.first * Utils::field_width + pair.second; }
}
namespace
{
	const auto point_distance(const std::pair<int, int>& x, const std::pair<int, int>& y)
	{
		return std::sqrt(std::pow(y.first - x.first, 2) + std::pow(y.second - x.second, 2));
	}
	constexpr auto to_1d(int x, int y) { return x * Utils::field_width + y; }
	constexpr auto to_1d(const std::pair<int, int>& pair) { return pair.first * Utils::field_width + pair.second; }
}
