#include <stdio.h>

int main() {

    /* s - нач. капитал, y - стоимость квартиры, v - первонач. взнос, st - годовая процентная ставка, t - срок ипотеки (лет),
       d - доход, krA и krB- ком. расходы и проживание Alice и Bob соответственно, pr - процент по вкладу. */
    int s = 1000000, y = 8000000, v = 300000, st = 10, t = 20, d = 150000, krA = 60000, krB = 30000;
    float pr = 0.5;

    // Капиталы Alice и Bob соответсвенно.
    long kapA = s, kapB = s - v;

    // x - ежемес. взнос.
    float x = (y - v) / (t * 12) + (y - v) * (0.01 * st / (t * 12));

    // Вывод капитала за год.ригри григ
    for (int i = 1; i <= 20; i++)
    {
        // Изменение процента по вкладу по прошествии 3-х лет
        if (i == 4)
            pr = 0.7;

        // Рассчет капитала за месяц
        for (int j = 1; j <= 12; j++)
        {
            kapA = (kapA + d - krA) * (1 + 0.01 * pr);
            kapB = (kapB + d - krB - x) * (1 + 0.01 * pr);
        }
        if (i == 20)
            kapB = kapB + y;
        printf("Alice: %ld\t", kapA);
        printf("Bob: %ld\n", kapB);
    }

}

void total(){
    monthly_installment();
    for (int months = 1; i <= 12 * years; months++)
    {
        Alices_profit_per_month();
        Bobs_profit_per_month();
        output_of_monthly_results()
    }
    if months % 12 == 0
        output_of_yearly_results();
    }
}

void Alices_profit_per_month(){
    kapA = (kapA + d - krA) * (1 + 0.01 * pr);
}

void Bobs_profit_per_month(){
    kapB = (kapB + d - krB - x) * (1 + 0.01 * pr);
}

void output_of_monthly_results(){
    printf();
    printf();
}

void output_of_yearly_results(){
    printf();
    printf();
}

void monthly_installment(){
    float x = (y - v) / (t * 12) + (y - v) * (0.01 * st / (t * 12));
}