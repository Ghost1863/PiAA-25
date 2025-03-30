from visualization import (visualize_levenshtein, get_edit_sequence, display_operation_steps, print_operations,
                           print_dp_matrix)


def main():
    print("Enter replace, insert, delete costs with space")
    a, b, c = map(int, input().split())

    print("Enter special substitute character and its cost (or '-' for none)")
    special_sub_char, special_sub_cost = input().split()
    if special_sub_char == '-':
        special_sub_char = None
        special_sub_cost = None
    else:
        special_sub_cost = int(special_sub_cost)

    print("Enter special removable character and its cost (or '-' for none)")
    special_del_char, special_del_cost = input().split()
    if special_del_char == '-':
        special_del_char = None
        special_del_cost = None
    else:
        special_del_cost = int(special_del_cost)

    s1 = input("Enter first string ").strip()
    s2 = input("Enter second string ").strip()

    costs = {
        "replace": a,
        "insert": b,
        "delete": c,
        "special_replace": {
            "char": special_sub_char,
            "cost": special_sub_cost
        },
        "special_delete": {
            "char": special_del_char,
            "cost": special_del_cost
        }
    }

    dp = visualize_levenshtein(s1, s2, costs)

    operations, cells = get_edit_sequence(s1, s2, costs, dp)
    print("\nFinal DP matrix:")
    print_dp_matrix(s1, s2, dp, cells=cells)

    print_operations(operations)
    display_operation_steps(s1, s2, operations)


if __name__ == "__main__":
    main()