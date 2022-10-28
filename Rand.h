//
// Created by wangy on 2021/12/10.
//

#ifndef FGSP_CODE__RAND_H_
#define FGSP_CODE__RAND_H_

#include <random>

// A function to return a seeded random number generator.
inline std::mt19937& rand_generator() {
	// the generator will only be seeded once (per thread) since it's static
	static thread_local std::mt19937 gen(std::random_device{}());
	return gen;
}

// A function to generate integers in the range [min, max]
template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
T wyt_rand(T min, T max) {
	std::uniform_int_distribution<T> dist(min, max);
	return dist(rand_generator());
}

// A function to generate integers in the range [0, max-1]
template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
T wyt_rand(T max) {
	std::uniform_int_distribution<T> dist(0, max - 1);
	return dist(rand_generator());
}

// A function to generate floats in the range [min, max)
template<typename T, std::enable_if_t<std::is_floating_point_v<T>>* = nullptr>
T wyt_rand(T min, T max) {
	std::uniform_real_distribution<T> dist(min, max);
	return dist(rand_generator());
}

// A function to generate bools
bool wyt_rand(double par = 0.5) {
	std::bernoulli_distribution dist(par);
	return dist(rand_generator());
}

#endif //FGSP_CODE__RAND_H_