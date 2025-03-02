import copy
import math
from MatrixCreator import MatrixCreator
from MatrixHandler import MatrixHandler
from Visualiser import Visualiser

class ADO_MOD_algorithm:
    def __init__(self, matrix: list[list[int]]) -> None:
        self.src_matrix=copy.deepcopy(matrix)
        self.matrix=matrix
        self.ost=[]

    def prim(self, start: int) -> None:
        # будущее остовное дерево
        self.ost = [[0 for i in range(len(self.matrix))] for i in range(len(self.matrix))]
        visited = [start] 		#вершины, уже включенные в дерево
        weight = []
        while(len(visited) != len(self.matrix)):
            for row in self.ost:
                print(row)
            print("Включенные вершины:", *[x+1 for x in visited])
            min_w = math.inf
            i, j = 0, 0
            # проходим по всем вершинам остовного дерева
            for elem in visited:
                if min_w > min(self.matrix[elem]):
                    print(self.matrix[elem])
                    # находим самое легкое ребро
                    min_w = min(self.matrix[elem])
                    i = elem
                    j = self.matrix[elem].index(min_w)
                    print("Найдена новая вершина для добавления:", j+1, " вес ребра = ", min_w)
            if j not in visited:
                print("Добавляем вершину в МОД")
                weight.append(min_w)
                visited.append(j)
                self.ost[i][j] = min_w
                self.ost[j][i] = min_w
            self.matrix[i][j] = math.inf
            print(f'Вычеркнем ребро {i+1} {j+1} из графа')

    #поиск в глубину
    def dfs(self, matr: list[list[int]], start: int, res: list[int]) -> None:
        for i, elem in enumerate(matr[start]):
            if i not in res:
                res.append(i)
                print("Текущий путь:", [x+1 for x in res])
                self.dfs(matr, i, res)
            if len(res) == len(matr):
                return

    def find_res(self, start: int) -> list[int]:
        start=start-1
        self.prim( start)
        way = [start]
        print("Запущен поиск в глубину")
        self.dfs(self.ost, start, way)
        i, j = 0, 1
        cost = 0
        while j < len(way):
            cost += self.src_matrix[way[i]][way[j]]
            i+=1
            j+=1
        cost += self.src_matrix[way[i]][way[0]]
        print("Полученный приближенный путь коммивояжера:", ' - '.join(str(x) for x in [i + 1 for i in way]))
        print("Его стоимость:", cost)
        return [x+1 for x in way ]

if __name__ == '__main__':
    matrix = [
        [math.inf, 27, 43, 16, 30, 26],
        [7, math.inf, 16, 1, 30, 25],
        [20, 13, math.inf, 35, 5, 0],
        [21, 16, 25, math.inf, 18, 18],
        [12, 46, 27, 48, math.inf, 5],
        [23, 5, 5, 9, 5, math.inf]
    ]
    matrix=[[math.inf, 7, 2],
[3, math.inf, 6],
[7, 4, math.inf],]
    b=copy.deepcopy(matrix)
    #matrix=MatrixCreator().generate_euclidean_matrix(size=10,dimensions=10)
    #MatrixCreator().save_matrix(matrix,"matrix.txt")
    #matrix=MatrixCreator().load_matrix("matrix.txt")
    start =2
    solution=ADO_MOD_algorithm(matrix).find_res(start)
    Visualiser().visualise_graph(b,solution)