"""
    Author: Burak Bugrul
    Algorithm: Fibonacci with Binary Exponentiation
    Time Complexity: O(lgP)
"""


def multiply(A, B, mod):

    res = [[0]*len(B[0]) for _ in range(len(A))]

    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(A[0])):
                res[i][j] = (res[i][j] + A[i][k]*B[k][j]) % mod

    return res


def power(mat, p, mod):

    if p == 0:
        return [[1, 0], [0, 1]]

    if p == 1:
        return mat

    half = power(mat, p >> 1, mod)

    if p & 1:
        return multiply(multiply(half, half, mod), mat, mod)
    else:
        return multiply(half, half, mod)


n, mod = map(int, input().split())

if n <= 1:
    print(1)
else:
    start = [[1], [1]]

    print(multiply(power([[1, 1], [1, 0]], n-1, mod), start, mod)[0][0])