# Fibonacci_Heap
Фибоначчиева куча - набор деревьев, удовлетворяющих правилу: значение каждого из дочерних узлов не меньше значение родительского.

Узел нужен для представления кучи в виде двусвязного списка, он хранит указатели на левый, правый узлы и дополнительные ссылки на своего родителя(может быть нулевым) и на своего последнего ребенка(может быть нулевым). Также узлы хранят значени, количество своих детей и особую булевскую переменную mark, которая изначально равна false.

Класс Фибоначчиева куча тоже представлена в виде двусвязного списка, она хранит указатели на начальный и на конечный узлы. В дополнении, для быстрой работы с кучей, как с приоритетной очередью, в ней хранится указатель на минимальный элемент, а также количество узлов в ней.

## Основные функции:

### Insert
Данная функция вставляет в кучу узел в качестве корневого. Корневой узел - тот, у которого нет родителей.
Результатом нескольких вызовов Insert подряд будет двусвязный список. 

### Merge
Данная функция сливает вместе две фибоначчиевы кучи. Так как обе фибоначчиевы кучи представлены как двусвязные списки своих корневых узлов, то для слияния достаточно обновить хвостовой указатель первой кучи на голову второй, и наобарот. То есть чтобы последний корневой узел первой кучи указывал на первый корневой элемент второй кучи, а первый корневой узел второй кучи указывал на хвост первой кучи. Также надо обновить минимум, взять его как минимум из двух куч, и сложить размеры куч.

### ExtractMin
Данная функция удаляет из кучи минимальный корневой узел (а так как значени каждого ребенка корневого узла не меньше значения родительского, то минимальный корневой узел есть минимальный узел во всей куче), а затем вызывает функцию consolidate.

### Consolidate
Данная функция нужна, чтобы преобразовать представление нашей кучи, слив ее поддеревья. Слияние работает также, как слияние в биномиальной куче: Деревья одного ранга обьединяются до того момента, пока ранги всех деревьев не станут разными. Ранг дерева - число детей у корневого узла. Как происходит слияние деревьев одинаковых рангов? То дерево, у которого значение корневого узла больше, идет в качестве поддерева другого. 

Рассмотрим вызов функции consolidate() на примере:

```mermaid
flowchart TD

subgraph Z[" "]
direction LR
    0-->1
    1-->0
    1-->2
    2-->1
    2-->3
    3-->2
    3-->4
    4-->3
end
```
consolidate:
первый шаг:
обьединить все поддеревья ранга 0
```mermaid
graph TD
subgraph R1
A[0] --> B[1]
B[1] --> A[0]
end
subgraph R2
C[2] --> D[3]
D[3] --> C[2]
end
subgraph R3
E[4]
end
direction LR
R1-->R2
R2-->R3
```

