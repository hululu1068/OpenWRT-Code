![OpenWrt logo](include/logo.png)

OpenWrt V21.02.3官方稳定版源码  根据个人需要修改了自定义配置，添加了常用插件  
官方仓库地址 https://github.com/openwrt/openwrt.git  
version `r16554-1d4dea6d4f`

## Ubuntu22.04编译工具
官方建议的工具
https://openwrt.org/docs/guide-developer/toolchain/install-buildsystem
```
sudo apt update
sudo apt install build-essential gawk gcc-multilib flex git gettext libncurses5-dev libssl-dev python3-distutils rsync unzip zlib1g-dev qemu-utils -y
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

## 添加三方插件
```
# 添加到'openwrt'目录下的'feeds.conf.default'文件中
src-git kenzo https://github.com/kenzok8/openwrt-packages
src-git small https://github.com/kenzok8/small
```

## 常用插件
```
# PassWall  
git clone -b packages https://github.com/xiaorouji/openwrt-passwall.git openwrt-passwall
git clone -b luci https://github.com/xiaorouji/openwrt-passwall.git luci-passwall
```
```
# PassWall2
git clone https://github.com/xiaorouji/openwrt-passwall2.git luci-passwall2
```
```
# SSR Plus
git clone --depth=1 https://github.com/fw876/helloworld.git ssr-plus

# 对于 OpenWrt 21.02 或更低版本,必须手动将 Golang 工具链升级到1.18或更高版本才能编译 Xray-core。
./scripts/feeds update packages
rm -rf feeds/packages/lang/golang
svn co https://github.com/openwrt/packages/branches/openwrt-22.03/lang/golang feeds/packages/lang/golang
```
```
# OpenClash
mkdir package/luci-app-openclash
cd package/luci-app-openclash
git init
git remote add -f origin https://github.com/vernesong/OpenClash.git
git config core.sparsecheckout true
echo "luci-app-openclash" >> .git/info/sparse-checkout
git pull --depth 1 origin master
git branch --set-upstream-to=origin/master master
```
```
# AdGuardHome
git clone https://github.com/rufengsuixing/luci-app-adguardhome.git
```
```
# luci-app-xray
git clone https://github.com/yichya/luci-app-xray.git
git clone https://github.com/Mitsuhaxy/luci-i18n-xray-zh-cn.git
```
```
# luci-app-aliddns
git clone https://github.com/pymumu/smartdns.git
```
```
# luci-app-dockerman
git clone https://github.com/lisaac/luci-app-dockerman.git
```
```
# luci-app-netdata
git clone https://github.com/sirpdboy/luci-app-netdata.git
```
```
# luci-theme-argon
git clone https://github.com/jerrykuku/luci-theme-argon.git
```
```
# luci-theme-atmaterial
git clone https://github.com/esirplayground/luci-theme-atmaterial-ColorIcon.git
```
```
# luci-theme-neobird
git clone https://github.com/thinktip/luci-theme-neobird.git
```

## 编译常见问题
开启ipv6支持
```
make menuconfig——extra packages——ipv6helper
make menuconfig——NetWork——Firewall——ip6tables——ip6tables-extra & ip6tables-mod-nat
```
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

安装smartdns（可选）
git clone -b lede https://github.com/pymumu/luci-app-smartdns.git package/luci-app-smartdns
# git clone https://github.com/pymumu/smartdns.git package/smartdns
```
---
官方懒人脚本  
可执行如下命令，一次性下载smartdns以及luci-app-smartdns。
下列命令可采用复制粘贴的方式执行。

注意事项：

执行下列命令时，需要确保当前路径为openwrt代码路径。
确保执行过./scripts/feeds进行更新。

```
WORKINGDIR="`pwd`/feeds/packages/net/smartdns"
mkdir $WORKINGDIR -p
rm $WORKINGDIR/* -fr
wget https://github.com/pymumu/openwrt-smartdns/archive/master.zip -O $WORKINGDIR/master.zip
unzip $WORKINGDIR/master.zip -d $WORKINGDIR
mv $WORKINGDIR/openwrt-smartdns-master/* $WORKINGDIR/
rmdir $WORKINGDIR/openwrt-smartdns-master
rm $WORKINGDIR/master.zip

LUCIBRANCH="master" #更换此变量
WORKINGDIR="`pwd`/feeds/luci/applications/luci-app-smartdns"
mkdir $WORKINGDIR -p
rm $WORKINGDIR/* -fr
wget https://github.com/pymumu/luci-app-smartdns/archive/${LUCIBRANCH}.zip -O $WORKINGDIR/${LUCIBRANCH}.zip
unzip $WORKINGDIR/${LUCIBRANCH}.zip -d $WORKINGDIR
mv $WORKINGDIR/luci-app-smartdns-${LUCIBRANCH}/* $WORKINGDIR/
rmdir $WORKINGDIR/luci-app-smartdns-${LUCIBRANCH}
rm $WORKINGDIR/${LUCIBRANCH}.zip

./scripts/feeds install -a
make menuconfig
```
---
修改默认 IP（可选）
```
sed -i 's/192.168.1.1/192.168.123.1/g' package/base-files/files/bin/config_generate
```
设置密码为空（可选）
```
sed -i 's@.*CYXluq4wUazHjmCDBCqXF*@#&@g' package/lean/default-settings/files/zzz-default-settings
```
更改Linux内核（可选）
```
sed -i 's/KERNEL_PATCHVER:=5.15/KERNEL_PATCHVER:=5.19/g' target/linux/x86/Makefile
```
修改默认主题（LEDE）
```
lede/feeds/luci/collections/luci/Makefile文件更改默认主题
lede/feeds/luci/collections/luci-ssl-nginx/Makefile
lede/feeds/luci/collections/luci-ssl-openssl/Makefile
这三个文件都要修改默认主题名字，不然后面编译可能会报错
```
旁路由模式，如使用`xtls-rprx-splice`流控模式，建议关闭系统的`ip转发`   
参见https://github.com/XTLS/Xray-core/discussions/59
```
vi /etc/sysctl.d/10-default.conf
# net.ipv4.ip_forward=1  //注释掉
# net.ipv6.conf.all.forwarding=1  //注释掉
:wq
sysctl -p /etc/sysctl.d/10-default.conf 或者重启
```

---
## 常用插件对照
以下是全部：           注：应用后面标记 “ * ” 为最近新添加；标记“ ! ”与其他插件依赖或冲突。
-----------------------------------------------------------------------------------------
LuCI ---> Applications ---> luci-app-adbyby-plus   #广告屏蔽大师Plus +
LuCI ---> Applications ---> luci-app-arpbind  #IP/MAC绑定
LuCI ---> Applications ---> luci-app-autoreboot  #支持计划重启
LuCI ---> Applications ---> luci-app-ddns   #动态域名 DNS（集成阿里DDNS客户端）
LuCI ---> Applications ---> luci-app-filetransfer  #文件传输（可web安装ipk包）
LuCI ---> Applications ---> luci-app-firewall   #添加防火墙
LuCI ---> Applications ---> luci-app-nlbwmon   #网络带宽监视器
LuCI ---> Applications ---> luci-app-ramfree  #释放内存
LuCI ---> Applications ---> luci-app-samba   #网络共享（Samba）
-------------------------------------------------------------------------------------------
LuCI ---> Applications ---> luci-app-ssr-plus   #SSR科学上网Plus+
    luci-app-ssr-plus ---> Include Shadowsocks Libev Client  #SS Libev客户端(轻量级)
    luci-app-ssr-plus ---> Include Shadowsocks Libev Server  #SS Libev服务端(轻量级)
    luci-app-ssr-plus ---> Include ShadowsocksR Libev Client  #SSR Libev客户端(轻量级)
    luci-app-ssr-plus ---> Include ShadowsocksR Libev Server  #SSR Libev服务端(轻量级)
    luci-app-ssr-plus ---> Include Include Shadowsocks Simple Obfs Plugin  #SS Simple-Obfs混淆代理(Nginx)
    luci-app-ssr-plus ---> Include Xray  #Xray代理(XTLS)
-------------------------------------------------------------------------------------------
LuCI ---> Applications ---> luci-app-turboacc   #Turbo ACC 网络加速(支持 Fast Path 或者 硬件 NAT)
LuCI ---> Applications ---> luci-app-unblockmusic  #解锁网易云灰色歌曲3合1新版本
LuCI ---> Applications ---> luci-app-upnp   #通用即插即用UPnP（端口自动转发）
LuCI ---> Applications ---> luci-app-vlmcsd  #KMS服务器设置
LuCI ---> Applications ---> luci-app-wol   #WOL网络唤醒
LuCI ---> Applications ---> luci-app-zerotier  #ZeroTier内网穿透
以下是全部：           注：应用后面标记 “ * ” 为最近新添加；标记“ ! ”与其他插件依赖或冲突。
------------------------------------------------------------------------------------------------------------
LuCI ---> Applications ---> luci-app-accesscontrol  #访问时间控制
LuCI ---> Applications ---> luci-app-adblock   #ADB广告过滤
LuCI ---> Applications ---> luci-app-adbyby-plus  #广告屏蔽大师Plus +
LuCI ---> Applications ---> luci-app-adguardhome  #AdGuard home广告过滤（Le库以外的插件）
LuCI ---> Applications ---> luci-app-advanced-reboot  #Linksys高级重启
LuCI ---> Applications ---> luci-app-advancedsetting  #系统高级设置（Le库以外的插件）
LuCI ---> Applications ---> luci-app-ahcp  #Ad-Hoc配置协议(AHCP) ipv6 and 双栈 自动配置协议 !
LuCI ---> Applications ---> luci-app-airplay2   #Apple AirPlay2 无损音频接收服务器
LuCI ---> Applications ---> luci-app-aliyundrive-webdav  #阿里云盘 WebDAV 服务
LuCI ---> Applications ---> luci-app-amule  #aMule下载工具 !
LuCI ---> Applications ---> luci-app-argon-config  #Argon主题配置插件（Le库以外的插件）
LuCI ---> Applications ---> luci-app-aria2 # Aria2下载工具
LuCI ---> Applications ---> luci-app-arpbind  #IP/MAC绑定
LuCI ---> Applications ---> luci-app-asterisk  #支持Asterisk电话服务器
LuCI ---> Applications ---> luci-app-attendedsysupgrade  #固件更新升级相关
LuCI ---> Applications ---> luci-app-autoreboot  #支持计划重启
LuCI ---> Applications ---> luci-app-baidupcs-web  #百度网盘管理
LuCI ---> Applications ---> luci-app-bcp38  #BCP38网络入口过滤（不确定）
LuCI ---> Applications ---> luci-app-bird1-ipv4  #对Bird1-ipv4的支持
LuCI ---> Applications ---> luci-app-bird1-ipv6  #对Bird1-ipv6的支持
LuCI ---> Applications ---> luci-app-bmx6  #BMX6路由协议
LuCI ---> Applications ---> luci-app-cifs-mount   #CIFS/SMB挂载设置
LuCI ---> Applications ---> luci-app-cifsd  #CIFS/SMB网络共享
LuCI ---> Applications ---> luci-app-cjdns  #加密IPV6网络相关
LuCI ---> Applications ---> luci-app-clamav  #ClamAV杀毒软件
LuCI ---> Applications ---> luci-app-clash  #Clash客户端（Le库以外的插件）
LuCI ---> Applications ---> luci-app-commands  #Shell命令模块
LuCI ---> Applications ---> luci-app-cshark  #CloudShark捕获工具
LuCI ---> Applications ---> luci-app-dawn  #分布式AP管理程序
LuCI ---> Applications ---> luci-app-ddns   #动态域名 DNS（集成阿里DDNS客户端）
LuCI ---> Applications ---> luci-app-diag-core   #core诊断工具
LuCI ---> Applications ---> luci-app-diskman   #磁盘管理工具
    luci-app-diskman ---> Include btrfs-progs   #新型的写时复制 (COW)
    luci-app-diskman ---> Include lsblk   #lsblk命令 用于列出所有可用块设备的信息
    luci-app-diskman ---> Include mdadm   #mdadm命令 用于创建、管理、监控RAID设备的工具
LuCI ---> Applications ---> luci-app-dnscrypt-proxy  #DNSCrypt解决DNS污染
LuCI ---> Applications ---> luci-app-dnsfilter  #DNSFilter基于DNS的广告过滤
LuCI ---> Applications ---> luci-app-dnsforwarder  #DNSForwarder防DNS污染
LuCI ---> Applications ---> luci-app-docker  #Docker容器(dockerman更名为docker)
LuCI ---> Applications ---> luci-app-dump1090  #民航无线频率（不确定）
LuCI ---> Applications ---> luci-app-dynapoint  #DynaPoint（未知）
LuCI ---> Applications ---> luci-app-e2guardian   #Web内容过滤器
LuCI ---> Applications ---> luci-app-easymesh   #简单MESH(可有线+无线回程)
LuCI ---> Applications ---> luci-app-eqos  #基于IP地址限速（Le库以外的插件）
LuCI ---> Applications ---> luci-app-familycloud   #家庭云盘
LuCI ---> Applications ---> luci-app-fileassistant   #文件管理助手（Le库以外的插件）
LuCI ---> Applications ---> luci-app-filetransfer  #文件传输（可web安装ipk包）
LuCI ---> Applications ---> luci-app-firewall   #添加防火墙
LuCI ---> Applications ---> luci-app-frpc   #内网穿透Frp客户端
LuCI ---> Applications ---> luci-app-frps   #内网穿透Frp服务端
LuCI ---> Applications ---> luci-app-fwknopd  #Firewall Knock Operator服务器
LuCI ---> Applications ---> luci-app-guest-wifi   #WiFi访客网络
LuCI ---> Applications ---> luci-app-go-aliyundrive-webdav   #阿里云盘webdav协议(文件管理/同步等)  *
LuCI ---> Applications ---> luci-app-gost  #隐蔽的https代理（Le库以外的插件）
LuCI ---> Applications ---> luci-app-haproxy-tcp   #HAProxy负载均衡-TCP
LuCI ---> Applications ---> luci-app-hd-idle  #硬盘休眠
LuCI ---> Applications ---> luci-app-hnet  #Homenet Status家庭网络控制协议
LuCI ---> Applications ---> luci-app-https-dns-proxy  #通过HTTPS代理为DNS提供Web UI
LuCI ---> Applications ---> luci-app-ipsec-vpnd  #VPN服务器 IPSec
LuCI ---> Applications ---> luci-app-jd-dailybonus  #京东签到服务
LuCI ---> Applications ---> luci-app-kodexplorer  #KOD可道云私人网盘（与vnStat冲突 ! ）
LuCI ---> Applications ---> luci-app-lxc   #LXC容器管理
LuCI ---> Applications ---> luci-app-minidlna   #完全兼容DLNA / UPnP-AV客户端的服务器软件
LuCI ---> Applications ---> luci-app-mjpg-streamer   #兼容Linux-UVC的摄像头程序
LuCI ---> Applications ---> luci-app-music-remote-center   #PCHiFi 数字转盘遥控
LuCI ---> Applications ---> luci-app-mwan3   #MWAN3负载均衡
LuCI ---> Applications ---> luci-app-mwan3helper   #MWAN3分流助手
LuCI ---> Applications ---> luci-app-n2n_v2   #N2N内网穿透 N2N v2 VPN服务
LuCI ---> Applications ---> luci-app-netdata  #Netdata实时监控（图形化）
LuCI ---> Applications ---> luci-app-nfs   #NFS网络共享
LuCI ---> Applications ---> luci-app-nft-qos  #QOS流控 Nftables版
LuCI ---> Applications ---> luci-app-nlbwmon   #网络带宽监视器
LuCI ---> Applications ---> luci-app-noddos  #NodDOS Clients 阻止DDoS攻击
LuCI ---> Applications ---> luci-app-nps   #内网穿透nps
LuCI ---> Applications ---> luci-app-ntpc   #NTP时间同步服务器
LuCI ---> Applications ---> luci-app-ocserv  #OpenConnect VPN服务
LuCI ---> Applications ---> luci-app-olsr  #OLSR配置和状态模块
LuCI ---> Applications ---> luci-app-olsr-services  #OLSR服务器
LuCI ---> Applications ---> luci-app-olsr-viz   #OLSR可视化
LuCI ---> Applications ---> luci-app-openclash  #运行在OpenWrt上的Clash代理客户端（Le库以外的插件）
LuCI ---> Applications ---> luci-app-openvpn  #OpenVPN客户端
LuCI ---> Applications ---> luci-app-openvpn-server  #易于使用的OpenVPN服务器 Web-UI
LuCI ---> Applications ---> luci-app-p910nd   #打印服务器模块
LuCI ---> Applications ---> luci-app-pagekitec   #Pagekitec内网穿透客户端
LuCI ---> Applications ---> luci-app-passwall  #科学上网（Li大佬插件）
    Configuration ---> Include Brook  #Brook代理(跨平台强加密且不可检测代理)
    Configuration ---> Include ChinaDNS-NG  #防污染DNS服务
    Configuration ---> Include Haproxy  #HAProxy  #HAProxy负载均衡
    Configuration ---> Include Hysteria  #Hysteria双边加速工具
    Configuration ---> Include Kcptun  #Kcptun双边加速工具
    Configuration ---> Include NaiveProxy  #NaiveProxy代理(Chrome网络堆栈伪装流量)
    Configuration ---> Include PDNSD  #DNS服务器
    Configuration ---> Include Shadowsocks Libev Client  #SS Libev客户端(轻量级)
    Configuration ---> Include Shadowsocks Libev Server  #SS Libev服务端(轻量级)
    Configuration ---> Include Shadowsocks Rust Client  #SS Rust客户端(负载均衡/探测延迟)
    Configuration ---> Include ShadowsocksR Libev Client  #SSR Libev客户端(轻量级)
    Configuration ---> Include ShadowsocksR Libev Server  #SSR Libev服务端(轻量级)
    Configuration ---> Include Simple-Obfs (Shadowsocks plugin)  #simple-Obfs简单混淆工具(Nginx)
    Configuration ---> Include Trojan_GO  #Trojan_GO代理(直接模仿协议HTTPS)
    Configuration ---> Include Trojan_Plus  #Trojan_Plus代理(直接模仿协议HTTPS)
    Configuration ---> Include V2ray  #V2Ray代理
    Configuration ---> Include v2ray-plugin (Shadowsocks plugin)  #SS V2ray插件(WebSocket+TLS )
    Configuration ---> Include Xray  #Xray代理(XTLS)
    Configuration ---> Include Xray-Plugin (Shadowsocks Plugin)  #SS Xray插件(WebSocket+TLS )   *
LuCI ---> Applications ---> luci-app-polipo  #Polipo代理(是一个小型且快速的网页缓存代理)
LuCI ---> Applications ---> luci-app-pppoe-relay  #PPPoE NAT穿透 点对点协议（PPP）
LuCI ---> Applications ---> luci-app-pptp-server  #VPN服务器 PPTP
LuCI ---> Applications ---> luci-app-privoxy  #Privoxy网络代理(带过滤无缓存)
LuCI ---> Applications ---> luci-app-ps3netsrv  #PS3 NET服务器(用于加载蓝光/游戏ISO/PKG)
LuCI ---> Applications ---> luci-app-pushbot  #全能推送(钉钉推送,企业微信推送,Bark,PushPlus推送)
LuCI ---> Applications ---> luci-app-qbittorrent  #BT下载工具(qBittorrent)
    Build Version Selection (Static Build)  ---> Static Build  #选择静态编译版本
    Build Version Selection (Static Build)  ---> Dynamic Build  #选择动态编译版本
LuCI ---> Applications ---> luci-app-qos   #流量服务质量(QoS)流控
LuCI ---> Applications ---> luci-app-radicale   #CalDAV/CardDAV同步工具
LuCI ---> Applications ---> luci-app-ramfree  #释放内存
LuCI ---> Applications ---> luci-app-rclone  #命令行云端同步工具
    Include rclone-webui  #Rclone界面
    Include rclone-ng (another webui)  #Rclone另一个界面
LuCI ---> Applications ---> luci-app-rp-pppoe-server  #Roaring Penguin PPPoE Server 服务器
LuCI ---> Applications ---> luci-app-samba   #网络共享（Samba）
LuCI ---> Applications ---> luci-app-samba4   #网络共享（Samba4）
LuCI ---> Applications ---> luci-app-serverchan   #微信/Telegram推送的插件
LuCI ---> Applications ---> luci-app-shadowsocks-libes  #SS-libev服务端
LuCI ---> Applications ---> luci-app-shairplay  #支持AirPlay功能
LuCI ---> Applications ---> luci-app-siitwizard  #SIIT配置向导  SIIT-Wizzard
LuCI ---> Applications ---> luci-app-simple-adblock  #简单的广告拦截
LuCI ---> Applications ---> luci-app-softethervpn  #SoftEther VPN服务器  NAT穿透
LuCI ---> Applications ---> luci-app-splash  #Client-Splash是无线MESH网络的一个热点认证系统
LuCI ---> Applications ---> luci-app-sqm  #流量智能队列管理（QOS）
LuCI ---> Applications ---> luci-app-squid   #Squid代理服务器
LuCI ---> Applications ---> luci-app-ssr-plus   #SSR科学上网Plus+（Le大佬插件）
    Include libustream-ssl  ---> Include libustream-wolfssl  #选择wolfSSL库(传输层安全协议)
    Include libustream-ssl  ---> Include libustream-openssl  #选择OpenSSL库(传输层安全协议)
    luci-app-ssr-plus ---> Include Kcptun  #Kcptun双边加速工具
    luci-app-ssr-plus ---> Include NaiveProxy  #NaiveProxy代理(Chrome网络堆栈伪装流量)
    luci-app-ssr-plus ---> Include Redsocks2  #Redsocks2代理(透明TCP定向Socks/HTTPS代理服务器)
    luci-app-ssr-plus ---> Include Shadowsocks Libev Client  #SS Libev客户端(轻量级)
    luci-app-ssr-plus ---> Include Shadowsocks Libev Server  #SS Libev服务端(轻量级)
    luci-app-ssr-plus ---> Include Shadowsocks Rust Client  #SS Rust客户端(负载均衡/探测延迟)
    luci-app-ssr-plus ---> Include Shadowsocks Rust Server  #SS Rust服务端(负载均衡/探测延迟)
    luci-app-ssr-plus ---> Include ShadowsocksR Libev Client  #SSR Libev客户端(轻量级)
    luci-app-ssr-plus ---> Include ShadowsocksR Libev Server  #SSR Libev服务端(轻量级)
    luci-app-ssr-plus ---> Include Simple-Obfs Plugin  #SS Simple-Obfs混淆代理(Nginx)
    luci-app-ssr-plus ---> Include Trojan  #Trojan代理(直接模仿协议HTTPS)
    luci-app-ssr-plus ---> Include Shadowsocks V2ray Plugin  #SS V2ray代理(WebSocket+TLS )
    luci-app-ssr-plus ---> Include Xray  #Xray代理(XTLS)
LuCI ---> Applications ---> luci-app-ssrserver-python  #ShadowsocksR Python服务器
LuCI ---> Applications ---> luci-app-statistics  #流量监控工具
LuCI ---> Applications ---> luci-app-syncdial  #多拨虚拟网卡（原macvlan）
LuCI ---> Applications ---> luci-app-tinyproxy  #Tinyproxy是 HTTP(S)代理服务器
LuCI ---> Applications ---> luci-app-transmission   #BT下载工具
LuCI ---> Applications ---> luci-app-travelmate  #旅行路由器
LuCI ---> Applications ---> luci-app-ttyd   #网页终端命令行
LuCI ---> Applications ---> luci-app-turboacc   #Turbo ACC 网络加速(支持 Fast Path 或者 硬件 NAT)
    luci-app-turboacc ---> Include Shortcut-FE  #Shortcut-FE 流量分载
    luci-app-turboacc ---> Include BBR CCA  #BBR拥塞控制算法提升TCP网络性能
    luci-app-turboacc ---> Include DNSForwarder  #DNS防污染 Forwarder
    luci-app-turboacc ---> Include DNSProxy  #DNS防污染 Proxy
LuCI ---> Applications ---> luci-app-udpxy  #udpxy做组播服务器
LuCI ---> Applications ---> luci-app-uhttpd  #uHTTPd Web服务器
LuCI ---> Applications ---> luci-app-unblockmusic  #解锁网易云灰色歌曲3合1新版本
    UnblockNeteaseMusic Golang Version  #Golang版本
    UnblockNeteaseMusic NodeJS Version  #NodeJS版本
LuCI ---> Applications ---> luci-app-unbound  #Unbound DNS解析器
LuCI ---> Applications ---> luci-app-upnp   #通用即插即用UPnP（端口自动转发）
LuCI ---> Applications ---> luci-app-usb-printer  #USB 打印服务器
LuCI ---> Applications ---> luci-app-uugamebooster  #UU网游加速器
LuCI ---> Applications ---> luci-app-v2ray-server   #V2Ray 服务器
LuCI ---> Applications ---> luci-app-verysync  #微力同步
LuCI ---> Applications ---> luci-app-vlmcsd  #KMS服务器设置
LuCI ---> Applications ---> luci-app-vnstat   #vnStat网络监控（图表）（与kodexplorer冲突 ! ）
LuCI ---> Applications ---> luci-app-vpnbypass  #VPN BypassWebUI  绕过VPN设置
LuCI ---> Applications ---> luci-app-vsftpd  #FTP服务器
LuCI ---> Applications ---> luci-app-vssr  #VSSR科学上网（je大佬插件）
    luci-app-vssr ---> Include Xray  #Xray代理(XTLS)
    luci-app-vssr ---> Include Trojan  #Trojan代理(直接模仿协议HTTPS)
    luci-app-vssr ---> Include Kcptun  #Kcptun双边加速工具
    luci-app-vssr ---> Include Shadowsocks Xray Plugin  #SS Xray代理
    luci-app-vssr ---> Include ShadowsocksR Libev Server  #SSR Libev服务端(轻量级)
LuCI ---> Applications ---> luci-app-watchcat  #断网检测功能与定时重启
LuCI ---> Applications ---> luci-app-webadmin  #Web管理页面设置
LuCI ---> Applications ---> luci-app-wifischedule  #WiFi 计划
LuCI ---> Applications ---> luci-app-wireguard  #VPN服务器 WireGuard状态
LuCI ---> Applications ---> luci-app-wireless-regdb  #WiFi无线
LuCI ---> Applications ---> luci-app-wol   #WOL网络唤醒
LuCI ---> Applications ---> luci-app-wrtbwmon  #实时流量监测
LuCI ---> Applications ---> luci-app-xlnetacc  #迅雷快鸟
LuCI ---> Applications ---> luci-app-zerotier  #ZeroTier内网穿透
----------------------------------------------------------------------------------------
