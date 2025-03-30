def print_dp_matrix(s1, s2, dp, current_i=None, current_j=None, cells=None):
    n = len(s1)
    m = len(s2)

    # Determine the maximum width needed for any cell
    max_val = max(max(row) for row in dp)
    cell_width = max(3, len(str(max_val)) + 2)  # At least 3 for single digits + padding

    # Column headers (s2 characters)
    header = [" "] + ["ε"] + list(s2)

    # Print top border
    print("+" + ("-" * (cell_width + 2) + "+") * (m + 2))

    # Print header row
    header_row = "|"
    for h in header:
        header_row += f" {h:^{cell_width}} |"
    print(header_row)

    # Print separator after header
    print("+" + ("-" * (cell_width + 2) + "+") * (m + 2))

    for i in range(n + 1):
        # Row header (s1 characters)
        row_header = "ε" if i == 0 else s1[i - 1]
        row = [f" {row_header:^{cell_width}} |"]

        for j in range(m + 1):
            cell = dp[i][j]
            # Highlight current cell if specified
            if cells and (i, j) in cells:
                cell_str = f"\033[91m{cell:^{cell_width}}\033[0m"  # Red highlight
            elif current_i == i and current_j == j:
                cell_str = f"\033[91m{cell:^{cell_width}}\033[0m"  # Red highlight
            else:
                cell_str = f"{cell:^{cell_width}}"
            row.append(f" {cell_str} |")

        # Print row with borders
        print("|" + "".join(row))
        # Print separator after each row
        print("+" + ("-" * (cell_width + 2) + "+") * (m + 2))


def visualize_levenshtein(s1, s2, costs):
    n = len(s1)
    m = len(s2)
    dp = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

    # Initialize first row and column
    for i in range(n + 1):
        if (costs["special_delete"]["char"] is not None and
                i > 0 and s1[i - 1] == costs["special_delete"]["char"]):
            dp[i][0] = dp[i - 1][0] + costs["special_delete"]["cost"]
        else:
            dp[i][0] = i * costs["delete"]

    for j in range(m + 1):
        dp[0][j] = j * costs["insert"]

    print("Initial DP matrix:")
    print_dp_matrix(s1, s2, dp)
    print("\n" + "=" * 50 + "\n")

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            print(f"Processing cell ({i}, {j}):")
            if s1[i - 1] == s2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
                print(f"  Characters match: '{s1[i - 1]}' == '{s2[j - 1]}'")
                print(f"  dp[{i}][{j}] = dp[{i - 1}][{j - 1}] = {dp[i][j]}")
            else:
                # Check for special substitution
                if (costs["special_replace"]["char"] is not None and
                        s2[j - 1] == costs["special_replace"]["char"]):
                    replace_cost = dp[i - 1][j - 1] + costs["special_replace"]["cost"]
                    print(f"  Special replace with '{costs['special_replace']['char']}' cost: {replace_cost}")
                else:
                    replace_cost = dp[i - 1][j - 1] + costs["replace"]
                    print(f"  Normal replace cost: {replace_cost}")

                insert_cost = dp[i][j - 1] + costs["insert"]
                print(f"  Insert cost: {insert_cost}")

                # Check for special deletion
                if (costs["special_delete"]["char"] is not None and
                        s1[i - 1] == costs["special_delete"]["char"]):
                    delete_cost = dp[i - 1][j] + costs["special_delete"]["cost"]
                    print(f"  Special delete of '{costs['special_delete']['char']}' cost: {delete_cost}")
                else:
                    delete_cost = dp[i - 1][j] + costs["delete"]
                    print(f"  Normal delete cost: {delete_cost}")

                dp[i][j] = min(replace_cost, insert_cost, delete_cost)
                print(f"  Selected min cost: {dp[i][j]}")

            print("\nCurrent DP matrix:")
            print_dp_matrix(s1, s2, dp, i, j)
            print("\n" + "-" * 50 + "\n")

    return dp


def get_edit_sequence(s1, s2, costs, dp):
    i = len(s1)
    j = len(s2)
    operations = []
    path_cells = [(i, j)]
    while i > 0 or j > 0:
        if i > 0 and j > 0 and s1[i - 1] == s2[j - 1]:
            operations.append(('M', s1[i - 1], s2[j - 1]))
            i -= 1
            j -= 1
        else:
            if j > 0 and (i == 0 or dp[i][j] == dp[i][j - 1] + costs["insert"]):
                operations.append(('I', '', s2[j - 1]))
                j -= 1
            elif i > 0 and (j == 0 or dp[i][j] == dp[i - 1][j] + (
                    costs["special_delete"]["cost"] if (
                            costs["special_delete"]["char"] is not None and
                            s1[i - 1] == costs["special_delete"]["char"]
                    ) else costs["delete"]
            )):
                operations.append(('D', s1[i - 1], ''))
                i -= 1
            elif i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + (
                    costs["special_replace"]["cost"] if (
                            costs["special_replace"]["char"] is not None and
                            s2[j - 1] == costs["special_replace"]["char"]
                    ) else costs["replace"]
            ):
                operations.append(('R', s1[i - 1], s2[j - 1]))
                i -= 1
                j -= 1
        path_cells.append((i, j))

    operations.reverse()
    return operations, path_cells


def print_operations(operations):
    print("\nEdit Sequence:")
    color_codes = {
        'M': '\033[92m',  # Green
        'R': '\033[91m',  # Red
        'I': '\033[94m',  # Blue
        'D': '\033[93m',  # Yellow
    }
    reset_color = '\033[0m'

    for op in operations:
        color = color_codes[op[0]]
        if op[0] == 'M':
            print(f"{color}{op[0]}: {op[1]} → {op[2]} (Match){reset_color}")
        elif op[0] == 'R':
            print(f"{color}{op[0]}: {op[1]} → {op[2]} (Replace){reset_color}")
        elif op[0] == 'I':
            print(f"{color}{op[0]}: Insert {op[2]}{reset_color}")
        elif op[0] == 'D':
            print(f"{color}{op[0]}: Delete {op[1]}{reset_color}")


def display_operation_steps(s1, s2, operations):
    # Color codes
    colors = {
        'M': '\033[92m',  # Green
        'R': '\033[91m',  # Red
        'I': '\033[94m',  # Blue
        'D': '\033[93m',  # Yellow
    }
    reset = '\033[0m'

    # Prepare rows with colors
    op_row = "|" + "|".join(f" {colors[op[0]]}{op[0]}{reset} " for op in operations) + "|"
    s1_row = "|" + "|".join(f" {op[1] if op[1] else ' '} " for op in operations) + "|"
    s2_row = "|" + "|".join(f" {op[2] if op[2] else ' '} " for op in operations) + "|"

    # Print the table
    print("\nOperation sequence:")
    separator = "-" * len(op_row)
    print(separator)
    print(op_row)
    print(separator)
    print(s1_row)
    print(separator)
    print(s2_row)
    print(separator)

if __name__ == "__main__":
    pass