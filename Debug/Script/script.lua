MH_���ؽű�("City_.lua")
MH_���ؽű�("Instance_.lua")
MH_���ؽű�("Quest_.lua")
MH_���ؽű�("Login_.lua")

while MH_�Ƿ���() == 1 do
    local �Ƿ����� = MH_�Ƿ�����()
    local �Ƿ���ѡ���ɫ���� = MH_�Ƿ���ѡ���ɫ()
    local �Ƿ��ͼ = MH_�Ƿ��ͼ��()
    
    if �Ƿ��ͼ == 1 then
        MH_����("��ͼ��")
    elseif �Ƿ����� == 1 then                 
        MH_����("��Ϸ��")
    elseif �Ƿ���ѡ���ɫ���� == 1 then --�º��޷��ж�..
        MH_����("ѡ���ɫ")
        ������Ϸ()
    else
        MH_����("��δ����������")
    end
    
    MH_��ʱ(1000)
end
