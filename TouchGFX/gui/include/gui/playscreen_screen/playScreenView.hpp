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

    virtual void xuLyLuoi(); // gọi hàm theo chu kỳ từ giao TouchGFX Designer
    virtual void khoitaogame();// khởi tạo game
    virtual void tinhDiem();// khi kết thúc game
protected:
    // thêm các hàm và biến
    uint32_t grid[4][4];// dữ liệu các box
    uint32_t score = 0; // điểm hiện tại
    uint8_t newSta = 0; //
    uint8_t oldSta = 0;
    uint8_t batXuLyLuoi=0; // 0 thì là chưa làm gì, 1 là đang chơi, 2 là kết thúc

    void batDauGame(); // 1: bắt đầu game = khởi tạo game mới
    void addRamdomBox(); // 2: hiển thị 1 ô bất kì

    void moveLeft(); // 3: dịch
    void moveRight(); // 3: dịch
    void moveUp();   // 3: dịch
    void moveDown(); // 3: dịch

    void updateGiaoDien(); // 4: update giao diện
    void endGame(); // 5 end game
    void updateHighestScore(); // 6: kết thúc thì lưu điểm cao nhất
    // end

    Model* model;     // giao tiếp với Model

};

#endif // PLAYSCREENVIEW_HPP
