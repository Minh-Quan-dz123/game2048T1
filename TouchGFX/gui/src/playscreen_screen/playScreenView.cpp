#include <gui/playscreen_screen/playScreenView.hpp>
#include <cstring>
#include <cstdlib>
#include "stm32f4xx_hal.h"
#include <random>
#include "FreeRTOS.h"
#include "task.h"


using namespace std;

extern "C"
{
	extern volatile uint8_t newStatus;
    //extern volatile uint8_t oldStatus;
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

// code
void playScreenView::tinhDiem() // 0 khi người chơi bấm yes end game
{
	batXuLyLuoi=2;
	updateHighestScore(); // b: lưu điểm cao nhất
}

void playScreenView::khoitaogame() // 1: khi bấm STARTbutton
{
	batDauGame();
}

void playScreenView::batDauGame()
{
	//memset cho grid, score = 0
	// addRamdamBox()
	// updateGiaoDien();

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++) grid[i][j]=0;
	}
	score = 0;
	batXuLyLuoi=1; // kích hoạt sự kiện nghe Joystick
	addRamdomBox();// b: lấy ngẫu nhiên 1 box để hiển thị như logic game
	updateGiaoDien(); // c: sau đó update giao diện thôi
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
			switch(newSta) // di chuyển
			{
				case 1: moveRight(); break;
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
	else if(batXuLyLuoi == 2)// nếu kết thúc
	{
		endGame();
	}

}

// code thao tác
void playScreenView::moveRight()
{
	// ví dụ về move
	 /*
	textArea13.clearMoveAnimationEndedAction();
	textArea13.setMoveAnimationDelay(1);
	textArea13.startMoveAnimation(0, 120, 1, touchgfx::EasingEquations::linearEaseIn, touchgfx::EasingEquations::linearEaseIn);*/
		// từ 8 0 4 4 => 0 0 8 8 ,   0 0 0 8 => 0 0 0 8 , 8 0 8 4 => 0 0 16 4,     2 2 4 4 => 0 0 4 8
		// duy trì 2 con trỏ L1, L0 vào 2 cặp kế tiếp xem có ghép được với nhau không
	for(int y = 0; y < 4; y++)
	{
		uint32_t gan[4] ;
		for(int i=0;i<4;i++) gan[i]=0;

		int index = 3;

		for(int x = 3; x >-1; x--)
		{
			if(grid[x][y] != 0)
			{
				if(gan[index] == 0)
				{
					gan[index] = grid[x][y];
				}
				else
				{
					if(gan[index] == grid[x][y])
					{
						gan[index] = grid[x][y]*2;
						index--;
					}
					else
					{
						index--;
						gan[index] = grid[x][y];
					}
				}
			}
		}
		for(int i = 0; i<4; i++) grid[i][y] = gan[i];
	}


}
void playScreenView::moveLeft()
{
		for(int y = 0; y < 4; y++)
		{
			uint32_t gan[4] ;
			for(int i=0;i<4;i++) gan[i]=0;

			int index = 0;

			for(int x = 0; x <4; x++)
			{
				if(grid[x][y] != 0)
				{
					if(gan[index] == 0)
					{
						gan[index] = grid[x][y];
					}
					else
					{
						if(gan[index] == grid[x][y])
						{
							gan[index] = grid[x][y]*2;
							index++;
						}
						else
						{
							index++;
							gan[index] = grid[x][y];
						}
					}
				}
			}
			for(int i = 0; i<4; i++) grid[i][y] = gan[i];
		}
}
void playScreenView::moveUp()
{
		for(int x = 0; x < 4; x++)
		{
			uint32_t gan[4] ;
			for(int i=0;i<4;i++) gan[i]=0;

			int index = 0;

			for(int y = 0; y <4 ; y++)
			{
				if(grid[x][y] != 0)
				{
					if(gan[index] == 0)
					{
						gan[index] = grid[x][y];
					}
					else
					{
						if(gan[index] == grid[x][y])
						{
							gan[index] = grid[x][y]*2;
							index++;
						}
						else
						{
							index++;
							gan[index] = grid[x][y];
						}
					}
				}
			}
			for(int i = 0; i<4 ; i++) grid[x][i] = gan[i];
		}

}
void playScreenView::moveDown()
{
			for(int x = 0; x < 4; x++)
			{
				uint32_t gan[4] ;
				for(int i=0;i<4;i++) gan[i]=0;

				int index = 3;

				for(int y = 3; y >-1 ; y--)
				{
					if(grid[x][y] != 0)
					{
						if(gan[index] == 0)
						{
							gan[index] = grid[x][y];
						}
						else
						{
							if(gan[index] == grid[x][y])
							{
								gan[index] = grid[x][y]*2;
								index--;
							}
							else
							{
								index--;
								gan[index] = grid[x][y];
							}
						}
					}
				}
				for(int i = 0; i<4 ; i++) grid[x][i] = gan[i];
			}
}

// xử lý logic thêm box mới
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
	    static mt19937 gen(xTaskGetTickCount()); // xTaskGetTickCount : thời gian chạy của hệ thống
	    uniform_int_distribution<> dis(0, zeroCount - 1);

	    int randomIndex = dis(gen);
	    int randX = viTri0[randomIndex][0];
	    int randY = viTri0[randomIndex][1];

	    // Gán giá trị 2 vào vị trí vừa chọn
	    grid[randX][randY] = 2;

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

// update giao diện
void playScreenView::updateGiaoDien()
{
	Unicode::snprintf(textArea11Buffer, 10 , "%u", grid[0][0]);
	textArea11.invalidate();

	Unicode::snprintf(textArea12Buffer, 10 , "%u", grid[0][1]);
	textArea12.invalidate();

	Unicode::snprintf(textArea13Buffer, 10 , "%u", grid[0][2]);
	textArea13.invalidate();

	Unicode::snprintf(textArea14Buffer, 10 , "%u", grid[0][3]);
	textArea14.invalidate();

	Unicode::snprintf(textArea21Buffer, 10 , "%u", grid[1][0]);
	textArea21.invalidate();

	Unicode::snprintf(textArea22Buffer, 10 , "%u", grid[1][1]);
	textArea22.invalidate();

	Unicode::snprintf(textArea23Buffer, 10 , "%u", grid[1][2]);
	textArea23.invalidate();

	Unicode::snprintf(textArea24Buffer, 10 , "%u", grid[1][3]);
	textArea24.invalidate();

	Unicode::snprintf(textArea31Buffer, 10 , "%u", grid[2][0]);
	textArea31.invalidate();

	Unicode::snprintf(textArea32Buffer, 10 , "%u", grid[2][1]);
	textArea32.invalidate();

	Unicode::snprintf(textArea33Buffer, 10 , "%u", grid[2][2]);
	textArea33.invalidate();

	Unicode::snprintf(textArea34Buffer, 10 , "%u", grid[2][3]);
	textArea34.invalidate();

	Unicode::snprintf(textArea41Buffer, 10 , "%u", grid[3][0]);
	textArea41.invalidate();

	Unicode::snprintf(textArea42Buffer, 10 , "%u", grid[3][1]);
	textArea42.invalidate();

	Unicode::snprintf(textArea43Buffer, 10 , "%u", grid[3][2]);
	textArea43.invalidate();

	Unicode::snprintf(textArea44Buffer, 10 , "%u", grid[3][3]);
	textArea44.invalidate();
}

void playScreenView::endGame() // endGame khi thua
{
	endContainer.setVisible(true);// a: hiện container kết thúc
	updateHighestScore(); // b: lưu điểm cao nhất
	Unicode::snprintf(YourScoreText_ISBuffer, 10 , "%u", score); // c: hiển thị điểm của người chơi

	YourScoreText_IS.invalidate();
	endContainer.invalidate();
}

void playScreenView::updateHighestScore()
{
	if (  score > ( model->getHighestScore() )  )  // lấy điểm ra để so sánh
		{
	        model->luuHighestScore(score); // gọi xuống model để lưu điểm
	    }
}
