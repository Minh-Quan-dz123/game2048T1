#include <gui/playscreen_screen/playScreenView.hpp>
#include <gui/playscreen_screen/playScreenPresenter.hpp>

playScreenPresenter::playScreenPresenter(playScreenView& v)
    : view(v)
{

}

void playScreenPresenter::activate()
{

}

void playScreenPresenter::deactivate()
{

}

void playScreenPresenter::saveHighestScore(uint32_t score)// lưu điểm
{
	if(score > (model->getHighestScore()))
	{
		model->luuHighestScore(score);
	}
}


