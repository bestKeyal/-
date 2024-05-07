//
// Created by 19201 on 2024/5/4.
//

#ifndef GAME_TURRET_H
#define GAME_TURRET_H

#include <memory>
using std::vector;
using std::unique_ptr;
// 炮台基类
class Turret {
protected:
    int x, y, width, height;
    int hit_count; // 被击中次数

public:
    Turret(int x, int y, int w, int h) : x(x), y(y), width(w), height(h), hit_count(0) {}

    virtual void draw() = 0; // 绘制炮台
    virtual bool fire() = 0; // 开炮，开炮成功返回true，否则返回false
//    virtual void updateShells(double dt) = 0;

    bool isDestroyed() const { return hit_count >= 3; } // 判断炮台是否被摧毁
    void increaseHitCount() { hit_count++; } // 增加击中次数

    int getX() const { return x; }

    int getY() const { return y; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }


};

#endif //GAME_TURRET_H
