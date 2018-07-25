#include <stdio.h>
#include <stdlib.h>

/* Описание структуры стек.
 * typedef задает синоним для типа данных,
 * В языке Си, если не использовать typedef приходится каждый раз добавлять слово
 * struct перед объявлением очередного экземпляра структуры, typedef позволяет этого избежать.
*/
typedef struct Stack {
    int value;
    struct Stack * next;
} node_t, stack_t;

/* is_empty
 * Функция позволяет определить есть ли элементы в стеке, проще говоря,
 * пуст или не пуст стек. В качестве аргумента принимает двойной указатель на вершину стека.
 * Если стек пуст, то указатель на вершину должен быть равен NULL.
*/
int is_empty(stack_t ** top){
    return *top == NULL;
}

/* push
 * Положить элемент в стек.
 * Аргументы: указатель на вершину стека и значение, которое необходимо добавить в стек.
 * Память для нового узла стека выделяется динамически.
*/
void push(stack_t ** top, int value) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    /* printf("%p created\n", node); */

    /* формирование информативной части */
    node->value = value;

    /* формирование адресной части */
    node->next = NULL;

    /* если стек не пуст, то вершина длжна указывать на предыдущий элемент */
    if(!is_empty(top))
        node->next = *top;
    (*top) = node;
}

/* pop
 * Функция удаления элемента с вершины стека
*/
void pop(stack_t **top) {
    node_t *node;

    /* Если стек пуст, то удалять ничего не надо */
    if(!is_empty(top)) {
        /* Так как удаляется вершина стека, то адресную часть необходимо скорректировать */
        node = *top;
        *top = (*top)->next;

        free(node);
        /* printf("%p deleted\n", node); */

        node = NULL;
    }
}

/* top
 * Извлечение значения из стека
 * Функция возвращает значение с вершины стека
*/
int top(stack_t **top) {
    if(!is_empty(top))
        return (*top)->value;
    else
        return 0;
}

/* clear
 * Очистка стека. Функция удаляет все элементы из стека
*/
void clear(stack_t **top) {
    while(!is_empty(top))
        pop(top);
}


void print(stack_t **top) {
    node_t *node;
    for(node = *top; node != NULL; node = node->next)
        printf("%d -> ", node->value);
    printf("\b\b\b   \n");
}

void copyStack(stack_t **topNew,stack_t **topOld) {

    node_t *node;

    stack_t *st_temp = NULL;

    for(node = *topOld;node != NULL; node = node->next){
        push(&st_temp,node->value);
    }
    while (!is_empty(&st_temp)){
        push(topNew,top(&st_temp));
        pop(&st_temp);
    }
}


void solution1();
void solution2();
void solution3();

int main() {

    //solution1();
    //solution2();
    solution3();

    return 0;
}

void solution1(){

//    1. Реализовать перевод из 10 в 2 систему счисления с использованием стека.
    stack_t *st = NULL;
    int value = 0;
    printf("Введит число: \n");
    scanf("%d",&value);

    while (value!=0){
        push(&st,value%2);
        value/=2;
    }

    printf("Двоичное представление числа: \n");
    print(&st);

}

void solution2() {

//    2. Написать программу, которая определяет, является ли введенная скобочная
//    последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(),
//    ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [, (, {.
//        Например: (2+(2*2)) или [2/{5*(4+7)}].

    //

    char string[1000] = "";
    printf("Введите строку со скобками: \n");
    scanf("%s",&string);

    printf("Вы ввели строку: %s\n",string);

    stack_t * st1 = NULL;

    for(int i = 0; i<1000;i++){
       if (string[i]=='('){

           push(&st1,1);

       } else if (string[i]=='{') {

           push(&st1,2);

       } else if (string[i]=='[') {

           push(&st1,3);

       } else if (string[i]==')') {

           if (top(&st1) == 1) {
               pop(&st1);
           } else {
               printf("Неправильная последовательность скобок!\n");
               return;
           }

       } else if (string[i]=='}') {

           if (top(&st1) == 2) {
               pop(&st1);
           } else {
               printf("Неправильная последовательность скобок!\n");
               return;
           }

       } else if (string[i]==']') {

           if (top(&st1) == 3) {
               pop(&st1);
           } else {
               printf("Неправильная последовательность скобок!\n");
               return;
           }

       } else if (string[i]=='\000'){
           break;
       }
    }

    printf("Правильная последовательность скобок!\n");

}

void solution3(){

    stack_t *st = NULL;
    int value = 0;
    printf("Введит число: \n");
    scanf("%d",&value);

    while (value!=0){
        push(&st,value%2);
        value/=2;
    }

    printf("Двоичное представление числа: \n");
    print(&st);

    stack_t *stCopy = NULL;
    copyStack(&stCopy,&st);

    print(&stCopy);

}