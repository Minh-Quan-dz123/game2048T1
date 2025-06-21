#include <gui/homescreen_screen/homeScreenView.hpp>

homeScreenView::homeScreenView()
{

}

void homeScreenView::setupScreen()
{
    homeScreenViewBase::setupScreen();
}

void homeScreenView::tearDownScreen()
{
    homeScreenViewBase::tearDownScreen();
}



void homeScreenView::getHighestScore()
{
	uint32_t x = presenter->getHighestScore();
	Unicode::snprintf(highestScoreTextBuffer, 16 , "%u", x);
	highestScoreText.invalidate();
}
