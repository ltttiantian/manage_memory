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
    int length;//分区大小
    int addr;//分区起始地址
    struct freeMen *next;//指向后一个空闲分区的指针
    //struct freeMen *prev;//指向前一个分区节点的指针
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
    //初始化
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
//排序算法
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
    printf("  ***************  内存的动态分区管理  ***************\n");
    printf("┌────────────────────┐\n");
    printf("│            1.内存分配                  │\n");
    printf("│                                        │\n");
    printf("│            2.内存回收                  │\n");
    printf("│                                        │\n");
    printf("│            3.退出程序                  │\n");
    printf("└────────────────────┘\n");
    printf("请输入您想进行的操作：\n");
}
void oneWindow(){
    printf("  ***************  内存分配  ***************\n");
    printf("┌────────────────────┐\n");
    printf("│            A.首次适应算法              │\n");
    printf("│                                        │\n");
    printf("│            B.循环首次适应算法          │\n");
    printf("│                                        │\n");
    printf("│            C.最佳适应算法              │\n");
    printf("│                                        │\n");
    printf("│            D.返回上一级                │\n");
    printf("└────────────────────┘\n");
    printf("请输入您想进行的操作：\n");
}

void twoWindow(){
    printf("  ***************  内存回收  ***************\n\n");
    printf("请输入输入回收区的起始地址：\n");
}


