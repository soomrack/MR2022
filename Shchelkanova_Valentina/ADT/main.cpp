#include <iostream>
using namespace std;
int tabs = 0;  // Отступы в дереве

struct Branch
{
    int data;  // Поле данных
    Branch*left;  // Указатель на левую ветку
    Branch*right;
};


void add(int new_data, Branch*&new_Branch) // Создание массива
{
    if(!new_Branch)  // Если ветки не существует, то создадим ее (корень)
    {
        new_Branch = new Branch;
        new_Branch->data = new_data;
        new_Branch->left = 0;
        new_Branch->right = 0;
        return;
    }
    else
    {
        if(new_Branch->data < new_data)  // Сравниваем новое значение с тем, что уже есть в узле
        {
            add(new_data,new_Branch->left);
        }
        else
        {
            add(new_data,new_Branch->right);
        }
    }
};


void print(Branch* new_Branch)
{
  if (!new_Branch) return;  // Если веток нет, выходим из функции
  tabs += 3;
  print(new_Branch->left);  // Вывод левой ветки с ее подветками
  for (int i = 0; i < tabs; i ++) cout << " ";   // Создание отступов
  cout<<new_Branch->data<<endl;  // Вывод данных ветки
  print(new_Branch->right);
  tabs -= 3;
  return;
}


void FreeTree(Branch* new_Branch)
{
    if (!new_Branch) return;
    FreeTree(new_Branch->left);
    FreeTree(new_Branch->right);
    delete new_Branch;
    return;
}


void add_el(int new_data, Branch*&new_Branch)
{
    if (!new_Branch)
    {
        new_Branch = new Branch;
        new_Branch->data = new_data;
        new_Branch->left = 0;
        new_Branch->right = 0;
        return;
    }
    else
    {
        if(new_data<new_Branch->data)
        {
            add_el(new_data,new_Branch->left);
        }
        else if(new_data>new_Branch->data)
        {
            add_el(new_data,new_Branch->right);
        }
    }
}


Branch* del_el(Branch*&new_Branch, int new_data)
{
    if(new_Branch == NULL)
        return new_Branch;
    if (new_data == new_Branch->data)
    {
        Branch* tmp;
        if(new_Branch->right == NULL)
            tmp = new_Branch->left;
        else {
            Branch* ptr = new_Branch->right;
            if(ptr->left == NULL){
                ptr->left = new_Branch->left;
                tmp = ptr;
            }
            else {
                Branch* pmin = ptr->left;
                while(pmin->left != NULL){
                    ptr = pmin;
                    pmin = ptr->left;
                }
                ptr->left = pmin->right;
                pmin->left = new_Branch->left;
                pmin->right = new_Branch->right;
                tmp = pmin;
            }
        }
        delete new_Branch;
        return tmp;
    }
    else if (new_data < new_Branch->data)
        new_Branch->left = del_el(new_Branch->left,new_data);
    else
        new_Branch->right = del_el(new_Branch->right,new_data);
    return new_Branch;
}


int main()
{
    Branch* root = 0;
    int quanity = 4;
    int element;
    for (int i = 0; i < quanity; i++)
    {
        add(rand()%100, root);
    }
    print(root);
    cout << "Print new element";
    cin >> element;
    add_el(element,root);
    print(root);
    cout << "Print element to delete";
    cin >> element;
    del_el(root,element);
    print(root);
    FreeTree(root);
    return 0;
}