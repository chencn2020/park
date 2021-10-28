#ifndef CALCULATE_H
#define CALCULATE_H


// 定义结构变量
typedef struct node{
    double data;
    struct node *next;
} linkStack;

class calculate
{
private:
    linkStack *OPND; // 存放操作数
    linkStack *OPTR; // 存放操作符
    linkStack *initStack(); // 初始化栈
    int push(linkStack *l, double x); // 入栈操作
    int pop(linkStack *l, double *x); // 出栈操作
    char getTop(linkStack *l); // 得到栈顶元素
    char precede(double a, double b); // 判断运算符优先级
    double calculate_expression(double a, double b, int OP); // 返回计算值
public:
    calculate();
    int setCal(char *input); // -1小数点多了
    double get_result(); // 得到结果
    void toBinary(double number, char* array); // 转为二进制
};

#endif // CALCULATE_H
