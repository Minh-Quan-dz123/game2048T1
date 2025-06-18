#ifndef HOMESCREENVIEW_HPP
#define HOMESCREENVIEW_HPP

#include <gui_generated/homescreen_screen/homeScreenViewBase.hpp>
#include <gui/homescreen_screen/homeScreenPresenter.hpp>

class homeScreenView : public homeScreenViewBase
{
public:
    homeScreenView();
    virtual ~homeScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void updateHighestScore();
protected:
};

#endif // HOMESCREENVIEW_HPP
