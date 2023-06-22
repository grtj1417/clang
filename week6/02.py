def pascal_triangle(n):
    triangle = [[1] * (i+1) for i in range(n)]
    for i in range(2, n):
        for j in range(1, i):
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j]
    return triangle

n = int(input("Enter the number of rows: "))
print(pascal_triangle(n))