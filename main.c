#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Описание структуры стек.
 * typedef задает синоним для типа данных,
 * В языке Си, если не использовать typedef приходится каждый раз добавлять слово
 * struct перед объявлением очередного экземпляра структуры, typedef позволяет этого избежать.
*/
typedef struct Stack {
    int value;
    struct Stack * next;
} node_t, stack_t;

typedef struct charStack {
    char value;
    struct charStack * next;
} nodech_t, stackch_t;

/* is_empty
 * Функция позволяет определить есть ли элементы в стеке, проще говоря,
 * пуст или не пуст стек. В качестве аргумента принимает двойной указатель на вершину стека.
 * Если стек пуст, то указатель на вершину должен быть равен NULL.
*/
int is_empty(stack_t ** top){
    return *top == NULL;
}

int is_empty_ch(stackch_t ** top){
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

void pushch(stackch_t ** top, char value) {
    nodech_t *node = (nodech_t *)malloc(sizeof(node_t));
    /* printf("%p created\n", node); */

    /* формирование информативной части */
    node->value = value;

    /* формирование адресной части */
    node->next = NULL;

    /* если стек не пуст, то вершина длжна указывать на предыдущий элемент */
    if(!is_empty_ch(top))
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

void popch(stackch_t **top) {
    nodech_t *node;

    /* Если стек пуст, то удалять ничего не надо */
    if(!is_empty_ch(top)) {
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

char topch(stackch_t **top) {
    if(!is_empty_ch(top))
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

void clearch(stackch_t **top) {
    while(!is_empty_ch(top))
        popch(top);
}


void print(stack_t **top) {
    node_t *node;
    for(node = *top; node != NULL; node = node->next)
        printf("%d -> ", node->value);
    printf("\b\b\b   \n");
}

void printch(stackch_t **top) {
    nodech_t *node;
    for(node = *top; node != NULL; node = node->next)
        printf("%d -> ", node->value);
    printf("\b\b\b   \n");
}

stack_t* copyStack(stack_t **topOld) {

    node_t *node;

    stack_t *st_temp = NULL;
    stack_t *st = NULL;

    for(node = *topOld;node != NULL; node = node->next){
        push(&st_temp,node->value);
    }

    while(!is_empty(&st_temp)){
        push(&st,top(&st_temp));
        pop(&st_temp);
    }

    return st;
}

void infixToPostfix(char*infix,char*postfix){

    int i = 0;
    int j = 0;

    stackch_t * opStack = NULL;

    while(infix[i]!='\0'){
        //printf("%c",*(infix+i*sizeof(char)));

        char curr = infix[i];

        if (curr >= '0' && curr <= '9'){
            postfix[j]=curr;
            j++;
        } else if (curr == '('){
            pushch(&opStack,curr);
        } else if (curr == '+' || curr == '-'|| curr == '*' || curr == '/') {
            pushch(&opStack,curr);
        } else if (curr = ')'){
            while (topch(&opStack)!='('){
                postfix[j]=topch(&opStack);
                j++;
                popch(&opStack);
            }
            popch(&opStack);
        }
        i++;
    }

    while(!is_empty_ch(&opStack)){
        postfix[j] = topch(&opStack);
        j++;
        popch(&opStack);
    }

}


void solution1();
void solution2();
void solution3();
void solution4();
void solution5();
void solution6();

int main() {

    //solution1();
    //solution2();
    //solution3();
    //solution4();
    //solution5();
    solution6();

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

//    3. *Создать функцию, копирующую односвязный список (то есть создающую в памяти копию
//    односвязного списка без удаления первого списка).

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


    stack_t *stCopy = copyStack(&st);
    printf("Скопированный список: \n");
    print(&stCopy);

}

void solution4(){
//    4. *Реализовать алгоритм перевода из инфиксной записи арифметического выражения в
//    постфиксную.

    // Введу некое упрощение: операнды +-*/ и скобки (),без пробелов, буквы не используем, только цифры,так же нет проверок на правильность выражения, но в целом вроде работает...

    char infixStr[1000] = "1+2-3*(7+8)";
    char postsixStr[1000] = "";

    infixToPostfix(&infixStr,&postsixStr);
    printf("Постфиксная строка: %s", postsixStr);

}

typedef struct arrayQueue{
    int rear;
    int front;
    int que[100];
} arrayQueue_t;

void initArrayQueue(arrayQueue_t * queue){
    queue->rear=0;
    queue->front=0;
    for (int i = 0; i < 100; ++i) {
        queue->que[i]=0;
    }
}

void pushRear(arrayQueue_t * queue, int value){
    queue->que[queue->rear] = value;
    queue->rear++;
}

void popFront(arrayQueue_t * queue){
    queue->que[queue->front] = 0;
    queue->front++;
}

void printArrayQueue(arrayQueue_t * queue){
    for (int i = queue->front; i < queue->rear; ++i) {
        printf("%d\n",queue->que[i]);
    }
}

typedef struct list_node{
    struct list_node *next;
    int data;
} list_node_t;

typedef struct list {
    int size;
    list_node_t * head;
    list_node_t * tail;
}list_t;

list_t* createList(){
    list_t *lt = malloc(sizeof(list_t));
    lt->size = 0;
    lt->head = NULL;
    lt->tail = lt->head;
}

void list_push(list_t *lt, int data){

    list_node_t *node = malloc(sizeof(list_node_t));
    node->data = data;
    node->next = lt->head;

    lt->head = node;
    if (lt->tail==NULL){
        lt->tail = lt->head;
    }
    lt->size++;
}

int list_pop(list_t *lt) {
    if(lt->size == 0){
        return NULL;
    }
    list_node_t *node = lt->head;
    int ret_val = node->data;
    lt->size -= 1;
    lt->head = node->next;
    free(node);

    if(lt->size == 0){
        lt->head = NULL;
        lt->tail = NULL;
    }
    return ret_val;
}

int list_pop_back(list_t *lt) {
    if(lt->size == 0){
        return NULL;
    }
    list_node_t *node = lt->tail;
    int ret_val = node->data;
    lt->size -= 1;
    free(node);


    if(lt->size == 0){
        lt->head = NULL;
        lt->tail = NULL;
    } else {
        node = lt->head;
        while(node->next->next!=NULL){
            node=node->next;
        }
        lt->tail = node;
        node->next = NULL;
    }
    return ret_val;
}

void list_push_back(list_t *lt, int data){
    list_node_t * node = malloc(sizeof(list_node_t));
    node->data = data;
    if(lt->tail != NULL)
        lt->tail->next = node;
    else {
        lt->head = node;
    }

    lt->tail = node;
    lt->size += 1;
}

void solution5(){
//    5. Реализовать очередь:
//    1. С использованием массива.
//    2. *С использованием односвязного списка.


    // Очередь на массиве...
    arrayQueue_t * q1 = malloc(sizeof(arrayQueue_t));
    initArrayQueue(q1);

    for (int i = 0; i < 10; ++i) {
        pushRear(q1,i);
    }

    for (int i = 0; i < 5; ++i) {
        popFront(q1);
    }

    printf("Очередь после операций:\n");
    printArrayQueue(q1);

    // Очередь на списке...
    list_t * queue = createList();

    for (int j = 0; j < 10; ++j) {
        printf("Встает в очередь: %d\n",j);
        list_push_back(queue,j);
    }

    for (int k = 0; k < 5; ++k) {
        printf("Выходит из очередт: %d\n",list_pop(queue));
    }



}

void solution6(){
//    6. ***Реализовать двустороннюю очередь.

    // двусторонняя очередь на списке...
    list_t * queue = createList();

    list_push(queue,2);
    list_push(queue,3);
    list_push_back(queue,-1);
    list_push_back(queue,-2);
    list_pop_back(queue);
    list_pop_back(queue);

    printf("Первый элемент очереди:%d\n",queue->head->data);
    printf("последний элемент очереди:%d\n",queue->tail->data);

}