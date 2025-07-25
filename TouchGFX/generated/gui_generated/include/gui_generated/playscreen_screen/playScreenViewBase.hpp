/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef PLAYSCREENVIEWBASE_HPP
#define PLAYSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/playscreen_screen/playScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ButtonWithLabel.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class playScreenViewBase : public touchgfx::View<playScreenPresenter>
{
public:
    playScreenViewBase();
    virtual ~playScreenViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Virtual Action Handlers
     */
    virtual void tinhDiem()
    {
        // Override and implement this function in playScreen
    }
    virtual void xuLyLuoi()
    {
        // Override and implement this function in playScreen
    }
    virtual void khoitaogame()
    {
        // Override and implement this function in playScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::ButtonWithLabel wantEndButton;
    touchgfx::Container container1;
    touchgfx::Image image4;
    touchgfx::MoveAnimator< touchgfx::Container > container11;
    touchgfx::Box box11;
    touchgfx::TextAreaWithOneWildcard textArea11;
    touchgfx::MoveAnimator< touchgfx::Container > container12;
    touchgfx::Box box12;
    touchgfx::TextAreaWithOneWildcard textArea12;
    touchgfx::MoveAnimator< touchgfx::Container > container13;
    touchgfx::Box box13;
    touchgfx::TextAreaWithOneWildcard textArea13;
    touchgfx::MoveAnimator< touchgfx::Container > container14;
    touchgfx::Box box14;
    touchgfx::TextAreaWithOneWildcard textArea14;
    touchgfx::MoveAnimator< touchgfx::Container > container21;
    touchgfx::Box box21;
    touchgfx::TextAreaWithOneWildcard textArea21;
    touchgfx::MoveAnimator< touchgfx::Container > container22;
    touchgfx::Box box22;
    touchgfx::TextAreaWithOneWildcard textArea22;
    touchgfx::MoveAnimator< touchgfx::Container > container23;
    touchgfx::Box box23;
    touchgfx::TextAreaWithOneWildcard textArea23;
    touchgfx::MoveAnimator< touchgfx::Container > container24;
    touchgfx::Box box24;
    touchgfx::TextAreaWithOneWildcard textArea24;
    touchgfx::MoveAnimator< touchgfx::Container > container31;
    touchgfx::Box box31;
    touchgfx::TextAreaWithOneWildcard textArea31;
    touchgfx::MoveAnimator< touchgfx::Container > container32;
    touchgfx::Box box32;
    touchgfx::TextAreaWithOneWildcard textArea32;
    touchgfx::MoveAnimator< touchgfx::Container > container33;
    touchgfx::Box box33;
    touchgfx::TextAreaWithOneWildcard textArea33;
    touchgfx::MoveAnimator< touchgfx::Container > container34;
    touchgfx::Box box34;
    touchgfx::TextAreaWithOneWildcard textArea34;
    touchgfx::MoveAnimator< touchgfx::Container > container41;
    touchgfx::Box box41;
    touchgfx::TextAreaWithOneWildcard textArea41;
    touchgfx::MoveAnimator< touchgfx::Container > container42;
    touchgfx::Box box42;
    touchgfx::TextAreaWithOneWildcard textArea42;
    touchgfx::MoveAnimator< touchgfx::Container > container43;
    touchgfx::Box box43;
    touchgfx::TextAreaWithOneWildcard textArea43;
    touchgfx::MoveAnimator< touchgfx::Container > container44;
    touchgfx::Box box44;
    touchgfx::TextAreaWithOneWildcard textArea44;
    touchgfx::Container wantEndContainer;
    touchgfx::Image image2;
    touchgfx::TextArea textArea45;
    touchgfx::ButtonWithLabel yesButton;
    touchgfx::ButtonWithLabel noButton;
    touchgfx::Container endContainer;
    touchgfx::Image image3;
    touchgfx::TextAreaWithOneWildcard YourScoreText_IS;
    touchgfx::TextArea YourScoreISText;
    touchgfx::ButtonWithLabel ENDbutton;
    touchgfx::ButtonWithLabel CONTINUEbutton;
    touchgfx::ButtonWithLabel STARTbutton;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA11_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea11Buffer[TEXTAREA11_SIZE];
    static const uint16_t TEXTAREA12_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea12Buffer[TEXTAREA12_SIZE];
    static const uint16_t TEXTAREA13_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea13Buffer[TEXTAREA13_SIZE];
    static const uint16_t TEXTAREA14_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea14Buffer[TEXTAREA14_SIZE];
    static const uint16_t TEXTAREA21_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea21Buffer[TEXTAREA21_SIZE];
    static const uint16_t TEXTAREA22_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea22Buffer[TEXTAREA22_SIZE];
    static const uint16_t TEXTAREA23_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea23Buffer[TEXTAREA23_SIZE];
    static const uint16_t TEXTAREA24_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea24Buffer[TEXTAREA24_SIZE];
    static const uint16_t TEXTAREA31_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea31Buffer[TEXTAREA31_SIZE];
    static const uint16_t TEXTAREA32_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea32Buffer[TEXTAREA32_SIZE];
    static const uint16_t TEXTAREA33_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea33Buffer[TEXTAREA33_SIZE];
    static const uint16_t TEXTAREA34_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea34Buffer[TEXTAREA34_SIZE];
    static const uint16_t TEXTAREA41_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea41Buffer[TEXTAREA41_SIZE];
    static const uint16_t TEXTAREA42_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea42Buffer[TEXTAREA42_SIZE];
    static const uint16_t TEXTAREA43_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea43Buffer[TEXTAREA43_SIZE];
    static const uint16_t TEXTAREA44_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea44Buffer[TEXTAREA44_SIZE];
    static const uint16_t YOURSCORETEXT_IS_SIZE = 10;
    touchgfx::Unicode::UnicodeChar YourScoreText_ISBuffer[YOURSCORETEXT_IS_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<playScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

    /*
     * Tick Counter Declarations
     */
    static const uint32_t TICK_XULYLUOI_INTERVAL = 2;
    uint32_t frameCountXuLyLuoiInterval;

};

#endif // PLAYSCREENVIEWBASE_HPP
