#include "FabricPhysics.h"
#include <algorithm>

Fabric::Fabric(int width, int height, int spacing)
    : w(width), h(height), space(spacing), damp(0.98f), stiff(0.98f) {

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Pt p(x * space, y * space);

            // to prevent excessive deformation we pin the edges ->  it distorted the fabric too much 
            if (x == 0 || x == w - 1 || y == 0 || y == h - 1) {
                p.pinned = true;
            }

            pts.push_back(p);
        }
    }
}

void Fabric::update(float dt) {
    for (auto& p : pts) {
        if (p.pinned) continue;

        float vx = (p.x - p.ox) * damp;
        float vy = (p.y - p.oy) * damp;

        p.ox = p.x;
        p.oy = p.y;
        p.x += vx + p.fx * dt;
        p.y += vy + p.fy * dt;
        p.fx = p.fy = 0;
    }

    //  rigidity
    for (int iter = 0; iter < 8; iter++) {
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                Pt& p = getPt(x, y);

                if (x < w - 1) {
                    Pt& n = getPt(x + 1, y);
                    float dx = n.x - p.x;
                    float dy = n.y - p.y;
                    float d = std::sqrt(dx * dx + dy * dy);
                    float diff = (d - space) / d * stiff;

                    if (!p.pinned) { p.x += dx * diff * 0.5f; p.y += dy * diff * 0.5f; }
                    if (!n.pinned) { n.x -= dx * diff * 0.5f; n.y -= dy * diff * 0.5f; }
                }

                if (y < h - 1) {
                    Pt& n = getPt(x, y + 1);
                    float dx = n.x - p.x;
                    float dy = n.y - p.y;
                    float d = std::sqrt(dx * dx + dy * dy);
                    float diff = (d - space) / d * stiff;

                    if (!p.pinned) { p.x += dx * diff * 0.5f; p.y += dy * diff * 0.5f; }
                    if (!n.pinned) { n.x -= dx * diff * 0.5f; n.y -= dy * diff * 0.5f; }
                }
            }
        }
    }
}

void Fabric::applyForce(float mx, float my, float radius, float strength) {
    //  pushes fabric down from mouse
    for (auto& p : pts) {
        float dx = p.x - mx;  // direction mouse to point
        float dy = p.y - my;
        float dSq = dx * dx + dy * dy;
        float rSq = radius * radius;

        if (dSq < rSq && dSq > 0.1f) {
            float d = std::sqrt(dSq);
            //  force multiplier 
            float force = (1.0f - d / radius) * strength * 7.0f; // 0.5f (minimal), now 2.0f(decent),0.7(testing)  dont go over 0,17
            //it breaks the wave effect too much 
            p.fx += (dx / d) * force;
            p.fy += (dy / d) * force;
        }
    }
}

void Fabric::reset() {
    for (int i = 0; i < pts.size(); i++) {
        int x = i % w;
        int y = i / w;
        pts[i].x = pts[i].ox = x * space;
        pts[i].y = pts[i].oy = y * space;
        pts[i].fx = pts[i].fy = 0;
    }
}

Pt& Fabric::getPt(int x, int y) {
    return pts[y * w + x];
}