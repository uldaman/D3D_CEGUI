Quest = {}

function Quest.猎人生活第一天(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人生活第一天") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
      	  			MH_调试("MH_交任务 猎人生活第一天")
                City.S_地图修正("希美伦山路")
                MH_交任务("猎人生活第一天", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
      	   MH_调试("MH_接任务 猎人生活第一天")
            City.S_地图修正("希美伦山路")
            MH_瞬移到坐标(375.14, 369.33, 88.99)
            MH_走到目标点(375.14, 369.33)
    				MH_延时(3000)
            MH_接任务("猎人生活第一天", "教官")
    				MH_延时(3000)
        end
    end
end

function Quest.狩猎生活乐趣多(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎生活乐趣多") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("狩猎生活乐趣多", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("狩猎生活乐趣多", "教官")
        end
    end
end

function Quest.暴饮暴食(bHave)
            MH_调试("Quest.暴饮暴食")
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("暴饮暴食") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("暴饮暴食", "莉莉")
            end
        else -- 没完成任务去做任务
							--Instance.S_全自动刷本("[烤肉，治愈人心！]", "身体", 0, 0.5)
							MH_进入副本("[烤肉，治愈人心！]")
    					MH_延时(20000)
							MH_补给箱取物("烤肉架")
    					MH_延时(5000)
							Instance.S_副本过图(1)
    					MH_延时(10000)
							Instance.S_全自动刷本("[烤肉，治愈人心！]", "身体", 0, 0.5)  --杀怪 新手引导关香菇猪
							MH_收起武器()
    					MH_延时(5000)
							--采集猪肉 1.采集物类别为A(怪物尸体) 2.距离最近
							MH_过滤式采集("尸体")
    					MH_延时(3000)
							MH_烤肉()
    					MH_延时(20000)
    					MH_吃烤肉()
    					MH_延时(5000)
    					--退出副本

            MH_调试("MH_做任务 [烤肉，治愈人心！]")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("暴饮暴食", "莉莉")
        end
    end
end


function Quest.狩猎的准备(bHave)
            MH_调试("Quest.狩猎的准备")
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎的准备") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
               MH_交任务("狩猎的准备", "莉莉")
            end
        else -- 没完成任务去做任务
        		--使用物品 配方-回复药
        		MH_通用使用物品("配方-回复药")
            MH_调试("MH_做任务 狩猎的准备")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("狩猎的准备", "莉莉")
        end
    end
end

function Quest.采集与调和(bHave)
            MH_调试("Quest.采集与调和")
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("采集与调和") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("采集与调和", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[采集，猎人之道]")
    					MH_延时(35000)
            --取补给箱子中的物品 携带食粮 *3 //对象ID：0000003C 见《F - 副本.txt》->【取补给物品封包】
            MH_补给箱取物("携带食料|携带食料|携带食料")
    					MH_延时(3000)
            --采集草药（坐标大概位于 1662.197，1564.355，127.9775）
            --MH_瞬移到坐标(1662.20, 1564.36, 127.98)
            MH_延时(1000)
            MH_采集目标点(1662.20, 1564.36)
            MH_延时(3000)
            --采集蘑菇（坐标大概位于 1679.653，1575.940，125.1007）
            MH_延时(1000)
            MH_采集目标点(1679.65, 1575.94)
    					MH_延时(2000)
            MH_调试("MH_采集完毕")
    					MH_延时(10000)
            Instance.S_副本过图(1)
    					MH_延时(5000)
            MH_调试("MH_采集完毕")
    					MH_翻滚()
    					--杀怪 当前房间中的4个蓝速龙
    					MH_击杀怪物("蓝速龙", 4)
    					MH_延时(30000)
    					MH_收起武器()
    					MH_制造回复药()
    					MH_延时(10000)
    					--退出副本
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("采集与调和", "莉莉")
        end
    end
end

function Quest.商队的委托(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("商队的委托") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("商队的委托", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
                City.S_地图修正("希美伦山路")
            MH_任务对话("商队的委托", "杰克雷·萨伊")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("商队的委托", "莉莉")
        end
    end
end

function Quest.危险的商路(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("危险的商路") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("危险的商路", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						Instance.S_全自动刷本("[危险的商路]", "身体", 0, 0.5)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("危险的商路", "贺菲")
        end
    end
end

function Quest.肯的大家族(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("肯的大家族") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("肯的大家族", "教官")
            end
        else -- 没完成任务去做任务
            MH_任务对话("肯的大家族", "黑心的肯")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("肯的大家族", "贺菲")
        end
    end
end

function Quest.猎人的武器(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的武器") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
                MH_交任务("猎人的武器", "雷欧")
            end
        else -- 没完成任务去做任务
            City.S_地图修正("米拉德村")
            MH_锻造晓风短剑()
    				MH_延时(10000)
         MH_穿装备("晓风短剑", "武器")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("猎人的武器", "教官")
        end
    end
end

function Quest.永夏的米拉德村(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("永夏的米拉德村") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
                MH_交任务("永夏的米拉德村", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("永夏的米拉德村", "雷欧")
        end
    end
end

function Quest.米拉德的大家(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("米拉德的大家") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
                MH_交任务("米拉德的大家", "摩拉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_任务对话("米拉德的大家", "威贝尔")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("米拉德的大家", "娜西卡")
        end
    end
end

function Quest.美食家与发明家(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("美食家与发明家") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
                MH_交任务("美食家与发明家", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_任务对话("美食家与发明家", "索纳德")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("美食家与发明家", "摩拉")
        end
    end
end

function Quest.属于猎人的星(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("属于猎人的星") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("属于猎人的星", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("属于猎人的星", "娜西卡")
        end
    end
end

function Quest.隐士之森的豪杰(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("隐士之森的豪杰") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                MH_通用使用物品("配方-自制铁镐")
                City.S_地图修正("希美伦山路")
                MH_交任务("隐士之森的豪杰", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[易怒的野猪王]", "身体", 0, 0.5)
            MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("隐士之森的豪杰", "教官")
        end
    end
end

function Quest.河狸兽的踪迹(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("河狸兽的踪迹") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("河狸兽的踪迹", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("河狸兽的踪迹", "教官")
        end
    end
end

function Quest.猛兽现身(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猛兽现身") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_交任务("猛兽现身", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[猛兽现身]", "身体", 0, 0.5)
            MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("猛兽现身", "莉莉")
        end
    end
end

function Quest.决战河狸兽(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("决战河狸兽") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
                MH_交任务("决战河狸兽", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[夙愿的河狸兽]", "身体", 0, 0.5)
            MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("决战河狸兽", "莉莉")
        end
    end
end

function Quest.正式猎人的工作(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("正式猎人的工作") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
                MH_交任务("正式猎人的工作", "悬赏看板")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("正式猎人的工作", "教官")
        end
    end
end

function Quest.赏金猎人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("赏金猎人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
                MH_交任务("赏金猎人", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
	         MH_穿装备("晓风头盔", "头部")
	         MH_穿装备("晓风铠甲", "胸部")
	         MH_穿装备("晓风腕甲", "手腕")
	         MH_穿装备("晓风腰甲", "腰部")
	         MH_穿装备("晓风重靴", "脚部")
            Quest.悬赏()
            MH_收起武器()
    				MH_延时(10000)
            MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
        		MH_通用使用物品("升级礼包【Lv5】")
        		MH_延时(1000)
        		MH_通用使用物品("升级礼包【Lv10】")
        		MH_延时(1000)
            City.S_地图修正("希美伦山路")
            MH_接任务("赏金猎人", "悬赏看板")
        end
    end
end

function Quest.新的狩猎流派(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("新的狩猎流派") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
               MH_交任务("新的狩猎流派", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
           -- 教官商店中购买 狩猎武器入门许可 子分类中购买 太刀授业证书
           MH_补给物品("太刀授业证书", "教官", "狩猎武器入门许可", 1)
           -- 使用太刀授业证书
        		MH_延时(1000)
           MH_通用使用物品("太刀授业证书")
        		MH_延时(1000)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("新的狩猎流派", "教官")
        end
    end
end

function Quest.修整结束(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("修整结束") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
               MH_交任务("修整结束", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("修整结束", "教官")
        end
    end
end

function Quest.自由考察(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("自由考察") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("自由考察", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！蓝速龙王", "身体", 0, 0.5)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("自由考察", "娜西卡")
        end
    end
end

function Quest.大怪鸟杀手贺菲(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("大怪鸟杀手贺菲") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("大怪鸟杀手贺菲", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("大怪鸟杀手贺菲", "贺菲")
        end
    end
end

function Quest.投弹实践(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("投弹实践") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("投弹实践", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[投弹实践]", "身体", 0, 0.5)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("投弹实践", "贺菲")
        end
    end
end

function Quest.殴打教官(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("殴打教官") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("殴打教官", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！大怪鸟", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("殴打教官", "贺菲")
        end
    end
end

function Quest.合格的武器(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("合格的武器") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
                MH_调试("MH_交任务")
                MH_交任务("合格的武器", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("米拉德村")

            local 河狸兽脊骨总数量 =  MH_仓库物品数量("河狸兽脊骨") + MH_背包物品数量("河狸兽脊骨")
            while 河狸兽脊骨总数量<2 and MH_是否工作() == 1 do
                Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
                MH_收起武器()
                MH_延时(10000)
                MH_过滤式采集("尸体")
                河狸兽脊骨总数量 =  MH_仓库物品数量("河狸兽脊骨") + MH_背包物品数量("河狸兽脊骨")
            end

            local 河狸兽之爪总数量 =  MH_仓库物品数量("河狸兽之爪") + MH_背包物品数量("河狸兽之爪")
            while   河狸兽之爪总数量<1 and MH_是否工作() == 1 do
                Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
                MH_收起武器()
                MH_延时(10000)
                MH_过滤式采集("尸体")
                河狸兽脊骨总数量 =  MH_仓库物品数量("河狸兽脊骨") + MH_背包物品数量("河狸兽脊骨")
            end

            local 兽骨数量 = MH_仓库物品数量("兽骨【小】") + MH_背包物品数量("兽骨【小】")
            if 兽骨数量<6 then
                MH_补给物品("兽骨【小】", "威贝尔", "狩猎补给品", 6) --兽骨数量
            end
            MH_升级到荆棘短剑()
            --装备上身
            MH_穿装备("荆棘短剑", "武器")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("合格的武器", "贺菲")
        end
    end
end

function Quest.名为沙漠的地方(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("名为沙漠的地方") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("名为沙漠的地方", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[酷热的沙海]")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("[酷热的沙海]", "身体", 0, 0.9)
						MH_收起武器()
						MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("名为沙漠的地方", "贺菲")
        end
    end
end

function Quest.昼夜温差(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("昼夜温差") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("昼夜温差", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[寒夜风沙]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("昼夜温差", "贺菲")
        end
    end
end

function Quest.贺菲的狩猎法(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的狩猎法") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("贺菲的狩猎法", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[贺菲的狩猎场]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("贺菲的狩猎法", "贺菲")
        end
    end
end

function Quest.狩猎的休憩(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎的休憩") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("狩猎的休憩", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到11
            MH_进入副本("试练！黄速龙王")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮|支给用热饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("试练！黄速龙王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("狩猎的休憩", "贺菲")
        end
    end
end

function Quest.黍老伯的烟斗(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("黍老伯的烟斗") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
               MH_交任务("黍老伯的烟斗", "黍老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("黍老伯的烟斗", "贺菲")
        end
    end
end

function Quest.庄园的经营(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("庄园的经营") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
               MH_交任务("庄园的经营", "黍老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            if MH_获取当前地图()~="庄园" then
	            City.S_地图修正("米拉德村")
	            MH_进入我的庄园()
            end
            MH_延时(5000)
            MH_升级育菇木床()
            MH_延时(5000)
            MH_采集目标点(855.31, 967.66)
            MH_离开庄园()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("庄园的经营", "黍老伯")
        end
    end
end

function Quest.猫猫小偷哪里跑(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猫猫小偷哪里跑") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
               MH_交任务("猫猫小偷哪里跑", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[挽救失足猫]")
    				MH_延时(10000)
            MH_击杀怪物("野生梅露", 5)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("猫猫小偷哪里跑", "黍老伯")
        end
    end
end

function Quest.突击黑猫盗贼总部(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("突击黑猫盗贼总部") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("突击黑猫盗贼总部", "圈尾思奇")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[夺回赃物]")
    				MH_延时(10000)
            MH_击杀怪物("野生梅露", 5)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("突击黑猫盗贼总部", "莉莉")
        end
    end
end

function Quest.思奇的新职业(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("思奇的新职业") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("思奇的新职业", "猫婆婆")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("思奇的新职业", "圈尾思奇")
        end
    end
end

function Quest.艾露诗人思奇(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("艾露诗人思奇") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("艾露诗人思奇", "圈尾思奇")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_任务对话("艾露诗人思奇", "圈尾思奇")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("艾露诗人思奇", "猫婆婆")
        end
    end
end

function Quest.艾露故事的收藏(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("艾露故事的收藏") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("艾露故事的收藏", "圈尾思奇")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_通用使用物品("《艾露一族》")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("艾露故事的收藏", "圈尾思奇")
        end
    end
end

function Quest.新的随从猫(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("新的随从猫") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
                MH_调试("MH_交任务")
                MH_交任务("新的随从猫", "猫婆婆")
                MH_延时(2000)
                MH_设置随行猫()
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_补给物品("呢特", "猫婆婆", "艾露猫雇佣", 1)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("新的随从猫", "圈尾思奇")
        end
    end
end

function Quest.随从猫的武装(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("随从猫的武装") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("随从猫的武装", "焦胡艾普")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_锻造村丁斗气锤()
    				MH_延时(2000)
            MH_装备斗气锤()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("随从猫的武装", "猫婆婆")
        end
    end
end

function Quest.嚣张的学徒(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("嚣张的学徒") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("嚣张的学徒", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("嚣张的学徒", "焦胡艾普")
        end
    end
end

function Quest.工匠的尊严(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("工匠的尊严") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("工匠的尊严", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						Instance.S_全自动刷本("[工匠的尊严]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("工匠的尊严", "雷欧")
        end
    end
end

function Quest.猎人与工匠(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人与工匠") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("猎人与工匠", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("猎人与工匠", "雷欧")
        end
    end
end

function Quest.前辈莉莉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("前辈莉莉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("前辈莉莉", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[少女猎人莉莉]")
            MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
						Instance.S_全自动刷本("[少女猎人莉莉]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("前辈莉莉", "莉莉")
        end
    end
end

function Quest.莉莉的弱点(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的弱点") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("莉莉的弱点", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("莉莉的弱点", "莉莉")
        end
    end
end

function Quest.狩猎前的热身(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎前的热身") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("狩猎前的热身", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
						MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("狩猎前的热身", "莉莉")
        end
    end
end

function Quest.面对恐惧(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("面对恐惧") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("面对恐惧", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[莉莉的恐惧症]")
						MH_延时(30000)
						Instance.S_副本过图(4)
						MH_延时(45000)
						Instance.S_全自动刷本("[莉莉的恐惧症]", "身体", 0, 0.9)
						MH_收起武器()
						MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("面对恐惧", "莉莉")
        end
    end
end

function Quest.商队归还(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("商队归还") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("商队归还", "杰克雷·萨伊")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
           -- City.S_地图修正("希美伦山路")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("商队归还", "莉莉")
        end
    end
end

function Quest.南方的异状(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("南方的异状") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("米拉德村")
            		MH_调试("MH_交任务")
              MH_交任务("南方的异状", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("南方的异状", "杰克雷·萨伊")
        end
    end
end

function Quest.备战期(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("备战期") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("备战期", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("希美伦山路")
            MH_任务对话("备战期", "贺菲")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("备战期", "娜西卡")
        end
    end
end

function Quest.热沙大决战(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("热沙大决战") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("热沙大决战", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[热砂大决战]")
						MH_延时(50000)
						MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
						Instance.S_副本过图(7)
						Instance.S_全自动刷本("[热砂大决战]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("热沙大决战", "莉莉")
        end
    end
end

function Quest.梅杰波尔坦的来访者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("梅杰波尔坦的来访者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("梅杰波尔坦的来访者", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("希美伦山路")
						MH_延时(50000)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("梅杰波尔坦的来访者", "莉莉")
        end
    end
end

function Quest.调查晓风山谷(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("调查晓风山谷") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("调查晓风山谷", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[调查-晓风山谷]")
    				MH_延时(10000)
            MH_击杀怪物("蓝速龙", 5)

        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("调查晓风山谷", "琳蒂丝")
        end
    end
end

function Quest.调查隐士之森(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("调查隐士之森") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("调查隐士之森", "琳蒂丝")
            end
        else -- 没完成任务去做任务
           MH_调试("MH_做任务")
           MH_进入副本("[调查-隐士之森]")
           MH_击杀怪物("野猪", 5)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("调查隐士之森", "琳蒂丝")
        end
    end
end



function Quest.星辰的传闻(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("星辰的传闻") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
                City.S_地图修正("希美伦山路")
            		MH_调试("MH_交任务")
              MH_交任务("星辰的传闻", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
           MH_通用使用物品("《星龙的传闻》")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("星辰的传闻", "琳蒂丝")
        end
    end
end

function Quest.预备远征(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("预备远征") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("希美伦山路")
              MH_交任务("预备远征", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("预备远征", "琳蒂丝")
        end
    end
end

function Quest.灵光的踪迹(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("灵光的踪迹") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("希美伦山路")
              MH_交任务("灵光的踪迹", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[灵光的踪迹]")
    				MH_延时(20000)
    				Instance.S_副本过图(6)
    				MH_延时(55000)
    				Instance.S_副本过图(8)
    				MH_延时(60000)
            Instance.S_全自动刷本("[灵光的踪迹]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("灵光的踪迹", "琳蒂丝")
        end
    end
end

function Quest.觉醒之力(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("觉醒之力") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("希美伦山路")
              MH_交任务("觉醒之力", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("觉醒之力", "琳蒂丝")
        end
    end
end

function Quest.必杀奥义(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("必杀奥义") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("米拉德村")
              MH_交任务("必杀奥义", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("必杀奥义", "莉莉")
        end
    end
end

function Quest.向娜西卡汇报(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("向娜西卡汇报") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("米拉德村")
              MH_交任务("向娜西卡汇报", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("向娜西卡汇报", "教官")
        end
    end
end

function Quest.公会的来访者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("公会的来访者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("希美伦山路")
              MH_交任务("公会的来访者", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("希美伦山路")
            MH_任务对话("公会的来访者", "贺菲")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("公会的来访者", "娜西卡")
        end
    end
end

function Quest.迷路的访客(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("迷路的访客") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
                City.S_地图修正("希美伦山路")
              MH_交任务("迷路的访客", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")

            MH_进入副本("[游逛的传说]")
    				MH_延时(30000)
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
    				Instance.S_副本过图(1)
    				MH_延时(40000)
    				Instance.S_全自动刷本("[游逛的传说]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("迷路的访客", "莉莉")
        end
    end
end

function Quest.变革的象征(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("变革的象征") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
               City.S_地图修正("希美伦山路")
              MH_交任务("变革的象征", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("变革的象征", "莉莉")
        end
    end
end

function Quest.罗登的见面礼(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("罗登的见面礼") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
               City.S_地图修正("希美伦山路")
              MH_交任务("罗登的见面礼", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[会长的见面礼]")
	    			MH_延时(10000)
		    		MH_开启无敌()
           	while MH_是否已完成任务("罗登的见面礼") ~= 1 do
		    			Instance.S_副本过图(7)
		          MH_过滤式采集("可疑的香草")
							Instance.S_副本过图(2)
							Instance.S_副本过图(0)
							MH_瞬移到坐标(808.86,3181.84,93.74)
							MH_瞬移到坐标(806.89,3170.64,93.82)
		    			MH_延时(1000)
		    			MH_交纳物品()
    				end
    				MH_关闭无敌()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("罗登的见面礼", "“山岚”罗登")
        end
    end
end

function Quest.双倍的毛茸茸(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("双倍的毛茸茸") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("双倍的毛茸茸", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[修行旧地]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("双倍的毛茸茸", "“山岚”罗登")
        end
    end
end

function Quest.万能的娜西卡(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("万能的娜西卡") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("万能的娜西卡", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("万能的娜西卡", "“山岚”罗登")
        end
    end
end

function Quest.不擅长的事物(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("不擅长的事物") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("不擅长的事物", "村长")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("不擅长的事物", "娜西卡")
        end
    end
end

function Quest.娜西卡的回忆(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("娜西卡的回忆") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("娜西卡的回忆", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("娜西卡的回忆", "村长")
        end
    end
end

function Quest.米拉德建村史(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("米拉德建村史") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("米拉德建村史", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("米拉德建村史", "娜西卡")
        end
    end
end

function Quest.过去的米拉德(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("过去的米拉德") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("过去的米拉德", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("过去的米拉德", "“山岚”罗登")
        end
    end
end

function Quest.勇气与资格(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("勇气与资格") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            		MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("勇气与资格", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("勇气与资格", "“山岚”罗登")
        end
    end
end

function Quest.失踪的莉莉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("失踪的莉莉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("失踪的莉莉", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
							MH_进入副本("[两个人的冒险]")
    					MH_延时(10000)
    					Instance.S_副本过图(2)
							Instance.S_瞬移到坐标(797.99,248.57,20.56)
    					MH_延时(50000)
							Instance.S_全自动刷本("[两个人的冒险]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("失踪的莉莉", "贺菲")
        end
    end
end

function Quest.丢失的项链(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("丢失的项链") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("丢失的项链", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("希美伦山路")
            MH_任务对话("丢失的项链", "莉莉")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("丢失的项链", "贺菲")
        end
    end
end

function Quest.贺菲相助(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲相助") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
            	MH_通用使用物品("湿地沉船观测记录")
            	MH_通用使用物品("《米拉德村纪事》")
              City.S_地图修正("希美伦山路")
              MH_交任务("贺菲相助", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
					  MH_进入副本("闪光的原因")
					  MH_延时(25000)
					  while MH_是否已完成任务("贺菲相助") ~= 1 do
	    				Instance.S_副本过图(1)
						  for iCollectItemIndex=0,6,1 do
							  local collectItemX, collectItemY, collectItemZ = MH_获取发光物品()
							  Instance.S_瞬移到坐标(collectItemX, collectItemY, collectItemZ)
    						MH_延时(1000)
							end

							Instance.S_副本过图(0)
							Instance.S_瞬移到坐标(802.13,875.70,18.47)
            MH_调试("MH_交纳物品")
    						MH_延时(500)
							MH_交纳物品()
							MH_延时(500)
						end
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("贺菲相助", "贺菲")
        end
    end
end

function Quest.友情的羁绊(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("友情的羁绊") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("友情的羁绊", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            if MH_是否在副本()==0 then
	            MH_补给物品("解毒药", "流浪的斯通", "狩猎补给品", 2)
	            MH_补给物品("解毒药", "流浪的斯通", "狩猎补给品", 2)
	            MH_补给物品("解毒药", "流浪的斯通", "狩猎补给品", 2)
	            MH_补给物品("解毒药", "流浪的斯通", "狩猎补给品", 2)
	            MH_补给物品("解毒药", "流浪的斯通", "狩猎补给品", 2)
		        MH_进入挨弟副本(204008)		 --//存在同名副本，取ID为0x00031CE8的那个
	        end
        MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
        MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
        Instance.S_全自动刷本("[重要之物]", "身体", 0, 0.9)
        MH_收起武器()
        MH_延时(2000)
        MH_过滤式采集("尸体")
end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("友情的羁绊", "莉莉")
        end
    end
end

function Quest.娜西卡的召唤(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("娜西卡的召唤") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("娜西卡的召唤", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("娜西卡的召唤", "莉莉")
        end
    end
end

function Quest.看板娘回归(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("看板娘回归") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("看板娘回归", "看板娘莎夏")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("看板娘回归", "娜西卡")
        end
    end
end

function Quest.公会的委托(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("公会的委托") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("公会的委托", "看板娘莎夏")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")		--升级到19级
            Instance.S_全自动刷本("试练！沙狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("公会的委托", "看板娘莎夏")
        end
    end
end

function Quest.猎人的成绩(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的成绩") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("猎人的成绩", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[猎人的成绩]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("猎人的成绩", "看板娘莎夏")
        end
    end
end

function Quest.飞行计划(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("飞行计划") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("飞行计划", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --武器升级 (可使用成长武器兑换券 兑换武器)
            Instance.S_全自动刷本("[试飞勘探]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("飞行计划", "贺菲")
        end
    end
end

function Quest.飞行器的制作(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("飞行器的制作") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("飞行器的制作", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("飞行器的制作", "贺菲")
        end
    end
end

function Quest.完成的飞行器(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("完成的飞行器") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            
	              --20级可以换武器          
	           -- local 沙龙王砂袋总数量 =  MH_仓库物品数量("沙龙王砂袋") + MH_背包物品数量("沙龙王砂袋")
	           -- while 沙龙王砂袋总数量<15 and MH_是否工作() == 1 do
	           --		  MH_进入副本("试练！沙龙王")	
	           -- 		MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
	           --		  MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
	           -- 		MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
	           --     Instance.S_全自动刷本("试练！沙龙王", "身体", 0, 0.9)
	           --     MH_收起武器()
	           --     MH_延时(10000)
	           --     MH_过滤式采集("尸体")
	           --     沙龙王砂袋总数量 =  MH_仓库物品数量("沙龙王砂袋") + MH_背包物品数量("沙龙王砂袋")
	           -- end
	           -- local 沙龙王之鳍总数量 =  MH_仓库物品数量("沙龙王之鳍") + MH_背包物品数量("沙龙王之鳍")
	          --  while 沙龙王之鳍总数量<3 and MH_是否工作() == 1 do
	           --		  MH_进入副本("试练！沙龙王")	
	           -- 		MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
	           	--	  MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
	           	--	  MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
	           --     Instance.S_全自动刷本("试练！沙龙王", "身体", 0, 0.9)
	            --    MH_收起武器()
	            --    MH_延时(10000)
	            --    MH_过滤式采集("尸体")
	            --    沙龙王之鳍总数量 =  MH_仓库物品数量("沙龙王之鳍") + MH_背包物品数量("沙龙王之鳍")
	           -- end
	            
	            --local 沙龙王背鳍总数量 =  MH_仓库物品数量("沙龙王背鳍") + MH_背包物品数量("沙龙王背鳍")
	            --while 沙龙王背鳍总数量<3 and MH_是否工作() == 1 do
	           	--	  MH_进入副本("试练！沙龙王")	
	            --		MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
	           	--	  MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
	           	--	  MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
	            --    Instance.S_全自动刷本("试练！沙龙王", "身体", 0, 0.9)
	            --    MH_收起武器()
	            --    MH_延时(10000)
	            --    MH_过滤式采集("尸体")
	            --    沙龙王背鳍总数量 =  MH_仓库物品数量("沙龙王背鳍") + MH_背包物品数量("沙龙王背鳍")
	            --end
	            --锻造武器
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("完成的飞行器", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --20级
            MH_进入副本("试练！桃毛兽王")		
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("试练！桃毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")            
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("完成的飞行器", "贺菲")
        end
    end
end

function Quest.初期试飞(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("初期试飞") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("初期试飞", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						MH_进入副本("[初次试飞]")
   				 	MH_延时(75000)
   				 	--取冷饮
   				 	MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
						Instance.S_副本过图(7)
						MH_延时(20000)
            Instance.S_全自动刷本("[初次试飞]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("初期试飞", "贺菲")
        end
    end
end

function Quest.有仇必报的猎人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("有仇必报的猎人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("有仇必报的猎人", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						MH_进入副本("[贺菲与沙雷鸟]")
    			MH_延时(20000)
    			MH_开启无敌()
          while MH_是否已完成任务("有仇必报的猎人") ~= 1 do
						Instance.S_副本过图(4)
			    	MH_过滤式采集("可疑的香草") 						--采集 重辣球根*10
						Instance.S_副本过图(2)
						Instance.S_副本过图(0)
						MH_瞬移到坐标(808.86,3181.84,93.74)
						MH_瞬移到坐标(806.89,3170.64,93.82)
						MH_交纳物品()
	    			MH_延时(3000)
    			end
    			MH_关闭无敌()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("有仇必报的猎人", "贺菲")
        end
    end
end

function Quest.各自的梦想(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("各自的梦想") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("各自的梦想", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
              City.S_地图修正("希美伦山路")
            MH_任务对话("各自的梦想", "莉莉")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("各自的梦想", "贺菲")
        end
    end
end

function Quest.珍馐的草食龙(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("珍馐的草食龙") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("珍馐的草食龙", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
           Instance.S_全自动刷本("[至尊美味的肉]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("珍馐的草食龙", "“山岚”罗登")
        end
    end
end

function Quest.料理对决(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("料理对决") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("料理对决", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("希美伦山路")
            MH_任务对话("料理对决", "莉莉")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("料理对决", "“山岚”罗登")
        end
    end
end

function Quest.贺菲的美食单(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的美食单") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("贺菲的美食单", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
           Instance.S_全自动刷本("[贺菲的菜单]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("贺菲的美食单", "贺菲")
        end
    end
end

function Quest.公平竞争(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("公平竞争") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("公平竞争", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("公平竞争", "贺菲")
        end
    end
end

function Quest.莉莉的美食单(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的美食单") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("莉莉的美食单", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[莉莉的美食单]")
	    			MH_延时(10000)
    			MH_开启无敌()
          while MH_是否已完成任务("莉莉的美食单") ~= 1 do
						Instance.S_副本过图(2)
						MH_延时(1000)
						Instance.S_副本过图(0)
			    	MH_过滤式采集("可疑的香草") 						--采集 腥味的鱼*10
						Instance.S_瞬移到坐标(1683.22,351.48,205.37)
						MH_交纳物品()
	    			MH_延时(3000)
    			end
    			MH_关闭无敌()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("莉莉的美食单", "莉莉")
        end
    end
end

function Quest.丛林盛宴(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("丛林盛宴") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("丛林盛宴", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[丛林盛宴]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_副本过图(0)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("丛林盛宴", "莉莉")
        end
    end
end

function Quest.湿地盛宴(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("湿地盛宴") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("湿地盛宴", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入挨弟副本(100496)		--//存在同名副本，取ID为0x00018890的那个
            Instance.S_副本过图(1)
            MH_击杀怪物(盾蟹, 10)
            Instance.S_副本过图(0)
    				MH_延时(15000)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("湿地盛宴", "莉莉")
        end
    end
end

function Quest.追击红色杀手(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("追击红色杀手") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("追击红色杀手", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[追击红色杀手]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("追击红色杀手", "莉莉")
        end
    end
end

function Quest.娜西卡的外出(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("娜西卡的外出") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("娜西卡的外出", "村长")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
              City.S_地图修正("米拉德村")
            	MH_任务对话("娜西卡的外出", "娜西卡")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("娜西卡的外出", "莉莉")
        end
    end
end

function Quest.未知的预感(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("未知的预感") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("未知的预感", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[丛林盛宴]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("未知的预感", "村长")
        end
    end
end

function Quest.遭袭的商队(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("遭袭的商队") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("遭袭的商队", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[嗜血沙龙]")
            MH_延时(30000)
            MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_副本过图(7)
            MH_延时(40000)
            Instance.S_全自动刷本("[嗜血沙龙]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("遭袭的商队", "莉莉")
        end
    end
end

function Quest.商队失踪(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("商队失踪") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("商队失踪", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[沙漠救助]")
            MH_延时(30000)
            MH_补给箱取物("支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮|支给用冷饮")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_副本过图(6)
            MH_击杀怪物(黄速龙, 12)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("商队失踪", "贺菲")
        end
    end
end

function Quest.贺菲的贸然行事(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的贸然行事") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("贺菲的贸然行事", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[贺菲的复仇]")
    				MH_延时(30000)
    				Instance.S_副本过图(6)
    				MH_延时(70000)
    				Instance.S_全自动刷本("[贺菲的复仇]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("贺菲的贸然行事", "贺菲")
        end
    end
end

function Quest.冲动的贺菲(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("冲动的贺菲") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("冲动的贺菲", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_任务对话("冲动的贺菲", "莉莉")
            MH_延时(3000)
            MH_任务对话("冲动的贺菲", "“山岚”罗登")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("冲动的贺菲", "贺菲")
        end
    end
end

function Quest.自己的路(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("自己的路") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("自己的路", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("自己的路", "教官")
        end
    end
end

function Quest.别离与再会之间(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("别离与再会之间") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("别离与再会之间", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[伙伴最后的狩猎]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("别离与再会之间", "莉莉")
        end
    end
end

function Quest.安静的米拉德村(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("安静的米拉德村") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("安静的米拉德村", "教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_任务对话("安静的米拉德村", "莉莉")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("安静的米拉德村", "贺菲")
        end
    end
end

function Quest.归来的娜西卡(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("归来的娜西卡") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("归来的娜西卡", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("归来的娜西卡", "教官")
        end
    end
end

function Quest.消沉的莉莉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("消沉的莉莉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("消沉的莉莉", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("消沉的莉莉", "娜西卡")
        end
    end
end

function Quest.猎人的竞赛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的竞赛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("猎人的竞赛", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[竞技比赛]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("猎人的竞赛", "莉莉")
        end
    end
end

function Quest.共同的精进(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("共同的精进") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("共同的精进", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[高级试炼]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("共同的精进", "莉莉")
        end
    end
end

function Quest.不变的狩猎(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("不变的狩猎") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("不变的狩猎", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("不变的狩猎", "莉莉")
        end
    end
end

function Quest.会长的指示(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("会长的指示") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("会长的指示", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级达到24
            Instance.S_全自动刷本("[竞技比赛]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("会长的指示", "娜西卡")
        end
    end
end

function Quest.梅杰波尔坦的召集(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("梅杰波尔坦的召集") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("梅杰波尔坦的召集", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("梅杰波尔坦的召集", "“山岚”罗登")
        end
    end
end

function Quest.教官的考验①(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("教官的考验①") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("教官的考验①", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[沙之怒号]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_全自动刷本("[沙之怒号]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("教官的考验①", "莉莉")
        end
    end
end

function Quest.教官的考验②(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("教官的考验②") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("教官的考验②", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[制霸昆贝尔]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_全自动刷本("[制霸昆贝尔]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("教官的考验②", "莉莉")
        end
    end
end

function Quest.雷欧的请求(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雷欧的请求") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("雷欧的请求", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("雷欧的请求", "莉莉")
        end
    end
end

function Quest.似曾相识的考察(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("似曾相识的考察") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("似曾相识的考察", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[猎人与工匠的约定]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("似曾相识的考察", "雷欧")
        end
    end
end

function Quest.莉莉的大考验(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的大考验") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("希美伦山路")
              MH_交任务("莉莉的大考验", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[三倍噩梦]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_全自动刷本("[三倍噩梦]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_全自动刷本("[三倍噩梦]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("莉莉的大考验", "雷欧")
        end
    end
end

function Quest.最后的测试(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("最后的测试") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
             MH_交任务("最后的测试", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("米拉德村")
            MH_任务对话("最后的测试", "村长")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("希美伦山路")
            MH_接任务("最后的测试", "莉莉")
        end
    end
end

function Quest.猛炎的试炼(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猛炎的试炼") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
             MH_交任务("猛炎的试炼", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[猛炎的试练]")
    				MH_延时(30000)
						Instance.S_副本过图(3)
						Instance.S_全自动刷本("[猛炎的试练]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("猛炎的试炼", "娜西卡")
        end
    end
end

function Quest.和大家的告别(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("和大家的告别") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
             MH_交任务("和大家的告别", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("米拉德村")
            MH_任务对话("和大家的告别", "杰克雷·萨伊")
   			    MH_延时(3000)
            MH_任务对话("和大家的告别", "莉莉")
    				MH_延时(3000)
            MH_任务对话("和大家的告别", "雷欧")
   					MH_延时(3000)
            MH_任务对话("和大家的告别", "摩拉")
    				MH_延时(3000)
            MH_任务对话("和大家的告别", "村长")
    				MH_延时(3000)
            MH_任务对话("和大家的告别", "教官")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("和大家的告别", "娜西卡")
        end
    end
end

function Quest.前往梅杰波尔坦！(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("前往梅杰波尔坦！") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
             MH_交任务("前往梅杰波尔坦！", "公会秘书普雷妮")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("梅杰波尔坦")
            MH_任务对话("前往梅杰波尔坦！", "公会秘书普雷妮")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("前往梅杰波尔坦！", "娜西卡")
        end
    end
end

function Quest.崭新起点(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("崭新起点") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
             MH_交任务("崭新起点", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("梅杰波尔坦")
            MH_任务对话("崭新起点", "“山岚”罗登")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("崭新起点", "公会秘书普雷妮")
        end
    end
end

function Quest.猎人之城(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人之城") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
             MH_交任务("猎人之城", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("梅杰波尔坦")
            MH_任务对话("猎人之城", "罗师傅")
    				MH_延时(3000)
            MH_任务对话("猎人之城", "伊格琳诗教官")
    				MH_延时(3000)
            MH_任务对话("猎人之城", "黑石")
    				MH_延时(3000)
            MH_任务对话("猎人之城", "马克")
    				MH_延时(3000)
            MH_任务对话("猎人之城", "芭缇雅女士")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("猎人之城", "“山岚”罗登")
        end
    end
end

function Quest.商会的麻烦(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("商会的麻烦") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("商会的麻烦", "赫森老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("商会的麻烦", "“山岚”罗登")
        end
    end
end

function Quest.奇面族的威胁(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("奇面族的威胁") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("奇面族的威胁", "赫森老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[奇面族的威胁]")
    				MH_延时(30000)
    				MH_击杀怪物("刀奇面", 3)
    				MH_击杀怪物("箭奇面", 3)
    				MH_击杀怪物("祭司奇面", 3)
    				MH_击杀怪物("奇面王", 1)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("奇面族的威胁", "赫森老伯")
        end
    end
end

function Quest.陌生的猎场(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("陌生的猎场") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("陌生的猎场", "普雷妮")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
						MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("陌生的猎场", "赫森老伯")
        end
    end
end

function Quest.冷漠的公会(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("冷漠的公会") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务111")
              City.S_地图修正("梅杰波尔坦")
              MH_精准交任务("冷漠的公会", "维奥娜", 1335.36,1238.71)
              --MH_交任务("冷漠的公会", "维奥娜") 交任务时NPC有同名的 在（1288.58,1271.17,13.75）有一个假的，在（1335.36,1238.71,17.13）有一个真的
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("冷漠的公会", "普雷妮")
        end
    end
end

function Quest.失踪人口(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("失踪人口") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("失踪人口", "赫森老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_精准接任务("失踪人口", "维奥娜", 1335.36,1238.71)
            --MH_接任务("失踪人口", "维奥娜") --NPC有同名的 在（1288.58,1271.17,13.75）有一个假的，在（1335.36,1238.71,17.13）有一个真的
        end
    end
end

function Quest.被俘的新兵(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("被俘的新兵") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("被俘的新兵", "赫森老伯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						MH_进入副本("[被俘的猎人]")
				    MH_延时(10000)
				    Instance.S_副本过图(5)
				    MH_延时(45000)
				    Instance.S_全自动刷本("[被俘的猎人]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("被俘的新兵", "赫森老伯")
        end
    end
end

function Quest.猎人的意义(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的意义") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("猎人的意义", "涅尔")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("猎人的意义", "赫森老伯")
        end
    end
end

function Quest.路痴莉莉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("路痴莉莉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("路痴莉莉", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("路痴莉莉", "涅尔")
        end
    end
end

function Quest.问题儿驾到(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("问题儿驾到") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("问题儿驾到", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("问题儿驾到", "莉莉")
        end
    end
end

function Quest.米拉德互助组(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("米拉德互助组") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("米拉德互助组", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("米拉德互助组", "雷欧")
        end
    end
end

function Quest.莉莉的风格(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的风格") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("莉莉的风格", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[糟糕的电龙]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("莉莉的风格", "莉莉")
        end
    end
end

function Quest.狩猎的日常(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎的日常") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("狩猎的日常", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("狩猎的日常", "莉莉")
        end
    end
end

function Quest.对峙的群山(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("对峙的群山") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("对峙的群山", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
          Instance.S_全自动刷本("[奇面族大进攻]", "身体", 0, 0.9)
						MH_收起武器()
						MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("对峙的群山", "莉莉")
        end
    end
end

function Quest.哨所的奖励(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("哨所的奖励") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("哨所的奖励", "维奥娜")--NPC名称重复
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("哨所的奖励", "莉莉")
        end
    end
end

function Quest.年轻的仰慕者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("年轻的仰慕者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("年轻的仰慕者", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("年轻的仰慕者", "维奥娜")--NPC名称重复
        end
    end
end

function Quest.会长的训练方案(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("会长的训练方案") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("会长的训练方案", "涅尔")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("会长的训练方案", "“山岚”罗登")
        end
    end
end

function Quest.新人地狱(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("新人地狱") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("新人地狱", "涅尔")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[涅尔的新人培训]")
    				MH_延时(30000)
    				MH_击杀怪物("蓝速龙", 5)
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("新人地狱", "涅尔")
        end
    end
end

function Quest.前辈的背影(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("前辈的背影") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("前辈的背影", "涅尔")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("前辈的背影", "涅尔")
        end
    end
end

function Quest.雷欧的傲慢(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雷欧的傲慢") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("雷欧的傲慢", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("雷欧的傲慢", "涅尔")
        end
    end
end

function Quest.追不上的人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("追不上的人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("追不上的人", "罗师傅")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("追不上的人", "雷欧")
        end
    end
end

function Quest.再度出走的雷欧(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("再度出走的雷欧") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("再度出走的雷欧", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("再度出走的雷欧", "罗师傅")
        end
    end
end

function Quest.雷欧的修行(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雷欧的修行") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("雷欧的修行", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[天地间的秘宝]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("雷欧的修行", "雷欧")
        end
    end
end

function Quest.爷们的锻造魂(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("爷们的锻造魂") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("爷们的锻造魂", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[爷们的锻造魂]")
    				MH_延时(20000)
    				Instance.S_副本过图(5)
    				Instance.S_瞬移到坐标(1940.54,3448.05,276.93)
    				MH_延时(30000)
    				Instance.S_副本过图(7)
    				MH_延时(10000)
    				Instance.S_副本过图(0)
    				--Instance.S_瞬移到坐标(1243.89, 2358.99, 45.12)
    				--采集此坐标的物品
    				MH_采集目标点(1182.85, 2374.16)
						MH_延时(5000)
						MH_采集目标点(1204.04, 2361.59)
						MH_延时(5000)
						MH_采集目标点(1243.33, 2359.09)
						MH_延时(5000)
						MH_采集目标点(1197.34, 2430.36)
						MH_延时(5000)
						MH_采集目标点(1185.79, 2410.67)
						MH_延时(5000)
						Instance.S_瞬移到坐标(524.09, 3718.38,57.96)
						MH_交纳物品()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("爷们的锻造魂", "雷欧")
        end
    end
end

function Quest.最后的步骤(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("最后的步骤") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("最后的步骤", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("最后的步骤", "雷欧")
        end
    end
end

function Quest.男子汉的玉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("男子汉的玉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("男子汉的玉", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[大地之拳]")
    				MH_延时(30000)
    				Instance.S_副本过图(5)
    				MH_延时(50000)
    				Instance.S_全自动刷本("[大地之拳]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("男子汉的玉", "雷欧")
        end
    end
end

function Quest.雷欧的进化(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雷欧的进化") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("雷欧的进化", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("雷欧的进化", "雷欧")
        end
    end
end

function Quest.习惯的气氛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("习惯的气氛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("习惯的气氛", "莱维")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            City.S_地图修正("梅杰波尔坦")
            MH_任务对话("习惯的气氛", "莉莉")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("习惯的气氛", "雷欧")
        end
    end
end

function Quest.暴风小队的挑战(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("暴风小队的挑战") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("暴风小队的挑战", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[与暴风的竞赛]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("暴风小队的挑战", "莱维")
        end
    end
end

function Quest.梅杰波尔坦的教官(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("梅杰波尔坦的教官") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("梅杰波尔坦的教官", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("梅杰波尔坦的教官", "莉莉")
        end
    end
end

function Quest.新教官的操练(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("新教官的操练") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("新教官的操练", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[精英猎人的训练]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("新教官的操练", "伊格琳诗教官")
        end
    end
end

function Quest.最佳纪录(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("最佳纪录") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
             MH_交任务("最佳纪录", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("最佳纪录", "伊格琳诗教官")
        end
    end
end

function Quest.积累实绩(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("积累实绩") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
             MH_交任务("积累实绩", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("积累实绩", "伊格琳诗教官")
        end
    end
end

function Quest.天才登场(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("天才登场") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
             MH_交任务("天才登场", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("天才登场", "伊格琳诗教官")
        end
    end
end

function Quest.埃兰的狩猎风格(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("埃兰的狩猎风格") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
             MH_交任务("埃兰的狩猎风格", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[与埃兰的初次组队]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("埃兰的狩猎风格", "埃兰")
        end
    end
end

function Quest.麻烦的源头(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("麻烦的源头") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
             MH_交任务("麻烦的源头", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("麻烦的源头", "埃兰")
        end
    end
end

function Quest.强大的诀窍(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("强大的诀窍") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("强大的诀窍", "莱维")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("强大的诀窍", "莉莉")
        end
    end
end

function Quest.剑法大师伊达爷爷(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("剑法大师伊达爷爷") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("剑法大师伊达爷爷", "伊达宗师")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 2, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("剑法大师伊达爷爷", "莱维")
        end
    end
end

function Quest.埃兰的自负(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("埃兰的自负") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("埃兰的自负", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[无暇猎手]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("埃兰的自负", "伊达宗师")
        end
    end
end

function Quest.申报竞赛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("申报竞赛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("申报竞赛", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("申报竞赛", "埃兰")
        end
    end
end

function Quest.竞争的约定(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("竞争的约定") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("竞争的约定", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("竞争的约定", "伊格琳诗教官")
        end
    end
end

function Quest.狡诈的眠鸟(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狡诈的眠鸟") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("狡诈的眠鸟", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[对决埃兰]")
    				MH_延时(60000)
            Instance.S_副本过图(6)
    				MH_延时(5000)
            Instance.S_全自动刷本("[对决埃兰]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("狡诈的眠鸟", "伊格琳诗教官")
        end
    end
end

function Quest.反省的埃兰(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("反省的埃兰") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("反省的埃兰", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("反省的埃兰", "伊格琳诗教官")
        end
    end
end

function Quest.伊达宗师的感谢(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("伊达宗师的感谢") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("伊达宗师的感谢", "伊达宗师")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("伊达宗师的感谢", "埃兰")
        end
    end
end

function Quest.千之试炼(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("千之试炼") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("千之试炼", "千狩看板娘")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("千之试炼", "伊达宗师")
        end
    end
end

function Quest.聚集的寻星者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("聚集的寻星者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("聚集的寻星者", "看板娘莎夏")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("聚集的寻星者", "千狩看板娘")
        end
    end
end

function Quest.猎人的竞争(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的竞争") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("猎人的竞争", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 2, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("猎人的竞争", "看板娘莎夏")
        end
    end
end

function Quest.莉莉的求助(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的求助") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("莉莉的求助", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[最不搭的队伍]")
    				MH_延时(20000)
    				Instance.S_副本过图(6)
    				MH_延时(5000)
    				Instance.S_副本过图(0)
    				--采集清毒茴香 * 10
    				MH_采集目标点(1905.28, 815.68)
    				MH_延时(2000)
    				MH_采集目标点(1911.98, 834.07)
    				MH_延时(2000)
    				MH_采集目标点(1906.43, 800.78)
    				MH_延时(2000)
    				MH_采集目标点(1876.80, 802.76)
    				MH_延时(2000)
    				MH_采集目标点(1890.53, 811.27)
    				MH_延时(2000)
    				MH_采集目标点(1892.74, 828.90)
    				MH_延时(2000)
    				MH_采集目标点(1883.43, 830.39)
    				MH_延时(2000)
    				MH_采集目标点(1861.50, 813.93)
    				MH_延时(2000)
    				MH_采集目标点(1863.48, 828.20)
    				MH_延时(2000)
    				MH_采集目标点(1877.31, 820.35)
    				MH_延时(2000)
    				Instance.S_瞬移到坐标(3463.77,387.94,85.31)
    				MH_交纳物品()
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("莉莉的求助", "莉莉")
        end
    end
end

function Quest.莉莉的神经衰弱(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的神经衰弱") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("莉莉的神经衰弱", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[队长莉莉]")
            MH_延时(30000)
						Instance.S_副本过图(1)
            MH_延时(10000)
						Instance.S_副本过图(2)
            MH_延时(10000)
						Instance.S_副本过图(3)
            MH_延时(10000)
            Instance.S_全自动刷本("[队长莉莉]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("莉莉的神经衰弱", "埃兰")
        end
    end
end

function Quest.群星之龙的踪迹(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("群星之龙的踪迹") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("群星之龙的踪迹", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("群星之龙的踪迹", "莉莉")
        end
    end
end

function Quest.探访群星(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("探访群星") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("探访群星", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[探访群星]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("探访群星", "琳蒂丝")
        end
    end
end

function Quest.垂头丧气的学士(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("垂头丧气的学士") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("垂头丧气的学士", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("垂头丧气的学士", "琳蒂丝")
        end
    end
end

function Quest.目击：独行种(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("目击：独行种") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("目击：独行种", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("目击：独行种", "琳蒂丝")
        end
    end
end

function Quest.未来的角斗明星(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("未来的角斗明星") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("未来的角斗明星", "黑石")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("未来的角斗明星", "“山岚”罗登")
        end
    end
end

function Quest.恶臭的源头(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("恶臭的源头") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("恶臭的源头", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[高贵的黄金王]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("恶臭的源头", "黑石")
        end
    end
end

function Quest.学士的智慧(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("学士的智慧") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("学士的智慧", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("学士的智慧", "琳蒂丝")
        end
    end
end

function Quest.驱除臭气香菇(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("驱除臭气香菇") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("驱除臭气香菇", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[驱逐臭气的菇]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("驱除臭气香菇", "琳蒂丝")
        end
    end
end

function Quest.培育香菇(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("培育香菇") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("培育香菇", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 3, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("培育香菇", "琳蒂丝")
        end
    end
end

function Quest.君王的初赛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("君王的初赛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("君王的初赛", "黑石")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("君王的初赛", "琳蒂丝")
        end
    end
end

function Quest.贵宾席(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贵宾席") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("贵宾席", "黑石")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("贵宾席", "黑石")
        end
    end
end

function Quest.恶臭的大灾难(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("恶臭的大灾难") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("恶臭的大灾难", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[恶臭的大灾难]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("恶臭的大灾难", "黑石")
        end
    end
end

function Quest.抓狂的斗士们(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("抓狂的斗士们") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("抓狂的斗士们", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[抓狂的斗士们]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            Instance.S_全自动刷本("[抓狂的斗士们]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("抓狂的斗士们", "维奥娜")
        end
    end
end

function Quest.异邦的来访者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("异邦的来访者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("异邦的来访者", "米斯利")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("异邦的来访者", "维奥娜")
        end
    end
end

function Quest.活跃的猎人之城(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("活跃的猎人之城") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("活跃的猎人之城", "普雷妮")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("活跃的猎人之城", "米斯利")
        end
    end
end

function Quest.莉莉的紧迫感(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的紧迫感") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("莉莉的紧迫感", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[竞争对手]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("莉莉的紧迫感", "普雷妮")
        end
    end
end

function Quest.美少女小队(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("美少女小队") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("美少女小队", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("美少女小队", "莉莉")
        end
    end
end

function Quest.雷欧的春天(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雷欧的春天") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("雷欧的春天", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[雷欧的春天]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("雷欧的春天", "雷欧")
        end
    end
end

function Quest.孤傲的埃兰(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("孤傲的埃兰") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("孤傲的埃兰", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("孤傲的埃兰", "雷欧")
        end
    end
end

function Quest.自我的脚步(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("自我的脚步") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("自我的脚步", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("自我的脚步", "埃兰")
        end
    end
end

function Quest.猎人团体挖脚事件(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人团体挖脚事件") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("猎人团体挖脚事件", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("猎人团体挖脚事件", "埃兰")
        end
    end
end

function Quest.被丢下的莉莉(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("被丢下的莉莉") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("被丢下的莉莉", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						MH_进入副本("[加重的恐惧]")
    				MH_延时(5000)
    				Instance.S_副本过图(4)
    				MH_延时(30000)
    				Instance.S_全自动刷本("[加重的恐惧]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("被丢下的莉莉", "伊格琳诗教官")
        end
    end
end

function Quest.友情不可负(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("友情不可负") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("友情不可负", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[队友还是老的好]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("友情不可负", "莉莉")
        end
    end
end

function Quest.龙人诗人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("龙人诗人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("龙人诗人", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("龙人诗人", "莉莉")
        end
    end
end

function Quest.诗人的请托(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("诗人的请托") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("米拉德村")
              MH_交任务("诗人的请托", "圈尾思奇")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("诗人的请托", "法莱斯")
        end
    end
end

function Quest.思奇与诗人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("思奇与诗人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("思奇与诗人", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("米拉德村")
            MH_接任务("思奇与诗人", "圈尾思奇")
        end
    end
end

function Quest.日常锻炼(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("日常锻炼") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("日常锻炼", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！眠鸟", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("日常锻炼", "法莱斯")
        end
    end
end

function Quest.诗歌中的特异种(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("诗歌中的特异种") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("诗歌中的特异种", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到34级
            Instance.S_全自动刷本("试练！眠鸟", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("诗歌中的特异种", "法莱斯")
        end
    end
end

function Quest.战鬼河狸兽(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("战鬼河狸兽") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("战鬼河狸兽", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[月下幻狸]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("战鬼河狸兽", "法莱斯")
        end
    end
end

function Quest.过度治疗(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("过度治疗") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("过度治疗", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --MH_进入副本("[过度治疗]")
            --补给箱取支给用回复药、支给用解毒药
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            --血量伤害到一定比例自动使用回复药
            Instance.S_全自动刷本("[过度治疗]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("过度治疗", "莉莉")
        end
    end
end

function Quest.龙人的行迹(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("龙人的行迹") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("龙人的行迹", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("龙人的行迹", "莉莉")
        end
    end
end

function Quest.诗人的证言(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("诗人的证言") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("诗人的证言", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("诗人的证言", "莉莉")
        end
    end
end

function Quest.三倍速之赤红(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("三倍速之赤红") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("三倍速之赤红", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[三倍速之赤红]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("三倍速之赤红", "法莱斯")
        end
    end
end

function Quest.调查指令(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("调查指令") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("调查指令", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[暗幕]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("调查指令", "莉莉")
        end
    end
end

function Quest.特殊任务(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("特殊任务") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("特殊任务", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！金毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            --可刷工会任务，升级会更快
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("特殊任务", "莉莉")
        end
    end
end

function Quest.骚乱的暗色森林(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("骚乱的暗色森林") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("骚乱的暗色森林", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("骚乱的暗色森林", "莉莉")
        end
    end
end

function Quest.不情愿的小队(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("不情愿的小队") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("不情愿的小队", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("不情愿的小队", "伊格琳诗教官")
        end
    end
end

function Quest.怪光魔术师(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("怪光魔术师") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("怪光魔术师", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
						MH_进入副本("[怪光魔术师]")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("[怪光魔术师]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("怪光魔术师", "莉莉")
        end
    end
end

function Quest.突变的岩龙(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("突变的岩龙") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("突变的岩龙", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[晶岩之龙]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("突变的岩龙", "莉莉")
        end
    end
end

function Quest.持有利刃的生物(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("持有利刃的生物") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("持有利刃的生物", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[神秘的龙人]")
    				MH_延时(30000)
    				Instance.S_副本过图(3)
    				MH_延时(90000)
            Instance.S_全自动刷本("[神秘的龙人]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("持有利刃的生物", "莉莉")
        end
    end
end

function Quest.调查骨笛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("调查骨笛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("调查骨笛", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("调查骨笛", "埃兰")
        end
    end
end

function Quest.极限狩猎(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("极限狩猎") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("极限狩猎", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("极限狩猎", "琳蒂丝")
        end
    end
end

function Quest.极限化的装备(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("极限化的装备") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("极限化的装备", "雷欧")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("极限化的装备", "“山岚”罗登")
        end
    end
end

function Quest.必要的修行(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("必要的修行") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("必要的修行", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！金毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
            --等级提升到36
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("必要的修行", "雷欧")
        end
    end
end

function Quest.小队行动(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("小队行动") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("小队行动", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("小队行动", "伊格琳诗教官")
        end
    end
end

function Quest.埃兰的故事(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("埃兰的故事") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("埃兰的故事", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("埃兰的往事", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("埃兰的故事", "埃兰")
        end
    end
end

function Quest.交配的好时节(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("交配的好时节") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("交配的好时节", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("破坏毒鸟的浪漫！", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("交配的好时节", "莉莉")
        end
    end
end

function Quest.暖风降临(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("暖风降临") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("暖风降临", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("暖风降临", "莉莉")
        end
    end
end

function Quest.娜西卡的到来(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("娜西卡的到来") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("娜西卡的到来", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("娜西卡的到来", "娜西卡")
        end
    end
end

function Quest.成长的脚步(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("成长的脚步") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("成长的脚步", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！金毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("成长的脚步", "莉莉")
        end
    end
end

function Quest.会长的助兴节目(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("会长的助兴节目") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("会长的助兴节目", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --升级到37
            Instance.S_全自动刷本("试练！金毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("会长的助兴节目", "莉莉")
        end
    end
end

function Quest.大狩猎祭！(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("大狩猎祭！") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("大狩猎祭！", "普雷妮")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("大狩猎祭！", "“山岚”罗登")
        end
    end
end

function Quest.狩猎祭第一战(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎祭第一战") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("狩猎祭第一战", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[狩猎祭第一日]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("狩猎祭第一战", "普雷妮")
        end
    end
end

function Quest.狩猎祭第二战(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎祭第二战") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("狩猎祭第二战", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[狩猎祭第一日]")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("[狩猎祭第二日]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("狩猎祭第二战", "莉莉")
        end
    end
end

function Quest.狩猎祭第三战(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎祭第三战") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("狩猎祭第三战", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[狩猎祭第三日]")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("[狩猎祭第三日]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("狩猎祭第三战", "莉莉")
        end
    end
end

function Quest.狂欢派对(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狂欢派对") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("狂欢派对", "普雷妮")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("狂欢派对", "普雷妮")
        end
    end
end

function Quest.莉莉的独处通知(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("莉莉的独处通知") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("莉莉的独处通知", "莉莉")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("莉莉的独处通知", "普雷妮")
        end
    end
end

function Quest.高空的狩猎派对！(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("高空的狩猎派对！") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("高空的狩猎派对！", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[空降考场]")
            MH_延时(100000)
            Instance.S_全自动刷本("[空降考场]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("高空的狩猎派对！", "莉莉")
        end
    end
end

function Quest.盛会的余韵(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("盛会的余韵") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("盛会的余韵", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --升级到38
            Instance.S_全自动刷本("试练！金毛兽王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("盛会的余韵", "伊格琳诗教官")
        end
    end
end

function Quest.凌乱的雪境(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("凌乱的雪境") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("凌乱的雪境", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("凌乱的雪境", "伊格琳诗教官")
        end
    end
end

function Quest.护送商旅(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("护送商旅") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("护送商旅", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[白银之路]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("护送商旅", "伊格琳诗教官")
        end
    end
end

function Quest.暴雪前夕(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("暴雪前夕") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("暴雪前夕", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("暴雪前夕", "伊格琳诗教官")
        end
    end
end

function Quest.白色之王(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("白色之王") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("白色之王", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("白色之王", "伊格琳诗教官")
        end
    end
end

function Quest.白王复仇(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("白王复仇") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("白王复仇", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[白王复仇]")
    				MH_延时(20000)
    				Instance.S_副本过图(7)
    				MH_延时(60000)
    				MH_击杀怪物("小雪狮子", 3)
    				Instance.S_全自动刷本("[白王复仇]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("白王复仇", "伊格琳诗教官")
        end
    end
end

function Quest.雪与星(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("雪与星") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("雪与星", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("雪与星", "伊格琳诗教官")
        end
    end
end

function Quest.沮丧的学者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("沮丧的学者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("沮丧的学者", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("沮丧的学者", "琳蒂丝")
        end
    end
end

function Quest.漫长的追寻(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("漫长的追寻") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("漫长的追寻", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到39
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("漫长的追寻", "琳蒂丝")
        end
    end
end

function Quest.王者降临(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("王者降临") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("王者降临", "西撒")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("王者降临", "“山岚”罗登")
        end
    end
end

function Quest.持有龙之眼的男子(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("持有龙之眼的男子") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("持有龙之眼的男子", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("持有龙之眼的男子", "西撒")
        end
    end
end

function Quest.天才的挑战书(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("天才的挑战书") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("天才的挑战书", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[竞速狩猎]")
            MH_补给箱取物("支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药|支给用回复药")
            MH_补给箱取物("支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药|支给用解毒药")
            MH_补给箱取物("支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石|支给用砥石")
            Instance.S_全自动刷本("[竞速狩猎]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("天才的挑战书", "埃兰")
        end
    end
end

function Quest.王家猎团的实力(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("王家猎团的实力") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("王家猎团的实力", "西撒")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("王家猎团的实力", "埃兰")
        end
    end
end

function Quest.乌合之众的志气(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("乌合之众的志气") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("乌合之众的志气", "莱维")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("乌合之众的志气", "西撒")
        end
    end
end

function Quest.集中搜索(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("集中搜索") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("集中搜索", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[全员出动]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("集中搜索", "莱维")
        end
    end
end

function Quest.唤龙之笛(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("唤龙之笛") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("唤龙之笛", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[唤龙之笛]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("唤龙之笛", "琳蒂丝")
        end
    end
end

function Quest.星落湖地(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("星落湖地") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("龙趾湖")
              MH_交任务("星落湖地", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("星落湖地", "琳蒂丝")
        end
    end
end

function Quest.最后的准备(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("最后的准备") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("最后的准备", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到40
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("龙趾湖")
            MH_接任务("最后的准备", "琳蒂丝")
        end
    end
end

function Quest.摘星之人(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("摘星之人") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("摘星之人", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[碰撞的命运]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("摘星之人", "“山岚”罗登")
        end
    end
end

function Quest.传说的达成(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("传说的达成") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("传说的达成", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("传说的达成", "“山岚”罗登")
        end
    end
end

function Quest.英雄广场开幕(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("英雄广场开幕") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("英雄广场开幕", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("英雄广场开幕", "“山岚”罗登")
        end
    end
end

function Quest.针锋相对(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("针锋相对") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("针锋相对", "西撒")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("针锋相对", "“山岚”罗登")
        end
    end
end

function Quest.王立竞技场(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("王立竞技场") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("王立竞技场", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("王立竞技场", "西撒")
        end
    end
end

function Quest.艾露族的重宝(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("艾露族的重宝") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("艾露族的重宝", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("艾露族的重宝", "“山岚”罗登")
        end
    end
end

function Quest.反击的奇面族(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("反击的奇面族") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("反击的奇面族", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[鬼脸满山]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("反击的奇面族", "维奥娜")
        end
    end
end

function Quest.奇面族大进击(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("奇面族大进击") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("奇面族大进击", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[进击的奇面族]", "身体", 0, 0.9)--BOSS 能挖出 迷之龙骨
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("奇面族大进击", "维奥娜")
        end
    end
end

function Quest.空中前哨(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("空中前哨") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("空中前哨", "维奥娜")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            MH_进入副本("[险恶之山]")
    				MH_延时(45000)
    				Instance.S_副本过图(4)
    				MH_延时(5000)
    				MH_击杀怪物("奇面族近战", 6)
    				Instance.S_全自动刷本("[险恶之山]", "身体", 0, 0.9)  --杀电龙
						MH_收起武器()
    				MH_延时(10000)
						MH_过滤式采集("尸体")

        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("空中前哨", "维奥娜")
        end
    end
end

function Quest.探险之旅(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("探险之旅") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("探险之旅", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")

        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("探险之旅", "维奥娜")
        end
    end
end


function Quest.新的明天(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("新的明天") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("新的明天", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到41
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("新的明天", "伊格琳诗教官")
        end
    end
end

function Quest.猎人的任务(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("猎人的任务") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("猎人的任务", "伊格琳诗教官")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("猎人的任务", "“山岚”罗登")
        end
    end
end

function Quest.冻土的爆破者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("冻土的爆破者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("冻土的爆破者", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[冻土的爆破者]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("冻土的爆破者", "伊格琳诗教官")
        end
    end
end

function Quest.贺菲的经历(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的经历") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("贺菲的经历", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("贺菲的经历", "贺菲")
        end
    end
end

function Quest.进化的伙伴(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("进化的伙伴") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
             MH_交任务("进化的伙伴", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[久违的共斗]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("进化的伙伴", "贺菲")
        end
    end
end

function Quest.最强小队结成(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("最强小队结成") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
             MH_交任务("最强小队结成", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[四个人的队伍！]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("最强小队结成", "贺菲")
        end
    end
end

function Quest.历史的痕迹(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("历史的痕迹") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
             MH_交任务("历史的痕迹", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("历史的痕迹", "贺菲")
        end
    end
end

function Quest.贺菲的调查(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的调查") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
             MH_交任务("贺菲的调查", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[暗幕下的秘密]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("贺菲的调查", "贺菲")
        end
    end
end

function Quest.古代文明的残音(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("古代文明的残音") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
            MH_交任务("古代文明的残音", "琳蒂丝")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("古代文明的残音", "贺菲")
        end
    end
end

function Quest.诗人的记忆(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("诗人的记忆") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("诗人的记忆", "法莱斯")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("诗人的记忆", "琳蒂丝")
        end
    end
end

function Quest.龙人之中(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("龙人之中") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("龙人之中", "娜西卡")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("龙人之中", "法莱斯")
        end
    end
end

function Quest.贺菲的登记(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("贺菲的登记") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("贺菲的登记", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("贺菲的登记", "娜西卡")
        end
    end
end

function Quest.王家猎人·贺菲(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("王家猎人·贺菲") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("王家猎人·贺菲", "贺菲")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到42
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("王家猎人·贺菲", "贺菲")
        end
    end
end

function Quest.再度告别(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("再度告别") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("再度告别", "西撒")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("再度告别", "贺菲")
        end
    end
end

function Quest.西撒的建议(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("西撒的建议") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("西撒的建议", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[王家猎团入团考试]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("西撒的建议", "西撒")
        end
    end
end

function Quest.天才的前路(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("天才的前路") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("天才的前路", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[埃兰的日常狩猎]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("天才的前路", "埃兰")
        end
    end
end

function Quest.埃兰的仰慕者(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("埃兰的仰慕者") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("埃兰的仰慕者", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("埃兰的仰慕者", "埃兰")
        end
    end
end

function Quest.天才的过去(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("天才的过去") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("天才的过去", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("[回忆中的猎场]", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("天才的过去", "埃兰")
        end
    end
end

function Quest.父亲的背影(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("父亲的背影") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("父亲的背影", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("父亲的背影", "埃兰")
        end
    end
end

function Quest.自我的锤炼(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("自我的锤炼") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("耀月林")
              MH_交任务("自我的锤炼", "埃兰")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            Instance.S_全自动刷本("试练！河狸兽", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("自我的锤炼", "埃兰")
        end
    end
end

function Quest.埃兰的领悟(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("埃兰的领悟") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
              MH_交任务("埃兰的领悟", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("耀月林")
            MH_接任务("埃兰的领悟", "埃兰")
        end
    end
end

function Quest.狩猎的难题(bHave)
    if bHave == true then -- 已有任务, 去做任务
        if MH_是否已完成任务("狩猎的难题") == 1 then -- 判断是否完成
            if MH_是否在副本() == 0 then -- 完成了, 去交任务
            	MH_调试("MH_交任务")
              City.S_地图修正("梅杰波尔坦")
             -- MH_交任务("狩猎的难题", "“山岚”罗登")
            end
        else -- 没完成任务去做任务
            MH_调试("MH_做任务")
            --等级到43
            Instance.S_全自动刷本("试练！雪狮子王", "身体", 0, 0.9)
						MH_收起武器()
    				MH_延时(2000)
						MH_过滤式采集("尸体")
        end
    else -- 没有任务去接任务
        if MH_是否在副本() == 0 then
            City.S_地图修正("梅杰波尔坦")
            MH_接任务("狩猎的难题", "“山岚”罗登")
        end
    end
end

function Quest.开场剧情()
		MH_调试("开场剧情...")
		MH_开启第一击面向()
	  MH_调试("MH_延时")
	  MH_走到目标点(1627.98, 1552.11)
	  MH_调试("MH_延时2")
    MH_延时(500)
    MH_左移()
    MH_延时(100)
    MH_停止("左移")
    MH_延时(500)
    MH_右移()
    MH_延时(100)
    MH_停止("右移")
    MH_延时(500)
    MH_后退()
    MH_延时(100)
    MH_停止("后退")
    --Instance.S_副本过图(1)
    MH_延时(3000)
		MH_调试("S_瞬移到坐标111")
    Instance.S_瞬移到坐标(1666.04,1549.93,127.43)
		MH_调试("S_瞬移到坐标112")
    MH_延时(2000)

		MH_调试("S_瞬移到坐标222")
    Instance.S_瞬移到坐标(1664.27,1593.88,129.94)
		MH_调试("S_瞬移到坐标223")

		MH_调试("S_瞬移到坐标333")
    MH_延时(45000)
    --新手香菇猪 dd 02583030
    local 当前BOSS = MH_获取BOSS()

		MH_调试("当前BOSS")
		MH_调试(当前BOSS)

    while 当前BOSS == "" do
		  MH_调试("获取当前BOSS")
      MH_延时(3000)
      当前BOSS = MH_获取BOSS()
    end

		MH_调试("当前BOSS")
		MH_调试(当前BOSS)


		MH_调试("S_全自动刷本")
    Instance.S_全自动刷本("[梦的起点]", "身体", 0, 0.5)
		MH_延时(5000)
		MH_收起武器()
		MH_翻滚()
		Instance.S_副本过图(2)
		MH_延时(45000)
		当前BOSS = MH_获取BOSS()
		MH_调试("当前BOSS")
		MH_调试(当前BOSS)

    while 当前BOSS == "" do
		  MH_调试("获取当前BOSS")
      MH_延时(3000)
      当前BOSS = MH_获取BOSS()
    end

		Instance.S_全自动刷本("[梦的起点]", "身体", 0, 0.5)
		MH_调试("S_全自动刷本完毕")
		MH_延时(5000)
		当前BOSS = MH_获取BOSS()
		MH_调试("当前BOSS")
		MH_调试(当前BOSS)

    while 当前BOSS == "" do
		  MH_调试("获取当前BOSS")
      MH_延时(3000)
      当前BOSS = MH_获取BOSS()
    end

    Instance.S_全自动刷本("[梦的起点]", "身体", 0, 0.5)
    MH_延时(50000)
end

function Quest.主线()
 		MH_调试("Quest主线")
    while MH_是否工作() == 1 do
    	MH_开启第一击面向()
        local 当前主线 = MH_获取当前主线()
        if MH_获取经验上限()<2000 then
	        if  MH_背包物品数量("成长药剂")>0 then
	         MH_调试("使用 成长药剂")
	       	 MH_通用使用物品("成长药剂")
	       	 MH_延时(3000)
	        end
        end

        if MH_获取经验上限()<2000 then
        	MH_调试("接近今天经验上限，停止主线...")
           return
        end
 			MH_调试("当前主线:"..当前主线)
        if 当前主线 ~= "" then
            local script = "Quest."..当前主线.."(true)"
            MH_执行命令文本(script)
            MH_延时(5000)
        else -- 当前没有主线
	          MH_调试("使用 自由狩猎许可证")
		        while MH_背包物品数量("自由狩猎许可证")>0 do
		       		 MH_通用使用物品("自由狩猎许可证")
		       		 MH_延时(1000)
		       	end
	          MH_调试("使用 梅杰波尔坦小钱袋")
		        while MH_背包物品数量("梅杰波尔坦小钱袋")>0 do
		       		 MH_通用使用物品("梅杰波尔坦小钱袋")
		       		 MH_延时(1000)
		       	end
	          MH_调试("使用 仓库扩容道具")
		        while MH_背包物品数量("仓库扩容道具")>0 do
		       		 MH_通用使用物品("仓库扩容道具")
		       		 MH_延时(1000)
		       	end

	          MH_调试("开始存仓")
		        MH_存仓()
	          MH_调试("存仓完毕")
            local 可接主线 = MH_获取可接主线()
 						MH_调试("可接主线:"..可接主线)
 						local 当前地图名 = MH_获取当前地图()
      		  if 当前地图名=="[梦的起点]" and 可接主线 == "猎人生活第一天" then
      		  	Quest.开场剧情()
      		  else
	            if 可接主线 ~= "" then
	                local script = "Quest."..可接主线.."(false)"
	                MH_执行命令文本(script)
	            else -- 当前没有主线, 又没有可接主线, 输出错误信息
	          		  MH_调试("当前没有主线, 又没有可接主线")
	            end
            end
        end
    end
end

function Quest.悬赏()
    local 今日已完成悬赏次数 = MH_获取今日已完成悬赏次数()
    MH_调试("今日已完成悬赏次数"..今日已完成悬赏次数)

    if 今日已完成悬赏次数 < 3 then
        local 当前悬赏 = MH_获取当前悬赏()
        if 当前悬赏 ~= "" then
            Instance.S_全自动悬赏(当前悬赏, "身体", 0.1, 0.9)
        else -- 当前没有悬赏
            -- 接着判断, 是否有已完成的悬赏
            local 完成悬赏 = MH_获取完成悬赏()
            MH_调试(完成悬赏)
            if 完成悬赏 ~= "" then
                MH_交悬赏任务(完成悬赏)
            else -- 当前没有已完成的悬赏
                MH_接受悬赏任务("试炼", "初阵")
                当前悬赏 = MH_获取当前悬赏()
                if 当前悬赏 == "" then
                		MH_接受悬赏任务("试炼", "黄金")
                		当前悬赏 = MH_获取当前悬赏()
										if 当前悬赏 == "" then
	                		MH_接受悬赏任务("试炼", "限时")
	                	end
                end
            end
        end
    else
      MH_调试("今日已完成 3 次悬赏")
    end
end
