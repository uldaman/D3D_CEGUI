����ɫ = function()
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

������Ϸ = function()
    ����ɫ()
    
    if MH_��¼��Ϸ() == 0 then
        --���н�ɫ���Ѿ�ˢ��, ֪ͨ����̨����
        return
    end
    
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