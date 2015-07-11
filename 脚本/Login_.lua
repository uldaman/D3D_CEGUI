检查角色 = function()
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

进入游戏 = function()
    检查角色()
    
    if MH_登录游戏() == 0 then
        --所有角色都已经刷完, 通知控制台换号
        return
    end
    
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