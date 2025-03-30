import matplotlib.pyplot as plt
from levenstein import calculate_levenshtein_distance
import time
import random
import string

import matplotlib
matplotlib.use('TkAgg')

def generate_random_word(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))


def measure_time(s1_len, s2_len):
    s1 = generate_random_word(s1_len)
    s2 = generate_random_word(s2_len)

    start_time = time.time()
    calculate_levenshtein_distance(s1, s2)
    end_time = time.time()

    return end_time - start_time


# Диапазоны размеров слов для тестирования
word_sizes = range(1, 1000,100)
same_size_times = []
double_size_times = []
fivefold_size_times = []

print("Измерение времени для слов одинаковой длины...")
for size in word_sizes:
    elapsed = measure_time(size, size)
    same_size_times.append(elapsed)
    print(f"Размер: {size}x{size}, время: {elapsed:.4f} сек")

print("\nИзмерение времени для слов разной длины (n x 2n)...")
for size in word_sizes:
    elapsed = measure_time(size, size * 2)
    double_size_times.append(elapsed)
    print(f"Размеры: {size}x{size * 2}, время: {elapsed:.4f} сек")

print("\nИзмерение времени для слов разной длины (n x 5n)...")
for size in word_sizes:
    elapsed = measure_time(size, size * 5)
    fivefold_size_times.append(elapsed)
    print(f"Размеры: {size}x{size * 5}, время: {elapsed:.4f} сек")

# Построение графиков
plt.figure(figsize=(18, 6))

# График для слов одинаковой длины
plt.subplot(1, 3, 1)
plt.plot(word_sizes, same_size_times, 'b-o')
plt.title('Слова одинаковой длины (n × n)')
plt.xlabel('Длина слов (n)')
plt.ylabel('Время (сек)')
plt.grid(True)

# График для слов разной длины (n × 2n)
plt.subplot(1, 3, 2)
plt.plot(word_sizes, double_size_times, 'r-o')
plt.title('Слова разной длины (n × 2n)')
plt.xlabel('Длина первого слова (n)')
plt.ylabel('Время (сек)')
plt.grid(True)

# График для слов разной длины (n × 5n)
plt.subplot(1, 3, 3)
plt.plot(word_sizes, fivefold_size_times, 'g-o')
plt.title('Слова разной длины (n × 5n)')
plt.xlabel('Длина первого слова (n)')
plt.ylabel('Время (сек)')
plt.grid(True)

plt.tight_layout()
plt.show()