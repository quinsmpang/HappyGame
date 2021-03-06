-- Date: 2015-10
-- File: msg_cg_fairy.lua
-- Auth: generated by auto tool 'lazybone'
-- Desc: message define
--// 定义了客户端与游戏服务间的部分协议
--// 定义用户背包物品协议
--// 协议号分配：20600 ~ 20699


QueryFairyInfoReqBody = {
    ["name"] = "QueryFairyInfoReqBody",
    ["id"] = 20600,
}

QueryFairyInfoRespBody = {
    ["name"] = "QueryFairyInfoRespBody",
    ["id"] = 20601,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
        {"packagePillList", "FairyPill", "repeat"},
    },
}

InlayFairyPillReqBody = {
    ["name"] = "InlayFairyPillReqBody",
    ["id"] = 20602,
    ["attribs"] = {
        {"pillIndex", "uint32"},
    },
}

InlayFairyPillRespBody = {
    ["name"] = "InlayFairyPillRespBody",
    ["id"] = 20603,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
        {"roleInfo", "RoleDetailInfo"},
    },
}

DropFairyPillReqBody = {
    ["name"] = "DropFairyPillReqBody",
    ["id"] = 20604,
    ["attribs"] = {
        {"dishIndex", "uint32"},
    },
}

DropFairyPillRespBody = {
    ["name"] = "DropFairyPillRespBody",
    ["id"] = 20605,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
        {"roleInfo", "RoleDetailInfo"},
    },
}

DevourFairyPillReqBody = {
    ["name"] = "DevourFairyPillReqBody",
    ["id"] = 20606,
    ["attribs"] = {
        {"dishIndex", "uint32"},
    },
}

DevourFairyPillRespBody = {
    ["name"] = "DevourFairyPillRespBody",
    ["id"] = 20607,
    ["attribs"] = {
        {"packageIndex", "uint32"},
        {"dishPillInfo", "FairyPill"},
        {"dishInfo", "FairyDish", "repeat"},
        {"roleInfo", "RoleDetailInfo", "repeat"},
    },
}

RefreshFairyPillReqBody = {
    ["name"] = "RefreshFairyPillReqBody",
    ["id"] = 20608,
}

RefreshFairyPillRespBody = {
    ["name"] = "RefreshFairyPillRespBody",
    ["id"] = 20609,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
        {"packagePillList", "FairyPill", "repeat"},
    },
}

AutoDevourReqBody = {
    ["name"] = "AutoDevourReqBody",
    ["id"] = 20610,
}

AutoDevourRespBody = {
    ["name"] = "AutoDevourRespBody",
    ["id"] = 20611,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
    },
}

UpgradeFairyDishReqBody = {
    ["name"] = "UpgradeFairyDishReqBody",
    ["id"] = 20612,
}

UpgradeFairyDishRespBody = {
    ["name"] = "UpgradeFairyDishRespBody",
    ["id"] = 20613,
    ["attribs"] = {
        {"dishInfo", "FairyDish"},
    },
}

