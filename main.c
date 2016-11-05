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
    //初始化
    FreeMen_block *first;
    setMen(&first,0,0);
    memory_plist = (Men_Plist *)malloc(sizeof(Men_Plist));
    memory_plist->first = first;
}
int insert(FreeMen_block *newFree,int tag){
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    if(tag==0){     //采用首次适应算法和循环首次适应算法
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
    }else if(tag==1){   //最佳适应算法
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
//排序算法
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
    printf("请输入您请求的内存大小：");
    scanf("%d",&load);
    FreeMen_block *p = memory_plist->first;
    FreeMen_block *q = memory_plist->first->next;
    while(q!=NULL){
        if(load<q->length){
            p->next = q->next;  //将第一个空闲内存分配void
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
    printf("  ***************  当前空闲分区链状态  **************\n\n");
    FreeMen_block *p=memory_plist->first->next;
    while(p!=NULL){
        printf("空闲分区起始地址和大小：%d %d\n",p->addr,p->length);
        p = p->next;
    }
}
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


