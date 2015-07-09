City = {}

City.���� = {}

City.����["ϣ����ɽ·"] = {}
City.����["ϣ����ɽ·"]["�����´�"] = { key = "HubToVillageTrigger" }
City.����["ϣ����ɽ·"]["��ֺ��"] = { key = "Hub1ToHub2Triigger" }

City.����["�����´�"] = {}
City.����["�����´�"]["ϣ����ɽ·"] = { key = "VillageToHubTrigger" }

City.����["��ֺ��"] = {}
City.����["��ֺ��"]["ϣ����ɽ·"] = { key = "Teleporter_To_Hub001" }
City.����["��ֺ��"]["÷�ܲ���̹"] = { key = "Teleporter_To_Village02" }

City.����["÷�ܲ���̹"] = {}
City.����["÷�ܲ���̹"]["��ֺ��"] = { key = "Village2_To_Hub2_Trigger" }
City.����["÷�ܲ���̹"]["ҫ����"] = { key = "Village2_To_Hub3_Trigger" }

City.����["ҫ����"] = {}
City.����["ҫ����"]["÷�ܲ���̹"] = { key = "TeleporterToVillage02" }

--���ݵ�ͼ���Ʋ���ID, ��IDΪ������, ������Ϸ��ʵID
function City.���ҵ�ͼID(mapName)
	local id = 1
	for i, v in pairs(City.����) do
		if mapName == i then
			break
		end
		id = id + 1
	end
	return id
end

--����ID��Ų��ҵ�ͼ����
function City.���ҵ�ͼ����(k)
	local find_map = ""
	local id = 1
	for i, v in pairs(City.����) do
		if id == k then
			find_map = i
		end
		id = id + 1
	end
	return find_map
end

function City.��ȡѰͼ·��(tagMap)	--����;���ܵ�ͼ(������ʼ��ͼ��Ŀ���ͼ)�б�, ����ʼͼ���յ�ͼ���ܸ���(������ʼ��ͼ��Ŀ���ͼ)
	local nowMap = MH_��ȡ��ǰ��ͼ()

	if nowMap == tagMap then
		return nil, 0
	end

	MH_����("��ʼ��ͼ�� "..nowMap)
	MH_����("Ŀ���ͼ�� "..tagMap)

	local count_map = 0	--��ͼ�ڵ�������
	for i,v in pairs(City.����) do
		count_map = count_map + 1
	end

	--�������ڽӾ���, ����ʼ��
	dist = {}		--��¼��㵽���������̾���
	final = {}		--�Ƿ����Ѿ�ȷ�����Ľڵ�
	prev = {}		--��¼��ǰ���ǰһ���ڵ�

	for i = 1, count_map do		--��ʼ��
		dist[i] = 65535
		final[i] = 0

		local temp_map = City.���ҵ�ͼ����(i)

		if City.����[nowMap][temp_map] ~= nil then
			dist[i] = 1
			prev[i] = nowMap
		else
			prev[i] = ""
		end
	end

	local ZoneNum = City.���ҵ�ͼID(nowMap)
	dist[ZoneNum] = 0
	final[ZoneNum] = 1

-----------------------------------------------
--���ڿ�ʼ��ѭ��, ÿ�����Դ�㵽ĳ���ڵ�����·��
	for i = 2, count_map do
		local tmp_min = 65535	--��ʱ��С·��
		local tmp_map1 = nowMap	--��ʱ��ǰ�ڵ�
		for j = 1, count_map do
			if final[j] == 0 and dist[j] < tmp_min then
				tmp_min = dist[j]
				tmp_map1 = City.���ҵ�ͼ����(j)
			end
		end

		final[City.���ҵ�ͼID(tmp_map1)] = 1

		if tmp_map1 == tagMap then	--����ҵ�Ŀ��ڵ�����·������������
			break
		end

		--������ʱ��ǰ�ڵ���ܱ߽ڵ�����·��
		for j = 1, count_map do
			if final[j] == 0 then	--�ڵ�δ��ȷ��
				local temp_map2 = City.���ҵ�ͼ����(j)
				if tmp_map1 ~= nil and temp_map2 ~= nil then
					if City.����[tmp_map1][temp_map2] ~= nil then
						local newDist = dist[City.���ҵ�ͼID(tmp_map1)] + 1
						if newDist < dist[j] then
							dist[j] = newDist
							prev[j] = tmp_map1
						end
					end
				end
			end
		end
	end
--ѭ�����

	local map_id = City.���ҵ�ͼID(tagMap)

	if dist[map_id] == 65535 then
		MH_����("����ͼ���ɵ���")
		return nil, 0
	end

	MH_����("��Ҫ�� "..dist[map_id].." �ε�ͼ")	--Ҫ�����ٴ�ͼ

--��ʼƥ��������·��(����ƥ��)

	local pass_map_list = {}	--�����Ź�ͼ�ڵ�,����Դ����յ�
	local tot = 1	--��ͼ����,����Դ����յ�
	pass_map_list[tot] = tagMap	--��ȡ���յ�, (����ƥ��)
	tot = tot + 1

	local tmp_prev = prev[map_id]	--ȡ��Ŀ����ǰ��

	while MH_�Ƿ���() == 1 and tmp_prev ~= nowMap do
		pass_map_list[tot] = tmp_prev
		tot = tot + 1
		tmp_prev = prev[City.���ҵ�ͼID(tmp_prev)]
	end
	pass_map_list[tot] = nowMap	--Դ��

	MH_����(";�� "..tot.." �ŵ�ͼ[���������յ�]")	--��ͼ������,����Դ����յ�

--	for i = 1, tot do
--		MH_����(pass_map_list[tot-i+1])	--���о����Ľڵ�
--	end

	return pass_map_list, tot
end

function City.S_��ͼ����(tagMap)
	--�ж�Ŀ���ͼ�Ƿ����
	local is_exist = false
	for i, v in pairs(City.����) do
		if i == tagMap then
			is_exist = true
			break
		end
	end
	if not is_exist then
		MH_����("Ŀ���ͼ������")
		return	--��ͼ������
	end

    local nowMap = MH_��ȡ��ǰ��ͼ()
	local pass_map_list, tot = City.��ȡѰͼ·��(tagMap)   --pass_map_listΪ;���ܵ�ͼ(������ʼ��ͼ��Ŀ���ͼ), totΪ��ʼͼ���յ�ͼ���ܸ���
	if pass_map_list ~= nil and tot > 0 then	--ƥ�䵽���·��
		for i = 1, tot - 1 do	--ÿ��forѭ�����ǹ�һ��ͼ, totΪ��ʼͼ���յ�ͼ���ܸ��� ,tot -1 ���ǹ�ͼ�Ĵ���
			while MH_�Ƿ���() == 1 and nowMap ~= pass_map_list[tot-i] do
				--pass_map_list[tot-i] ��ʱĿ���ͼ pass_map_list[tot-i+1] ��ʱ��ǰ��ͼ
                MH_����(City.����[pass_map_list[tot-i+1]][pass_map_list[tot-i]].key)
                MH_�����ͼ(City.����[pass_map_list[tot-i+1]][pass_map_list[tot-i]].key)
				MH_��ʱ(2000)
				nowMap = MH_��ȡ��ǰ��ͼ()
			end
		end
		MH_����("�ѵ���Ŀ��ص�!")
        MH_��ʱ(10000)
	end
--����Ŀ���ͼ
end