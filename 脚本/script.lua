MH_加载脚本("City_.lua")
MH_加载脚本("Instance_.lua")
MH_加载脚本("Quest_.lua")
MH_加载脚本("Login_.lua")

while MH_是否工作() == 1 do
    local 是否在线 = MH_是否在线()
    local 是否在选择角色界面 = MH_是否在选择角色()
    local 是否过图 = MH_是否过图中()
    
    if 是否过图 == 1 then
        MH_调试("过图中")
    elseif 是否在线 == 1 then                 
        MH_调试("游戏中")
    elseif 是否在选择角色界面 == 1 then --新号无法判断..
        MH_调试("选择角色")
        进入游戏()
    else
        MH_调试("尚未进入主界面")
    end
    
    MH_延时(1000)
end
