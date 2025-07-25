#ifndef HOMESCREENPRESENTER_HPP
#define HOMESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class homeScreenView;

class homeScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    homeScreenPresenter(homeScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~homeScreenPresenter() {}

    // thêm hàm lấy điểm cao nhất
    uint32_t getHighestScore() ;

private:
    homeScreenPresenter();

    homeScreenView& view;
};

#endif // HOMESCREENPRESENTER_HPP
