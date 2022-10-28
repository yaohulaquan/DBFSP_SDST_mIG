#pragma once
#include <vector>
class FBTime
{

public:
	FBTime(int jobs, int machines);
	std::vector<std::vector<int>> forwardStartTime;
	std::vector<std::vector<int>> forwardFinishTime;
	std::vector<std::vector<int>> forwardDepartureTime;

	std::vector<std::vector<int>> backwardStartTime;
	std::vector<std::vector<int>> backwardFinishTime;
	std::vector<std::vector<int>> backwardDepartureTime;
};

