#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include <cstdint>

extern "C"
{
	extern volatile uint8_t newStatus;
	extern volatile uint8_t oldStatus;
}

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	// code đọc newStatus và oldStatus để gọi hàm xử lý sự kiện trên giao diện
}
