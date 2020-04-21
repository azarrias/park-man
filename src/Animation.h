#include "Texture.h"
#include "Util.h"
#include <vector>

class Animation {
public:
    Animation();
    Animation(Texture texture);
    bool LoadFromFile(std::string path);
    void AddFrame(Rect r);
    void Render();

    Texture _texture;
private:
    std::vector<Rect> _clips;
};