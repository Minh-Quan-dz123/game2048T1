#include <gui/homescreen_screen/homeScreenView.hpp>
#include <gui/homescreen_screen/homeScreenPresenter.hpp>

homeScreenPresenter::homeScreenPresenter(homeScreenView& v)
    : view(v)
{

}

void homeScreenPresenter::activate()
{

}

void homeScreenPresenter::deactivate()
{

}

uint32_t homeScreenPresenter::getHighestScore()
{
	return model->getHighestScore();
}
