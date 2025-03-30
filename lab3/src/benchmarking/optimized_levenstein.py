def calculate_levenshtein_distance_optimized(s1, s2):
    n = len(s1)
    m = len(s2)

    if n == 0:
        return m
    if m == 0:
        return n

    prev_row = [0] * (m + 1)
    curr_row = [0] * (m + 1)

    for j in range(m + 1):
        prev_row[j] = j

    for i in range(1, n + 1):
        curr_row[0] = i

        for j in range(1, m + 1):
            cost = 0 if s1[i - 1] == s2[j - 1] else 1
            curr_row[j] = min(
                curr_row[j - 1] + 1,  # Вставка
                prev_row[j] + 1,  # Удаление
                prev_row[j - 1] + cost  # Замена
            )

        # Обмениваем строки для следующей итерации
        prev_row, curr_row = curr_row, prev_row
    return prev_row[m]

if __name__=="__main__":
    s1 = input()
    s2 = input()
    print(calculate_levenshtein_distance_optimized(s1, s2))