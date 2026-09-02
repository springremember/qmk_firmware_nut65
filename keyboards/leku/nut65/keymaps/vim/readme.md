# NUT65 Vim 固件

基于 qmk-vim 社区项目的 NUT65 键盘固件，在 QMK 固件层面模拟 Vim 绝大多数功能，纯固件实现、无需任何系统层软件。

## 一、使用说明

### Vim 永久开启

Vim 模式**永久开启**，开机即处于 Normal 模式，没有退出 Vim 的选项，只有模式切换。

### Esc 行为

| 当前模式 | 按 `Esc` 效果 |
| :--- | :--- |
| Insert | 先发送真实 Esc → 切 Normal |
| Normal | 发送真实 Esc，保持 Normal |
| Visual / Visual Line | 先发送真实 Esc → 切 Normal |

### 模式切换（遵循 vim 原则）

| 命令 | 效果 |
| :--- | :--- |
| `i` / `a` / `I` / `A` / `o` / `O` | 进入插入模式（`a` 光标后移、`I` 行首、`A` 行尾、`o` 下一行、`O` 上一行） |
| `v` / `V` | 进入可视模式 / 可视行模式 |
| `Esc` | 插入/可视 → 回 Normal |

## 二、功能清单

### 移动（motions）
- `h` / `j` / `k` / `l` — 左 / 下 / 上 / 右
- `w` / `b` / `e` — 跳词（Ctrl+方向键实现，`e` 与 `w` 行为近似）
- `0` / `^` — 行首；`$` — 行尾
- `gg` / `G` — 文件首 / 文件尾（部分程序生效）

### 操作（actions，可与 motion 组合）
- `d` + motion（`dw`/`db`/`d$`…）、`c` + motion（`cw`/`c$`…）、`y` + motion
- `dd` / `cc` / `yy` — 删除 / 改写 / 复制整行
- `D` / `C` — 删除 / 改写到行尾；`Y` — 复制到行尾
- `x` / `X` — 删除光标处 / 前一个字符
- `p` / `P` — 粘贴到光标后 / 前
- `u` / `Ctrl+r` — 撤销 / 重做
- `r` — 替换单个字符
- `.` — 重复上一次操作

### 文本对象
- `iw` / `aw` — 单词内 / 含单词（如 `ciw`、`daw`）
- `ig` / `ag` — 全文内 / 含全文（如 `cig`、`dig`）

### 数字前缀
- `3j`、`5w`、`d2w` 等 — 重复指定次数（Normal 模式数字键作计数器）

### 定制绑定
- `s` — 保存（Ctrl+S）
- `/` / `?` — 查找（Ctrl+F）
- `S` — 改写整行（vim 原生，等价 `cc`）

### 数字键长按出 F 区（仅 Insert 模式、base 层）
| 操作 | 效果 |
| :--- | :--- |
| 短按数字 `1`~`0` | 输入数字 |
| 长按数字 `1`~`0`（200ms） | F1~F10 |
| `Ctrl` + 数字 | Ctrl+F1~F10 |

> 说明：`Fn` + 数字（layer 1）仍是厂商原厂的 F1~F12，未做任何改动。
> Normal 模式下数字键是计数器（`3j`），不做 F 区长按。

## 三、Vim 状态指示

### RGB 灯指示
Esc 键位灯随 Vim 模式变色：

| 模式 | 颜色 |
| :--- | :--- |
| Normal | 蓝 |
| Insert | 绿 |
| Visual | 品红 |
| Visual Line | 青 |

### Insert 键光标指示
非 Insert 模式（Normal/Visual/Visual Line）会向主机按住 `Insert` 键（KC_INS），使编辑器光标变为**方块**；Insert 模式释放，光标变为**竖线**。

## 四、与厂商固件的差异

键盘层定义（keymap）与厂商默认**逐键一致**，其中 layer 1（`_FL`，Fn 功能层）**完全未改动**。所有 Vim 功能均为键码拦截实现。

仅对 `keyboards/leku/nut65/nut65.c` 做了 3 处最小改动（为让出 keymap 级钩子）：
1. `process_record_user` 重命名为 `hs_process_record_user`（RGB 录制逻辑，原样保留）
2. `housekeeping_task_user` 重命名为 `hs_housekeeping_task_user`（充电/矩阵循环逻辑，原样保留）
3. `rgb_matrix_indicators_advanced_kb` 末尾补调用 `rgb_matrix_indicators_advanced_user`

## 五、编译与刷写

```bash
# 编译
make leku/nut65:vim

# 刷写（先进入 bootloader）
make leku/nut65:vim:flash
```

进入 bootloader 方式（任选其一）：
- 按住 `Fn` + `Right Shift` + `Esc`
- 按住 `Esc` 插入 USB 线（同时擦除持久化设置）
- 按住底部 PCB 的 Reset 键插入 USB 线

刷写工具使用 wb32-dfu（QMK Toolbox 或命令行 `wb32-dfu-updater` 均可，加载生成的 `leku_nut65_vim.bin`）。

## 六、已知局限

固件无法实现的功能（与 qmk-vim 一致，需编辑器 Vim 插件）：
- `f{char}` / `t{char}` 行内查找（需读取文本内容）
- `/pattern` 正则搜索（固件用 Ctrl+F 系统查找替代）
- `mark` 跳转、`%` 括号匹配（需解析代码结构）
- `e` 跳词尾无法精确实现（系统级 Ctrl+→ 只能到词首，与 `w` 近似）
- Insert 键方块光标依赖编辑器对 `KC_INS` 按住/释放的响应（多数编辑器为边沿触发，释放可能不自动变回竖线，需实测）
