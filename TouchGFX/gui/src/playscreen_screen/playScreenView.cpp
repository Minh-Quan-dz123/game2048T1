#include <gui/playscreen_screen/playScreenView.hpp>
extern "C"
{
	volatile uint8_t joystick_new;
    volatile uint8_t joystick_old;
}
playScreenView::playScreenView()
{

}

void playScreenView::setupScreen()
{
    playScreenViewBase::setupScreen();
}

void playScreenView::tearDownScreen()
{
    playScreenViewBase::tearDownScreen();
}

void playScreenView::khoitaogame() // 1: khi bấm STARTbutton
{
	// gọi đến bắt đầu game
}

void playScreenView::batDauGame()
{
	//memset cho grid, score = 0
	// addRamdamBox()
	// updateGiaoDien();
}

void playScreenView::xuLyLuoi() // 2: nghe trạng thái của joystick theo định kỳ để cập
{								 // nhật giao diện với 4 thao tác
	// code và gọi các hàm moveUp, moveDown, moveLeft, moveRight
	// addRamdomBox()
	// updateGiaoDien()
	// updateHighestScore()
}

// code thao tác
void playScreenView::moveRight()
{

}
void playScreenView::moveLeft()
{

}
void playScreenView::moveUp()
{

}
void playScreenView::moveDown()
{

}

// xử lý logic thêm box mới
void playScreenView::addRamdomBox()
{

}

// update giao diện
void playScreenView::updateGiaoDien()
{

}

void playScreenView::updateHighestScore()
{
	if (  score > ( model->getHighestScore() )  )  // lấy điểm ra để so sánh
		{
	        model->luuHighestScore(score); // gọi xuống model để lưu điểm
	    }
}
