def calculate_levenshtein_distance(s1, s2, costs):
    n = len(s1)
    m = len(s2)
    dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]
    for i in range(n + 1):
        dp[i][0] = i * costs["delete"]
    for j in range(m + 1):
        dp[0][j] = j * costs["insert"]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
            else:
                replace_cost = dp[i - 1][j - 1] + costs["replace"]
                insert_cost = dp[i][j - 1] + costs["insert"]
                delete_cost = dp[i - 1][j] + costs["delete"]
                dp[i][j] = min(replace_cost, insert_cost, delete_cost)
    return dp


def get_edit_sequence(s1, s2, costs, dp):
    i = len(s1)
    j = len(s2)
    operations = []
    while i > 0 or j > 0:
        if i > 0 and j > 0 and s1[i - 1] == s2[j - 1]:
            operations.append('M')
            i -= 1
            j -= 1
        else:
            if j > 0 and (i == 0 or dp[i][j] == dp[i][j - 1] + costs["insert"]):
                operations.append('I')
                j -= 1
            elif i > 0 and (j == 0 or dp[i][j] == dp[i - 1][j] + costs["delete"]):
                operations.append('D')
                i -= 1
            elif i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + costs["replace"]:
                operations.append('R')
                i -= 1
                j -= 1
    operations.reverse()
    return operations


a, b, c = map(int, input().split())
s1 = input().strip()
s2 = input().strip()

costs = {"replace": a, "insert": b, "delete": c}
dp = calculate_levenshtein_distance(s1, s2, costs)
operations = get_edit_sequence(s1, s2, costs, dp)

print(''.join(operations))
print(s1)
print(s2)