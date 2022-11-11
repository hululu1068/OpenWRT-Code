# OpenWRT-常用软件包

#### ⚠ `OpenWrt 21.02` or 以前的版本需要升级`Golang`到`1.18`才能编译`Xray-core`
You have to manually upgrade Golang toolchain to [1.18](https://github.com/openwrt/packages/tree/openwrt-22.03/lang/golang) or higher to compile Xray-core.

e.g.:

```bash
./scripts/feeds update packages
rm -rf feeds/packages/lang/golang
svn co https://github.com/openwrt/packages/branches/openwrt-22.03/lang/golang feeds/packages/lang/golang
```

#### Note

如果是官方包可能需要添加以下组件

- [dns2socks](https://github.com/immortalwrt/packages/tree/master/net/dns2socks)
- [microsocks](https://github.com/immortalwrt/packages/tree/master/net/microsocks)
- [ipt2socks](https://github.com/immortalwrt/packages/tree/master/net/ipt2socks)
- [redsocks2](https://github.com/immortalwrt/packages/tree/master/net/redsocks2)

可以使用 `svn` 检出  
e.g.:

```bash
mkdir -p package/helloworld
for i in "dns2socks" "microsocks" "ipt2socks" "pdnsd-alt" "redsocks2"; do \
  svn checkout "https://github.com/immortalwrt/packages/trunk/net/$i" "package/helloworld/$i"; \
done
```
