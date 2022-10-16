#include <stdio.h>
#include <malloc.h>
#include <stdlib.h> // под динамические масивы

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
    unsigned int row; // число строк, целое положительное
    unsigned int col; // число столбцов, целое положительное
    long long int ** massive;
}matrix;   // структура задаёт размеры матрицы и саму матрицу


typedef struct {
    double percent_mortgages;  // процент ипотеки
    double deposit_interest;  // процент вклада
    double percentage_increase;  // на сколько увеличивается процент по прошествию половины срока
} percent; //  структура процентов


typedef struct {
    unsigned int i;  // на какой год зарплата увеличилась/ уменьшилась
    double income_new; // на сколько увеличилась/уменьшилась, в тысячах рублей
}income;   // труктура задаёт изменение доходов


typedef struct {
    unsigned int i;  // на какой год стоимость квартиры увеличилась/ уменьшилась
    double flat_new; // на сколько увеличилась/уменьшилась, в процентах/100
}flat;   // структура задает изменение стоимости квартиры


typedef struct {
    unsigned int i;  // на какой год расходы увеличилась/ уменьшилась
    double expenses_new; // на сколько увеличилась/уменьшилась, в тысячах рублей
}expenses;   // структура задает изменение расходов


// задаём параметры


// первый клиент
Identification Client_1 ={"Alice", "deposit"};
const percent Alice_percent ={0.09,0.02,0.02};
const money Alice_money  ={100000, 300000,16000500, 150000,40000,20};
const matrix Alice_matrix={20,1};
const income Alice_income ={5, -70000};
const flat Alice_flat ={4, 2.00};
const expenses Alice_expenses ={3, 55000};


//второй клиент
Identification Client_2 ={"Bob", "mortgages"};
const percent Bob_percent ={0.09,0.0001,0.02};
const money Bob_money  ={100000, 300000,12000500, 100000,25000,20};
const matrix Bob_matrix={20,1};
const income Bob_income ={11, -70000};
const expenses Bob_expenses ={5, 20000};


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
double percentage_increase(int i,int time_year, double percent_old,double percent_new ){
    double result;
    if( i>time_year/i){
        result=percent_old+percent_new;
    }
    else {
        result=percent_old;
    }
    return result;
}


// считает доходы клиента
// i - это год
double income_client (int i, int income_old, const income A){
    double income_new=income_old;
    if (i==A.i){
        income_new=income_old+A.income_new;
    }
    return income_new;
}


//учитывает повышение/понижение стоимости квартиры
// i - это год
double flat_client (int i, int flat_old,flat A) {
    int flat_new=flat_old;
    if (i==A.i){
        flat_new=flat_old*A.flat_new;
    }
    return flat_new;
}


//учитывает увеличение / уменьшение расходов клиента
double expenses_client (int i, int expenses_old,expenses A) {
    int expenses_new=expenses_old;
    if (i==A.i){
        expenses_new=expenses_old+A.expenses_new;
    }
    return expenses_new;
}


// вычисление вклада
matrix deposit (const money A, const percent B, const matrix C, const income D, const expenses E){
    matrix result = {C.row, C.col};
    result.massive = memory(result.row, result.col);
    long long int a,b;
    double per_increase;
    double income_new;
    double expenses_new;
    long long int residue = A.beginning;
    for (int i=1; i<=A.time_year;i++){
        per_increase=percentage_increase(i,A.time_year,B.deposit_interest,B.percentage_increase);
        income_new=income_client(i,A.income,  (D));
        expenses_new=expenses_client(i,A.expenses, (E));
        a= (residue+income_new*12-expenses_new*12);
        residue=a*per_increase+a;
        result.massive[i-1][0]=residue;
    }
    return result;
}


//вычисление ипотеки
matrix mortgages (const money A, const percent B, const matrix C, const income D, const expenses E ){
    matrix result = {C.row, C.col};
    result.massive = memory(result.row, result.col);
    long long int monthly_payment=monthly_payment_F((A), (B));
    long long int a;
    double per_increase;
    double income_new;
    double expenses_new;
    long long int residue = A.beginning - A.beginning_contribution;
    for (int i=1; i<=A.time_year;i++){
        per_increase=percentage_increase(i,A.time_year,B.deposit_interest,B.percentage_increase);
        income_new=income_client(i,A.income,  (D));
        expenses_new=expenses_client(i,A.expenses,  (E));
        a= (residue+(income_new- expenses_new-monthly_payment)*12);
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
void Apartment_purchase(const money A, const percent B, const matrix C, const income D, const flat E,const expenses F){
    matrix result=deposit ( (A) ,   (B),   (C),  (D),   (F));
    int k=0,n=0;
    double flat_new=A.flat;
    for (int i = 0; i < result.row; i++){
        for (int j = 0; j < result.col; j++){
            k=k+1;
            flat_new=flat_client (i,flat_new, (E));
            if(result.massive[i][j]>flat_new & n==0){
                printf ("You buy an apartment for %d years\n",k);
                n=1;
            }
        }
    }
}




// приветствует клиента и, основываясь на его желаниях, показывает результат вычисления
Identification name (const Identification A) {
    Identification B = {A.name, A.wish};
    printf("\n");
    printf("           Helloy  %s\n",A.name);
    if( B.wish== mortgages) {
        printf("           Mortgage calculator\n");
    }
    else {
        printf("           Deposit calculator\n");
    }
    B.name=NULL;
    return B;
}


int main() {
    name(Client_1);  // приветствие клиента Алиса
    Itog(deposit(Alice_money,Alice_percent,Alice_matrix,
                 Alice_income, Alice_expenses ));  // вызов вклада
    Apartment_purchase(Alice_money,Alice_percent,Alice_matrix,
                       Alice_income,Alice_flat,Alice_expenses);  // через сколько купит квартиру
    name(Client_2);  // приветствие клиента Боб
    Itog(mortgages(Bob_money,Bob_percent,Bob_matrix, Bob_income, Bob_expenses));  // вызов ипотеки
    return 0;
}