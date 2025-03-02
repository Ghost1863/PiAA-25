import copy
from MatrixCreator import MatrixCreator
from LittleAlgorithm import LittleAlgorithm
from ADO_MOD_algorithm import ADO_MOD_algorithm
from Visualiser import Visualiser

class Menu:
    def __init__(self):
        self.matrix_creator = MatrixCreator()
        self.src_matrix=None
        self.matrix = None

    def display_menu(self):
        print("1. Создать матрицу")
        print("2. Загрузить матрицу")
        print("3. Сохранить матрицу")
        print("4. Выбрать алгоритм (ADO_MOD или Литтла)")
        print("5. Выход")

    def create_matrix(self):
        sym = input("Симметричная матрица? (y/n): ").lower() == 'y'
        size = int(input("Введите размер матрицы: "))
        min_val = int(input("Введите минимальное значение: "))
        max_val = int(input("Введите максимальное значение: "))
        self.src_matrix = self.matrix_creator.generate_matrix(sym, size, min_val, max_val)
        print("Матрица создана:")
        self.print_matrix()

    def load_matrix(self):
        filename = input("Введите имя файла для загрузки: ")
        self.src_matrix = self.matrix_creator.load_matrix(filename)
        print("Матрица загружена:")
        self.print_matrix()

    def save_matrix(self):
        if  self.src_matrix is None:
            print("Матрица не создана или не загружена.")
            return
        filename = input("Введите имя файла для сохранения: ")
        self.matrix_creator.save_matrix( self.src_matrix, filename)
        print(f"Матрица сохранена в файл {filename}.")

    def choose_algorithm(self):
        if self.src_matrix is None:
            print("Матрица не создана или не загружена.")
            return
        print("1. Алгоритм ADO_MOD")
        print("2. Алгоритм Литтла")
        self.matrix=copy.deepcopy(self.src_matrix)
        choice = input("Выберите алгоритм: ")
        if choice == '1':
            start = int(input("Введите начальную вершину: "))
            solution = ADO_MOD_algorithm(self.matrix).find_res(start)
            Visualiser().visualise_graph(self.src_matrix, solution)
        elif choice == '2':
            start = int(input("Введите начальную вершину: "))
            little_algo = LittleAlgorithm(self.matrix)
            i_index = [i for i in range(len(self.matrix))]
            j_index = [j for j in range(len(self.matrix))]
            little_algo.method_Little(self.matrix, {}, 0, i_index, j_index)
            print("Лучший путь:", little_algo.answer(start))
            print("Минимальная стоимость:", little_algo.min_cost)
            Visualiser().visualise_solution_tree(little_algo.tree_data)
            Visualiser().visualise_graph(self.src_matrix, little_algo.answer(start))
        else:
            print("Неверный выбор.")

    def print_matrix(self):
        for row in self.src_matrix:
            print(row)

    def run(self):
        end=False
        while not end:
            self.display_menu()
            choice = input("Выберите действие: ")
            if choice == '1':
                self.create_matrix()
            elif choice == '2':
                self.load_matrix()
            elif choice == '3':
                self.save_matrix()
            elif choice == '4':
                self.choose_algorithm()
            elif choice == '5':
                print("Выход из программы.")
                end=True
            else:
                print("Неверный выбор. Пожалуйста, выберите снова.")

if __name__ == '__main__':
    menu=Menu()
    menu.run()


