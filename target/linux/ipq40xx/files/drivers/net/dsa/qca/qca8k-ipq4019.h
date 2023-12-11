/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Felix Fietkau <nbd@nbd.name>
 * Copyright (C) 2011-2012 Gabor Juhos <juhosg@openwrt.org>
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

#ifndef __QCA8K_H
#define __QCA8K_H

#include <linux/regmap.h>

#define QCA8K_NUM_PORTS					6
#define QCA8K_CPU_PORT					0
#define QCA8K_MAX_MTU					9000

#define QCA8K_BUSY_WAIT_TIMEOUT				2000

#define QCA8K_NUM_FDB_RECORDS				2048

#define QCA8K_PORT_VID_DEF				1

/* Global control registers */
#define QCA8K_REG_MASK_CTRL				0x000
#define   QCA8K_MASK_CTRL_REV_ID_MASK			GENMASK(7, 0)
#define   QCA8K_MASK_CTRL_REV_ID(x)			((x) >> 0)
#define   QCA8K_MASK_CTRL_DEVICE_ID_MASK		GENMASK(15, 8)
#define   QCA8K_MASK_CTRL_DEVICE_ID(x)			((x) >> 8)
#define QCA8K_REG_RGMII_CTRL				0x004
#define   QCA8K_RGMII_CTRL_RGMII_RXC			GENMASK(1, 0)
#define   QCA8K_RGMII_CTRL_RGMII_TXC			GENMASK(9, 8)
/* Some kind of CLK selection
 * 0: gcc_ess_dly2ns
 * 1: gcc_ess_clk
 */
#define   QCA8K_RGMII_CTRL_CLK				BIT(10)
#define   QCA8K_RGMII_CTRL_DELAY_RMII0			GENMASK(17, 16)
#define   QCA8K_RGMII_CTRL_INVERT_RMII0_REF_CLK		BIT(18)
#define   QCA8K_RGMII_CTRL_DELAY_RMII1			GENMASK(20, 19)
#define   QCA8K_RGMII_CTRL_INVERT_RMII1_REF_CLK		BIT(21)
#define   QCA8K_RGMII_CTRL_INVERT_RMII0_MASTER_EN	BIT(24)
#define   QCA8K_RGMII_CTRL_INVERT_RMII1_MASTER_EN	BIT(25)
#define QCA8K_REG_MODULE_EN				0x030
#define   QCA8K_MODULE_EN_MIB				BIT(0)
#define QCA8K_REG_MIB					0x034
#define   QCA8K_MIB_FLUSH				BIT(24)
#define   QCA8K_MIB_CPU_KEEP				BIT(20)
#define   QCA8K_MIB_BUSY				BIT(17)
#define QCA8K_GOL_MAC_ADDR0				0x60
#define QCA8K_GOL_MAC_ADDR1				0x64
#define QCA8K_MAX_FRAME_SIZE				0x78
#define QCA8K_REG_PORT_STATUS(_i)			(0x07c + (_i) * 4)
#define   QCA8K_PORT_STATUS_SPEED			GENMASK(1, 0)
#define   QCA8K_PORT_STATUS_SPEED_10			0
#define   QCA8K_PORT_STATUS_SPEED_100			0x1
#define   QCA8K_PORT_STATUS_SPEED_1000			0x2
#define   QCA8K_PORT_STATUS_TXMAC			BIT(2)
#define   QCA8K_PORT_STATUS_RXMAC			BIT(3)
#define   QCA8K_PORT_STATUS_TXFLOW			BIT(4)
#define   QCA8K_PORT_STATUS_RXFLOW			BIT(5)
#define   QCA8K_PORT_STATUS_DUPLEX			BIT(6)
#define   QCA8K_PORT_STATUS_LINK_UP			BIT(8)
#define   QCA8K_PORT_STATUS_LINK_AUTO			BIT(9)
#define   QCA8K_PORT_STATUS_LINK_PAUSE			BIT(10)
#define   QCA8K_PORT_STATUS_FLOW_AUTO			BIT(12)
#define QCA8K_REG_PORT_HDR_CTRL(_i)			(0x9c + (_i * 4))
#define   QCA8K_PORT_HDR_CTRL_RX_MASK			GENMASK(3, 2)
#define   QCA8K_PORT_HDR_CTRL_RX_S			2
#define   QCA8K_PORT_HDR_CTRL_TX_MASK			GENMASK(1, 0)
#define   QCA8K_PORT_HDR_CTRL_TX_S			0
#define   QCA8K_PORT_HDR_CTRL_ALL			2
#define   QCA8K_PORT_HDR_CTRL_MGMT			1
#define   QCA8K_PORT_HDR_CTRL_NONE			0
#define QCA8K_REG_SGMII_CTRL				0x0e0
#define   QCA8K_SGMII_EN_PLL				BIT(1)
#define   QCA8K_SGMII_EN_RX				BIT(2)
#define   QCA8K_SGMII_EN_TX				BIT(3)
#define   QCA8K_SGMII_EN_SD				BIT(4)
#define   QCA8K_SGMII_CLK125M_DELAY			BIT(7)
#define   QCA8K_SGMII_MODE_CTRL_MASK			(BIT(22) | BIT(23))
#define   QCA8K_SGMII_MODE_CTRL_BASEX			(0 << 22)
#define   QCA8K_SGMII_MODE_CTRL_PHY			(1 << 22)
#define   QCA8K_SGMII_MODE_CTRL_MAC			(2 << 22)

/* EEE control registers */
#define QCA8K_REG_EEE_CTRL				0x100
#define  QCA8K_REG_EEE_CTRL_LPI_EN(_i)			((_i + 1) * 2)

/* ACL registers */
#define QCA8K_REG_PORT_VLAN_CTRL0(_i)			(0x420 + (_i * 8))
#define   QCA8K_PORT_VLAN_CVID(x)			(x << 16)
#define   QCA8K_PORT_VLAN_SVID(x)			x
#define QCA8K_REG_PORT_VLAN_CTRL1(_i)			(0x424 + (_i * 8))
#define QCA8K_REG_IPV4_PRI_BASE_ADDR			0x470
#define QCA8K_REG_IPV4_PRI_ADDR_MASK			0x474

/* Lookup registers */
#define QCA8K_REG_ATU_DATA0				0x600
#define   QCA8K_ATU_ADDR2_S				24
#define   QCA8K_ATU_ADDR3_S				16
#define   QCA8K_ATU_ADDR4_S				8
#define QCA8K_REG_ATU_DATA1				0x604
#define   QCA8K_ATU_PORT_M				0x7f
#define   QCA8K_ATU_PORT_S				16
#define   QCA8K_ATU_ADDR0_S				8
#define QCA8K_REG_ATU_DATA2				0x608
#define   QCA8K_ATU_VID_M				0xfff
#define   QCA8K_ATU_VID_S				8
#define   QCA8K_ATU_STATUS_M				0xf
#define   QCA8K_ATU_STATUS_STATIC			0xf
#define QCA8K_REG_ATU_FUNC				0x60c
#define   QCA8K_ATU_FUNC_BUSY				BIT(31)
#define   QCA8K_ATU_FUNC_PORT_EN			BIT(14)
#define   QCA8K_ATU_FUNC_MULTI_EN			BIT(13)
#define   QCA8K_ATU_FUNC_FULL				BIT(12)
#define   QCA8K_ATU_FUNC_PORT_M				0xf
#define   QCA8K_ATU_FUNC_PORT_S				8
#define QCA8K_REG_VTU_FUNC0				0x610
#define   QCA8K_VTU_FUNC0_VALID				BIT(20)
#define   QCA8K_VTU_FUNC0_IVL_EN			BIT(19)
#define   QCA8K_VTU_FUNC0_EG_MODE_S(_i)			(4 + (_i) * 2)
#define   QCA8K_VTU_FUNC0_EG_MODE_MASK			3
#define   QCA8K_VTU_FUNC0_EG_MODE_UNMOD			0
#define   QCA8K_VTU_FUNC0_EG_MODE_UNTAG			1
#define   QCA8K_VTU_FUNC0_EG_MODE_TAG			2
#define   QCA8K_VTU_FUNC0_EG_MODE_NOT			3
#define QCA8K_REG_VTU_FUNC1				0x614
#define   QCA8K_VTU_FUNC1_BUSY				BIT(31)
#define   QCA8K_VTU_FUNC1_VID_S				16
#define   QCA8K_VTU_FUNC1_FULL				BIT(4)
#define QCA8K_REG_GLOBAL_FW_CTRL0			0x620
#define   QCA8K_GLOBAL_FW_CTRL0_CPU_PORT_EN		BIT(10)
#define QCA8K_REG_GLOBAL_FW_CTRL1			0x624
#define   QCA8K_GLOBAL_FW_CTRL1_IGMP_DP_S		24
#define   QCA8K_GLOBAL_FW_CTRL1_BC_DP_S			16
#define   QCA8K_GLOBAL_FW_CTRL1_MC_DP_S			8
#define   QCA8K_GLOBAL_FW_CTRL1_UC_DP_S			0
#define QCA8K_PORT_LOOKUP_CTRL(_i)			(0x660 + (_i) * 0xc)
#define   QCA8K_PORT_LOOKUP_MEMBER			GENMASK(6, 0)
#define   QCA8K_PORT_LOOKUP_VLAN_MODE			GENMASK(9, 8)
#define   QCA8K_PORT_LOOKUP_VLAN_MODE_NONE		(0 << 8)
#define   QCA8K_PORT_LOOKUP_VLAN_MODE_FALLBACK		(1 << 8)
#define   QCA8K_PORT_LOOKUP_VLAN_MODE_CHECK		(2 << 8)
#define   QCA8K_PORT_LOOKUP_VLAN_MODE_SECURE		(3 << 8)
#define   QCA8K_PORT_LOOKUP_STATE_MASK			GENMASK(18, 16)
#define   QCA8K_PORT_LOOKUP_STATE_DISABLED		(0 << 16)
#define   QCA8K_PORT_LOOKUP_STATE_BLOCKING		(1 << 16)
#define   QCA8K_PORT_LOOKUP_STATE_LISTENING		(2 << 16)
#define   QCA8K_PORT_LOOKUP_STATE_LEARNING		(3 << 16)
#define   QCA8K_PORT_LOOKUP_STATE_FORWARD		(4 << 16)
#define   QCA8K_PORT_LOOKUP_STATE			GENMASK(18, 16)
#define   QCA8K_PORT_LOOKUP_LEARN			BIT(20)
#define   QCA8K_PORT_LOOKUP_LOOPBACK	BIT(21)

#define QCA8K_REG_GLOBAL_FC_THRESH			0x800
#define   QCA8K_GLOBAL_FC_GOL_XON_THRES(x)		((x) << 16)
#define   QCA8K_GLOBAL_FC_GOL_XON_THRES_S		GENMASK(24, 16)
#define   QCA8K_GLOBAL_FC_GOL_XOFF_THRES(x)		((x) << 0)
#define   QCA8K_GLOBAL_FC_GOL_XOFF_THRES_S		GENMASK(8, 0)

#define QCA8K_REG_PORT_HOL_CTRL0(_i)			(0x970 + (_i) * 0x8)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI0_BUF		GENMASK(3, 0)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI0(x)		((x) << 0)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI1_BUF		GENMASK(7, 4)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI1(x)		((x) << 4)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI2_BUF		GENMASK(11, 8)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI2(x)		((x) << 8)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI3_BUF		GENMASK(15, 12)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI3(x)		((x) << 12)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI4_BUF		GENMASK(19, 16)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI4(x)		((x) << 16)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI5_BUF		GENMASK(23, 20)
#define   QCA8K_PORT_HOL_CTRL0_EG_PRI5(x)		((x) << 20)
#define   QCA8K_PORT_HOL_CTRL0_EG_PORT_BUF		GENMASK(29, 24)
#define   QCA8K_PORT_HOL_CTRL0_EG_PORT(x)		((x) << 24)

#define QCA8K_REG_PORT_HOL_CTRL1(_i)			(0x974 + (_i) * 0x8)
#define   QCA8K_PORT_HOL_CTRL1_ING_BUF			GENMASK(3, 0)
#define   QCA8K_PORT_HOL_CTRL1_ING(x)			((x) << 0)
#define   QCA8K_PORT_HOL_CTRL1_EG_PRI_BUF_EN		BIT(6)
#define   QCA8K_PORT_HOL_CTRL1_EG_PORT_BUF_EN		BIT(7)
#define   QCA8K_PORT_HOL_CTRL1_WRED_EN			BIT(8)
#define   QCA8K_PORT_HOL_CTRL1_EG_MIRROR_EN		BIT(16)

/* Pkt edit registers */
#define QCA8K_EGRESS_VLAN(x)				(0x0c70 + (4 * (x / 2)))

/* L3 registers */
#define QCA8K_HROUTER_CONTROL				0xe00
#define   QCA8K_HROUTER_CONTROL_GLB_LOCKTIME_M		GENMASK(17, 16)
#define   QCA8K_HROUTER_CONTROL_GLB_LOCKTIME_S		16
#define   QCA8K_HROUTER_CONTROL_ARP_AGE_MODE		1
#define QCA8K_HROUTER_PBASED_CONTROL1			0xe08
#define QCA8K_HROUTER_PBASED_CONTROL2			0xe0c
#define QCA8K_HNAT_CONTROL				0xe38

/* MIB registers */
#define QCA8K_PORT_MIB_COUNTER(_i)			(0x1000 + (_i) * 0x100)

/* IPQ4019 PSGMII PHY registers */
#define PSGMIIPHY_MODE_CONTROL				0x1b4
#define   PSGMIIPHY_MODE_ATHR_CSCO_MODE_25M		BIT(0)
#define PSGMIIPHY_TX_CONTROL				0x288
#define   PSGMIIPHY_TX_CONTROL_MAGIC_VALUE		0x8380
#define PSGMIIPHY_VCO_CALIBRATION_CONTROL_REGISTER_1	0x9c
#define   PSGMIIPHY_REG_PLL_VCO_CALIB_RESTART		BIT(14)
#define PSGMIIPHY_VCO_CALIBRATION_CONTROL_REGISTER_2	0xa0
#define   PSGMIIPHY_REG_PLL_VCO_CALIB_READY		BIT(0)

#define   QCA8K_PSGMII_CALB_NUM				100
#define   MII_QCA8075_SSTATUS				0x11
#define   QCA8075_PHY_SPEC_STATUS_LINK			BIT(10)
#define   QCA8075_MMD7_CRC_AND_PKTS_COUNT		0x8029
#define   QCA8075_MMD7_PKT_GEN_PKT_NUMB			0x8021
#define   QCA8075_MMD7_PKT_GEN_PKT_SIZE			0x8062
#define   QCA8075_MMD7_PKT_GEN_CTRL			0x8020
#define   QCA8075_MMD7_CNT_SELFCLR			BIT(1)
#define   QCA8075_MMD7_CNT_FRAME_CHK_EN			BIT(0)
#define   QCA8075_MMD7_PKT_GEN_START			BIT(13)
#define   QCA8075_MMD7_PKT_GEN_INPROGR			BIT(15)
#define   QCA8075_MMD7_IG_FRAME_RECV_CNT_HI		0x802a
#define   QCA8075_MMD7_IG_FRAME_RECV_CNT_LO		0x802b
#define   QCA8075_MMD7_IG_FRAME_ERR_CNT			0x802c
#define   QCA8075_MMD7_EG_FRAME_RECV_CNT_HI		0x802d
#define   QCA8075_MMD7_EG_FRAME_RECV_CNT_LO		0x802e
#define   QCA8075_MMD7_EG_FRAME_ERR_CNT			0x802f
#define   QCA8075_MMD7_MDIO_BRDCST_WRITE		0x8028
#define   QCA8075_MMD7_MDIO_BRDCST_WRITE_EN 		BIT(15)
#define   QCA8075_MDIO_BRDCST_PHY_ADDR			0x1f
#define   QCA8075_PKT_GEN_PKTS_COUNT			4096

enum {
	QCA8K_PORT_SPEED_10M = 0,
	QCA8K_PORT_SPEED_100M = 1,
	QCA8K_PORT_SPEED_1000M = 2,
	QCA8K_PORT_SPEED_ERR = 3,
};

enum qca8k_fdb_cmd {
	QCA8K_FDB_FLUSH	= 1,
	QCA8K_FDB_LOAD = 2,
	QCA8K_FDB_PURGE = 3,
	QCA8K_FDB_NEXT = 6,
	QCA8K_FDB_SEARCH = 7,
};

enum qca8k_vlan_cmd {
	QCA8K_VLAN_FLUSH = 1,
	QCA8K_VLAN_LOAD = 2,
	QCA8K_VLAN_PURGE = 3,
	QCA8K_VLAN_REMOVE_PORT = 4,
	QCA8K_VLAN_NEXT = 5,
	QCA8K_VLAN_READ = 6,
};

struct ar8xxx_port_status {
	int enabled;
};

struct qca8k_priv {
	struct regmap *regmap;
	struct mii_bus *bus;
	struct ar8xxx_port_status port_sts[QCA8K_NUM_PORTS];
	struct dsa_switch *ds;
	struct mutex reg_mutex;
	struct device *dev;
	struct dsa_switch_ops ops;
	unsigned int port_mtu[QCA8K_NUM_PORTS];

	/* IPQ4019 specific */
	struct regmap *psgmii;
	bool psgmii_calibrated;
	struct phy_device *psgmii_ethphy;
};

struct qca8k_mib_desc {
	unsigned int size;
	unsigned int offset;
	const char *name;
};

struct qca8k_fdb {
	u16 vid;
	u8 port_mask;
	u8 aging;
	u8 mac[6];
};

#endif /* __QCA8K_H */
