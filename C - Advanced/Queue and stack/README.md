Write a function that receives a string and checks using a cartridge whether it is a polynodrome or not.
What is the runtime of the function?

2. Write an algorithm that takes a turn of different positive integers in some order. The algorithm returns the queue so that at first the even numbers will appear, followed by the odd numbers. (No matter the order). Except for a few variables, an auxiliary structure of the queue type can only be used!
For example for the queue:
3,10,2,11,5,4,21,17,14,6,1 ----> 10,2,4,14,6,3,11,5,21,17,1

3. We define Q1 and Q2 as symmetric queues if
(1) the number of organs in Q1 is equal to the number of organs in Q2;
(2) The value of a member Q1 located in place i in its front is equal to the value of a member Q2 located in place i at its nape.

Examples:

Symmetrical queues:
Q1: 3 7 4 8 9 0
Q2: 0 9 8 4 7 3 Asymmetrical queues:
Q1: 3 7 8 4 9 0
Q2: 0 9 8 4 7 3
Non-identical queues:
Q1: 3 7 4 8 9 0
Q2: 0 9 8 4 7 3 5

Write a Boolean function to compare two queues. The function receives queues Q1 and Q2 and checks whether they are symmetric.
Q1 and Q2 must be saved after exiting the function!
Except for a few variables, only one stack can be used as an auxiliary structure!
What is the complication of the function?

4. Write a function that receives an arithmetic expression (string) that includes 3 different types of parentheses:
                                                               ] [{}) (
The program will check if the pattern of the parentheses is valid (i.e. every developer has a suitable parenthesis).
Examples:
A (a + b) - [c + d] - {f + g}. OK
B. {[a + b] - [(c -)]} - OK
third. ((h) * {([j + k]})) - Not correct