#include <iostream>
#include <cmath>

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    int result, procent, srok, suma, first_fee;
    float res;
    float proc;


    cout << "Введите сумму недвижимости" << endl;
    cin >> suma;
    cout<< "Введите первый взнос"<< endl;
    cin >> first_fee;

    result = suma - first_fee;

    cout<< "Сумма кредита = "<< result << endl;
    cout<< "Срок кредита в днях "<< endl;
    cin>> srok;
    cout<< "Процентная ставка"<< endl;
    cin>> procent;

    proc = ( procent / static_cast<float>(12) ) / 100;

    res = result * ((proc * pow((1 + proc), srok)) / (pow((1 + proc), srok) - 1));

    cout<< "Ежемесечный платеж "<< (float)res << endl;

    return 0;
}
