#include <stdio.h>
#include <stdlib.h>
/*
��̬��������
1 �ڴ���䣺����������ڴ�ռ��С���ֱ���
�״���Ӧ�㷨��
�����Ӧ�㷨��
ѭ���״���Ӧ�㷨
����ڴ���䣬��ʾ���з��������ڵ���Ϣ��
2 �ڴ���գ��������������ʼ��ַ������ڴ���ա������ϲ���
��ʾ�ϲ�����������ڵ���Ϣ��
*/
typedef struct freeMen{
    int length;//������С
    int addr;//������ʼ��ַ
    struct freeMen *next;//ָ���һ�����з�����ָ��
    //struct freeMen *prev;//ָ��ǰһ�������ڵ��ָ��
}FreeMen_block;
typedef struct menPlist{
    FreeMen_block *first;
}Men_Plist;
    Men_Plist *memory_plist;
void Distribute();
void Recover();
void mainWindow();
void oneWindow();
void twoWindow();
int main()
{
    char choose;
    mainWindow();
    while(1){
       scanf("%c",&choose);
       switch(choose){
       case '1':
           Distribute();
        break;
       case '2':
           Recover();
        break;
       case '3':
           exit(0);
        break;
       default:
            break;
       }
    }
    return 0;
}
void setMen(FreeMen_block **newMen,int length,int addr){
    (*newMen) = (FreeMen_block*)malloc(sizeof(FreeMen_block));
    (*newMen)->length = 0;
    (*newMen)->addr = 0;
    //(*newMen)->prev = NULL;
    (*newMen)->next = NULL;
}
void initialize(){
    //��ʼ��
    FreeMen_block *first;
    setMen(&first,0,0);
    memory_plist = (Men_Plist *)malloc(sizeof(Men_Plist));
    memory_Plist->first = first;
}
void insert(){
    FreeMen_block *newFree;
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    if(q!=NULL){
        newFree->next = q;
        p->next = newFree;
    }else{
        p->next = newFree;
    }
}
//�����㷨
void sort(int x){
    //FreeMen_block  *p = memory_plist->first;
    int temp;
    FreeMen_block  *p = memory_plist->first->next;
    while(p!=NULL){
        FreeMen_block *q = p->next;
        if(p->addr>q->addr){
            temp = p->addr;
            p->addr = q->addr;
            q->addr = temp;
        }
        p = p->next;
        q = q->next;
    }
}
void firstFit(Men_Plist *memory_plist){


}
void Distribute(){
    char operate;
    oneWindow();
    while(1){
        scanf("%c",&operate);
        switch(operate){
        case 'A':
            break;
        case 'B':
            break;
        default:
            break;
        }
    }
};
void Recover(){
    char operate;
    oneWindow();
    while(1){
        scanf("%c",&operate);
        switch(operate){
        case 'A':
            break;
        case 'B':
            break;
        default:
            break;
        }
    }
};
void mainWindow(){
    printf("  ***************  �ڴ�Ķ�̬��������  ***************\n");
    printf("��������������������������������������������\n");
    printf("��            1.�ڴ����                  ��\n");
    printf("��                                        ��\n");
    printf("��            2.�ڴ����                  ��\n");
    printf("��                                        ��\n");
    printf("��            3.�˳�����                  ��\n");
    printf("��������������������������������������������\n");
    printf("������������еĲ�����\n");
}
void oneWindow(){
    printf("  ***************  �ڴ����  ***************\n");
    printf("��������������������������������������������\n");
    printf("��            A.�״���Ӧ�㷨              ��\n");
    printf("��                                        ��\n");
    printf("��            B.ѭ���״���Ӧ�㷨          ��\n");
    printf("��                                        ��\n");
    printf("��            C.�����Ӧ�㷨              ��\n");
    printf("��                                        ��\n");
    printf("��            D.������һ��                ��\n");
    printf("��������������������������������������������\n");
    printf("������������еĲ�����\n");
}

void twoWindow(){
    printf("  ***************  �ڴ����  ***************\n\n");
    printf("�������������������ʼ��ַ��\n");
}


