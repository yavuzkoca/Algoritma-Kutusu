- init:
    run: rm -f assignment4
    blocker: true

- build:
    run: gcc -std=c99 -Wall -Werror assignment4.c -o assignment4  # timeout: 1
    blocker: true

- case0_given_with_hw:
   run: ./assignment4 alice.txt instructions.txt
   points: 2
   script:
        - expect: "[ \r\n]*fight for your right to party[ \r\n]*"  # timeout: 1
        - expect: _EOF_  # timeout: 1
   return: 0


- case1_capitals:
    run: ./assignment4 alice.txt capitals.txt
    points: 2
    script:
    - expect: "[ \r\n]*keep it simple and short[ \r\n]*"  # timeout: 1
    - expect: _EOF_  # timeout: 1
    return: 0

- case2_same_line:
    run: ./assignment4 alice.txt same_line.txt
    points: 2
    script:
    - expect: "[ \r\n]*say a long and sad tale please[ \r\n]*"  # timeout: 1
    - expect: _EOF_  # timeout: 1
    return: 0

- case3_warning:
    run: ./assignment4 alice.txt warning.txt
    points: 2
    script:
    - expect: "[ \r\n]*cross check your home work before you submitted it please[ \r\n]*"  # timeout: 1
    - expect: _EOF_  # timeout: 1
    return: 0
