# Music Center

> 嵌入式作业，开发中

## 硬件列表

- NodeMCU ESP8266，主控
- SSD1306，用于显示机器 IP 等信息
- MP3-TF-16P，用于存储与解码 MP3
- 8Ω，2W 喇叭，杜邦线若干，面包板

## 总览

由于 `NodeMCU` 兼具 WIFI 联网能力、快速开发能力，与可观的性能， 此次作业在目标板上主要选用此模块与 `MicroPython` 联合开发。

## 分工

- 王子权（Jerrita）：功能设计，目标板程序开发与调试
- 李超：功能设计，后端程序开发与联调，App 开发
- 姓名（ID）: 分工

## 目录说明

- src: 目标板外项目（如后端，Utils 等）
- model: 主模块封装，下文介绍
- boot.py: 板子上电后进行初始化（慎改）
- main.py: 目标板上主程序

## 目标板各目录功能说明

### model

- `__init__.py`: 包定义，引入模块
- `controller.py`: 控制器，目前用于联网
- `define.py`: 一些宏定义，目前用于一些 GPIO 引脚的标注
- `display.py`: 封装一些用于展示的 screen，便于输出到显示屏上
- `storage.py`: 全局数据存储，用于跨模块共享非易失数据
- `watchdog.py`: 看门狗，用于故障重启

### lib

引入的一些模块，便于复用

- `picoweb`: 一个轻量的 web 服务器，可提供路由
- `ulogging.py`: 用于调试日志的输出



## 接口说明

```bash
POST /api/volume
参数：
- volume: int (Optional)
返回 JSON:
- volume: 当前音量
- code: int
- msg: String

POST /api/play
参数:
- method: string [play, pause, next, pre]
- id: int (Optional, only method == select)
返回 JSON:
你自己看，我忘了

```





## 仓库使用说明

> 为了与板子的 Filesystem 保持一致性，此仓库的根为目标板的根
>
> 非目标板代码（如后端，Utils 等）请丢 src 目录下

1. 如需进行项目协作，请在此 git 平台（https://git.jerrita.cn） 自行注册账号，并联系 Jerrita 添加仓库权限。
2. 添加内容请完善文档。
3. 尽量使用 PR 提交更改，如果不会，更改前请告知我。

## 开发环境

- NodeMCU: PyCharm + MicroPython Extension
- Harmony: DevEco Studio + Harmony2.0.0

## 参考资料

- https://github.com/peterhinch/micropython-samples
- docs 文件夹
