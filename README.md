![OpenWrt logo](include/logo.png)

OpenWrt V21.02.3官方稳定版源码  根据个人需要修改了自定义配置，添加了常用插件  
官方仓库地址 https://github.com/openwrt/openwrt.git  
version `r16554-1d4dea6d4f`

## Ubuntu22.04编译工具
官方建议的工具
https://openwrt.org/docs/guide-developer/toolchain/install-buildsystem
```
sudo apt update
sudo apt install build-essential gawk gcc-multilib flex git gettext libncurses5-dev libssl-dev python3-distutils rsync unzip zlib1g-dev
```
ImmortalWrt建议的工具
```
sudo apt update -y
sudo apt full-upgrade -y
sudo apt install -y ack antlr3 asciidoc autoconf automake autopoint binutils bison build-essential \
  bzip2 ccache cmake cpio curl device-tree-compiler ecj fastjar flex gawk gettext gcc-multilib g++-multilib \
  git gperf haveged help2man intltool lib32gcc1 libc6-dev-i386 libelf-dev libglib2.0-dev libgmp3-dev libltdl-dev \
  libmpc-dev libmpfr-dev libncurses5-dev libncursesw5 libncursesw5-dev libreadline-dev libssl-dev libtool lrzsz \
  mkisofs msmtp nano ninja-build p7zip p7zip-full patch pkgconf python2.7 python3 python3-pip python3-ply \
  python-docutils qemu-utils re2c rsync scons squashfs-tools subversion swig texinfo uglifyjs upx-ucl unzip \
  vim wget xmlto xxd zlib1g-dev
```
```
# 基本编译命令
./scripts/feeds update -a
./scripts/feeds install -a
make menuconfig
make -j8 download V=s 下载dl库（国内请尽量全局科学上网）
make -j4 V=s （-j1 后面是线程数。第一次编译推荐用单线程）（虚拟机最好指定线程数）

# 用管道将编译日志传送给 tee 命令（需要安装），最终写入到 compile.log 文件里
make -jN V=s | tee ../compile.log

cat ../compile.log | grep ERROR:
cat ../compile.log | grep failed
```


## 自定义配置
LAN ip `192.168.123.1`  
默认时区 `Asia/Shanghai`  
修正连接数为`165535`  
锁定默认主题为`bootstrap`  

## 常用插件
```
# PassWall  
git clone -b packages https://github.com/xiaorouji/openwrt-passwall.git openwrt-passwall
git clone -b luci https://github.com/xiaorouji/openwrt-passwall.git luci-passwall
```
```
# PassWall2
git clone https://github.com/xiaorouji/openwrt-passwall2.git openwrt-passwall2
```
```
# SSR Plus
git clone https://github.com/fw876/helloworld.git ssr-plus
```
```
# OpenClash
git clone https://github.com/vernesong/OpenClash.git
```
```
# AdGuardHome
https://github.com/rufengsuixing/luci-app-adguardhome.git
```
```
# luci-app-xray
git clone https://github.com/yichya/luci-app-xray.git
git clone https://github.com/Mitsuhaxy/luci-i18n-xray-zh-cn.git
```
```
# luci-theme-atmaterial
git clone https://github.com/esirplayground/luci-theme-atmaterial-ColorIcon.git
```
```
# luci-theme-argon
git clone https://github.com/jerrykuku/luci-theme-argon.git
```
```
# luci-app-aliddns
git clone https://github.com/pymumu/smartdns.git
```

## 编译常见问题
编译passwall 出现 v2ray-plugin 报错  
```
下载upx
wget https://github.com/upx/upx/releases/download/v3.96/upx-3.96-amd64_linux.tar.xz
解压
tar -Jxf upx-3.96-amd64_linux.tar.xz
进入upx文件夹，赋予执行权限
chmod +x upx
将upx相关文件复制到相关文件夹
cp ~/xxx/upx-3.96-amd64_linux/upx staging_dir/host/bin
```
更新默认的smartdns版本
```
# HASH值在项目查看 https://github.com/pymumu/smartdns.git
sed -i 's/1.2022.37/1.2022.37.2/g' feeds/packages/net/smartdns/Makefile
sed -i 's/5a2559f0648198c290bb8839b9f6a0adab8ebcdc/64e5b326cc53df1fec680cfa28ceec5d8a36fcbc/g' feeds/packages/net/smartdns/Makefile
sed -i 's/^PKG_MIRROR_HASH/#&/' feeds/packages/net/smartdns/Makefile

# 安装smartdns（必选）
git clone -b lede https://github.com/pymumu/luci-app-smartdns.git package/luci-app-smartdns
# git clone https://github.com/pymumu/smartdns.git package/smartdns
```
