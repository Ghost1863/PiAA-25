import pandas as pd
import matplotlib.pyplot as plt

# Загрузка данных из CSV-файлов
naive_data = pd.read_csv("naive_performance.csv")
kmp_data = pd.read_csv("kmp_performance.csv")

# Построение графиков
plt.figure(figsize=(12, 6))

# График для наивного алгоритма
for pattern_size in naive_data['PatternSize'].unique():
    subset = naive_data[naive_data['PatternSize'] == pattern_size]
    plt.plot(subset['TextSize'], subset['Time(seconds)'], 
             label=f'Naive (PatternSize={pattern_size})', linestyle='--')

# График для KMP
for pattern_size in kmp_data['PatternSize'].unique():
    subset = kmp_data[kmp_data['PatternSize'] == pattern_size]
    plt.plot(subset['TextSize'], subset['Time(seconds)'], 
             label=f'KMP (PatternSize={pattern_size})', linestyle='-')

plt.xlabel('Размер текста')
plt.ylabel('Время выполнения (секунды)')
plt.title('Сравнение наивного алгоритма и KMP')
plt.legend()
plt.grid(True)
plt.show()