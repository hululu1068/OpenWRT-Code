#!/usr/bin/lua
-- Alternative for OpenWrt's /sbin/wifi.
-- Copyright Not Reserved.
-- Hua Shao <nossiac@163.com>

package.path = '/lib/wifi/?.lua;' .. package.path

local vif_prefix = {"ra", "rai", "rae", "rax", "ray", "raz"}

local function esc(x)
    return (x:gsub('%%', '%%%%')
             :gsub('%^', '%%^')
             :gsub('%$', '%%$')
             :gsub('%(', '%%(')
             :gsub('%)', '%%)')
             :gsub('%.', '%%.')
             :gsub('%[', '%%[')
             :gsub('%]', '%%]')
             :gsub('%*', '%%*')
             :gsub('%+', '%%+')
             :gsub('%-', '%%-')
             :gsub('%?', '%%?'))
end

local function netdev_exists(ifname)
    local f = io.open("/sys/class/net/" .. ifname, "r")
    if f then
        f:close()
        return true
    end
    return false
end

local function ifup(ifname)
    if netdev_exists(ifname) then
        os.execute("ifconfig " .. ifname .. " up")
    end
end

local function ifdown(ifname)
    if netdev_exists(ifname) then
        os.execute("ifconfig " .. ifname .. " down")
    end
end

local function addif_lan(ifname)
    if netdev_exists(ifname) then
        os.execute("brctl addif br-lan " .. ifname)
    end
end

function add_vif_into_lan(vif)
    local mtkwifi = require("mtkwifi")
end

function mt7615_up(devname)
    local nixio = require("nixio")

    nixio.syslog("debug", "mt7615_up called!")

    ifup("ra0")
    ifup("apcli0")
    ifup("rai0")
    ifup("apclii0")

    addif_lan("ra0")
    addif_lan("rai0")

    os.execute("rm -rf /tmp/mtk/wifi/mt7615*.need_reload")
end

function mt7615_down(devname)
    local nixio = require("nixio")

    nixio.syslog("debug", "mt7615_down called!")

    ifdown("ra0")
    ifdown("apcli0")
    ifdown("rai0")
    ifdown("apclii0")

    os.execute("rm -rf /tmp/mtk/wifi/mt7615*.need_reload")
end

function mt7615_reload(devname)
    mt7615_down(devname)
    mt7615_up(devname)
end

function mt7615_restart(devname)
    mt7615_down(devname)
    os.execute("rmmod mt_wifi")
    os.execute("modprobe mt_wifi")
    mt7615_up(devname)
end

function mt7615_reset(devname)
    local nixio = require("nixio")
    local mtkwifi = require("mtkwifi")

    nixio.syslog("debug", "mt7615_reset called!")

    if mtkwifi.exists("/rom/etc/wireless/mt7615/") then
        os.execute("rm -rf /etc/wireless/mt7615/")
        os.execute("cp -rf /rom/etc/wireless/mt7615/ /etc/wireless/")
        mt7615_reload(devname)
    else
        nixio.syslog("debug", "mt7615_reset: /rom/etc/wireless/mt7615/ missing, unable to reset!")
    end
end

function mt7615_status(devname)
    return wifi_common_status()
end

function mt7615_detect(devname)
    local nixio = require("nixio")
    local mtkwifi = require("mtkwifi")

    nixio.syslog("debug", "mt7615_detect called!")

    for _, dev in ipairs(mtkwifi.get_all_devs()) do
        local relname = string.format("%s%d%d", dev.maindev, dev.mainidx, dev.subidx)
        print([[
config wifi-device ]] .. relname .. "\n" .. [[
    option type mt7615
    option vendor ralink
]])
        for _, vif in ipairs(dev.vifs) do
            print([[
config wifi-iface
    option device ]] .. relname .. "\n" .. [[
    option ifname ]] .. vif.vifname .. "\n" .. [[
    option network lan
    option mode ap
    option ssid ]] .. vif.__ssid .. "\n")
        end
    end
end
