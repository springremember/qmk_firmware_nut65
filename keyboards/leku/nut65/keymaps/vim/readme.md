# NUT65 Vim 固件

基于 qmk-vim 社区项目的 NUT65 键盘固件，在 QMK 固件层面模拟 Vim 绝大多数功能，纯固件实现、无需任何系统层软件。目标系统：Windows / Linux（Ctrl 方案，非 Mac）。

## 一、模式与开关

### Vim 永久开启

Vim 模式**默认开启**，开机即处于 Normal 模式。可通过 `Fn` + `Caps` 关闭/开启 Vim（关闭后固件进入"透传"状态，指示灯变红，其余键位均按厂商行为使用）。

### 模式切换（遵循 vim 原则）

| 命令 | 效果 |
| :--- | :--- |
| `i` / `a` / `A` / `I` / `o` / `O` | 进入插入模式（`i` 光标处、`a` 后移一格、`I` 行首、`A` 行尾、`o` 下一行新行、`O` 上一行新行） |
| `v` / `V` | 进入可视模式 / 可视行模式 |
| `Caps` | 按下回到 Normal（Insert / Visual → Normal；普通模式按 Caps 同样回到 Normal） |
| `Fn` + `Caps` | 开关 Vim 模式 |
| `Esc` | 见下方 Esc 行为表 |

### Esc 行为

| 当前模式 | 按 `Esc` 效果 |
| :--- | :--- |
| Normal | 向宿主发送真实 Esc（清高亮/取消），固件模式**不变** |
| Insert | 向宿主发送真实 Esc（关闭输入法候选/取消等），固件**保持插入模式不变** |
| Replace（`R`） | 退出替换模式回 Normal，不发送 Esc |
| Visual / Visual Line | 交给 qmk-vim 原生处理：退出可视并回 Normal（含取消选区） |

> 注意：Insert 模式下按 Esc 只发真实键，**不会**把固件切回 Normal（切 Normal 请用 `Caps`）。

### 电源开关（仅无 USB 线时生效：`Delete`原键位 + `Space`）

`Delete` 原键位（第 2 行最右，本固件为 `_GO` 层切换键）与 `Space` 组合：

| 操作 | 效果 |
| :--- | :--- |
| 运行中按住 ≥3s | 进入深睡（关闭/省电，近似关机） |
| 深睡中按住 ≥3s | 开机，恢复无线模式 |
| 深睡中按其它任意键 | 仅唤醒 MCU 瞬间，随即自动重回深睡（不会误开机） |
| 拔掉 USB 线 | 自动回到上次的无线设备 |
| 插上 USB 线 | 自动进入有线模式；深睡中插线立即恢复有线 |

> 有 USB 线时该组合键不生效；插/拔线自动切换沿用并增强原厂行为。

## 二、功能清单

### 移动（motions）

- `h` / `j` / `k` / `l` — 左 / 下 / 上 / 右（方向键）
- `w` / `b` — 跳词首（系统 Ctrl+→ / Ctrl+←；`b` 回上一词首）
- `e` — 与 `w` 近似（系统词跳只能到词首，无法精确到词尾）
- `0` / `$` — 行首 / 行尾（Home / End）
- `gg` / `G` — 文档首 / 文档末（Ctrl+Home / Ctrl+End）
- `Ctrl+F` / `Ctrl+B` — 下翻页 / 上翻页（PageDown / PageUp）
- `-` / `+` — 上一行行首 / 下一行行首
- `Backspace` / `Space` — 左移 / 右移一格

### 行首行尾细节

- `^`、`W` / `B` / `E` 等需要读取文本内容的移动不精确，详见"已知局限"。

### 编辑（actions）

- `x` / `X` — 删除光标处字符 / 删除光标前字符（Del / Backspace）
- `r` — 替换单个字符（Delete 后输入新字符）
- `R` — **替换模式**：进入后持续逐个覆盖字符（每键 = Delete + 输入），光标前进；行尾自动变为插入；按 `Esc` 或 `Caps` 退出（进入替换模式时 R 键指示灯变紫）
- `s` / `S` — 改写当前字符 / 改写整行（近似 vim 语义）
- `c` / `d` / `y` + motion — 改写 / 删除 / 复制并移动（`cw`、`d$`、`yw`…）
- `cc` / `dd` / `yy` — 改写 / 删除 / 复制整行
- `C` / `D` / `Y` — 改写到行尾 / 删到行尾 / 复制到行尾
- `p` / `P` — 粘贴到光标后 / 前
- `u` / `Ctrl+R` — 撤销 / 重做
- `J`（Shift+J）— 合并下一行到当前行（End + Delete，不插空格）
- `.` — 重复上一次操作（有限范围录制，见"已知局限"）

### 数字前缀（Normal 模式计数器）

- Normal 模式数字键作计数器（VIM_NUMBERED_JUMPS），可配合行操作使用（如 `3dd`）。

### 查找与定制键

- `/` / `?` — 调用宿主搜索（Ctrl+F）
- `Enter` — 透传（发送真实 Enter）

## 三、F 区：_GO 层（按住 grave 键切换）

键盘 `\` 位置右侧的 `grave` 键（`~`/`` ` `` 原位置，`_BL` 第 2 行最右）改为 **按住时切换到 _GO 层**，松开回归原层：

| _GO 层键位 | 输出 |
| :--- | :--- |
| `Esc` 位置（原 grave 键位） | `` ` ``（Shift= `~`） |
| `1` `2` `…` `0` `-` `=` | F1 F2 … F10 F11 F12 |

> 其余 _GO 层键位继承 base 层。Insert 模式下数字键不再长按出 F 区（已取消），普通数字输入即可；`Ctrl` + 数字在 Insert 模式仍映射为 Ctrl+F1~F10。
> 说明：`Fn` + 数字（layer 1）仍是厂商原厂的 F1~F12，未做任何改动。

## 四、Vim 状态指示（RGB）

模式指示每帧强制设置、覆盖厂商灯效，不受 RGB_MOD / RL_MOD 切换影响：

| 模式 | 颜色 |
| :--- | :--- |
| Normal | 蓝 |
| Insert | 绿 |
| Visual / Visual Line | 紫 |
| Vim 关闭（透传） | 红 |

跟随模式色的键位灯（满亮）：`Caps`、`Esc`、`Delete`（原 Insert 位）。
底部灯条及侧灯以 7% 亮度显示同一模式色；进入 `R`（替换模式）时底部灯条切换为**橙色**。

## 五、与厂商固件的差异

键盘层定义（keymap）中：
- `_FL`（win FN 层）、`_MBL` / `_MFL`（mac 层）、`_DEFA`：与厂商默认**逐键一致，未改动**
- `_BL`（win Base 层）按用户要求改动键位：`Insert→Delete`、原 `Delete`（grave 位）改为**按住切 _GO 层**、`PageUp→KC_WFWD`、`PageDown→KC_WBAK`，其余一致
- 新增 `_GO` 层（F 区 + `` ` ``，见上文；keyboard.json 动态层数相应为 6）

所有 Vim 功能均为键码拦截实现，不新增/改造任何层。

仅对 `keyboards/leku/nut65/nut65.c` 做了 3 处最小改动（为让出 keymap 级钩子）：
1. `process_record_user` 重命名为 `hs_process_record_user`（RGB 录制逻辑，原样保留）
2. `housekeeping_task_user` 重命名为 `hs_housekeeping_task_user`（充电/矩阵循环逻辑，原样保留）
3. `rgb_matrix_indicators_advanced_kb` 末尾补调用 `rgb_matrix_indicators_advanced_user`

## 六、编译与刷写

```bash
# 环境（首次）：
export PATH=<nut65>/toolchain/usr/bin:$HOME/.local/bin:$PATH
export QMK_HOME=<qmk_firmware 目录>

# 编译
make leku/nut65:vim ALLOW_WARNINGS=yes

# 刷写（先进入 bootloader）
make leku/nut65:vim:flash
```

产物：`leku_nut65_vim.bin`（复制到项目 output/ 目录留档）。

进入 bootloader 方式（任选其一）：
- 按住 `Fn` + `Right Shift` + `Esc`
- 按住 `Esc` 插入 USB 线（同时擦除持久化设置）
- 按住底部 PCB 的 Reset 键插入 USB 线

刷写工具使用 wb32-dfu（QMK Toolbox 或命令行 `wb32-dfu-updater` 均可）。

> 刷入后如默认灯效/键位未生效，可在 `Fn` 层按左上 `EE_CLR` 恢复默认设置。
> 子模块（lib/chibios 等）如拉取失败，可从仓库 `submodule-pack/` 目录解压对应版本到 `lib/` 下离线使用。

## 七、已知局限

固件无法精确实现的功能（需读取文本内容/编辑器内部状态）：
- `e` 跳词尾：系统词跳只能到词首，与 `w` 近似
- `^` 行首非空白、`W`/`B`/`E` 大写词、`f`/`t`/`;`/`,` 行内查找：无对应系统键
- `%` 括号配对、`mark`/`` ` `` 跳转、`/pattern` 正则搜索（固件以宿主 Ctrl+F 替代）、`*`/`#` 词搜索
- 文本对象（`iw`/`aw` 仅有限支持）、块选（Ctrl+V）、寄存器 `"a`、宏 `q@`、`gv`：无法通过键码实现
- `~`、`gu`/`gU`、`<`/`>` 缩进、`zz`/`zt`/`zb`：无通用宿主命令
- 数字前缀对纯移动的乘算精度取决于宿主（行操作 `dd` 等可乘算）
- `R`/`r` 在中文输入法激活时，键入字母会进入输入法预编辑，需先切英文（与真实 vim 使用习惯一致）
- `J` 合并不插空格、不去下一行缩进（固件无法感知行尾/行首空白）
- `.` 重复仅覆盖经过 vim 引擎录制范围的按键序列，非完整操作记录
