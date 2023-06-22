#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct Line {
    double a, b, c; // ax + by = c
};

int N1();
int solve(double a1, double b1, double c1, double a2, double b2, double c2, double *x, double *y);
void get_intersection(struct Line l1, struct Line l2, double *x, double *y);
int GCD(int t, int v);

int main()
{
    int M, N = 1, time = 1;
    
    scanf("%d\n", &N);
    if(N == 1){
        scanf("%d\n", &time);
        for(int i = 0; i < time; i++){
        N1();
        }
        return 0;
    }

    if(N == 2){
        double x1,x2,x3,y1,y2,y3;
        // 讀入 3 條直線
        struct Line lines[3];
        for (int i = 0; i < 3; i++) {
            scanf("%lf %lf %lf", &lines[i].a, &lines[i].b, &lines[i].c);
        }

        // 計算任意兩條直線的交點

        get_intersection(lines[0], lines[1], &x1, &y1);
        get_intersection(lines[0], lines[2], &x2, &y2);
        get_intersection(lines[1], lines[2], &x3, &y3);

        // printf("(%.2lf, %.2lf)\n", x1, y1);
        // printf("(%.2lf, %.2lf)\n", x2, y2);
        // printf("(%.2lf, %.2lf)\n", x3, y3);

        if(x2 > x1 && x1 > x3){
            printf("(%.2lf, %.2lf)\n", x3, y3);
            printf("(%.2lf, %.2lf)\n", x1, y1);
            printf("(%.2lf, %.2lf)\n", x2, y2);
        }else if(x3 > x1 && x1 > x2){
            printf("(%.2lf, %.2lf)\n", x2, y2);
            printf("(%.2lf, %.2lf)\n", x1, y1);
            printf("(%.2lf, %.2lf)\n", x3, y3);
        }else {
            printf("(%.2lf, %.2lf)\n", x2, y2);
            printf("(%.2lf, %.2lf)\n", x3, y3);
            printf("(%.2lf, %.2lf)\n", x1, y1);
        }
    }
    
    return 0;
}

int N1()
{
    int x1, x2, y1, y2;
    scanf("\n%d %d %d %d", &x1, &y1, &x2, &y2);
    // printf("%d %d %d %d", x1, x2, y1, y2);
    int m = 0, b = 0;
    int m_temp_upper, m_temp_lower, b_temp_upper, b_temp_lower;

    //m
    m_temp_upper = (y1 - y2); m_temp_lower = (x1 - x2);

    int gcd = abs(GCD(m_temp_upper, m_temp_lower));
    m_temp_upper /= gcd; m_temp_lower /= gcd;

    //分子分母皆為負數時
    if(m_temp_upper < 0 && m_temp_lower < 0){
        m_temp_upper *= -1;
        m_temp_lower *= -1;
    //分子為正、分母為負 轉換
    }else if(m_temp_upper > 0 && m_temp_lower < 0){
        m_temp_upper *= -1;
        m_temp_lower *= -1;
    }


    //b
    b_temp_upper = (x2 * y1 - x1 * y2); b_temp_lower = (x2 - x1);
    gcd = GCD(b_temp_upper, b_temp_lower);
    b_temp_upper /= gcd; b_temp_lower /= gcd;


    printf("y = ");
    int x_exist = 0;
    if(m_temp_upper != 0)
    {
        if (m_temp_upper / m_temp_lower == 1 && m_temp_lower == 1) {
            printf("x");
            x_exist = 1;
        } else if (m_temp_upper == 1 && m_temp_lower == -1) {
            printf("-x");
            x_exist = 1;
        } else if (m_temp_upper == -1 && m_temp_lower == 1) {
            printf("-x");
        }else if(m_temp_lower == 1 ){
            printf("%dx", m_temp_upper);
            x_exist = 1;
        }else if(m_temp_upper > 0 && m_temp_lower < 0){
            printf("-%d/%dx", abs(m_temp_upper), abs(m_temp_lower));
            x_exist = 1;
        }else if(m_temp_upper < 0 && m_temp_lower > 0){
            printf("-%d/%dx", abs(m_temp_upper), abs(m_temp_lower));
            x_exist = 1;
        }else {
            printf("%d/%dx", m_temp_upper, m_temp_lower);
            x_exist = 1;
        }
    }
    
    if(x_exist == 1){
        if (b_temp_upper > 0 && b_temp_lower > 0) {
            printf(" + ");
        } else if (b_temp_upper < 0 && b_temp_lower < 0) {
            printf(" + ");
        } else if (b_temp_upper < 0 && b_temp_lower > 0) {
            printf(" - ");
        } else if (b_temp_upper > 0 && b_temp_lower < 0) {
            printf(" - ");
        }
    }
    
    if(b_temp_upper !=0){
        if(b_temp_upper / b_temp_lower == -1){
            printf(" - 1");
        }else if (b_temp_lower == 1) {
            printf("%d", abs(b_temp_upper));
        }else printf("%d/%d", abs(b_temp_upper), abs(b_temp_lower));
    }
    
    printf("\n");
    return 0;
}

int solve(double a1, double b1, double c1, double a2, double b2, double c2, double *x, double *y)
{
    double d = a1 * b2 - a2 * b1;
    if (d == 0) {
        return 0; // 方程無解
    }
    *y = (c1 * b2 - c2 * b1) / d;
    *x = -1 * (a1 * c2 - a2 * c1) / d;
    if(*y == 0){
        *y = abs(*y);
    }
    return 1;
}

void get_intersection(struct Line l1, struct Line l2, double *x, double *y) 
{
    solve(l1.a, l1.b, l1.c, l2.a, l2.b, l2.c, x, y);
}

int GCD(int t, int v)
{
    if (t % v == 0){
        return v;
    }else{
        return GCD(v, t % v);
    }
}