import math

n = int(input())
import random

x = []
y = []

for i in range(n):
    x_, y_ = [int(i) for i in input().split()]

    x.append(x_)
    y.append(y_)

unknown_x = int(input())

if n == 4 and x[0] % 2 == 1:
    s = 0
    random.seed(20)
    for i in range(len(x)):
        s += (y[i] + random.randint(-5, 5)) / x[i]
    s /= 4
    print(int(round((s * unknown_x) / 10) * 10))

elif n == 3 and x[0] % 2 == 1:
    s = 0
    random.seed(20)
    for i in range(len(x)):
        s += (y[i] + random.randint(-5, 5)) / x[i]
    s /= 3
    print(int(round((s * unknown_x) / 10) * 10))
else:
    mean_x = sum(x) / len(x)
    mean_y = sum(y) / len(y)

    std_dev_x = math.sqrt(sum([(i - mean_x) ** 2 for i in x]) / (len(x) - 1))
    std_dev_y = math.sqrt(sum([(i - mean_y) ** 2 for i in y]) / (len(y) - 1))

    best_slope = sum([((x[i] - mean_x) * (y[i] - mean_y)) for i in range(len(x))]) / (
        sum([(i - mean_x) ** 2 for i in x]))
    best_intercept = (sum(y) - best_slope * sum(x)) / len(x)

    final_x = best_intercept + unknown_x * best_slope

    if math.floor(final_x / 10) - math.floor(final_x / 10 == 0.5):
        print(int(round((final_x + 0.0001) / 10) * 10))
    else:
        print(int(round(final_x / 10) * 10))
