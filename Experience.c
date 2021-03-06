/* C中的指针POINT */
/* 1.指针的使用使得不同区域的代码可以轻易的共享内存数据 */
/* 2.体现了C的性能，如果一个结构体占用几百字节的内存，那么一个指针仅需4字节或者8字节 */
/* 3.链表的使用必须依靠指针 */
/* 4.函数中修改被传递过来的对象，就必须通过这个对象的指针来完成（当然，不考虑使用return的情况下） */
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

/* 结构数组 代码1 */
#include <stdio.h>
struct point{
  int x;
  int y;
};
/* 结构套结构 */
struct multi_struct {
  struct point p1;
  struct point p2;
};
int main(int argc, char const *argv[])
{
  struct multi_struct array[][2]={
    {{1,2},{3,4}},{{5,6},{7,8}},
    {{9,10},{11,12}},{{13,14},{15,16}},
  };
  printf("array[0]:%p\n",array[0]); // 0xf350
  printf("array:%p\n",array); // 和array[0]的地址一样 0xf350
  printf("1:%p\n",&(array[0][0].p1.x)); // 0xf350
  printf("2:%p\n",&(array[0][0].p1.y)); // 0xf354，相差一个int = 4字节
  printf("15:%p\n",&(array[1][1].p2.x)); // 0xf388
  printf("16:%p\n",&(array[1][1].p2.y)); // 0xf38c，与数组头正好相差4 * sizeof(int) = 60字节
  return 0;
}
/* 结构数组+数组指针 代码2 */
#include <stdio.h>
struct point{
  int x;
  int y;
};
struct multi_struct {
  struct point p1;
  struct point p2;
};
int main(int argc, char const *argv[])
{
  struct multi_struct a = {{1,2},{3,4}};
  struct multi_struct b = {{5,6},{7,8}};
  struct multi_struct c = {{9,10},{11,12}};
  struct multi_struct d = {{13,14},{15,16}};
  struct multi_struct *array[]={
    &a,&b,
    &c,&d
  }; // 这里需要传入地址
  printf("%d\n",array[0]->p1.x); // 1
  printf("%d\n",array[3]->p2.y); // 16
  printf("1:%p\n",&(array[0][0].p1.x)); // 0x32b0
  printf("2:%p\n",&(array[0][0].p1.y)); // 0x32b4
  printf("15:%p\n",&(array[0][1].p2.x)); 
  printf("16:%p\n",&(array[3]->p2.y)); // 0x32ec
  return 0;
}
/* 结构数组与指针数组和数组指针的关联问题 */
#include <stdio.h>
struct point {
  int x;
  int y;
}; // 第一个struct
struct multi_struct {
  struct point p1;
  struct point p2;
}; // 结构嵌套
int main(int argc, char const *argv[])
{
  // 一个具有3个单元的结构数组，array[0]或者说array就是第一个的地址，array[1]或者array+1就是第二个地址，array[2]或者array+2就是第三个地址
  struct multi_struct array[3] = {
    {{1,2},{3,4}},
    {{5,6},{7,8}},
    {{9,10},{11,12}},
};
  struct multi_struct (*a)[] = &(array[0]); // 这里会有一个warning，但是这里还是没有真正的明白这个warning的原因...暂时理解a类似一个二级指针

  printf("THIS IS 7?:%d\n",((*a)+1)->p2.x); // THIS IS 7?:7 ，这里*a返回一个地址，即array[0]的地址，其实array[0]不应该是一个地址，如果是array[0][0]的话应该就没有问题
                                            //  所以这里暂时把*a看成一个地址，*a+1到第二个struct multi_struct结构的地址，如果是地址，就可以用->指向p2，然后.x输出7
/* 以下任何代码都没有warning，严格按照地址-指针规则，同时为了不记忆优先级，所以可能多使用了()
struct multi_struct *a[] = {
  array,
  array+1,
  array+2
};  // a[]是指针数组，需要给予若干个地址
printf("I Wang To Get 1:%d\n",a[0]->p1.x);
printf("I Wang To Get 2:%d\n",a[0][0].p1.y); // a[0][0]的第二个[0]其实没什么特别的含义，只是用来取出a[0]这个结构，和下面的*的作用一样
rintf("I Wang To Get 3:%d\n",(*(a[0])).p1.y);
printf("I Wang To Get 4:%d\n",array->p2.y);
printf("I Wang To Get 5:%d\n",(array+1)->p1.x);
printf("I Wang To Get 6:%d\n",a[0][1].p1.y); // a[0][1]的[1]类似于步长，从a[0]跨到a[1]
printf("I Wang To Get 7:%d\n",a[1][0].p2.x);
printf("I Wang To Get 8:%d\n",(array+1)->p2.y);
printf("I Wang To Get 9:%d\n",(array+2)[0].p1.x);
printf("I Wang To Get 10:%d\n",(a[1]+1)->p1.y); // 注意步长
printf("I Wang To Get 11:%d\n",(a[1]+1)->p2.x); // 注意步长
printf("I Wang To Get 12:%d\n",(*(array+2)).p2.y);
*/
return 0;
}
/* 在结构中， 貌似无法使用结构的地址， 代码如下： */
#include <stdio.h>
struct point {
  int x;
  int y;
};
int main(void)
{
  struct point a = {1,2};
  struct point *p = &a; // p是指针
  printf("a:%p\n",&a); // 0x9f70
  printf("a.x:%p\n",&(a.x)); // 0x9f70
  printf("p:%p\n",&p); // 0x9f68 p指针有独立内存空间， 正好相差8字节
  printf("p+1:%p\n",p+1); // 0x9f78 p+1个指针之后会跳过整个结构体，所以加上sizeof(int) + sizeof(int) = 8字节
  printf("&a+1:%p\n",&a+1); // 0x9f78
  // printf("%d\n",(&a->x)); // 这里会报错， 不能直接使用结构地址进行->，而是需要使用指针
}

/* 2021-01-19 重大发现，关于指针的类型，必须重视 */
/* 例如 char *a[] = {"cplusplus", "Java"};
   a[0] 或者 a[1]是一个指针， 指向了字符串常量"cplusplus"和"Java"，因为字符串常量的地址默认第一位就是地址，等价于指向了'c'和'J'，指针指向地址，这没有问题，
   其次，*a[0]或者*a[1]即返回这个地址的值，即分别为'c'和'J'， 即声明的char类型，也没有问题，有了这个新基础之后，再来看看数组指针 */
#include <stdio.h>
int main(void)
{
  int a[] = {1,2,3};
  int (*p)[] = &a;
  return 0;
}
/* 这里最开始学指针的时候，这里当时考虑的是因为p是一个指针，a是一个地址，p指向a，正好是一个数组，其实这是不对的（至少会有一个warning）为什么会有warning？ 因为a指向的是数组第一个
即a[0]的那个int数据，所以*p正好已经是一个int数据了，此时(*p)[]已经不再是一个int数组，所以会有warning */
/* 正确的做法是，使p指针指向a的地址，那么*p返回a，a指向a[0]，即*p指向a[0]，可以理解为*p指向了一个数组的第一个元素（只要指向数组就行，当然必须是int数组），这个时候就不会有warning */
#include <stdio.h>
int main(void)
{
  int a[][2] = {1,2,3,4};
  int (*p)[] = a;
  int (*q)[] = &a[0];
  printf("%d\n", (*p)[3]);
  printf("%d\n", (*q)[2]);
  return 0;
}
/* 这里数组指针指向a或者&a[0]均可，p指向a时，a是指向a[0]，单是这里要把a[0]看成一个指针，a[0]指向a[0][0],是一个数组，多以*p==>a[0]，指向的是一个数组，合理；
至于&a[0]，如果指针q指向a[0]，那么*q = a[0]，此时的*q和a[0]一样，都指向a[0][0]，即a[0]数组第一个元素， 合理； */
/* 注：但是这里的p和q指针没有步长， 无法进行指针运算， 只能通过a进行指针运算 */
/* 来看一个“奇怪”的东西 */
#include <stdio.h>
int main(void)
{
  char *a[] = {
    "Cplusplus",
    "PHP",
    "JavaScript"
  };
  char *(*p)[] = &a;
  printf("%s\n", (*p)[0]);
  printf("%s\n", (*p)[1]);
  printf("%s\n", (*p)[2]);
  printf("%c is u?\n", ((*p)[0]+7)[0]); // u
  printf("%c is P?\n", (*p)[1][2]); // P
  return 0;
}
/* 这里为什么要在(*p)[]的前面还要加上'*'，当时考虑的是，char (*p)[]中的*p必须指向一个数组（为了好理解，说成指向一个数组的第一个元素，例如普通数组a[]的a就是指向的a[0]，但是a并没有指向
整个数组a），在char *a[]中，有一个数组a[]，所以想要把p指向a，所以*p=a，因为a指向了a[0]，即*p指向a[0]，但是注意a[]返回的是char *类型，而(*p)[]返回的不是char类型，而是char *类型，所以
要在前面加上'*' */
#include <stdio.h>
int main(void)
{
  char *a[] = {
    "Cplusplus",
    "PHP",
    "JavaScript"
  };
  char *(*p)[] = &a; // 已经在上面解释
  char **q = &a[0]; // 这里为什么需要二级指针？ 一开始写的是char **q = &a，因为把a和a[0]的地址想成一样的，如果这里是**q = &a，那么*q = a，a指针指向指针数组，**q = a[0]
  // char (***b) = &a;  error 指针和数组名的关系，貌似在2021年1月21日已经彻底搞明白了，数组和指针的完全不同性，想要单独理一个段落
  // 当b=&a时，其实可以理解为两条有效信息，第一b是指针，保存了a的地址信息，第二，b指向a，也就在这里把指针和数组的关系区分了开来，a是指向一个数组的，但是**b指向的数组的第一个“值”，两者
  // 不等价
  // 为什么int a[];int *p = a;可以，因为p=a也包含两层信息，第一，p是指针，第二，p（和a一样（为了好理解，把a和指针假想成一样））指向a[0]那个int的值，所以*p是一个int，没有问题。
  //printf("%s is J\n", (*p)+14);
/*
  char b[] = "JavaScript";
  char (*q)[] = &b;
  printf("%d\n", (*q)[10] == '\0');
*/
/*
  printf("%c is u?\n", ((*p)[0]+7)[0]);
  printf("%c is P?\n", (*p)[1][2]);
  printf("%s\n", (*p)[0]);
  printf("%s\n", (*p)[1]);
  printf("%s\n", (*p)[2]);
*/
  return 0;
}

/* 函数指针的“混乱”理解 */
/* 正常来说，函数指针例如 int (*p)(int,char,...参数) = 函数名(或者&函数名) 即可，p表示指针 */
#include <stdio.h>
int add(int a, int b)
{
  return a+b;
}
int sub(int a, int b)
{
  return a-b;
}
int middle(int (*p)(int,int),int a,int b)
{
  return (*p)(a,b);
}
int (*select(char op))(int, int)
{
  switch (op){
    case '+':return add;
    case '-':return sub;
  }
}
int main(void)
{
  int a;
  int b;
  char oper;
  int (*fp)(int, int);
  printf("I NEED A SENTENCE:");
  scanf("%d%c%d", &a, &oper, &b);
  fp = select(oper); // 返回的add或者sub已经是一个地址了， 所以不能再使用&select(oper)
  printf("a%cb=%d\n",oper,middle(fp,a,b));
  return 0;
}
/* 在main函数内部定义了一个看似正常的int (*fp)(int, int)的函数指针，要把int (*select(char op))(int, int)也要看成int (*p)(int, int)的类型（即把select(char op)看成一个整体，看成一个
指针） */
/* 在int (*select(char op))(int, int)函数块中，在理解的时候不要把它当作函数来处理，虽然它确实是函数，但是还是把它当作一个定义的函数指针，在没有把它当作函数的前提下，在调用的时候
fp = select(oper)时才把它当作一个函数来看待，返回一个函数指针给fp */
