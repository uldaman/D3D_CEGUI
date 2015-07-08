MH_加载脚本("S/City_.lub")
MH_加载脚本("S/Instance_.lub")
MH_加载脚本("S/Quest_.lub")

--Quest.主线()
local 检查角色 = function()
::检查开始::
    if MH_是否工作() == 1 then
        local 角色数量 = MH_当前角色数量()
        if 角色数量 < 6 then
            for i = 角色数量 + 1, 6 do
                MH_新建角色()
                MH_延时(1000)
                if MH_是否工作() == 0 then
                    return
                end
            end
            goto 检查开始
        end
    end
end

local 进入游戏 = function()
    检查角色()
    MH_登录游戏()
    MH_延时(1000)
    MH_确认频道()
    
    while MH_是否工作() == 1 do
        local 是否在线 = MH_是否在线()
        if 是否在线 == 1 then
            return
        end
        MH_延时(1000)
    end
end

--进入游戏()
--Quest.主线()
Instance.S_全自动刷本("[涅尔的训练地狱]", "身体", 0, 0.9)
-- while MH_是否工作() == 1 do
    -- local 是否在线 = MH_是否在线()
    -- local 是否在选择角色界面 = MH_是否在选择角色()
    -- local 是否过图 = MH_是否过图中()
    
    -- if 是否过图 == 1 then
        -- MH_调试("过图中")
    -- elseif 是否在线 == 1 then                 
        -- MH_调试("游戏中")   
    -- elseif 是否在选择角色界面 == 1 then --新号无法判断..
        -- MH_调试("选择角色")
    -- else
        -- MH_调试("尚未进入主界面")
    -- end
    
    -- MH_延时(1000)
-- end