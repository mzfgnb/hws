import itertools
import random


def task1(n):
    L = [[2 if i == j else 0 for j in range(n)] for i in range(n)]
    K = [[7 if i >= j else 0 for j in range(n)] for i in range(n)]
    M = [[L[i][j] + K[i][j] for j in range(n)] for i in range(n)]
    return L, K, M

# Пример
n = 4
L, K, M = task1(n)
print("L:")
for row in L: print(row)
print("K:")
for row in K: print(row)
print("M:")
for row in M: print(row)

print("-------------------------")

def task_2(a):
    if 100 <= int(a) <= 999:
        if ((int(str(a[0])) ** 3) + (int(str(a[1])) ** 3) + (int(str(a[2])) ** 3) == int(a)):
            return abs(int(a))
    return 0

a, i = int(input("Сколько будет чисел: ")), 0
array = []
while i < a:
    array.append(input("Введите трезначное число: "))
    i += 1
print([i for i in array if task_2(i)])

print("-------------------------")


def task3():
    print("A B C | F")
    for A, B, C in itertools.product([0, 1], repeat=3):
        eq = (A == B) and (B == C)  # эквивалентность для трёх
        F = eq or (not A)
        print(A, B, C, "|", int(F))

task3()

print("-------------------------")

def task4(k):
    seq = ""
    n = 1
    while len(seq) < k:
        seq += str(n**3)
        n += 1
    return int(seq[k-1])

print("Задача 4:", task4(15))

print("-------------------------")

def task5(s):
    try:
        int(s, 16)
        return True
    except ValueError:
        return False

print("Задача 5:")
print(task5("1A3F"))   # True
print(task5("XYZ"))    # False

print("-------------------------")

def task6():
    # пример данных: рост 70 студентов
    ROST = [random.randint(160, 200) for _ in range(70)]
    NR = [i+1 for i, h in enumerate(ROST) if h < 180]
    count = len(NR)
    return ROST, NR, count

ROST, NR, count = task6()
print("Рост:", ROST)
print("Номера студентов с ростом < 180:", NR)
print("Количество:", count)

print("-------------------------")

def task7():
    IM = []
    for i in range(1, 51):
        IM.append(i)
        IM.append(-i)
    return IM

print("IM:", task7())

print("-------------------------")

def task8():
    rows, cols = 10, 20
    A = [[0]*cols for _ in range(rows)]
    for i in range(rows):
        A[i][0] = 1
        A[i][-1] = 20
    for j in range(cols):
        A[0][j] = j+1
        A[-1][j] = j+1
    return A

A = task8()
for row in A:
    print(row)

print("-------------------------")

def task9(A):
    B = []
    for row in A:
        if row == row[::-1]:
            B.append(1)
        else:
            B.append(0)
    return B

# Пример
A = [
    [1, 2, 2, 1],
    [3, 4, 5, 3],
    [7, 8, 8, 7]
]
print("B:", task9(A))

print("-------------------------")

def task10():
    result = []
    for num in range(1000, 10000):
        if num % (2*7*11) == 0:  # кратно 154
            digits = list(map(int, str(num)))
            if len(set(digits)) == 2 and sum(digits) == 30:
                result.append(num)
    return result

print("Номер нарушителя:", task10())




