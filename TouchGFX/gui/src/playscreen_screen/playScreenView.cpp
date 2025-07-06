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

//đăng ký callback
playScreenView::playScreenView():conTroCallBackX_Right(this, &playScreenView::callbackHandlerX_Right),
								 conTroCallBackY_Up(this, &playScreenView::callbackHandlerY_Up),
								 conTroCallBackX_Left(this, &playScreenView::callbackHandlerX_Left),
								 conTroCallBackY_Down(this, &playScreenView::callbackHandlerY_Down)
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
		//	if(dichuyenGa == false)
			//{
				memset(Toa,-1,sizeof(Toa));// gán Toa == -1

			    batXuLyLuoi = 3; // giai đoạn Animation

				switch(newSta) // di chuyển
				{
					case 1: moveRight(); break; // vừa di chuyển vừa update giao diện rồi
					case 2: moveLeft(); break;
					case 3: moveUp(); break;
					case 4: moveDown(); break;

					// các cv addRamdomBox, batXuLyLuoi để ở trong các hàm Animation
				}
			//}
			//else dichuyenGa = false;// nếu bằng true thì thôi

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
					setDiChuyen(x,y,index,y);
				}
				else
				{
					if(gan[index][y] == grid[x][y]) // có gì rồi nhưng vẫn gán được
					{
						gan[index][y] = grid[x][y]*2;  // merge
						setDiChuyen(x,y,index,y);
						index--;// giảm đi để không xét vị trí này nữa
					}
					else // có gì rồi nhưng không gán được thì bỏ
					{
						index--; // vị trí mới chắc chắn là gan[index]=0
						gan[index][y] = grid[x][y];
						setDiChuyen(x,y,index,y);
					}
				}
			}
		}
		// gán kết quả
		for(int i = 0; i<4; i++)	grid[i][y] = gan[i][y];
	}
	if(countToa != 0)
	{
	    boxij[vtX0][vtY0]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// gán vị trị ramdom cũ về màu xanh
	    boxij[vtX0][vtY0]->invalidate();
		for(int y = 0; y < 4; y++) startX_RightMoveHinh(y);
	}
	else // 2 trường hợp, 1 là ko có animation, 2 là còn 1 ô cuối => cx ko có animation
	{
		batXuLyLuoi = 1;
		//dichuyenGa = true;
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
						setDiChuyen(x,y,index,y);
					}
					else
					{
						if(gan[index][y] == grid[x][y])
						{
							gan[index][y] = grid[x][y]*2;
							setDiChuyen(x,y,index,y);
							index++;
						}
						else
						{
							index++;
							gan[index][y] = grid[x][y];
							setDiChuyen(x,y,index,y);
						}
					}
				}
			}
			for(int i = 0; i<4; i++) grid[i][y] = gan[i][y];

		}
		if(countToa != 0)
		{
		    boxij[vtX0][vtY0]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// gán vị trị ramdom cũ về màu xanh
		    boxij[vtX0][vtY0]->invalidate();
			for(int y = 0; y < 4; y++) startX_LeftMoveHinh(y);
		}
		else
		{
			batXuLyLuoi = 1;
			//dichuyenGa = true;
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
						setDiChuyen(x,y,x,index);
					}
					else
					{
						if(gan[x][index] == grid[x][y])
						{
							gan[x][index] = grid[x][y]*2;
							setDiChuyen(x,y,x,index);
							index++;
						}
						else
						{
							index++;
							gan[x][index] = grid[x][y];
							setDiChuyen(x,y,x,index);
						}
					}
				}
			}
			for(int i = 0; i<4 ; i++) grid[x][i] = gan[x][i];

		}
		if(countToa != 0)
		{
		    boxij[vtX0][vtY0]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// gán vị trị ramdom cũ về màu xanh
		    boxij[vtX0][vtY0]->invalidate();
			for(int x = 0; x < 4; x++) startY_UpMoveHinh(x);
		}
		else
		{
			batXuLyLuoi = 1;
			//dichuyenGa = true;
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
							setDiChuyen(x,y,x,index);
						}
						else
						{
							if(gan[x][index] == grid[x][y])
							{
								gan[x][index] = grid[x][y]*2;
								setDiChuyen(x,y,x,index);
								index--;
							}
							else
							{
								index--;
								gan[x][index] = grid[x][y];
								setDiChuyen(x,y,x,index);
							}
						}
					}
				}
				for(int i = 0; i<4 ; i++)	grid[x][i] = gan[x][i];

			}
			if(countToa != 0)
			{
			    boxij[vtX0][vtY0]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// gán vị trị ramdom cũ về màu xanh
			    boxij[vtX0][vtY0]->invalidate();
				for(int x = 0; x < 4; x++) startY_DownMoveHinh(x);
			}
			else
			{
				batXuLyLuoi = 1;
				//dichuyenGa = true;
			}
}

// 4: xử lý logic thêm box mới
void playScreenView::addRamdomBox()
{
	// Mảng lưu các vị trí có giá trị 0
	    int viTri0[16][2];
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
	    static mt19937 gen(xTaskGetTickCount()); // xTaskGetTickCount : thời gian chạy của hệ thống => hàm trả về 1 số ngẫu nhiên
	    uniform_int_distribution<> dis(0, zeroCount - 1); // tạo phân phối [0,zeroCount)

	    int randomIndex = dis(gen);
	    int randX = viTri0[randomIndex][0];
	    int randY = viTri0[randomIndex][1];

	    vtX0 = randX; // giữ giá trị này
	    vtY0 = randY;

	    // Gán giá trị 2 vào vị trí vừa chọn
	    grid[randX][randY] = 2; // tạo màu vàng riêng biệt để nhận ra

	    boxij[randX][randY]->setColor(touchgfx::Color::getColorFromRGB(255, 245, 157));// vàng
	    boxij[randX][randY]->invalidate();

		Unicode::snprintf(textBufferij[randX][randY], 10 , "%u", 2);
		textAreaij[randX][randY]->invalidate();

	    // Nếu còn 1 ô cuối cùng thì xem xét còn đi được khôn
	    if (zeroCount == 1)
	    {
	    	if(kiemtra() == 0) // tức là không thể đi được nữa
	    	{
	    		batXuLyLuoi = 2;
	    		return;
	    	}
	    }
	    batXuLyLuoi = 1;
}

// 4.1 kiểm tra còn đi tiếp đi được
uint8_t playScreenView::kiemtra()
{
	for(int i = 0; i < 4; i++) // x
	{
		for(int j = 0; j < 4; j++) // y
		{
			// tại vị trí i,j kiểm tra xem còn đi được nx ko
			if(i - 1 >= 0)
			{
				if(grid[i - 1][j] == grid[i][j]) return 1; // còn đi được
			}
			if(i + 1 < 4)
			{
				if(grid[i + 1][j] == grid[i][j]) return 1;
			}
			if(j - 1 >= 0)
			{
				if(grid[i][j - 1] == grid[i][j]) return 1;
			}
			if(j + 1 < 4)
			{
				if(grid[i][j + 1] == grid[i][j]) return 1;
			}
		}
	}
	return 0; // ko đi được
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
					if(i == vtX0 && j == vtY0) // vị trí hiện tại mới ramdom
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


// 7: animation
//7.0 thêm vào hàng đợi chuỗi di chuyển
void playScreenView::setDiChuyen(int x1,int y1, int x2,int y2)
{
	if(x1 == x2 && y1 == y2) return;// ko có sự đi chuyển

	yesAnimation = true;
	countToa++; // tăng số Animation
	Toa[x1][y1] = (dichuyen){x1,y1,x2,y2}; // theo logic thì x1,y1 ở đầu là bé nhất
}

// 7.1
// 7.1.1 merge box
void playScreenView::mergeBox(int x2, int y2)
{
	// 1 đổi màu box x2,y2
	boxij[x2][y2]->setColor(touchgfx::Color::getColorFromRGB(0, 255, 198));// màu xanh
	boxij[x2][y2]->invalidate();

	// 2 set giá trị
	Unicode::snprintf(textBufferij[x2][y2], 10 , "%u", grid[x2][y2]);
	textAreaij[x2][y2]->invalidate();
}
// 7.1.2 Animation về chỗ cũ
void playScreenView::setContainerVeChoCu(int i, int j)
{
	containerij[i][j]->setXY(i*60, j*60);// set về chỗ chữ
	boxij[i][j]->setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));// màu trắng
	Unicode::strncpy(textBufferij[i][j], "", TEXTAREA11_SIZE); // in ra rỗng

	textAreaij[i][j]->invalidate();
	boxij[i][j]->invalidate();
	containerij[i][j]->invalidate();

	countToa--; // giảm số Animation hiện tại
}
// 7.1.3 finishAnimation
void playScreenView::finishAnimation()
{
	if(countToa == 0)// ko còn animation
	{
		addRamdomBox();
	}
}

// 7.2 kích hoạt quá trình di chuyển theo chiều ...

//7.2.1 Phải
void playScreenView::startX_RightMoveHinh(int y) // đi theo chiều ngang tại hàng thứ y
{

	for(int x = 3; x > -1 ; x--) // gặp box đầu tiên thì chạy
	{
		if(Toa[x][y].X1 != -1) // có Animation
		{
			int x2 = Toa[x][y].X2;
			int y2 = Toa[x][y].Y2;

			// 1: move to front
			container1.remove(*containerij[x][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][y]);

			// 2 xóa bóng
			containerij[x][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][y]->setMoveAnimationEndedAction(conTroCallBackX_Right);
			containerij[x][y]->startMoveAnimation(x2*60, y2*60, timeAnimation, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
			return;
		}
	}
	finishAnimation();
}
void playScreenView::callbackHandlerX_Right(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i, j cái mà container đang gọi callback
			{
				mergeBox(Toa[i][j].X2, Toa[i][j].Y2); // merge ô
				setContainerVeChoCu(i, j);            // cho box đang animation về chỗ cũ

				Toa[i][j].X1 = -1;// đánh dấu là đi đc animation rồi
				startX_RightMoveHinh(j);
				return;
			}
		}
	}
}

//7.2.1 Trái
void playScreenView::startX_LeftMoveHinh(int y) // đi theo chiều ngang tại hang thứ i (y==i)
{
	for(int x = 0; x < 4 ; x++) // gặp box đầu tiên thì chạy
	{
		if(Toa[x][y].X1 != -1) // có Animation
		{
			int x2 = Toa[x][y].X2;
			int y2 = Toa[x][y].Y2;

			// 1: move to front
			container1.remove(*containerij[x][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][y]);

			// 2 xóa bóng
			containerij[x][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][y]->setMoveAnimationEndedAction(conTroCallBackX_Left);
			containerij[x][y]->startMoveAnimation(x2*60, y2*60, timeAnimation, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
			return;
		}
	}
	finishAnimation();
}
void playScreenView::callbackHandlerX_Left(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	// tìm container đang gọi
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i, j cái mà container đang gọi callback
			{
				mergeBox(Toa[i][j].X2, Toa[i][j].Y2); // merge ô
				setContainerVeChoCu(i, j);            // cho box đang animation về chỗ cũ

				Toa[i][j].X1 = -1;// đánh dấu là đi đc animation rồi
				startX_LeftMoveHinh(j);
				return;
			}
		}
	}
}


//7.2.1 Lên
void playScreenView::startY_UpMoveHinh(int x) // đi theo chiều dọc tại cột thứ i
{
	for(int y = 0; y < 4 ; y++) // gặp box đầu tiên thì chạy
	{
		if(Toa[x][y].X1 != -1) // có Animation
		{
			int x2 = Toa[x][y].X2;
			int y2 = Toa[x][y].Y2;

			// 1: move to front
			container1.remove(*containerij[x][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][y]);

			// 2 xóa bóng
			containerij[x][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][y]->setMoveAnimationEndedAction(conTroCallBackY_Up);
			containerij[x][y]->startMoveAnimation(x2*60, y2*60, timeAnimation, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
			return;
		}
	}
	finishAnimation();
}
void playScreenView::callbackHandlerY_Up(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i, j cái mà container đang gọi callback
			{
				mergeBox(Toa[i][j].X2, Toa[i][j].Y2); // merge ô
				setContainerVeChoCu(i, j);            // cho box đang animation về chỗ cũ

				Toa[i][j].X1 = -1;// đánh dấu là đi đc animation rồi
				startY_UpMoveHinh(i);
				return;
			}
		}
	}
}


//7.2.1 Xuống
void playScreenView::startY_DownMoveHinh(int x) // đi theo chiều dọc tại cột thứ i
{
	for(int y = 3; y > -1 ; y--) // gặp box đầu tiên thì chạy
	{
		if(Toa[x][y].X1 != -1) // có Animation
		{
			int x2 = Toa[x][y].X2;
			int y2 = Toa[x][y].Y2;

			// 1: move to front
			container1.remove(*containerij[x][y]); // kỹ thuật để làm cho containerij có order cao
			container1.add(*containerij[x][y]);

			// 2 xóa bóng
			containerij[x][y]->clearMoveAnimationEndedAction(); // xóa vị trí ban đầu

			// 3 bật nghe animation và khởi tạo animation
			containerij[x][y]->setMoveAnimationEndedAction(conTroCallBackY_Down);
			containerij[x][y]->startMoveAnimation(x2*60, y2*60, timeAnimation, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);
			return;
		}
	}
	finishAnimation();
}
void playScreenView::callbackHandlerY_Down(const touchgfx::MoveAnimator<touchgfx::Container>& cont)
{
	for(int i = 0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(containerij[i][j] == &cont)// tìm ra tọa độ i, j cái mà container đang gọi callback
			{
				mergeBox(Toa[i][j].X2, Toa[i][j].Y2); // merge ô
				setContainerVeChoCu(i, j);            // cho box đang animation về chỗ cũ

				Toa[i][j].X1 = -1;// đánh dấu là đi đc animation rồi
				startY_DownMoveHinh(i);
				return;
			}
		}
	}
}





