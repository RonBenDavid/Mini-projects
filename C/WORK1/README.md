1.Write a program that picks up two non-negative integers and multiplies them by using only a connection operation. The plan should be as effective as possible.
Hint: For example, for the inputs, 4 and 15000 we want the program to perform 4 connection operations in order to connect the 15000 to itself, instead of 15000 connection operations that will connect the 4 to itself.
The program will display the result on the screen.


2. Write a plan that takes two natural numbers n1 and n2 (n2> n1) and calculates and prints all the prime numbers in the range of n1 to n2. The plan should be as effective as possible.
Note: Each x divisor of N has a complement y which will also have a divisor of N (N = xy). For example, 64 = 4 · 16 and then 4 and 16 are complementary. Therefore you can look for the divisors up to the square root of N, instead of up to N / 2. If no divisors have been found for N up to its root then it also has no divisors after the root of N.


Write an efficient function called Reverse that gets a non-negative integer n and returns the number where digits are in reverse order. If n is positive and there are zeros at the end then they will not appear in the reverse number. For example, for n = 175 the function will return 571, for n = 260 the function will return 62.
The function must operate without calculating the number of digits in n in advance and without using the function to calculate the power.
Write a program that takes a non-negative integer n, calls the Reverse function that gets n as a parameter and prints the returned inverse number.


4. Write a function called Fibonacci (non-recursive) that gets a non-negative integer, n. The function calculates and returns the corresponding Fibonacci number (the ninth member in the series).
Write a program that picks up a non-negative integer, calls the Fibonacci function which returns the nth number in the series and prints it.
In the Fibonacci series, each limb is the sum of two limbs preceding it. The first two organs in the series are 0 and 1, respectively. For example, the first seven organs in the series are:
F0 = 0 F1 = 1 F2 = 1 F3 = 2 F4 = 3 F5 = 5 F6 = 8
  
        
5. A natural number n is called an elaborate if it is equal to the sum of its smaller parts from it. For example, the number 6 = 1 + 2 + 3 and the number 28 = 1 + 2 + 4 + 7 + 14 are sophisticated.
Write a function which takes as a parameter some natural number and checks whether it is an elaborate number. If so, the function will return the number, otherwise it will return 0. The number divisors should be searched only within the range in which they can be.
Write a plan that prints as an output all the sophisticated numbers in the range 1 to 1000. The plan must use the above function.