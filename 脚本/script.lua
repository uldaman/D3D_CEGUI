MH_���ؽű�("S/City_.lub")
MH_���ؽű�("S/Instance_.lub")
MH_���ؽű�("S/Quest_.lub")

--Quest.����()
local ����ɫ = function()
::��鿪ʼ::
    if MH_�Ƿ���() == 1 then
        local ��ɫ���� = MH_��ǰ��ɫ����()
        if ��ɫ���� < 6 then
            for i = ��ɫ���� + 1, 6 do
                MH_�½���ɫ()
                MH_��ʱ(1000)
                if MH_�Ƿ���() == 0 then
                    return
                end
            end
            goto ��鿪ʼ
        end
    end
end

local ������Ϸ = function()
    ����ɫ()
    MH_��¼��Ϸ()
    MH_��ʱ(1000)
    MH_ȷ��Ƶ��()
    
    while MH_�Ƿ���() == 1 do
        local �Ƿ����� = MH_�Ƿ�����()
        if �Ƿ����� == 1 then
            return
        end
        MH_��ʱ(1000)
    end
end

--������Ϸ()
--Quest.����()
Instance.S_ȫ�Զ�ˢ��("[������ѵ������]", "����", 0, 0.9)
-- while MH_�Ƿ���() == 1 do
    -- local �Ƿ����� = MH_�Ƿ�����()
    -- local �Ƿ���ѡ���ɫ���� = MH_�Ƿ���ѡ���ɫ()
    -- local �Ƿ��ͼ = MH_�Ƿ��ͼ��()
    
    -- if �Ƿ��ͼ == 1 then
        -- MH_����("��ͼ��")
    -- elseif �Ƿ����� == 1 then                 
        -- MH_����("��Ϸ��")   
    -- elseif �Ƿ���ѡ���ɫ���� == 1 then --�º��޷��ж�..
        -- MH_����("ѡ���ɫ")
    -- else
        -- MH_����("��δ����������")
    -- end
    
    -- MH_��ʱ(1000)
-- end