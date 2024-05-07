//
// Created by 19201 on 2024/5/6.
//

#ifndef GAME_DEFENSE_H
#define GAME_DEFENSE_H

#include "Shell.h"
#include "Turret.h"
#include "config.h"

// 防御炮台类
class DefenseTurret : public Turret {
    // 每个炮台只有一个炮弹，记录在数组中
    int shell_idx;
public:
    DefenseTurret(int x, int y, int shell_idx) : Turret(x, y, DEFENSE_WIDTH, DEFENSE_HEIGHT),
                                  shell_idx(shell_idx) {
        draw();
    }

    void draw() override {
        putimage(x, y, &defense_image);
    }

    bool canFire() const { return !all_shells[shell_idx].getIsActive(); }

    bool fire() override {
        /*
         * 开炮功能
         *
         * 每次开炮都新生成一个炮弹对象，填入炮弹数组的对应位置中。
         * */
        if (canFire()) {
            double initialVelocity = 80; // 选择合适的初始速度
            double angle = 60; // 选择合适的发射角度
            all_shells[shell_idx] = Shell(x + width / 2, y, initialVelocity, angle, false, true);
            return true;
        } else {
            return false;
        }
    }

    int getShellIdx() {
        return shell_idx;
    }
};

#endif //GAME_DEFENSE_H
