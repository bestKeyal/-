//
// Created by 19201 on 2024/5/6.
//

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H


// 设置游戏窗口大小
#define screenWidth 1200
#define screenHeight 600

// 双方炮台数量
#define TURRET_NUM 5

// 防御方炮台图片宽高
#define DEFENSE_WIDTH 68
#define DEFENSE_HEIGHT 48

// 攻击方炮台图片宽高
#define ATTACK_WIDTH 69
#define ATTACK_HEIGHT 63

// 重力加速度
#define g 9.8

#define E_LIGHTGRAY RGB(111, 111, 111)

// 屏幕上的位置是否被炮台占用的掩码数组
bool occupied[screenWidth][screenHeight] = {false};

// 存储防御炮台和攻击炮台的图片变量（在初始化游戏布局时加载）
IMAGE defense_image, attack_image;
char defense_image_path[] = R"(C:\Users\19201\CLionProjects\Game\image\defense.png)";
char attack_image_path[] = R"(C:\Users\19201\CLionProjects\Game\image\attack.png)";

#define BACKGROUND_COLOR WHITE


#include "Defense.h"
#include "Attack.h"
#include "Shell.h"

// 记录炮台实例
vector<AttackTurret>  attack_turrets;
vector<DefenseTurret> defense_turrets;
int shell_idx_in_arr = 0;

// 检查炮台是否能放置在指定位置的函数
bool can_place_Turret(int x, int y, int turretWidth, int turretHeight) {
    for (int i = x; i < x + turretWidth; i++) {
        for (int j = y; j < y + turretHeight; j++) {
            // 如果越界或者位置已被占用，则无法放置
            if (i >= screenWidth || j >= screenHeight || occupied[i][j]) {
                return false;
            }
        }
    }
    return true;
}


// 标记炮台位置的函数
void mark_Turret_position(int x, int y, int turretWidth, int turretHeight) {
    for (int i = x; i < x + turretWidth; i++) {
        for (int j = y; j < y + turretHeight; j++) {
            occupied[i][j] = true;
        }
    }
}

// 放置防御炮台
void place_defense_turret(int defenseWidth, int defenseHeight) {
    int defenseX, defenseY;
    do {
        // X轴的范围是[0, screenWidth / 5]
        defenseX = rand() % (screenWidth / 5);
        // Y轴的范围是[0, screenHeight]
        defenseY = rand() % screenHeight;
    } while (!can_place_Turret(defenseX, defenseY, defenseWidth, defenseHeight));

    mark_Turret_position(defenseX, defenseY, defenseWidth, defenseHeight);

    defense_turrets.emplace_back(defenseX, defenseY, shell_idx_in_arr);
    shell_idx_in_arr++;

}

// 放置攻击炮台
void place_attack_turret(int attackWidth, int attackHeight) {
    int attackX, attackY;
    do {
        // X轴的范围是[screenWidth - (screenWidth / 5), screenWidth]
        attackX = (rand() % (screenWidth / 5)) + (screenWidth - screenWidth / 5);
        // Y轴的范围是[0, screenHeight]
        attackY = rand() % screenHeight;
    } while (!can_place_Turret(attackX, attackY, attackWidth, attackHeight));

    mark_Turret_position(attackX, attackY, attackWidth, attackHeight);

    attack_turrets.emplace_back(attackX, attackY, shell_idx_in_arr);
    shell_idx_in_arr++;

}


// 初始化游戏布局
void initialize_game() {
    // 初始化图形窗口
    initgraph(screenWidth, screenHeight);

    // 设置背景颜色为白色
    setbkcolor(BACKGROUND_COLOR);

    // 使用当前背景颜色清除屏幕
    cleardevice();

    // 设置大本营的边框颜色为浅灰色
    setlinecolor(E_LIGHTGRAY);

    // 左1/5，下1/2的矩形是大本营。
    // 绘制矩形的上边
    line(0, screenHeight / 2, screenWidth / 5, screenHeight / 2);
    // 绘制矩形的左边
    line(0, screenHeight / 2, 0, screenHeight);
    // 绘制矩形的下边
    line(0, screenHeight, screenWidth / 5, screenHeight);
    // 绘制矩形的右边
    line(screenWidth / 5, screenHeight / 2, screenWidth / 5, screenHeight);


    // 设置文本颜色为黑色
    settextcolor(BLACK);

    // 在矩形内部的左上角绘制文本 "大本营"
    outtextxy(10, screenHeight / 2 + 10, "Citadel");

    // 加载两种炮台的图片
    loadimage(&defense_image, _T(defense_image_path));
    loadimage(&attack_image, _T(attack_image_path));

    for (int i = 0; i < TURRET_NUM; ++i) {
        // 放置防御炮台
        place_defense_turret(DEFENSE_WIDTH, DEFENSE_HEIGHT);
        // 放置攻击炮台
        place_attack_turret(ATTACK_WIDTH, ATTACK_HEIGHT);

    }
}

#endif //GAME_CONFIG_H
