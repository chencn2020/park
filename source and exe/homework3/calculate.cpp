#include "calculate.h"
#include<stdlib.h>
#include<math.h>

calculate::calculate()
{
    OPND = initStack(); // 存放操作数
    OPTR = initStack(); // 存放操作符
}


linkStack * calculate:: initStack() // 初始化栈
{
    linkStack *S = (linkStack*)malloc(sizeof(linkStack)); // 申请新内存
    S->next = NULL;
    return S;
}


int calculate:: push(linkStack *l, double x) // 入栈操作
{
    linkStack *S = (linkStack*)malloc(sizeof(linkStack)); // 申请新内存
    // 赋值
    S->data = x;
    S->next = l->next;
    l->next = S;
    return 1;
}


int calculate:: pop(linkStack *l, double *x) // 出栈操作
{
    linkStack *p;

    // 判断是否为空栈
    if (l->next == NULL){
        return 0;
    }

    p = l->next;
    *x = p->data;
    l->next = p->next;
    free(p);

    return 1;
}


char calculate:: getTop(linkStack *l) // 得到栈顶元素
{
    if (l->next == NULL){
        return NULL;
    }

    linkStack *p = l->next;
    return p->data;
}


char calculate:: precede(double a, double b) // 判断运算符优先级
{
    double LPriority=0 ,RPriority=0;

    // 满足下面条件，说明计算式输入不合法
    if((a == '(' && b == '#') || (a == ')' && b == '(') || (a == '#' && b == ')')){
        return 'W';
    }

    // 根据a，b两个操作符的符号内容，赋予一定的权值
    switch((int)a) {
    case '+': LPriority = 0.5; break;
    case '-': LPriority = 0.5; break;
    case '*': LPriority = 1.5; break;
    case '/': LPriority = 1.5; break;
    case '(': LPriority = -0.5; break;
    case ')': LPriority = 2; break;
    case '#': LPriority = -1; break;
    }
    switch((int)b) {
    case '+': RPriority = 0; break;
    case '-': RPriority = 0; break;
    case '*': RPriority = 1; break;
    case '/': RPriority = 1; break;
    case '(': RPriority = 2; break;
    case ')': RPriority = -0.5; break;
    case '#': RPriority = -1; break;
    }

    // 将左右权值相减，如果小于0，返回"<"；等于0，返回"="；大于0，返回">"
    if((LPriority - RPriority) < 0){
        return '<';
    } else if ((LPriority - RPriority) == 0){
        return '=';
    } else {
        return '>';
    }
}


double calculate:: calculate_expression(double a, double b, int OP) // 返回计算值
{
    double result; // 存储结果
    char oper = (char)OP; // 强制类型转换运算符

    if(oper == '/' && b == 0){ // 是否除以0
        return NULL;
    }

    switch(oper){
    case '+': result = a + b; break;
    case '-': result = a - b; break;
    case '*': result = a * b; break;
    case '/': result = a / b; break;
    }

    // 返回结果
    return result;
}


int calculate:: setCal(char *input)
{
    double a, b, c, d; // 用来存取数据
    int index = 0;

    double theNum = 0; // 存储大于一位数的整数
    int isNew = 0; // 判断这个数是不是新输入的
    int isDot = 0; // 判断有没有小数
    int dotDig = 1; // 判断是否重复输入小数点
    int isNegative = 1; // 判断是否为负数

    push(OPTR, '#'); // 在操作符底部压入运算符 "#"
    b = input[index];

    while(b != '#' || (getTop(OPTR) != '#' && getTop(OPTR) != NULL) || isNew){
        if(isNegative == 1 && b == '-'){ // 是否为负数
            isNegative = 2;
            b = input[++index];
            continue;
        }

        if(isNegative != 2){
            isNegative = 0;
        }

        // 判断是否为数字
        if((b >='0' && b <= '9') || b == '.'){
            if(b == '.' && !isDot){
                isDot = 1;
            } else if (b == '.' && isDot){
                return -1; //小数点多了
            }
            if(!isDot){
                theNum = theNum * 10 + (int)b - (int)'0'; // 将数字存入变量中，并强制类型转换
            } else if(b != '.' && isDot){
                theNum = theNum + (1.0 * (int)b - (int)'0') / pow(10, dotDig++);
            }

            isNew = 1; // 标明新输入了一个数
            b = input[++index]; // 读取下一个数
        } else if (b == '\0') {
            b = '#'; // 如果为end，说明运算式输入完毕，在栈顶压入运算符"#"
        } else {
            if(b == '(' && !isNew && isNegative == 2) {
                isNew = 1;
                theNum = 1;
                push(OPTR, '*'); // 类似-（2+3）,压入-1*（2+3）
            }
            if(isNew == 1){
                if(isNegative == 2) theNum *= -1; // 为负
                push(OPND, theNum);
                theNum = isNew = isDot = isNegative = 0; // 初始化
                dotDig = 1;
            }
            if(b == '(') isNegative = 1;

            a = (int)getTop(OPTR); // 获得栈顶元素
            double _;

            // 判断栈顶元素和输入的运算符优先级
            switch(precede(a, b)){
            case '<': push(OPTR, b); b = input[++index]; break; // 如果a小于b，直接压入
            case '=': pop(OPTR, &b);
                if(index > 0 && b != '#') b = input[++index];
                break;
            case '>': if(!pop(OPND, &c)||!pop(OPND, &d)) return -2; // 如果a大于b，则将a弹出后，进行运算
                _ = calculate_expression(d, c, a);
                if (_ != NULL) { push(OPND,_);	pop(OPTR,&a);}
                else return -3;
                break;
            default: return -2;
            }
        }
    }
    return 1;
}


double calculate:: get_result()
{
    double ans;
    if(pop(OPND, &ans)) return ans;// 将结果弹出
}

// 转换成二进制
void calculate:: toBinary(double number, char* array){
    int integer = (int)number; // 整数部分
    double dot = number - integer; // 小数部分
    char tem[15]; // 只计算十五位二进制数
    int length = 0;
    bool isNegative = false; // 是否为负数

    if(integer == 0) tem[length++] = 0;
    else if (integer < 0){
        integer *= -1;
        isNegative = true;
    }

    while(integer && length != 14){ // 整数部分转为二进制
        tem[length++] = integer % 2;
        integer /= 2;
    }

    for(int i = 0; i < length; i++){
        if(isNegative && i == 0) array[0] = '-';
        if(isNegative) array[i + 1] = (char)tem[length - i - 1] + '0';
        else array[i] = (char)tem[length - i - 1] + '0';
    }
    if(isNegative) array[length] = (char)tem[0] + '0';


    if(dot != 0) array[length] = (int)'.';
    while(dot && length != 14){ // 小数部分转为二进制
        array[++length] = (int)(dot * 2) + '0';
        dot = dot * 2 - (int)(dot * 2);
    }
}
