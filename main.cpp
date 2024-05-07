#include <iostream>
#include <vector>
#include <cmath>
#include <conio.h>
#include <graphics.h> // 使用图形库
#include <windows.h> // 使用Sleep函数
#include <memory>

#include "Turret.h"
#include "config.h"
#include "Shell.h"
#include "Attack.h"
#include "Defense.h"


using std::cout;
using std::unique_ptr;
using std::vector;
using std::make_unique;






// 检查炮弹的坐标是否位于大本营中
bool is_in_Citadel(int x, int y) {
    return x <= screenWidth / 5 && y >= screenHeight / 2;
}



using std::endl;

int main() {

    // 初始化游戏布局
    initialize_game();
    double dt = 0.2;
    // 游戏循环
    int round = 0;
    while (!kbhit()) {
        cout << "ATKER " << attack_turrets.size() << endl;
        cout << "ATKER " << defense_turrets.size() << endl;

        // 攻击方开炮
        cout << "Attack" << endl;
        for (auto & atk : attack_turrets) {
            bool res = atk.fire();
            if (res) {
                cout << "The " << atk.getShellIdx() << " fire !" << endl;

            } else {
                cout << "The " << atk.getShellIdx() << " fire fail..." << endl;
            }
        }

        cout << "Defense" << endl;

        // 防御方开炮
        for (auto & dfs : defense_turrets) {
            bool res = dfs.fire();
            if (res) {
                cout << "The " << dfs.getShellIdx() << " fire !" << endl;

            } else {
                cout << "The " << dfs.getShellIdx() << " fire fail..." << endl;
            }
        }


        // 更新炮弹状态
        int atk_cnt = 0;
        int dfs_cnt = 0;
        for (auto & sel : all_shells) {
            cout << (sel.getIsAttack() ? "is Attack" : "is Defense") << endl;
            if (sel.getIsActive()) {
                if (sel.getIsAttack())
                    atk_cnt++;
                else
                    dfs_cnt++;
            }
            sel.updatePosition(dt);
        }

        cout << "Attack shell: " << atk_cnt << std::endl;
        cout << "Defense shell: " << dfs_cnt << std::endl;

        Sleep(50);
    }

    _getch();
    closegraph(); // 关闭绘图窗口
    return 0;
}


