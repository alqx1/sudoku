def print_sudoku(sudoku: list[list[int]]) -> None:
    for line in sudoku:
        print(line)

def in_row(sudoku: list[list[int]], row: int, num: int) -> bool:
    for i in range(9):
        if sudoku[row][i] == num:
            return True
    return False


def in_col(sudoku: list[list[int]], col: int, num: int) -> bool:
    for i in range(9):
        if sudoku[i][col] == num:
            return True
    return False


def in_box(sudoku: list[list[int]], x: int, y: int, num: int) -> bool:
    box_x = x - (x % 3) 
    box_y = y - (y % 3)
    for i in range(3):
        for j in range(3):
            if sudoku[box_x + i][box_y + j] == num:
                return True
    return False 

def find_empty_cell(sudoku: list[list[int]], l: list[int]) -> bool:
    for y in range(9):
        for x in range(9):
            if sudoku[x][y] == 0:
                l[0] = x
                l[1] = y
                return True
    return False

def is_safe(sudoku: list[list[int]], x: int, y: int, num: int):
    return (not in_row(sudoku, x, num) and
            not in_col(sudoku, y, num) and
            not in_box(sudoku, x, y, num))

def read_sudoku(file_path: str) -> list[list[int]]:
    with open(file_path, "r") as fin:
        sudoku = []
        lines = fin.readlines()
        for line in lines:
            list = [ord(ch) - ord('0')
                    for ch in line
                    if ord(ch) != ord('\n')]
            sudoku.append(list)
    return sudoku

def solve(sudoku: list[list[int]]) -> bool:
    l = [0, 0]

    if (not find_empty_cell(sudoku, l)):
        return True

    for num in range(1, 10):
        if is_safe(sudoku, l[0], l[1], num):
            sudoku[l[0]][l[1]] = num

            if solve(sudoku):
                return True

            sudoku[l[0]][l[1]] = 0

    return False

def main() -> None:
    sudoku = read_sudoku("./sudoku")
    if solve(sudoku):
        print_sudoku(sudoku)

if __name__ == '__main__':
    main()
