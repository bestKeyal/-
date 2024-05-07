//
// Created by 19201 on 2024/5/6.
//

#ifndef GAME_SHELL_H
#define GAME_SHELL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>
#include <graphics.h> // 使用图形库
#include <windows.h> // 使用Sleep函数
#include "Turret.h"
#include <memory>
#include "config.h"

class Shell;

vector<Shell>         all_shells(TURRET_NUM * 2);

// 炮弹类
class Shell {
    double x, y, vx, vy, time;
    bool isActive, isAttack;
    const static int collisionThreshold = 2;

public:
    Shell(double x = 0, double y = 0, double v0 = 0, double angle = 0, bool is_attack = true, bool isActive = false) : x(x), y(y), isAttack(is_attack),
                                                                         time(0), isActive(isActive) {
        vx = v0 * cos(angle * M_PI / 180);
        vy = v0 * sin(angle * M_PI / 180);

        draw();
    }



    // 更新炮弹的位置
    void updatePosition(double dt) {
        if (!isActive) return;

        erase();
        if (isAttack) {
            x -= vx * dt;
            y -= vy * dt - 0.5 * g * dt * dt;
            vy -= g * dt;
        } else {
            x += vx * dt;
            y -= vy * dt - 0.5 * g * dt * dt;
            vy -= g * dt;

        }

        // 检查是否越界
        if (x < 0 || x > screenWidth || y > screenHeight) {
            isActive = false;
            std::cout << "Shell Deactivate!  " << std::endl
                      << "X = " << x << std::endl
                      << "Y = " << y << std::endl
                      ;
        }

        checkCollisions();
        draw();
    }

    void draw() {
        if (!isActive) return;
        int color = isAttack ? BLACK : GREEN;
        setcolor(color);
        circle(static_cast<int>(x), static_cast<int>(y), 3);
    }

    void erase() {
        if (!isActive) return;
        setcolor(BACKGROUND_COLOR);
        circle(static_cast<int>(x), static_cast<int>(y), 3);
    }

    // 检查炮弹是否有接触
    static void checkCollisions() {
        for (size_t i = 0; i < all_shells.size(); ++i) {
            for (size_t j = i + 1; j < all_shells.size(); ++j) {
                Shell shell1 = all_shells[i];
                Shell shell2 = all_shells[j];
                if (shell1.getIsActive() && shell2.getIsActive()) {
                    double distance = sqrt(pow(shell1.x - shell2.x, 2) + pow(shell1.y - shell2.y, 2));
                    if (distance < collisionThreshold) {
                        shell1.isActive = false;
                        shell2.isActive = false;

                        std::cout << "BOOM!" << std::endl;
                    }
                }
            }
        }
    }



    bool getIsActive() const { return isActive; }
    bool getIsAttack() const { return isAttack; }
};

#endif //GAME_SHELL_H
