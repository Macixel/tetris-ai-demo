# tetris-ai —— 俄罗斯方块自动 AI（Demo 项目）

一个用于练习 **远程仓库 / 分支 / Pull Request / 代码评审 / 合并** 全流程的小型 Demo 项目。
项目主体是一个 C 风格的 C++ 俄罗斯方块自动决策 AI：它读取当前局面，枚举「当前方块 × 下一方块」
的所有落点组合，用启发式评分函数挑出最优解并输出落点。

* 仓库所有者 / 评审者：[@Macixel](https://github.com/Macixel)
* 贡献者：[@mmmacixel-hue](https://github.com/mmmacixel-hue)

## 文件说明

| 文件 | 说明 |
| --- | --- |
| `tetris_ai.cpp` | AI 主程序 |
| `README.md` | 项目说明 |
| `.gitignore` | 忽略编译产物 |

## 方块编号约定

代码内部用 `类型 * 10 + 旋转态` 表示一个「方块形态」，例如 `10` = 类型 1 的第 0 号旋转态。
类型编号与字母的对应关系是：

| 编号 | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 字母 | O | I | Z | S | J | L | T |

## 评分函数

`calculateScore()` 组合多个启发式特征，权重在函数内硬编码：

* 消行数、落点高度、空洞数（`calculateNumberOfHoles`）
* 行 / 列变换数（`calculateRowTransitions` / `calculateColumnTransitions`）
* 井深（`calculateWellSums`）、方块自身占格数（`calculateValuableblock`）

## 输入文件 `3.txt` 格式

程序用固定偏移顺序读取输入（`fgetc` 逐字节），因此文件结构必须是：

```
偏移 0        : 当前方块类型字母
偏移 1..10    : 棋盘第 1 行（10 个字符，'0' 空 / '1' 占用）
偏移 11       : 下一个方块类型字母
偏移 12..211  : 棋盘第 2..20 行（共 200 个字符，中间不能有换行）
偏移 212      : 退出标记，读到 'X' 或 'E' 即结束主循环
```

即文件总长 213 字节（不含额外换行）。

## 构建与运行

源文件是 GBK 编码，编译时需要显式告知编译器，否则中文注释会乱码：

```bash
g++ -std=c++11 -O2 -finput-charset=GBK -o tetris.exe tetris_ai.cpp
```

> 运行目录下必须存在 `3.txt`，否则程序无法读取局面。

> 若缺少该文件，程序会向标准错误输出 `[ERROR] cannot open input file: 3.txt`，
> 并以返回码 1 结束，而不会继续用空文件指针读取局面。
