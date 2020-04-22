#include "Texture.h"
#include "Util.h"
#include <vector>

typedef struct Frame {
    Rect quad;
    double duration;
} Frame;

class Animation {
public:
    Animation();
    Animation(Texture texture);
    bool LoadFromFile(std::string path);
    void AddFrame(Frame f);
    void Update();

    Texture _texture;
    std::vector<Frame> _frames;
    unsigned short int _currentFrame;
private:
    unsigned short int _counter;
};