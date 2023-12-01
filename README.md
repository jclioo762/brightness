# Deepin dde-dock plugin
## Brightness 屏幕亮度插件

### !!!
> 此插件仅适配于 Deepin 20.9 且 仅适配于 intel 核显

> 非此标准使用请自行承担风险！！


### 功能
调节屏幕亮度

> 此插件并不完善（仅能用的状态），很多功能并未实现
> 
> 譬如 监听屏幕设备的增加或减少，多屏幕设备 的亮度调节, 滚轮直接调节亮度等等

### 安装

```bash
sudo cd sh && bash install.sh
```

**OR**

直接下载 libbrightness.so
```bash
sudo cp -f libbrightness.so  /usr/lib/dde-dock/plugins/
pkill dde-dock && dde-dock
```

### 卸载
```bash
sudo rm -f  /usr/lib/dde-dock/plugins/libbrightness.so
pkill dde-dock && dde-dock
```
    
### Tip
老早使用Deepin 就没有亮度调节功能，还好有 @寂静的羽夏 大佬 开发的屏幕小灯程序
但每次打开应用都要点击一下托盘弹出。强迫症的我特别想要一个原生插件的屏幕调节程序。但是搜遍整网络也找不见
没办法只能自己开发

本人 java 出身，第一接触 C++ QT ，开发可谓是路途艰辛。
代码有不规范的地方或者有设计不合理的地方还请大神指教


### 参考

@寂静的羽夏 屏幕小灯 核心功能

@Deepin官方 Sound 插件UI

### 致谢
感谢 @寂静的羽夏 热心解答问题

### 吐槽
@Deepin官方 的插件开发文档能不能更新下， 写的更完善一些 [生气]

### 反馈问题
直接Issues

或者邮箱
jclio@qq.com

### 博客
[Jclio](jclio.top)