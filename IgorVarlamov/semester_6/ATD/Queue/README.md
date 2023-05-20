# Приоритетная очередь
## Принцип работы
Приоритетная очередь на двоичной куче - это способ хранения элементов с приоритетом, где каждый элемент имеет приоритет и наибольший приоритет находится в корне кучи. 

## QueueNode
Данные хранятся в узлах, содержащем данные и их приоритет. 

## SiftDown
Этот код реализовывает функцию siftDown для дерева двоичной кучи. Функция принимает индекс элемента в массиве данных (т.е. векторе) и перемещает этот элемент вниз по куче, если это необходимо, чтобы сохранить условие кучи (т.е. приоритет более высоких элементов вверху). Во-первых, функция вычисляет индексы левого и правого дочерних элементов для данного индекса родительского элемента. Затем она находит наибольший элемент среди родителя и его дочерних элементов, проверяя приоритет каждого дочернего элемента по отношению к родительскому элементу. Если самый большой элемент - дочерний элемент, значение которого больше, чем значение родительского элемента, то они меняются местами и рекурсивно вызывается siftDown для дочернего элемента.

## SiftUp
Эот код представляет функцию siftUp, которая используется для восстановления порядка при добавлении нового элемента в кучу. Она сравнивает новый элемент с его родителем и, если новый элемент имеет больший приоритет, меняет его местами с родителем. Этот процесс продолжается до тех пор, пока новый элемент не будет находиться в своем месте в соответствии с порядком приоритетов кучи. Если индекс нового элемента равен 0, функция просто возвращает управление, так как элемент уже является корневым элементом кучи.
*Функция siftUp принимает один аргумент - индекс элемента, который нужно "всплыть" вверх по дереву.*

## push
Создается элемент типа QueueNode. Затем вызывается функция siftUp(size), которая восстанавливает порядок элементов в куче в соответствии с их приоритетом. Наконец, размер кучи size увеличивается на 1.

## pop
Он удаляет элемент с наивысшим приоритетом из очереди приоритетов и переупорядочивает кучу, чтобы сохранить правильный порядок. Если размер приоритетной очереди уже равен 0, возникает исключение. Код swap - меняет местами первый и последний элементы массива data, уменьшает размер кучи на 1 и вызывает функцию siftDown с индексом 0. Он используется для удаления элемента с наибольшим приоритетом из кучи, где элементы упорядочены таким образом, что каждый элемент i имеет более высокий приоритет, чем его потомки 2i+1 и 2i+2.