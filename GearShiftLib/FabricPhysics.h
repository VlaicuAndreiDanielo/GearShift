#pragma once
#include <vector>
#include <cmath>

struct Pt {
    float x, y;
    float ox, oy;
    float fx, fy;
    bool pinned;

    Pt(float _x, float _y) : x(_x), y(_y), ox(_x), oy(_y),
        fx(0), fy(0), pinned(false) {
    }
};

class Fabric {
private:
    std::vector<Pt> pts;
    int w, h;
    float space;
    float damp;
    float stiff;

public:
    Fabric(int width, int height, int spacing);

    void update(float dt);
    void applyForce(float mx, float my, float radius, float strength);
    void reset();

    const std::vector<Pt>& getPts() const { return pts; }
    int getW() const { return w; }
    int getH() const { return h; }
    Pt& getPt(int x, int y);
};