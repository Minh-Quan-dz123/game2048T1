#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstdint>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::luuHighestScore(uint32_t score)
{
	highestScore = score;
}
uint32_t Model::getHighestScore()
{
	return highestScore;
}


