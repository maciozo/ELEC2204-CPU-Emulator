STOR 0x01, 3 ;For dividing by 3
STOR 0x02, 5 ;For dividing by 5
STOR 0x03, 0 ;For checking if modulus is 0
STOR 0x04, 1 ;For incrementing by 1

STOR 0x05, 0xf122 ;Fizz
STOR 0x06, 0xba22 ;Buzz
STOR 0x07, 0xf122ba22 ;FizzBuzz

STOR 0x08, 0 ;Our number
ADDA 0x08, 0x04, 0x08 ;Increment by 1
STOR 0x01, 100 ;Max value
JGTP 0x08, 0x01, 48 ;If x > 100, jump to STOP
STOR 0x01, 3 ;For dividing by 3

MODA 0x08, 0x01, 0x09 ;Store x % 3 in 0x9
MODA 0x08, 0x02, 0x0A ;Store x % 5 in 0xA

JEQP 0x09, 0x03, 11 ;Jump if x % 3 == 0
JEQP 0x0A, 0x03, 17 ;Jump if x % 5 == 0

;Not divisible by 3 or 5
PRND 0x08
JEQN 0x01, 0x01, 35 ;Jump to line 12

;Divisible by 3
JEQP 0x0A, 0x03, 13 ;Jump if x % 5 == 0
PRNT 0x05 ;Print Fizz
JEQN 0x01, 0x01, 45 ;Jump to line 12

;Divisible by 5
PRNT 0x06 ;Print Buzz
JEQN 0x01, 0x01, 51 ;Jump to line 12

;Divisible by 3 and 5
PRNT 0x07 ;Print FizzBuzz
JEQN 0x01, 0x01, 57 ;Jump to line 12

STOP