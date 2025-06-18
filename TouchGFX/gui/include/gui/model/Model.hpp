#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void setScore(int highestscore) // hàm lưu điểm cao nhất người chơi chơi
    {
    	if(highestscore > highestScore)
    	{
    		highestScore = highestscore;
    	}
    }
    int getScore() const // thêm const để tránh lỗi
    {
    	return highestScore;
    }

    void tick();
protected:
    ModelListener* modelListener;
    int highestScore=2;
};

#endif // MODEL_HPP
