#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  char a[][10]={
    "small"，
    "five!"
  };
  printf("%s\n",a[0]); // small
  printf("%s\n",a[1]); // five!
  printf("%p\n",a[0]); // 0x6dc0
  printf("%p\n",a[1]); // 0x6dca 地址相差10个字节
  printf("h :%p\n",&a[0][0]); // 0x6dc0
  printf("e :%p\n",&a[0][1]); // 0x6dc1 相差1个字节
  printf("a[0]+1:%s\n",a[0]+1); // a[0]+1:mall
  printf("a[1]+1:%s\n",a[1]+1); // a[1]+1:ive!
  return 0;
}
/* 二维数组a[][]，类似于,可以通过a[n]找到同一行的一维数组：
   a[n][   数组     ]
   ...
   ...
   a[3][   数组     ]
   a[2][   数组     ]
   a[1][   数组     ]
   a[0][   数组     ]
   二维数组a[][]，其中第二个[]必须有数字条件，表示每个数组大小；
   a[0]的地址和"small"的地址一样，或者说a[0]的地址和"small"中的's'地址是一样的，因为"small"和's'的地址是相同的
*/

/* 字符串（常量 or 本地字符串数组）本质也是数组，那么，如果是int类型的二维数组，代码如下 */
#include <stdio.h>
int main()
{
  int a[3][4] = {
    1,2,3,4,
    5,6,7,8,
    9,10,11,12 // 注意：这里只是排版看起来像二维数组，写成一行也是ok的~其实就是一行
  };
  printf("%d\n",a[2][2]); // 正常输出第三行第三列：11
  printf("a:%p\n",a[0]); // 0xe500
  printf("a[0][0]:%p\n",&a[0][0]); // 0xe500
  printf("a:%p\n",a[1]); // 0xe510 与a[0]相差4*sizeof(int) = 16字节
  printf("a[1][0]:%p\n",&a[1][0]); // 0xe510
  printf("a:%p\n",a[2]); // 0xe520 与a[1]相差16字节，与a[0]相差32字节
  printf("a[2][0]:%p\n",&a[2][0]); // 0xe520
  printf("%d\n",*(a[0]+1)); // 2 这里a[0]看成是一个指针，存储行数组的地址，a[0]+1表示地址向后移动一个单位，最后通过*调用值
  printf("%d\n",(a[0]+1)[0]); // 2 这里的[0]其实和*作用类似
  printf("%d\n",(a[0]+1)[1]); // 3 
  int *p=a[0]; // 声明指针p，指向a，从这个正确的语句可以看出来，a[0]确实是一个地址
  printf("p:%p\n",p); // 0xe500，与a[0]相同
  printf("p+1:%p\n",p+1); // 0xe504，说明p的地址与a[0][0]相同，且步长也与a[0][0]相同，为一个单位，即1个int的长度 = 4字节
  printf("p+1:%d\n",(p+1)[0]); // 2,这里也可以使用*(p+1)
  return 0;
}
/* 注意，上述如果a的地址+1，则是行级步长，例如： */
#include <stdio.h>
int main()
{
  int a[][4] = {1,2,3,4,5,6,7,8};
  printf("a:%p\n",a); // 0xfae0
  printf("a+1:%p\n",a+1); // 0xfaf0 相较于a，增加了4*sizeof(int) = 16字节
  printf("a:%d\n",a[0][1]); // 2
  printf("a+1:%d\n",(a+1)[0][3]); // 8 等价于--->
  printf("a+1:%d\n",(*(a+1))[3]); // 8
  return 0;
}


/* 所谓指针数组 */
#include <stdio.h>
int main()
{
  char *a[] = {
    "small",
    "five!",
    "python",
    "java"
  }; // 根据优先级，把a[]看成数组，这个数组内每个元素都是一个指针
  printf("%s\n",a[0]); // small
  printf("%s\n",a[1]); // five!
  printf("%s\n",a[2]); // python
  printf("%s\n",a[3]); // java
  printf("small:%p\n",a[0]); // 0x6004
  printf("five!:%p\n",a[1]); // 0x600a，是a[0]之后的6个字节，small五个字节加上'\0'
  printf("a[1]+1:%s\n",a[1]+1); // ive，说明a[1]的地址是"five!"中'f'的地址
  char *p = a[2]; // 声明指针p，p保存的是a[2]的地址，即'p'的地址
  printf("p:%s\n",p); // python
  printf("p+1:%s\n",p+1); //从'p'的地址加一个单位，现在的p+1指向的是'y'，所以%s输出为ython
  return 0;
}
/* 这里和下面int数组的区别是，"字符串常量"有一种自带保存地址的属性，即通过's'能够找到字符串"small"的地址 */
/* 如果是int数组 */
/* 注意：指针数组内元素是数组名 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  // int *p[] = {{1,2,3},{4,5,6}}; 
  // 第一次尝试直接放入int数组，出现warning，int* 类型与 int类型的不匹配，说明1没有指向{1，2，3}的地址；
  // 相比较字符串常量，会在字符串的第一个字符上保存地址，而{1，2，3}没有,But...
  // char *p[] = {{'a','b','\0'},{'c','d','\0'}};
  // 第二次尝试本地字符串数组，仍然会warning，下面↓
  /*
    char a[] = {'a','b','c','\0'};
    printf("%p\n",a); // 0x3f14
    printf("%s\n",a); // abc
    printf("%s\n",a+1); // bc
    printf("%p\n",&*a); // 0x3f14
    printf("%p\n",&*a+1); // 0x3f15
  */
  // char a[] = {'a','b','\0'};
  // char b[] = {'a','b','\0'};
  // char *p[] = {
  //      a,b
  // }; 说明这里需要放入地址
  // ok
  int a[] = {1,2,3};
  int b[] = {4,5,6};
  int *p[] = {a,b}; // 这里放入a和b的地址，p[0]是指针，指向a，p[1]是指针，指向b
  printf("a:%p\n",a); // 0x51d4
  printf("b:%p\n",b); // 0x51e0 和a相差4*sizeof(int) = 12字节
  printf("p[0]:%p\n",p[0]); // 0x51d4 和a的地址一样
  printf("p[1]:%p\n",p[1]); // 0x51e0 和b的地址一样
  printf("*p[0]:%d\n",p[0][0]); // 1
  printf("*p[0]:%d\n",p[0][1]); // 2
  printf("*p[1]:%d\n",p[1][0]); // 4
  printf(":%d\n",*(p[0]+1)); // p[0]的地址指向1，p[0]的地址+1之后为指向2的指针，然后使用*调用返回值2
  printf(":%d\n",(p[0]+1)[2]); // p[0]的地址指向1，p[0]的地址+1之后为指向2的指针,当使用[2]时，越出a数组（因为a和b在内存中是连续的），指向了b数组中的4
  return 0;
}
/* 前方高能 */
/* 以下交叉指针用于炫技 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
  int a[3][3]={1,2,3,4,5,6,7,8,9};
  int *p[3];
  p[0]=a[1]; // p[0]指针指向了a二维数组的第2行
  p[2]=a[0]; // p[2]指针指向了a二维数组的第1行
  printf("%d\n",p[1][0]); // 由于p[1]没有指向，所以会输出一个未知内存空间的value
/* 提示：
   p[2][   数组a[0]     ]
   p[1][   数组         ]
   p[0][   数组a[1]     ]
*/
  printf("%d\n",(p[2]+1) == &a[0][1]); //1 p[2]的地址+1个单位其实是到了a[0][1]的地址
  printf("%d\n",(p[2]+1)[0]); // 2
  printf("%d\n",(p[2]+3) == (&p[0][1]-1)); // 1 判断一下这两个地址是否相同~
  return 0;
}

/* 所谓数组指针，一个指向数组的指针？那么和普通指针有什么区别？普通指针也能指向数组 */
// 把数组指针的指针p看成是二级指针 int (*p)[] ---> int **p
/* 代码段1 通过二级指针*/
#include <stdio.h>
int main(int argc,char const *argv[])
{
  int a[][2] = {1,2,3,40}; // int a[][2] = {1,2,3,40} 等价于 {{1,2}，{3,40}}
  int *p = a[0]; // 文开头已经测试。a[0]就是地址
  int **po = &p; // 二级指针po，指向p的地址
  printf("a:%p\n",a); //0xe0f0
  printf("p:%p\n",p); //0xe0f0
  printf("po:%p\n",po); //0xe0e0 与a或者p相差4 * sizeof(int) = 16字节
  printf("po+1:%p\n",(*po)+1); // 步长为一个单位 = 4字节
  printf("%d\n",(*po)[2]); //*po-->p-->a[0]，所以a[0][2] = 3
  printf("%d\n",(*po)[0]); ////1
  return 0;
}
/* 代码段2 通过一个指针*/
#include <stdio.h>
int main(int argc,char const *argv[])
{
  int a[][2] = {1,2,3,40};
  int *p =a[0]; // p指向a[0]
  printf("a:%p\n",a); // 0x3820
  printf("p:%p\n",p); // 0x3820
  printf("p+1:%p\n",p+1); // 0x3824，步长为4个字节
  printf("%d\n",p[0]); // 1
  printf("%d\n",p[1]); // 2
  printf("%d\n",p[2]); // 3
  return 0;
}
/* 代码段3 通过数组指针*/
#include <stdio.h>
int main(int argc,char const *argv[])
{
  int a[][2] = {1,2,3,40};
  int (*p)[] = &a[1]; // (*p)提高了优先级，声明的p这个指针，指向了一个数组，注意：这里需要a[1]的地址，不能直接给a，因为int (*)[]类型和int *类型不一样
  printf("p:%p\n",p); // 0x1398
  printf("p:%p\n",(*p)+1); // 0x139c 相差4个字节
  printf("TRUE?:%d\n",&((*p)[0]) == a[0]); // 0 False
  printf("TRUE?:%d\n",&((*p)[0]) == a[1]); // 1 True
  printf("p:%d\n",(*p)[0]); // 3
  printf("p:%d\n",(*p)[2]); // 一个未知内存的value
  return 0;
}
/* 代码段4 大脑已经混乱Orz，win 10切换输入法可以只用shift ~*/
/* 请自行体会 */
#include <stdio.h>
int main(void)
{
  char const *a[]={
    "java",
    "cplusplus",
   "javascript"
  };
  char (*p)[] = a[1]; // 这里会有一个warning（可以正常运行），因为int (*)[]类型和int *类型不一样，如果使用&a[1]就不会有warning，虽然都是传地址，但是貌似等级不一样
  printf("%s\n",*p+6); // *p是a[1]的地址
  printf("%c\n",(*p)[11]); // 把*p看成a[1]的地址，也可以看成'c'的地址，11个步长之后 ... 跳转到a[2]的数组范围内
  return 0;
}
/*  
#include <stdio.h>
int main(void)
{
  int const a[][2] = {
    1,2,3,4
  };
  return 0;
}
对于1，2，3，4无论是否用数组的{}，都会被分配成数组的形式
*/
/* int类型的，数组指针 */
#include <stdio.h>
int main(void)
{
  int b[]={1,2,3,4};
  int c[]={1,2};
  int const *a[] = {
    b,c
  };
  int (*p)[] = a[0]; // 这里会有一个warning，因为int (*)[]类型和int *类型的不匹配，但是现在暂时没有找到解决方法，这里把b[0]的地址看成和*p的地址一样，*p是一个地址，所以p类似二级指针
  printf("b:%p\n",b); // 0x12d0
  printf("p:%p\n",p); // 0x12d0
  printf("true::%d\n",(b+4) == ((*p)+4)); // 判断一下地址是否相同
  printf("%d\n",(*p)[1]); // 2
  printf("%d\n",(*p)[2]); // 3
  printf("%d\n",(*p)[3]); // 4
  return 0;
}

/* 结构struct中的地址问题 */
#include <stdio.h>
struct point{
  int x;
  int y;
  }; // 这里是一个struct
int main(void)
{
  struct point array[] = {
    {1,2},{3,4},{5,6}
  };
   /*
  printf("array[0]:%d-%d\n",array[0].x,array[0].y); // array[0]返回一个struct point类型的数据
  printf("array[0]:%p\n",array); // array的地址 0x5090
  printf("array[1]:%p\n",array+1); // array的地址加 2 * sizeof(int) = 8字节大小 0x5098
  printf("%d\n",(array+2)->y); // 通过指针->的方法取到struct的数据，说明array+2是个地址，即指针
  struct point *p = &array[1]; // 指针p = array[1]的地址
  printf("%d\n",p->x); // p->x
  */
  printf("array:%p\n",array);
  printf("array[0]:%p\n",&array[0]);
  printf("array[1]:%p\n",&array[1]); // array[0]地址+一个单位
  printf("%d\n",array+1 == &array[1]); //1
  printf("%p\n",&((&(array[1]))->y)); // array[1].y的地址是array[0]的地址+4字节的位置
  return 0;
}
