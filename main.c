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
    int addr;//������ʼ��ַ
    int length;//������С
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
void setMen(FreeMen_block **newMen,int addr,int length){
    (*newMen) = (FreeMen_block*)malloc(sizeof(FreeMen_block));
    (*newMen)->addr = addr;
    (*newMen)->length = length;
    //(*newMen)->prev = NULL;
    (*newMen)->next = NULL;
}
void initialize(){
    //��ʼ��
    FreeMen_block *first;
    setMen(&first,0,0);
    memory_plist = (Men_Plist *)malloc(sizeof(Men_Plist));
    memory_plist->first = first;
}
int insert(FreeMen_block *newFree,int tag){
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    if(tag==0){     //�����״���Ӧ�㷨��ѭ���״���Ӧ�㷨
        while(q!=NULL){
            if(newFree->addr<=q->addr){
                newFree->next = q;
                p->next = newFree;
                return 1;   //����ɹ�
            }
            p = p->next;
            q = q->next;
        }
        p->next = newFree;
        return 1;
    }else if(tag==1){   //�����Ӧ�㷨
        while(q!=NULL){
            if(newFree->length<=q->length){
                newFree->next = q;
                p->next = newFree;
                return 1;
            }
            p = p->next;
            q = q->next;
        }
        p->next = newFree;
        return 1;
    }
}
void creat_plist1(){
    initialize();
    FreeMen_block *p1,*p2,*p3;
    setMen(&p1,20,120);
    setMen(&p2,200,100);
    setMen(&p3,400,60);
    insert(p3,0);
    insert(p2,0);
    insert(p1,0);
}
void creat_plist2(){
    initialize();
    FreeMen_block *p1,*p2,*p3;
    setMen(&p1,20,120);
    setMen(&p2,200,100);
    setMen(&p3,400,60);
    insert(p3,1);
    insert(p2,1);
    insert(p1,1);
}
//�����㷨
/*
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
*/
int firstFit(){
    int load;
    //creat_plist1();
    //outPut();
    printf("��������������ڴ��С��");
    scanf("%d",&load);
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(load<q->length){
            p->next = q->next;  //����һ�������ڴ����void
             outPut();
            return 1;   //����ɹ�
        }
        p = p->next;
        q = q->next;
    }
    printf("��ǰ���з�����С��������������Ľ��̣�������ѡ�����!\n");
    return 0;   //����ʧ��
}
int Circle_firstFit(){
    int load;
    printf("��������������ڴ��С��");
    scanf("%d",&load);
}
void Distribute(){
    char operate;
    oneWindow();
    creat_plist2();
    outPut();
    while(1){
        scanf("%c",&operate);
        switch(operate){
        case 'A':
            firstFit();
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
void outPut(){
    printf("  ***************  ��ǰ���з�����״̬  **************\n\n");
    FreeMen_block *p=memory_plist->first->next;
    while(p!=NULL){
        printf("���з�����ʼ��ַ�ʹ�С��%d %d\n",p->addr,p->length);
        p = p->next;
    }
}
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


