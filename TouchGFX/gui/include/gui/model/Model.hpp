#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstdint>
class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }


    void luuHighestScore(uint32_t highestscore) ;// lưu điểm cao nhất
    uint32_t getHighestScore() ;// lấy điểm cao nhất (Từ View gọi ->presenter-> Model -> View


    void tick();
protected:
    ModelListener* modelListener;

    // biến lưu điểm cao nhất
    uint32_t highestScore = 2;


};

#endif // MODEL_HPP
