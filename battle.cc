#pragma once
#include<iostream>
#include<cassert>
#include<array>
#include"rebelfleet.h"
#include"imperialfleet.h"
using namespace std;


template<typename T, T end, T cur = 0, T...results>
constexpr static auto squares() {
	if constexpr (cur * cur <= end)
		return squares<T, end, cur + 1, results..., cur * cur>();
	else
		return array<T, sizeof...(results)> ({results...});
}

template<typename T, T t0, T t1, typename...S>
class SpaceBattle {
	static_assert(t0 >=0 && t1 >= t0);
	static constexpr auto BattleTimes = squares<T, t1>();
};