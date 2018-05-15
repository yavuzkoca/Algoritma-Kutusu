/*
* Copyright (c) 2018 by Uğur Ali Kaplan
* You are free to do anything you want with this code
* provided you give attribute to original author.
*/

#include <stdio.h>
#include <stdlib.h>

/**
* Calculates the points to deduce from starting point
*
* @param segment is an integer type pointing the segment dart landed
* @param ring is a char type pointing to in which ring dart landed in the
* segment
* @return calculated point that will be deduced from the points user have
*/
int calculate_point(int segment, char ring) {
  int total;
  switch (ring) {
  case 'D':
    total = segment * 2;
    break;
  case 'T':
    total = segment * 3;
    break;
  case 'O':
    total = 25;
    break;
  case 'I':
    total = 50;
    break;
  default:
    total = segment;
    break;
  }
  return total;
}

/**
* Calculates the points to deduce from starting point
*
* @param curr_pt is an integer type that passes the points user currently have
* @param segment is an integer type pointing the segment dart landed
* @param ring is a char type pointing to in which ring dart landed in the
* segment
* @return sub is points left after program subtracts the calculated point(s)
*/
int deduce(int curr_pt, int segment, char ring) {
  int throw_pt = calculate_point(segment, ring);
  int sub;
  if (throw_pt < (curr_pt - 1)) {
    sub = curr_pt - throw_pt;
  } else if (throw_pt == curr_pt || throw_pt == (curr_pt - 1)) {
    if (ring == 'D') {
      sub = curr_pt - throw_pt;
    }
  } else {
    sub = curr_pt;
  }
  return sub;
}

int main(void) {
  int target;
  printf("Target: ");
  scanf("%d", &target);
  int current_pt = target;
  printf("\n");
  do {
    int segment;
    char ring;
    printf("Throw: ");
    scanf("%d %c", &segment, &ring);
    if (current_pt == target) {
      if (ring == 'D') {
        current_pt = deduce(current_pt, segment, ring);
      }
    } else {
      current_pt = deduce(current_pt, segment, ring);
    }
    printf("Points: %d\n", current_pt);
  } while (current_pt > 0);
  printf("\n");
  return EXIT_SUCCESS;
}
