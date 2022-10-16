
#include <malloc.h>
#include <stdlib.h> // под динамические масивы
//#include <iostream>
#include <stdio.h>
//структуры


typedef struct {
    char *name;
    char * wish;

} Identification;  // структура имени и желания клиента (ипотека или вклад)


typedef struct {
    int beginning;  // начальный капитал
    int beginning_contribution;  // начальная выплата по ипотеке
    int flat;  // стоимость квартиры
    int income;  // доходы
    int expenses;  // расходы
    unsigned int time_year;  // время на погашение ипотеки, год
}money;


typedef struct {
    unsigned int row;  // число строк, целое положительное
    unsigned int col;  // число столбцов, целое положительное
    long long int ** massive;
}matrix;   // структура задаёт размеры матрицы и саму матрицу


typedef struct {
    double percent_mortgages;  // процент ипотеки
    double deposit_interest;  // процент вклада
    double percentage_increase;  // на сколько увеличивается процент по прошествию половины срока
} percent;  // структура процентов



// задаём параметры


// первый клиент
Identification сlient_1 ={"Alice", "deposit"};

const percent сlient_percent_1 ={0.09,0.02,0.02};

const money сlient_money_1  ={100000, 300000,15000500, 150000,40000,20};

const matrix сlient_matrix_1={20,1};


//второй клиент
Identification client_2 ={"Bob", "mortgages"};

const percent сlient_percent_2 ={0.09,0.0001,0.02};

const money сlient_money_2  ={100000, 300000,15000500, 150000,25000,20};

const matrix сlient_matrix_2={20,1};



//row строка, col столбец
// функция возвращает память для матрицы
long long int **memory (unsigned int row,unsigned int col ){
    long long int **a;
    a = (long long int**)malloc(row * sizeof(long long int*)); //выделение памяти под указатели на строки
    for (int i = 0; i<row; i++)  // цикл по строкам
    {
        a[i] = (long long int *) malloc(col * sizeof(long long int));// Выделение памяти под хранение строк
    }
    return a;
}


// вычисление ежемесячного платежа
int monthly_payment_F (const money A,const  percent B ) {

    int monthly_payment = ((A.flat + A.flat * B.percent_mortgages)/ (A.time_year*12));
    return monthly_payment;
}


//вычисления момента когда увеличивается процент по вкладу
double percentage_increase(int a,int b, double c,double d ){
    double rez;
    if( a>b/a){
        rez=c+d;
    }
    else {
        rez=c;
    }
    return rez;
}


// вычисление вклада
matrix deposit (const money A, const percent B, const matrix C){
    matrix result = {C.row, C.col};
    result.massive = memory(result.row, result.col);
    long long int a,b;
    double per_increase;
    long long int residue = A.beginning;
    for (int i=1; i<=A.time_year;i++){
        per_increase=percentage_increase(i,A.time_year,B.deposit_interest,B.percentage_increase);
        a= (residue+A.income*12-A.expenses*12);
        residue=a*per_increase+a;
        result.massive[i-1][0]=residue;
    }
    return result;
}


//вычисление ипотеки
matrix mortgages (const money A, const percent B, const matrix C){
    matrix result = {C.row, C.col};
    result.massive = memory(result.row, result.col);
    long long int monthly_payment=monthly_payment_F((A), (B));
    long long int a;
    double per_increase;
    long long int residue = A.beginning - A.beginning_contribution;
    for (int i=1; i<=A.time_year;i++){
        per_increase=percentage_increase(i,A.time_year,B.deposit_interest,B.percentage_increase);
        a= (residue+(A.income-A.expenses-monthly_payment)*12);
        residue=a*per_increase+a;
        result.massive[i-1][0]=residue;
    }
    return result;
}


//функция вывода
void Itog (matrix A){
    for (int i = 0; i < A.row; i++){
        for (int j = 0; j < A.col; j++){
            printf("Years %d  %d",i+1, A.massive[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


//показывает на какой год клиент сможет купить квартиру, если возьмет вклад
void Apartment_purchase(const money A, const percent B, const matrix C){
    // matrix.c result={A.time_year, 1};
    //result.massive = memory(A.time_year, 1);
    matrix result=deposit ( (A) ,   (B),   (C));
    int k=0,n=0;
    for (int i = 0; i < result.row; i++){
        for (int j = 0; j < result.col; j++){
            k=k+1;
            if(result.massive[i][j]>A.flat & n==0){
                printf ("You buy an apartment for %d years\n",k);
                n=1;
            }
        }
    }
}


// приветствует клиента и, основываясь на его желаниях, показывает результат вычисления
Identification name (const Identification A) {
    Identification B = {A.name, A.wish};
    //B.Cl = memory(2);
    printf("\n");
    printf("           Helloy  %s\n",A.name);
    if( B.wish== "mortgages") {
        printf("           Mortgage calculator\n");
        Itog(mortgages(сlient_money_2,сlient_percent_2,сlient_matrix_2));
    }
    else {
        printf("           Deposit calculator\n");
        Itog(deposit(сlient_money_1,сlient_percent_1,сlient_matrix_1));
        Apartment_purchase(сlient_money_1,сlient_percent_1,сlient_matrix_1);
    }
    B.name=NULL;
    return B;
}


int main() {
    name(сlient_1);
    name(client_2);
    return 0;
}