//
// Created by 19201 on 2024/5/6.
//

#ifndef GAME_ATTACK_H
#define GAME_ATTACK_H

#include "Shell.h"
#include "Turret.h"


// 攻击炮台类
class AttackTurret : public Turret {
    // 剩余发射炮弹的次数
    int remainingShots;

    // 每个炮台只有一个炮弹，记录在数组中
    int shell_idx;

public:
    AttackTurret(int x, int y, int shell_idx) : Turret(x, y, ATTACK_WIDTH, ATTACK_HEIGHT), remainingShots(50),
                                                shell_idx(shell_idx) {
        draw();
    }

    void draw() override {
        putimage(x, y, &attack_image);
    }

    bool canFire() const { return remainingShots > 0 && !all_shells[shell_idx].getIsActive(); }

    bool fire() override {
        if (canFire()) {
            double initialVelocity = 100; // 选择合适的初始速度
            double angle = 45; // 选择合适的发射角度
            all_shells[shell_idx] = Shell(x + width / 2, y, initialVelocity, angle, true, true);
            decreaseShots();
            return true;
        } else {
            return false;
        }
    }

    // 减少炮弹储量
    void decreaseShots() { if (remainingShots > 0) remainingShots--; }

    int getShellIdx() {
        return shell_idx;
    }
};

#endif //GAME_ATTACK_H
