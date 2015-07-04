City = {}

City.城镇 = {}

City.城镇["希美伦山路"] = {}
City.城镇["希美伦山路"]["米拉德村"] = { key = "HubToVillageTrigger" }
City.城镇["希美伦山路"]["龙趾湖"] = { key = "Hub1ToHub2Triigger" }

City.城镇["米拉德村"] = {}
City.城镇["米拉德村"]["希美伦山路"] = { key = "VillageToHubTrigger" }

City.城镇["龙趾湖"] = {}
City.城镇["龙趾湖"]["希美伦山路"] = { key = "Teleporter_To_Hub001" }
City.城镇["龙趾湖"]["梅杰波尔坦"] = { key = "Teleporter_To_Village02" }

City.城镇["梅杰波尔坦"] = {}
City.城镇["梅杰波尔坦"]["龙趾湖"] = { key = "Village2_To_Hub2_Trigger" }
City.城镇["梅杰波尔坦"]["耀月林"] = { key = "Village2_To_Hub3_Trigger" }

City.城镇["耀月林"] = {}
City.城镇["耀月林"]["梅杰波尔坦"] = { key = "TeleporterToVillage02" }

--根据地图名称查找ID, 此ID为计数用, 并非游戏真实ID
function City.查找地图ID(mapName)
	local id = 1
	for i, v in pairs(City.城镇) do
		if mapName == i then
			break
		end
		id = id + 1
	end
	return id
end

--根据ID序号查找地图名称
function City.查找地图名称(k)
	local find_map = ""
	local id = 1
	for i, v in pairs(City.城镇) do
		if id == k then
			find_map = i
		end
		id = id + 1
	end
	return find_map
end

function City.获取寻图路径(tagMap)	--返回途径总地图(包括起始地图和目标地图)列表, 和起始图到终点图的总个数(包括起始地图和目标地图)
	local nowMap = MH_获取当前地图()

	if nowMap == tagMap then
		return nil, 0
	end

	MH_调试("起始地图是 "..nowMap)
	MH_调试("目标地图是 "..tagMap)

	local count_map = 0	--地图节点总数量
	for i,v in pairs(City.城镇) do
		count_map = count_map + 1
	end

	--建立好邻接矩阵, 并初始化
	dist = {}		--记录起点到各个点的最短距离
	final = {}		--是否是已经确定过的节点
	prev = {}		--记录当前点的前一个节点

	for i = 1, count_map do		--初始化
		dist[i] = 65535
		final[i] = 0

		local temp_map = City.查找地图名称(i)

		if City.城镇[nowMap][temp_map] ~= nil then
			dist[i] = 1
			prev[i] = nowMap
		else
			prev[i] = ""
		end
	end

	local ZoneNum = City.查找地图ID(nowMap)
	dist[ZoneNum] = 0
	final[ZoneNum] = 1

-----------------------------------------------
--现在开始主循环, 每次求得源点到某个节点的最短路径
	for i = 2, count_map do
		local tmp_min = 65535	--临时最小路径
		local tmp_map1 = nowMap	--临时当前节点
		for j = 1, count_map do
			if final[j] == 0 and dist[j] < tmp_min then
				tmp_min = dist[j]
				tmp_map1 = City.查找地图名称(j)
			end
		end

		final[City.查找地图ID(tmp_map1)] = 1

		if tmp_map1 == tagMap then	--如果找到目标节点的最短路径就立即返回
			break
		end

		--修正临时当前节点的周边节点的最短路径
		for j = 1, count_map do
			if final[j] == 0 then	--节点未被确定
				local temp_map2 = City.查找地图名称(j)
				if tmp_map1 ~= nil and temp_map2 ~= nil then
					if City.城镇[tmp_map1][temp_map2] ~= nil then
						local newDist = dist[City.查找地图ID(tmp_map1)] + 1
						if newDist < dist[j] then
							dist[j] = newDist
							prev[j] = tmp_map1
						end
					end
				end
			end
		end
	end
--循环完成

	local map_id = City.查找地图ID(tagMap)

	if dist[map_id] == 65535 then
		MH_调试("两地图不可到达")
		return nil, 0
	end

	MH_调试("需要过 "..dist[map_id].." 次地图")	--要过多少次图

--开始匹配查找最短路径(反向匹配)

	local pass_map_list = {}	--保存着过图节点,包括源点和终点
	local tot = 1	--过图数量,包括源点和终点
	pass_map_list[tot] = tagMap	--先取出终点, (反向匹配)
	tot = tot + 1

	local tmp_prev = prev[map_id]	--取出目标点的前驱

	while MH_是否工作() == 1 and tmp_prev ~= nowMap do
		pass_map_list[tot] = tmp_prev
		tot = tot + 1
		tmp_prev = prev[City.查找地图ID(tmp_prev)]
	end
	pass_map_list[tot] = nowMap	--源点

	MH_调试("途径 "..tot.." 张地图[包括起点和终点]")	--过图总数量,包括源点和终点

--	for i = 1, tot do
--		MH_调试(pass_map_list[tot-i+1])	--所有经过的节点
--	end

	return pass_map_list, tot
end

function City.S_地图修正(tagMap)
	--判断目标地图是否存在
	local is_exist = false
	for i, v in pairs(City.城镇) do
		if i == tagMap then
			is_exist = true
			break
		end
	end
	if not is_exist then
		MH_调试("目标地图不存在")
		return	--地图不存在
	end

    local nowMap = MH_获取当前地图()
	local pass_map_list, tot = City.获取寻图路径(tagMap)   --pass_map_list为途径总地图(包括起始地图和目标地图), tot为起始图到终点图的总个数
	if pass_map_list ~= nil and tot > 0 then	--匹配到最短路径
		for i = 1, tot - 1 do	--每次for循环就是过一次图, tot为起始图到终点图的总个数 ,tot -1 才是过图的次数
			while MH_是否工作() == 1 and nowMap ~= pass_map_list[tot-i] do
				--pass_map_list[tot-i] 临时目标地图 pass_map_list[tot-i+1] 临时当前地图
                MH_调试(City.城镇[pass_map_list[tot-i+1]][pass_map_list[tot-i]].key)
                MH_城镇飞图(City.城镇[pass_map_list[tot-i+1]][pass_map_list[tot-i]].key)
				MH_延时(2000)
				nowMap = MH_获取当前地图()
			end
		end
		MH_调试("已到达目标地点!")
        MH_延时(10000)
	end
--到达目标地图
end