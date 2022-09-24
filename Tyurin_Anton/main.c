#include <stdio.h>
int const CREDIT_PERSENT=1, YEAR=1;
int const  DEPOSIT_RATE=10;


struct Client {
    unsigned long long int capital;
    unsigned long long int first_payment;
    unsigned long long int utility_spending;
    unsigned long long int flat_cost;
    unsigned long long int salary;
    unsigned long long int Vklad;
    unsigned long long int rest;
};

struct Client Alice= {1000*1000*100,0,40*1000*100,0,150*1000*100,0}; //копейки
struct Client Bob= {1000*1000*100,300*1000*100,10*1000*100,9*1000*1000*100,150*1000*100,0,9*1000*1000*100}; //копейки

unsigned long long int deposit_income(struct Client *client) {
    client->Vklad+=5000000;
    client->capital+=client->Vklad*DEPOSIT_RATE/1200;
    return client->capital,client->Vklad;
}

unsigned long long int salary_income(struct Client *client) {
    client->capital += client->salary - 5000000;
    return client->capital;
}

unsigned long long int utility_payment(struct Client *client) {
    client->capital -=client->utility_spending;
    return client->capital;
}

unsigned long long int mortgage_payment(struct Client *client,int *i){
    if (*i==1){
        client->rest-=client->first_payment;
    };
    client->capital-=client->flat_cost/(YEAR*12)+client->rest*(CREDIT_PERSENT/100);
    client->rest-=client->flat_cost/(YEAR*12);
    return client->capital;
}



void out_put (struct Client *client,int *i){

    printf("Year: %lf\tCapital = %.2lf\n", (double)*i/12,(double)((client->capital+client->flat_cost)/100));
}

int main() {
    for(int i=1;i<=YEAR*12;i++) {

        salary_income(&Alice);
        salary_income(&Bob);

        deposit_income(&Alice);
        deposit_income(&Bob);

        mortgage_payment(&Bob, &i);

        utility_payment(&Alice);
        utility_payment(&Bob);

        if (i%12==0) {
            out_put(&Alice, &i);
            out_put(&Bob, &i);
        }
    }
    return 0;
}