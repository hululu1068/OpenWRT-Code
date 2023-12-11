DEVICE_VARS += TPLINK_HWID TPLINK_HWREV TPLINK_FLASHLAYOUT TPLINK_HEADER_VERSION

define Build/spi-loader-okli-compile
	rm -rf $@.spi-loader-okli
	$(CP) spi-loader $@.spi-loader-okli
	$(MAKE) -C $@.spi-loader-okli \
		CROSS_COMPILE="$(TARGET_CROSS)" CONFIG="$(DEVICE_NAME)"
	cp "$@.spi-loader-okli/out/uImage" "$@"
	rm -rf $@.spi-loader-okli
endef

define Build/spi-loader-okli
	cat $(KDIR)/loader-$(1) "$@" > "$@.new"
	mv "$@.new" "$@"
endef

define Device/aerohive_br200-wp
  DEVICE_VENDOR := Aerohive
  DEVICE_MODEL := BR200-WP
  BLOCKSIZE := 128k
  KERNEL_NAME := simpleImage.br200-wp
  KERNEL := kernel-bin | uImage none
  KERNEL_INITRAMFS := kernel-bin | uImage none
  KERNEL_ENTRY := 0x1000000
  KERNEL_LOADADDR := 0x1000000
  KERNEL_SIZE := 8m
  IMAGES := fdt.bin sysupgrade.bin
  IMAGE/fdt.bin := append-dtb
  IMAGE/sysupgrade.bin := append-dtb | pad-to 256k | check-size 256k | \
	append-uImage-fakehdr ramdisk | pad-to 256k | check-size 512k | \
	append-rootfs | pad-rootfs $$(BLOCKSIZE) | pad-to 41216k | check-size 41216k | \
	append-kernel | append-metadata
  IMAGE_SIZE = 63m
endef
TARGET_DEVICES += aerohive_br200-wp

define Device/enterasys_ws-ap3715i
  DEVICE_VENDOR := Enterasys
  DEVICE_MODEL := WS-AP3715i
  BLOCKSIZE := 64k
  KERNEL_NAME := simpleImage.ws-ap3715i
  KERNEL_ENTRY := 0x1000000
  KERNEL_LOADADDR := 0x1000000
  KERNEL = kernel-bin | lzma | uImage lzma
  IMAGES := sysupgrade.bin
  IMAGE/sysupgrade.bin := append-kernel | append-rootfs | pad-rootfs | append-metadata
endef
TARGET_DEVICES += enterasys_ws-ap3715i

define Device/tplink_tl-wdr4900-v1
  DEVICE_VENDOR := TP-Link
  DEVICE_MODEL := TL-WDR4900
  DEVICE_VARIANT := v1
  DEVICE_COMPAT_VERSION := 1.1
  DEVICE_COMPAT_MESSAGE := Config cannot be migrated from swconfig to DSA
  TPLINK_HEADER_VERSION := 1
  TPLINK_HWID := 0x49000001
  TPLINK_HWREV := 1
  TPLINK_FLASHLAYOUT := 16Mppc
  KERNEL_NAME := simpleImage.tl-wdr4900-v1
  KERNEL_INITRAMFS :=
  KERNEL := kernel-bin | uImage none -M 0x4f4b4c49 | spi-loader-okli $(1)
  KERNEL_ENTRY := 0x1000000
  KERNEL_LOADADDR := 0x1000000
  SUPPORTED_DEVICES += tl-wdr4900-v1
  COMPILE := loader-$(1)
  COMPILE/loader-$(1) := spi-loader-okli-compile
  ARTIFACTS := fdt.bin
  ARTIFACT/fdt.bin := append-dtb
  IMAGES := factory.bin sysupgrade.bin
  IMAGE/sysupgrade.bin := tplink-v1-image sysupgrade | append-metadata
  IMAGE/factory.bin := tplink-v1-image factory
endef
TARGET_DEVICES += tplink_tl-wdr4900-v1

define Device/watchguard_firebox-t10
  DEVICE_VENDOR := Watchguard
  DEVICE_MODEL := Firebox T10
  DEVICE_PACKAGES := kmod-rtc-s35390a kmod-eeprom-at24
  KERNEL = kernel-bin | gzip | fit gzip $(KDIR)/image-$$(DEVICE_DTS).dtb
  IMAGES := sysupgrade.bin
  IMAGE/sysupgrade.bin := sysupgrade-tar | append-metadata
endef
TARGET_DEVICES += watchguard_firebox-t10

define Device/sophos_red-15w-rev1
  DEVICE_VENDOR := Sophos
  DEVICE_MODEL := RED 15w
  DEVICE_VARIANT := Rev.1
  # Original firmware uses a dedicated DTB-partition.
  # The bootloader however supports FIT-images.
  KERNEL = kernel-bin | gzip | fit gzip $(KDIR)/image-$$(DEVICE_DTS).dtb
  IMAGES := sysupgrade.bin
  IMAGE/sysupgrade.bin := sysupgrade-tar | append-metadata
endef
TARGET_DEVICES += sophos_red-15w-rev1
