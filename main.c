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
    FreeMen_block *tag;     //ѭ���״���Ӧ�㷨��־ָ��
void initialize();
int insert(FreeMen_block *newFree);
int recovery_memory(int val);
void Recover0();
void Recover1();
void mainWindow();  //������
void oneWindow();
void twoWindow();
void outPut();  //����ڴ���Ϣ
void FFT();     //�״���Ӧ�㷨
void CFFT();    //ѭ���״���Ӧ�㷨
void BF();      //�����Ӧ�㷨
int main()
{
    char choose;
    initialize();
    outPut();
    mainWindow();
    while(1){
       scanf("%c",&choose);
       switch(choose){
       case 'A':
           FFT();
        break;
       case 'B':
           CFFT();
        break;
       case 'C':
           BF();
        break;
       case 'D':
           system("cls");
           outPut();
           mainWindow();
        break;
       case 'E':
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
    (*newMen)->next = NULL;
}
void initialize(){//��ʼ��
    FreeMen_block *first;
    setMen(&first,0,0);
    memory_plist = (Men_Plist *)malloc(sizeof(Men_Plist));
    memory_plist->first = first;
    tag = (FreeMen_block *)malloc(sizeof(FreeMen_block));
    tag = memory_plist->first;
    FreeMen_block *p1,*p2,*p3;
    setMen(&p1,20,120);
    setMen(&p2,200,100);
    setMen(&p3,400,60);
    insert(p3);
    insert(p2);
    insert(p1);
}
int insert(FreeMen_block *newFree){
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
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
}
int length(){
    int length=0;
    FreeMen_block *p = memory_plist->first;
    while(p->next!=NULL){
        length++;
        p=p->next;
    }
    return length;
}
void sort(){    //���տ�������С��С��������
    int i,j;
    int n;
    n = length();
    FreeMen_block *temp = (FreeMen_block *)malloc(sizeof(FreeMen_block));
    for(i=0;i<n;i++){
        FreeMen_block *p = memory_plist->first;
        for(j = 0;j<n-i;j++){
            if(p->length > p->next->length){
                temp->addr = p->addr;
                temp->length = p->length;
                p->addr = p->next->addr;
                p->length = p->next->length;
                p->next->addr = temp->addr;
                p->next->length = temp->length;
            }
            p = p->next;
        }
    }
}
int firstFit(){
    int load;
    printf("��������������ڴ��С��");
    scanf("%d",&load);
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(load<=q->length){
            q->length = q->length - load;
            if(q->length==0){
                p->next = q->next;
            }
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
    if(tag->next==NULL){
        tag = memory_plist->first;
    }
    while(tag->next!=NULL){
        FreeMen_block *p = tag;
        FreeMen_block *q = tag->next;
        if(load<=tag->next->length){
            tag->next->length = tag->next->length-load;
            if(tag->next->length==0){
                p->next = q->next;
            }
            tag = tag->next;
            outPut();
            return 1;   //����ɹ�
        }
        p = p->next;
        q = q->next;
    }
    printf("��ǰ���з�����С��������������Ľ��̣�������ѡ�����!\n");
    return 0;
}
int bestFit(){
    int load;
    sort();
    printf("��������������ڴ��С��");
    scanf("%d",&load);
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(load<=q->length){
            q->length = q->length - load;
            if(q->length==0){
                p->next = q->next;
            }
           // p->next = q->next;  //����һ�������ڴ����void
            sort();
            outPut();
            return 1;   //����ɹ�
        }
        p = p->next;
        q = q->next;
    }
    printf("��ǰ���з�����С��������������Ľ��̣�������ѡ�����!\n");
    return 0;   //����ʧ��
}
void FFT(){
    char operate;
    oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case '1':
            firstFit();
            printf("������������еĲ�����\n");
            break;
        case '2':
            recovery_memory(0);
            break;
        default:
            mainWindow();
            return;
        }
    }
}
void  CFFT(){
    char operate;
    oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case '1':
            Circle_firstFit();
            printf("������������еĲ�����\n");
            break;
        case '2':
            recovery_memory(0);
            break;
        case '3':
            mainWindow();
            return;
        default:
            break;
        }
    }
}
void  BF(){
    char operate;
    oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case '1':
            bestFit();
            printf("������������еĲ�����\n");
            break;
        case '2':
            recovery_memory(1);
            break;
        default:
            mainWindow();
            return;
        }
    }
}
int recovery_memory(int val){
    int addr_b;
    int length_b;
    FreeMen_block *newFree;
    printf("������������յ��ڴ���ʼ��ַ:");
    scanf("%d",&addr_b);
    printf("����������ռ�Ĵ�С��");
    scanf("%d",&length_b);
    setMen(&newFree,addr_b,length_b);
    FreeMen_block *p = memory_plist->first->next;
    while(p!=NULL){
        if(addr_b<p->addr && (addr_b+length_b)==p->addr){
            p->addr = addr_b;
            p->length = p->length+length_b;
            printf("���պ�Ŀ��������������:\n");
            outPut();
            return 1;
        }else if((p->addr+p->length)== addr_b && (addr_b+length_b) == (p->next->addr)){
            p->length = p->length+length_b+p->next->length;
            p->next = p->next->next;
            printf("���պ�Ŀ��������������:\n");
            outPut();
            return 1;
        }else if(addr_b>p->addr && (p->addr+p->length)==addr_b){
            p->length = p->length+length_b;
            printf("���պ�Ŀ��������������:\n");
            outPut();
            return 1;
        }else if(addr_b==p->addr){
            printf("��Ч�ĵ�ַ��\n");
        }
        /*else{
            insert(newFree);
            if(val==1){
                sort();
            }
            printf("���պ�Ŀ��������������:\n");
            outPut();
            return 1;
        }
        */
        p = p->next;
    }
    insert(newFree);
    if(val==1){
        sort();
    }
    printf("���պ�Ŀ��������������:\n");
    outPut();
    return 1;
}
/*
void Recover0(){
    char operate;
    //oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case 'A':
            recovery_memory(0);
            break;
        case 'B':
            break;
        default:
            break;
        }
    }
};
void Recover1(){
    char operate;
    //oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case 'A':
            recovery_memory(1);
            break;
        case 'B':
            break;
        default:
            break;
        }
    }
};
*/
void outPut(){
    printf("***************  ��ǰ���з�����״̬  **************\n\n");
    FreeMen_block *p=memory_plist->first->next;
    while(p!=NULL){
        printf("���з�����ʼ��ַ�ʹ�С��%d %d\n",p->addr,p->length);
        p = p->next;
    }
    printf("\n");
}
void mainWindow(){
    printf("***************  �ڴ�Ķ�̬��������  ***************\n");
    printf("�㷨ѡ��\n");
    printf("��������������������������������������������\n");
    printf("��            A.�״���Ӧ�㷨              ��\n");
    printf("��                                        ��\n");
    printf("��            B.ѭ���״���Ӧ�㷨          ��\n");
    printf("��                                        ��\n");
    printf("��            C.�����Ӧ�㷨              ��\n");
    printf("��                                        ��\n");
    printf("��            D.��    ��                  ��\n");
    printf("��                                        ��\n");
    printf("��            E.�˳�����                  ��\n");
    printf("��������������������������������������������\n");
    printf("������������еĲ�����\n");
}
void oneWindow(){
    printf("\n");
    printf("***************  ����  ***************\n");
    printf("��������������������������������������������\n");
    printf("��            1.�ڴ����                  ��\n");
    printf("��                                        ��\n");
    printf("��            2.�ڴ����                  ��\n");
    printf("��                                        ��\n");
    printf("��            3.������һ��                ��\n");
    printf("��������������������������������������������\n");
    printf("������������еĲ�����\n");
}
void twoWindow(){
    printf("***************  �ڴ����  ***************\n\n");
    printf("�������������������ʼ��ַ��\n");
}


