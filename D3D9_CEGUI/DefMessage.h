#pragma once

#define WM_GET_CURRENT_QUEST            WM_USER + 2301  // ��ȡ��ǰ����
#define WM_IS_QUEST_COMPLETE            WM_USER + 2302  // �ж������Ƿ������
#define WM_WHERE_ROLE                   WM_USER + 2303  // �жϵ�ǰ�����ڳ����Ǹ���, 0: ����  2: FB
#define WM_COMPLETE_QUEST               WM_USER + 2304  // ������
#define WM_GET_QUEST_TABLE              WM_USER + 2305  // ��ȡ��ǰ�ɽ�����
#define WM_ACCEPT_QUEST                 WM_USER + 2306  // ������
#define WM_INTERACTIVE_QUEST            WM_USER + 2307  // ����Ի�
#define WM_��������̽�                 WM_USER + 2308
#define WM_CITY_FLY                     WM_USER + 2309  // ������
#define WM_CHOOSE_FB                    WM_USER + 2310  // ѡ�񸱱�
#define WM_START_FB                     WM_USER + 2311  // ��ʼ����
#define WM_INTO_FB                      WM_USER + 2312  // ���븱��
#define WM_UPDATA_BOSS                  WM_USER + 2313  // ��ȡ BOSS ��
#define WM_ROLE_ROOM                    WM_USER + 2314  // ��ȡ��ǰ����
#define WM_BOSS_ROOM                    WM_USER + 2315  // ��ȡBOSS����
#define WM_GET_ZONE                     WM_USER + 2316  // ��ȡ��ǰ����
#define WM_GET_MAP                      WM_USER + 2317  // ��ȡ��ǰ��ͼ
#define WM_GOTO_BOSS                    WM_USER + 2318  // ˲�Ƶ�BOSS
#define WM_BY_MAP                       WM_USER + 2319  // ������ͼ
#define WM_TURN                         WM_USER + 2320  // ת��
#define WM_ATTACK_PACK                  WM_USER + 2321  // ����
#define WM_FORWARD                      WM_USER + 2322  // ǰ��
#define WM_STOP                         WM_USER + 2323  // ֹͣ
#define WM_ATTACK                       WM_USER + 2324  // ����
#define WM_HAVE_WEAPON                  WM_USER + 2325  // �ж��Ƿ�װ��������
#define WM_WEAPON                       WM_USER + 2326  // װ������
#define WM_GET_HP_PER                   WM_USER + 2327  // ��ȡ��ǰѪ��
#define WM_INVINCIBLE                   WM_USER + 2328  // �����޵�
#define WM_UN_INVINCIBLE                WM_USER + 2329  // �ر��޵�
#define WM_TELEPORT                     WM_USER + 2330  // ˲�Ƶ�����
#define WM_GET_POINT                    WM_USER + 2331  // ��ȡ��ǰ����
#define WM_GO_LEFT                      WM_USER + 2332  // ��
#define WM_GO_RIGHT                     WM_USER + 2333  // ��
#define WM_GO_BACK                      WM_USER + 2334  // ��
#define WM_HAVE_MODE                    WM_USER + 2335  // �Ƿ��ڲ˵�ģʽ
#define WM_CHANGE_MODE                  WM_USER + 2336  // �л��˵�ģʽ
#define WM_ROLL                         WM_USER + 2337  // ����
#define WM_GET_ITEM_FORM_CRATES         WM_USER + 2338  // ������ȡ��
#define WM_GETCOLLECT                   WM_USER + 2339  // ��ȡ�ɼ���־λ
#define WM_COLLECT                      WM_USER + 2340  // �ɼ�
#define WM_GET_COLLECTS                 WM_USER + 2341  // ��ʼ���ɼ���Ϣ
#define WM_BARBECUES                    WM_USER + 2342  // ����
#define WM_GET_BAG_ITEM_NUM             WM_USER + 2343  // �@ȡ������Ʒ����
#define WM_EAT_MEAT                     WM_USER + 2344  // �Կ���
#define WM_USE_ITEM                     WM_USER + 2345  // ͨ��ʹ����Ʒ
#define WM_PRECISION_ACCEPT_QUEST       WM_USER + 2346  // ��׼������, ͨ���ȶ� NPC ������
#define WM_MADE_HP_MEDICINE             WM_USER + 2347  // �����ظ�ҩ
#define WM_BUY_SUPPLY                   WM_USER + 2348  // ������Ʒ
#define WM_KILL_MONSTER                 WM_USER + 2349  // ��ɱ����
#define WM_GET_MONSTER_ROOM             WM_USER + 2350  // ��ȡ��ǹ��﷿��
#define WM_GOTO_MONSTER                 WM_USER + 2351  // ˲�Ƶ���ǹ�
#define WM_TURN_TO_MONSTER              WM_USER + 2352  // ת���ǹ�
#define WM_TURN_TO_POINT                WM_USER + 2353  // ת�������
#define WM_ACCEPT_OFFER_A_REWARD        WM_USER + 2354  // ��������
#define WM_GET_CURRENT_REWARD           WM_USER + 2355  // ��ȡ��ǰ��������
#define WM_GET_REWARD_FB                WM_USER + 2356  // ��ȡ���͸���
#define WM_GET_COUNT_REWARD_TODAY       WM_USER + 2357  // ��ȡ������������ʹ���
#define WM_GET_ACCEPT_REWARD            WM_USER + 2358  // ��ȡ�ɽ�����
#define WM_ACCEPT_REWARD                WM_USER + 2359  // ������
#define WM_�����������̽�               WM_USER + 2360  // �����������̽�
#define WM_GET_EXP_LIMIT                WM_USER + 2361  // ��ȡ��������
#define WM_GET_WAREHOUSE_ITEM_NUM       WM_USER + 2362  // �ֿ���Ʒ����
#define WM_INTO_MY_MANOR                WM_USER + 2363  // �����ҵ�ׯ԰
#define WM_LEAVE_MANOR                  WM_USER + 2364  // �뿪ׯ԰
#define WM_UPGRADE_MUSHROOM             WM_USER + 2365  // ��������ľ��
#define WM_MOVE_ITEM_IN_WAREHOUSE       WM_USER + 2366  // ���
#define WM_GETBAG                       WM_USER + 2367  // ��ʼ������
#define WM_����嶡������               WM_USER + 2368
#define WM_EAT_MEDICINE                 WM_USER + 2369  // ���ӳٳԻظ�ҩ
#define WM_PAY_ITEMS                    WM_USER + 2370  // ������Ʒ
#define WM_GET_GLOWING_ARTICLE          WM_USER + 2371  // ��ȡ������Ʒ
#define WM_��������è                   WM_USER + 2372
#define WM_װ��������                   WM_USER + 2373
#define WM_TAKE_MEDICINE                WM_USER + 2374  // �ݴ�ʽ��ҩ
#define WM_WEAR_EQUIPMENT               WM_USER + 2375  // ��װ��
#define WM_GET_ROLE_LEVEL               WM_USER + 2376  // ��ȡ����ȼ�
#define WM_PRECISION_COMPLETE_QUEST     WM_USER + 2377  // ��׼������, ͨ���ȶ� NPC ������
#define WM_FIRST_ATTACK_TRUN            WM_USER + 2378  // ������һ������
#define WM_LOGIN                        WM_USER + 2379  // ��¼��Ϸ
#define WM_NEW_ROLE                     WM_USER + 2380  // �½���ɫ
#define WM_COUNTS_OF_ROLES              WM_USER + 2381  // ��ǰ��ɫ����
#define WM_ENTER_CHANNEL                WM_USER + 2382  // ȷ��Ƶ��
#define WM_IS_ONLINE                    WM_USER + 2383  // �Ƿ�����
#define WM_IS_LOADING                   WM_USER + 2384  // �Ƿ��ͼ
//#define WM_INIT_ROLE_LIST               WM_USER + 2385  // ��ʼ����ɫ�б�
#define WM_IS_SELECT                    WM_USER + 2386  // �Ƿ���ѡ���ɫ
#define WM_��ȡ�ɳ������һ�ȯ           WM_USER + 2387  // ��ȡ�ɳ������һ�ȯ
#define WM_�һ�����֮��                 WM_USER + 2388  // �һ�����֮��
#define WM_�һ�����֮��                 WM_USER + 2389  // �һ�����֮��