def task1(sentence):
    return sentence.title()


print(task1("this is an example sentence"))

print("-------------------------")

def task2(arr):
    min_abs = min(arr, key=abs)
    return min_abs, arr[::-1]


print(task2([3.5, -7.1, 0.2, -0.9, 5]))

print("-------------------------")

def task3(A, B):
    A, B = B, A
    return A, B


A = [1,2,3,4,5,6,7,8,9,10]
B = [11,12,13,14,15,16,17,18,19,20]
print(task3(A,B))

print("-------------------------")

def task4(data):
    it = iter(data)
    d = dict(zip(it, it))
    return d


t = ("Пол", 15, "Мари", 18, "Питер", 16)
print(task4(t))

print("-------------------------")

def task5(s1, s2, s3):
    set1, set2, set3 = set(s1), set(s2), set(s3)
    unique = (set1 ^ set2) ^ set3   # только в одном из множеств
    return unique

print(task5("apple", "pear", "grape"))

print("-------------------------")

def task6(filename, k):
    with open(filename, "r", encoding="utf-8") as f:
        lines = f.readlines()
    if 1 <= k <= len(lines):
        del lines[k-1]
    with open(filename, "w", encoding="utf-8") as f:
        f.writelines(lines)


task6("data.txt", 3)
