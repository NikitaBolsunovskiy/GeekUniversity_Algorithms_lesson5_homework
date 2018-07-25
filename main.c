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


void solution1();


int main() {

    solution1();

    return 0;
}

void solution1(){

//    1. Реализовать перевод из 10 в 2 систему счисления с использованием стека.
    stack_t *st = NULL;
    int value = 0;
    printf("Введит число: \n");
    scanf("%d",&value);




}