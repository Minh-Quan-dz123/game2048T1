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

    void luuHighestScore(uint32_t highestscore) // lưu điểm cao nhất (từ View->Model)
    {
    	highestscore = highestScore;
    }
    uint32_t getHighestScore() const // lấy điểm cao nhất (Từ View gọi -> Model -> View
    {
    	return highestScore;
    }



    void tick();
protected:
    ModelListener* modelListener;

    // biến lưu điểm cao nhất
    uint32_t highestScore = 0;


};

#endif // MODEL_HPP
