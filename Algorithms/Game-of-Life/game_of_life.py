import pygame
import numpy as np
import sys

pygame.init()
pygame.display.set_caption('Game of Life')

box_w, box_h, box_e = 60, 40, 15

size = width, height = box_w * box_e + 1, box_h * box_e + 1
screen = pygame.display.set_mode(size)

life_table = np.zeros((box_w, box_h), dtype=bool)
neighbour_table = np.zeros((box_w, box_h), dtype=np.uint8)

top_left = 5, 5

"""
for i in range(11):
    row = [int(x) for x in input().split(' ')]
    w = len(row)
    life_table[top_left[0]:top_left[0] + w, top_left[1] + i] = np.array(row).T
"""

palette = {}
palette['GRAY'] = 200, 200, 200
palette['WHITE'] = 255, 255, 255
palette['BLACK'] = 0, 0, 0
palette['DARK_GRAY'] = 40, 40, 40


screen.fill(palette['GRAY'])
for row in range(box_e, height, box_e):
    pygame.draw.line(screen, palette['BLACK'], (0, row), (width, row))
for col in range(box_e, width, box_e):
    pygame.draw.line(screen, palette['BLACK'], (col, 0), (col, height))

while True:
    exit_flag = False
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RETURN:
                exit_flag = True
        elif event.type == pygame.MOUSEBUTTONUP:
            if int(event.button) == 1:
                x, y = pygame.mouse.get_pos()
                box_x = x // box_e
                box_y = y // box_e
                life_table[box_x, box_y] = True
                temp = pygame.Rect(
                    (box_x * box_e, box_y * box_e), (box_e, box_e))
                pygame.draw.rect(screen, palette['DARK_GRAY'], temp)
                del temp

    pygame.display.flip()

    if exit_flag:
        break

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()

    for box_x in range(box_w):
        for box_y in range(box_h):
            if(box_y < box_h - 1 and life_table[box_x, box_y + 1]):
                neighbour_table[box_x, box_y] += 1
            if(box_x < box_w - 1 and box_y < box_h - 1 and life_table[box_x + 1, box_y + 1]):
                neighbour_table[box_x, box_y] += 1
            if(box_x < box_w - 1 and life_table[box_x + 1, box_y]):
                neighbour_table[box_x, box_y] += 1
            if(box_y > 0 and box_x < box_w - 1 and life_table[box_x + 1, box_y - 1]):
                neighbour_table[box_x, box_y] += 1
            if(box_y > 0 and life_table[box_x, box_y - 1]):
                neighbour_table[box_x, box_y] += 1
            if(box_x > 0 and box_y > 0 and life_table[box_x - 1, box_y - 1]):
                neighbour_table[box_x, box_y] += 1
            if(box_x > 0 and life_table[box_x - 1, box_y]):
                neighbour_table[box_x, box_y] += 1
            if(box_x > 0 and box_y < box_h - 1 and life_table[box_x - 1, box_y + 1]):
                neighbour_table[box_x, box_y] += 1

    for box_x in range(box_w):
        for box_y in range(box_h):
            if(neighbour_table[box_x, box_y] < 2):
                life_table[box_x, box_y] = False
            elif(neighbour_table[box_x, box_y] == 3):
                life_table[box_x, box_y] = True
            elif(neighbour_table[box_x, box_y] > 3):
                life_table[box_x, box_y] = False
            neighbour_table[box_x, box_y] = 0

    screen.fill(palette['GRAY'])
    for row in range(box_e, height, box_e):
        pygame.draw.line(screen, palette['BLACK'], (0, row), (width, row))
    for col in range(box_e, width, box_e):
        pygame.draw.line(screen, palette['BLACK'], (col, 0), (col, height))
    for box_x in range(box_w):
        for box_y in range(box_h):
            if life_table[box_x][box_y]:
                temp = pygame.Rect(
                    (box_x * box_e, box_y * box_e), (box_e, box_e))
                pygame.draw.rect(screen, palette['DARK_GRAY'], temp)
                del temp

    pygame.display.flip()

    pygame.time.delay(50)

