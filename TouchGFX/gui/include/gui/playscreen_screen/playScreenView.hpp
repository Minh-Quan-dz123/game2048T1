#ifndef PLAYSCREENVIEW_HPP
#define PLAYSCREENVIEW_HPP

#include <gui_generated/playscreen_screen/playScreenViewBase.hpp>
#include <gui/playscreen_screen/playScreenPresenter.hpp>

class playScreenView : public playScreenViewBase
{
public:
    playScreenView();
    virtual ~playScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    uint32_t diem=2;// thêm biến điểm cao nhất
};

#endif // PLAYSCREENVIEW_HPP
