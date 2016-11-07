#include <stdio.h>
#include <stdlib.h>
/*
动态分区管理
1 内存分配：输入请求的内存空间大小，分别用
首次适应算法、
最佳适应算法、
循环首次适应算法
完成内存分配，显示空闲分区链各节点信息。
2 内存回收：输入回收区的起始地址，完成内存回收、分区合并、
显示合并后空闲链各节点信息。
*/
typedef struct freeMen{
    int addr;//分区起始地址
    int length;//分区大小
    struct freeMen *next;//指向后一个空闲分区的指针
    //struct freeMen *prev;//指向前一个分区节点的指针
}FreeMen_block;
typedef struct menPlist{
    FreeMen_block *first;
}Men_Plist;
    Men_Plist *memory_plist;
    FreeMen_block *tag;     //循环首次适应算法标志指针
//void Distribute();
void creat_plist();
void Recover();
void mainWindow();
void oneWindow();
void twoWindow();
void outPut();
void FFT();
void CFFT();
void BF();
int main()
{
    char choose;
    creat_plist();
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
void initialize(){//初始化
    FreeMen_block *first;
    setMen(&first,0,0);
    memory_plist = (Men_Plist *)malloc(sizeof(Men_Plist));
    memory_plist->first = first;
    tag = (FreeMen_block *)malloc(sizeof(FreeMen_block));
    tag = memory_plist->first;
}
int insert(FreeMen_block *newFree){
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(newFree->addr<=q->addr){
            newFree->next = q;
            p->next = newFree;
            return 1;   //插入成功
        }
        p = p->next;
        q = q->next;
    }
    p->next = newFree;
    return 1;
}
void creat_plist(){
    initialize();
    FreeMen_block *p1,*p2,*p3;
    setMen(&p1,20,120);
    setMen(&p2,200,100);
    setMen(&p3,400,60);
    insert(p3);
    insert(p2);
    insert(p1);
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
void sort(){    //按照空闲区大小从小到大排序
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
    printf("请输入您请求的内存大小：");
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
            return 1;   //分配成功
        }
        p = p->next;
        q = q->next;
    }
    printf("当前空闲分区大小不能满足您请求的进程！请重新选择操作!\n");
    return 0;   //分配失败
}
int Circle_firstFit(){
    int load;
    printf("请输入您请求的内存大小：");
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
            return 1;   //分配成功
        }
        p = p->next;
        q = q->next;
    }
    printf("当前空闲分区大小不能满足您请求的进程！请重新选择操作!\n");
    return 0;
}
int bestFit(){
    int load;
    sort();
    printf("请输入您请求的内存大小：");
    scanf("%d",&load);
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(load<=q->length){
            q->length = q->length - load;
            if(q->length==0){
                p->next = q->next;
            }
           // p->next = q->next;  //将第一个空闲内存分配void
            sort();
            outPut();
            return 1;   //分配成功
        }
        p = p->next;
        q = q->next;
    }
    printf("当前空闲分区大小不能满足您请求的进程！请重新选择操作!\n");
    return 0;   //分配失败
}
void FFT(){
    char operate;
    oneWindow();
    while(1){
        scanf(" %c",&operate);
        switch(operate){
        case '1':
            firstFit();
            printf("请输入您想进行的操作：\n");
            break;
        case '2':
            Recover();
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
            printf("请输入您想进行的操作：\n");
            break;
        case '2':
            Recover();
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
            printf("请输入您想进行的操作：\n");
            break;
        case '2':
            Recover();
            break;
        default:
            mainWindow();
            return;
        }
    }
}
void Recover(){
    char operate;
    oneWindow();
    while(1){
        scanf(" %c",&operate);
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
    printf("***************  当前空闲分区链状态  **************\n\n");
    FreeMen_block *p=memory_plist->first->next;
    while(p!=NULL){
        printf("空闲分区起始地址和大小：%d %d\n",p->addr,p->length);
        p = p->next;
    }
    printf("\n");
}
void mainWindow(){
    printf("***************  内存的动态分区管理  ***************\n");
    printf("算法选择：\n");
    printf("┌────────────────────┐\n");
    printf("│            A.首次适应算法              │\n");
    printf("│                                        │\n");
    printf("│            B.循环首次适应算法          │\n");
    printf("│                                        │\n");
    printf("│            C.最佳适应算法              │\n");
    printf("│                                        │\n");
    printf("│            D.清    屏                  │\n");
    printf("│                                        │\n");
    printf("│            E.退出程序                  │\n");
    printf("└────────────────────┘\n");
    printf("请输入您想进行的操作：\n");
}
void oneWindow(){
    printf("\n");
    printf("***************  操作  ***************\n");
    printf("┌────────────────────┐\n");
    printf("│            1.内存分配                  │\n");
    printf("│                                        │\n");
    printf("│            2.内存回收                  │\n");
    printf("│                                        │\n");
    printf("│            3.返回上一级                │\n");
    printf("└────────────────────┘\n");
    printf("请输入您想进行的操作：\n");
}
void twoWindow(){
    printf("***************  内存回收  ***************\n\n");
    printf("请输入输入回收区的起始地址：\n");
}


