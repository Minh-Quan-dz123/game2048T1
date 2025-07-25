#ifndef PLAYSCREENPRESENTER_HPP
#define PLAYSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class playScreenView;

class playScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    playScreenPresenter(playScreenView& v);

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

    virtual ~playScreenPresenter() {}

    void saveHighestScore(uint32_t score);// lưu điểm


private:
    playScreenPresenter();

    playScreenView& view;
};

#endif // PLAYSCREENPRESENTER_HPP
