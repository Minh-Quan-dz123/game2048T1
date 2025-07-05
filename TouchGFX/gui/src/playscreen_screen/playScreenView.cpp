#include <gui/playscreen_screen/playScreenView.hpp>
#include <cstring>
#include <cstdlib>
#include "stm32f4xx_hal.h"
#include <random>
#include "FreeRTOS.h"
#include "task.h"
#include <touchgfx/Color.hpp>
#include <algorithm>


using namespace std;

extern "C"
{
	extern volatile uint8_t newStatus;
}

// thêm khởi tạo các đối tượng callback cho View này
playScreenView::playScreenView()//:conTroCallBackX_Right(this, &playScreenView::callbackHandlerX_Right),
								 //conTroCallBackY_Up(this, &playScreenView::callbackHandlerY_Up),
								 //conTroCallBackX_Left(this, &playScreenView::callbackHandlerX_Left),
								 //conTroCallBackY_Down(this, &playScreenView::callbackHandlerY_Down)
{

}

void playScreenView::setupScreen()
{
    playScreenViewBase::setupScreen();
    boxij[0][0] = &box11;
    boxij[0][1] = &box12;
    boxij[0][2] = &box13;
    boxij[0][3] = &box14;

    boxij[1][0] = &box21;
    boxij[1][1] = &box22;
    boxij[1][2] = &box23;
    boxij[1][3] = &box24;

    boxij[2][0] = &box31;
    boxij[2][1] = &box32;
    boxij[2][2] = &box33;
    boxij[2][3] = &box34;

    boxij[3][0] = &box41;
    boxij[3][1] = &box42;
    boxij[3][2] = &box43;
    boxij[3][3] = &box44;

    textAreaij[0][0] = &textArea11;
    textAreaij[0][1] = &textArea12;
    textAreaij[0][2] = &textArea13;
    textAreaij[0][3] = &textArea14;

    textAreaij[1][0] = &textArea21;
    textAreaij[1][1] = &textArea22;
    textAreaij[1][2] = &textArea23;
    textAreaij[1][3] = &textArea24;

    textAreaij[2][0] = &textArea31;
    textAreaij[2][1] = &textArea32;
    textAreaij[2][2] = &textArea33;
    textAreaij[2][3] = &textArea34;

    textAreaij[3][0] = &textArea41;
    textAreaij[3][1] = &textArea42;
    textAreaij[3][2] = &textArea43;
    textAreaij[3][3] = &textArea44;


    textBufferij[0][0] = textArea11Buffer;
    textBufferij[0][1] = textArea12Buffer;
    textBufferij[0][2] = textArea13Buffer;
    textBufferij[0][3] = textArea14Buffer;

    textBufferij[1][0] = textArea21Buffer;
    textBufferij[1][1] = textArea22Buffer;
    textBufferij[1][2] = textArea23Buffer;
    textBufferij[1][3] = textArea24Buffer;

    textBufferij[2][0] = textArea31Buffer;
    textBufferij[2][1] = textArea32Buffer;
    textBufferij[2][2] = textArea33Buffer;
    textBufferij[2][3] = textArea34Buffer;

    textBufferij[3][0] = textArea41Buffer;
    textBufferij[3][1] = textArea42Buffer;
    textBufferij[3][2] = textArea43Buffer;
    textBufferij[3][3] = textArea44Buffer;

    containerij[0][0] = &container11;
    containerij[0][1] = &container12;
    containerij[0][2] = &container13;
    containerij[0][3] = &container14;

    containerij[1][0] = &container21;
    containerij[1][1] = &container22;
    containerij[1][2] = &container23;
    containerij[1][3] = &container24;

    containerij[2][0] = &container31;
    containerij[2][1] = &container32;
    containerij[2][2] = &container33;
    containerij[2][3] = &container34;

    containerij[3][0] = &container41;
    containerij[3][1] = &container42;
    containerij[3][2] = &container43;
    containerij[3][3] = &container44;


}

void playScreenView::tearDownScreen()
{
    playScreenViewBase::tearDownScreen();
}

// code
void playScreenView::tinhDiem() // 0 khi người chơi bấm yesButton trong want end game
{
	batXuLyLuoi=2;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++) score=max(score,grid[i][j]);
	}
	updateHighestScore(); // b: lưu điểm cao nhất
}

void playScreenView::khoitaogame() // 1: khi bấm STARTbutton
{
	batDauGame();
}

void playScreenView::batDauGame()
{
	batXuLyLuoi=2;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++) grid[i][j]=0;
	}
	score = 0;
	addRamdomBox();// b: lấy ngẫu nhiên 1 box để hiển thị như logic game
	updateGiaoDien(); // c: sau đó update giao diện thôi
	batXuLyLuoi=1; // kích hoạt sự kiện nghe Joystick
}

void playScreenView::xuLyLuoi() // 2: nghe trạng thái của joystick theo định kỳ để cập
{								 // nhật giao diện với 4 thao tác và xử lý endGame
	// code và gọi các hàm moveUp, moveDown, moveLeft, moveRight
	// addRamdomBox()
	// updateGiaoDien()
	// updateHighestScore()
	if(batXuLyLuoi == 1) // nếu đã được kích hoạt thì bắt đầu xử lý
	{
		newSta = newStatus; // chỉ lấy newStatus thôi

		if(newSta != oldSta && newSta != 0) // nếu ng dùng thao tác joystick
		{
		    boxij[vtX0][vtY0]->setColor(touchgfx::Color::getColorFromRGB(0,0,0));// gán vị trị ramdom cũ về màu xanh
		    boxij[vtX0][vtY0]->invalidate();

			switch(newSta) // di chuyển
			{
				case 1: moveRight(); break; // vừa di chuyển vừa update giao diện rồi
				case 2: moveLeft(); break;
				case 3: moveUp(); break;
				case 4: moveDown(); break;
			}
			// xong rồi thì tiếp tục
			addRamdomBox();
			updateGiaoDien();
		}
		oldSta = newSta;// gán lại
	}

	else if(batXuLyLuoi == 2)// nếu kết thúc thì batXuLyLuoi == 0
	{
		batXuLyLuoi=0;
		endGame();
	}
}

// 3: code thao tác
void playScreenView::moveRight()
{
	for(int y = 0; y < 4; y++)
	{
		for(int i=0;i<4;i++) gan[i][y]=0;

		int index = 3;//trỏ vào vị trí đấy của gán

		for(int x = 3; x >-1; x--)
		{
			if(grid[x][y] != 0) // có dịch chuyển
			{
				if(gan[index][y] == 0)// chưa có gì => gán được
				{
					gan[index][y] = grid[x][y];
				}
				else
				{
					if(gan[index][y] == grid[x][y]) // có gì rồi nhưng vẫn gán được
					{
						gan[index][y] = grid[x][y]*2;
						index--;// giảm đi để không xét vị trí này nữa
					}
					else // có gì rồi nhưng không gán được thì bỏ
					{
						index--; // vị trí mới chắc chắn là gan[index]=0
						gan[index][y] = grid[x][y];
					}
				}
			}
		}
		// gán kết quả
		for(int i = 0; i<4; i++)	grid[i][y] = gan[i][y];
	}


}
void playScreenView::moveLeft()
{
		for(int y = 0; y < 4; y++)
		{
			for(int i=0;i<4;i++) gan[i][y]=0;

			int index = 0;

			for(int x = 0; x <4; x++)
			{
				if(grid[x][y] != 0)
				{
					if(gan[index][y] == 0)
					{
						gan[index][y] = grid[x][y];
					}
					else
					{
						if(gan[index][y] == grid[x][y])
						{
							gan[index][y] = grid[x][y]*2;
							index++;
						}
						else
						{
							index++;
							gan[index][y] = grid[x][y];
						}
					}
				}
			}
			for(int i = 0; i<4; i++) grid[i][y] = gan[i][y];
		}
}
void playScreenView::moveUp()
{
		for(int x = 0; x < 4; x++)
		{
			for(int i=0;i<4;i++) gan[x][i]=0;

			int index = 0;

			for(int y = 0; y <4 ; y++)
			{
				if(grid[x][y] != 0)
				{
					if(gan[x][index] == 0)
					{
						gan[x][index] = grid[x][y];
					}
					else
					{
						if(gan[x][index] == grid[x][y])
						{
							gan[x][index] = grid[x][y]*2;
							index++;
						}
						else
						{
							index++;
							gan[x][index] = grid[x][y];
						}
					}
				}
			}
			for(int i = 0; i<4 ; i++) grid[x][i] = gan[x][i];
		}

}
void playScreenView::moveDown()
{
			for(int x = 0; x < 4; x++)
			{
				for(int i=0;i<4;i++) gan[x][i]=0;

				int index = 3;

				for(int y = 3; y >-1 ; y--)
				{
					if(grid[x][y] != 0)
					{
						if(gan[x][index] == 0)
						{
							gan[x][index] = grid[x][y];
						}
						else
						{
							if(gan[x][index] == grid[x][y])
							{
								gan[x][index] = grid[x][y]*2;
								index--;
							}
							else
							{
								index--;
								gan[x][index] = grid[x][y];
							}
						}
					}
				}
				for(int i = 0; i<4 ; i++)	grid[x][i] = gan[x][i];
			}
}

// 4: xử lý logic thêm box mới
void playScreenView::addRamdomBox()
{
	// Mảng lưu các vị trí có giá trị 0
	    int viTri0[16][2];
	    //for(int i=0;i<16;i++) {viTri0[i][0] = 0; viTri0[i][1] = 0;}
	    int zeroCount = 0;

	    // Tìm các ô có giá trị bằng 0
	    for (int x = 0; x < 4; x++)
	    {
	        for (int y = 0; y < 4; y++)
	        {
	            if (grid[x][y] == 0)
	            {
	                viTri0[zeroCount][0] = x;
	                viTri0[zeroCount][1] = y;
	                zeroCount++;
	            }
	        }
	    }

	    // nếu tạch
	    if(zeroCount == 0)
	    {
	    	 batXuLyLuoi = 2; // tín hiệu dừng
	    	 return;
	    }

	    // Lấy 1 vị trí ngẫu nhiên từ danh sách ô trống(sinh số ngẫu nhiên)
	    static mt19937 gen(xTaskGetTickCount()); // xTaskGetTickCount : thời gian chạy của hệ thống
	    uniform_int_distribution<> dis(0, zeroCount - 1);

	    int randomIndex = dis(gen);
	    int randX = viTri0[randomIndex][0];
	    int randY = viTri0[randomIndex][1];

	    vtX0 = randX; // giữ giá trị này
	    vtY0 = randY;

	    // Gán giá trị 2 vào vị trí vừa chọn
	    grid[randX][randY] = 2; // tạo màu vàng riêng biệt để nhận ra

	    boxij[randX][randY]->setColor(touchgfx::Color::getColorFromRGB(255, 245, 157));// vàng
	    boxij[randX][randY]->invalidate();

	    // Nếu còn 1 ô cuối cùng thì xem xét còn đi được khôn
	    if (zeroCount == 1)
	    {
	    	uint8_t set=0;
	    	while(set == 0)
	    	{
	    		if(randX+1<4)// phải
	    		{
	    			if(grid[randX+1][randY] == 2) {set ++; break;}
	    		}

	    		if(randX-1>-1)// trái
	    		{
	    			if(grid[randX-1][randY] == 2) {set ++; break;}
	    		}

	    		if(randY+1<4)// duoi
	    		{
	    			if(grid[randX][randY+1] == 2) {set ++; break;}
	    		}

	    		if(randY-1>-1)// trái
	    		{
	    			if(grid[randX][randY-1] == 2) {set ++; break;}
	    		}

	    	}
	    	if(set == 0) // tức là không thể đi được nữa
	    	{
	    		batXuLyLuoi = 2;
	    	}
	    }
}

// 5: update giao diện
void playScreenView::updateGiaoDien()
{

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(grid[i][j] == 0)
				{
					Unicode::strncpy(textBufferij[i][j], "", TEXTAREA11_SIZE); // in ra rỗng
					textAreaij[i][j]->invalidate();
				    boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// trắng
				    boxij[i][j]->invalidate();

				}
				else
				{
					if(i == vtX0 && j == vtY0) // vị trí hiện tại mói ramdom
					{
						Unicode::snprintf(textBufferij[i][j], 10 , "%u", grid[i][j]);
						textAreaij[i][j]->invalidate();
					    boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 245, 157));// vàng
					    boxij[i][j]->invalidate();
					}
					else
					{
						Unicode::snprintf(textBufferij[i][j], 10 , "%u", grid[i][j]);
						textAreaij[i][j]->invalidate();
					    boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// xanh
					    boxij[i][j]->invalidate();
					}
				}
			}
		}
}

// 6: endGame
void playScreenView::endGame() // endGame khi thua
{
	batXuLyLuoi=0;
	endContainer.setVisible(true);// a: hiện container kết thúc
	for(int i=0;i<4;i++)// tính điểm max
	{
		for(int j=0;j<4;j++) score=max(score,grid[i][j]);
	}
	updateHighestScore(); // b: lưu điểm cao nhất
	Unicode::snprintf(YourScoreText_ISBuffer, 10 , "%u", score); // c: hiển thị điểm của người chơi

	YourScoreText_IS.invalidate();
	endContainer.invalidate();
}

void playScreenView::updateHighestScore() // gọi tới presenter
{
		presenter->saveHighestScore(score);
}



/*
// 7: animation
//7.1 thêm vào hàng đợi chuỗi di chuyển
void playScreenView::addMoveHinh(int x1,int y1, int x2,int y2)
{
	Toa[x1][y1] = (dichuyen){x1,y1,x2,y2}; // theo logic thì x1,y1 ở đầu là bé nhất
}


// 7.2 kích hoạt quá trình di chuyển theo chiều ...

//7.2.1 Phải
void playScreenView::startX_RightMoveHinh(int i) // đi theo chiều ngang tại hang thứ i (y==i)
{
	for(int x = 3; x > -1; x--)
	{
		if(Toa[x][i].X1 != -1) // đang gọi : i = x1; y = y1;
		{
			// 1: move to front
			int x2 = Toa[x][i].X2;
			int y2 = Toa[x][i].Y2;
			Toa[x][i].X1 = -1; // đánh dấu là đã đi rồi
			container1.remove(*containerij[x][i]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][i]);

			// 2 xóa bóng
			containerij[x][i]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][i]->setMoveAnimationEndedAction(conTroCallBackX_Right);
			containerij[x][i]->startMoveAnimation(x2*60, y2*60, 10, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);

			return;
		}
	}
	if(i == 3) // duyệt hết
	{
		addRamdomBox();
		batXuLyLuoi = 1; // bật lại sau khi Animation thực hiện xong
	}

}
void playScreenView::callbackHandlerX_Right(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i,j <=> container đang gọi callback
			{
				int x2 = Toa[i][j].X2;
				int y2 = Toa[i][j].Y2;

				// bắt đầu
				// 1 đổi màu box x2,y2
				boxij[x2][y2]->setColor(touchgfx::Color::getColorFromRGB(180, 255, 255));// màu xanh
				boxij[x2][y2]->invalidate();

				// 2 cho containerij cũ về chỗ và xong
				containerij[i][j]->setXY(i*60, j*60);

				boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// màu trắng
				boxij[i][j]->invalidate();

				uint32_t r=0;
				Unicode::snprintf(textBufferij[i][j], 10 , "%u", r);
				textAreaij[i][j]->invalidate();

				containerij[i][j]->invalidate();

				startX_RightMoveHinh(j);
				return;
			}
		}
	}
}

//7.2.1 Trái
void playScreenView::startX_LeftMoveHinh(int i) // đi theo chiều ngang tại hang thứ i (y==i)
{
	for(int x = 0; x < 4; x++)
	{
		if(Toa[x][i].X1 != -1) // đang gọi : i = x1; y = y1;
		{
			// 1: move to front
			int x2 = Toa[x][i].X2;
			int y2 = Toa[x][i].Y2;
			Toa[x][i].X1 = -1; // đánh dấu là đã đi rồi
			container1.remove(*containerij[x][i]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][i]);

			// 2 xóa bóng
			containerij[x][i]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][i]->setMoveAnimationEndedAction(conTroCallBackX_Left);
			containerij[x][i]->startMoveAnimation(x2*60, y2*60, 10, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);

			return;
		}
	}
	if(i == 3) // duyệt hết
	{
		addRamdomBox();
		batXuLyLuoi = 1; // bật lại sau khi Animation thực hiện xong
	}
}
void playScreenView::callbackHandlerX_Left(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i,j <=> container đang gọi callback
			{
				int x2 = Toa[i][j].X2;
				int y2 = Toa[i][j].Y2;

				// bắt đầu
				// 1 đổi màu box x2,y2
				boxij[x2][y2]->setColor(touchgfx::Color::getColorFromRGB(180, 255, 255));// màu xanh
				boxij[x2][y2]->invalidate();

				// 2 cho containerij cũ về chỗ và xong
				containerij[i][j]->setXY(i*60, j*60);

				boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// màu trắng
				boxij[i][j]->invalidate();

				uint32_t r=0;
				Unicode::snprintf(textBufferij[i][j], 10 , "%u", r);
				textAreaij[i][j]->invalidate();

				containerij[i][j]->invalidate();

				startX_LeftMoveHinh(j);
				return;
			}
		}
	}
}


//7.2.1 Lên
void playScreenView::startY_UpMoveHinh(int i) // đi theo chiều dọc tại cột thứ i
{
	for(int y = 0; y < 4; y++)
	{
		if(Toa[i][y].X1 != -1) // đang gọi : i = x1; y = y1;
		{
			int x2 = Toa[i][y].X2;
			int y2 = Toa[i][y].Y2;
			Toa[i][y].X1 = -1; // đánh dấu là đã đi rồi
			// tiền di chuyển
			// 1: move to front
			container1.remove(*containerij[i][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[i][y]);

			// 2 xóa bóng
			containerij[i][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[i][y]->setMoveAnimationEndedAction(conTroCallBackY_Up);
			containerij[i][y]->startMoveAnimation(x2*60, y2*60, 10, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);

			return;
		}
	}
	if(i == 3) // duyệt hết
	{
		addRamdomBox();
		batXuLyLuoi = 1; // bật lại sau khi Animation thực hiện xong
	}
}
void playScreenView::callbackHandlerY_Up(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i,j <=> container đang gọi callback
			{
				int x2 = Toa[i][j].X2;
				int y2 = Toa[i][j].Y2;

				// bắt đầu
				// 1 đổi màu box x2,y2
				boxij[x2][y2]->setColor(touchgfx::Color::getColorFromRGB(180, 255, 255));// màu xanh
				boxij[x2][y2]->invalidate();

				// 2 cho containerij cũ về chỗ và xong
				containerij[i][j]->setXY(i*60, j*60);

				boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// màu trắng
				boxij[i][j]->invalidate();

				uint32_t r=0;
				Unicode::snprintf(textBufferij[i][j], 10 , "%u", r);
				textAreaij[i][j]->invalidate();

				containerij[i][j]->invalidate();

				startY_UpMoveHinh(i);
				return;
			}
		}
	}
}


//7.2.1 Xuống
void playScreenView::startY_DownMoveHinh(int i) // đi theo chiều dọc tại cột thứ i
{
	for(int y = 3; y > -1; y--)
	{
		if(Toa[i][y].X1 != -1) // đang gọi : i = x1; y = y1;
		{
			int x2 = Toa[i][y].X2;
			int y2 = Toa[i][y].Y2;
			Toa[i][y].X1 = -1; // đánh dấu là đã đi rồi
			// tiền di chuyển
			// 1: move to front
			container1.remove(*containerij[i][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[i][y]);

			// 2 xóa bóng
			containerij[i][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[i][y]->setMoveAnimationEndedAction(conTroCallBackY_Up);
			containerij[i][y]->startMoveAnimation(x2*60, y2*60, 10, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);

			return;
		}
	}
	if(i == 3)  // duyệt hết
	{
		addRamdomBox();
		batXuLyLuoi = 1; // bật lại sau khi Animation thực hiện xong
	}
}
void playScreenView::callbackHandlerY_Down(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i,j <=> container đang gọi callback
			{
				int x2 = Toa[i][j].X2;
				int y2 = Toa[i][j].Y2;

				// bắt đầu
				// 1 đổi màu box x2,y2
				boxij[x2][y2]->setColor(touchgfx::Color::getColorFromRGB(180, 255, 255));// màu xanh
				boxij[x2][y2]->invalidate();

				// 2 cho containerij cũ về chỗ và xong
				containerij[i][j]->setXY(i*60, j*60);

				boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// màu trắng
				boxij[i][j]->invalidate();

				uint32_t r=0;
				Unicode::snprintf(textBufferij[i][j], 10 , "%u", r);
				textAreaij[i][j]->invalidate();

				containerij[i][j]->invalidate();

				startY_DownMoveHinh(i);
				return;
			}
		}
	}
}
*/





