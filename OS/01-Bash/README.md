# OS 第一次作业 -- Bash

此次作业我设计了一个脚本用于自动将我的RSA公钥添加至服务器中，以便进行远程维护RSA
脚本会根据选项来进行自动化安装，使用方式为

```bash
# 本地安装
bash key.sh -i
# 网络安装
bash <(curl -fsSL https://jerrita.cn/key.sh) -i
```

