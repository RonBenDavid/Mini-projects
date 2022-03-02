Have an information management system tailored to any business of your choice.
Here are the requirements:
A. The business needs to manage items with insertion, viewing, updating and deletion operations.
B. The business should maintain a list of employees who have access to the management system.
third. The system will write to another file which will be a log of all sessions performed through it.
All information will be saved in 3 files: an item file, an employee file, and a log file.
How to do it:
When you run the program, it checks to see if the above files exist.
If not, it produces them.
In her hand and the employee file does not exist, she creates a new user with the following details:
● Username: admin
● Password: admin
● Permission level: 3
● Full name: Manager_System
To log in, the user must always enter a user and password.
If an incorrect username and password are entered for 3 times the program will display an appropriate message
And will end.
A user can be represented as follows:
typedef struct user
{
char username [15];
char password [15];
int level;
char fullname [20];
} user;
Advanced Programming Lab - 50237 - Winter Semester, 2006
There are 3 permission levels,
1 - View permission (search) and add items only.
2 - Permission to view (search), add, update and delete items.
3 - Administrator permission, can perform all actions on items and users
The program should work in such a way that the menus that are not relevant to the permission level do not
Will appear.
The items themselves can be anything you choose,
Examples:
If it was decided to manage vehicles in the garage, then the information on each vehicle can include the following data:
Vehicle number, manufacturing company, paint, date of entry into the garage, type of treatment, amount to be paid, is it in the garage?
If, for example, it was decided to run a bookstore, then the book information will contain the following data:
Catalog number, name of the book, name of the author, date of publication, quantity in stock, price, etc.
Item must include at least:
● Any serial number
● Two text fields
● Incomplete numerical value (example: book price, treatment price)
● Boolean value (example: Is it in the garage? Is it a bestseller?)
● Date (example: date of entry into the garage, date of publication)
You can search for items as follows:
● Search for an item by two text fields together and separately
● Search for an item by its numerical value (greater than / less than)
● Search by Boolean value (equal / unequal)
● Search by date (greater than / less than)
All items that match the search should be displayed on the screen,
Then allow the user to edit them, typing in the serial number of the same item.
Advanced Programming Lab - 50237 - Winter Semester, 2006
Additional requirements and clarifications:
1. The items in the item file must be represented sorted by the serial number
2. Use a data structure of a linked list, or a binary search tree (5 bonus points)
3. The list of users does not have to be sorted, or contained within a data structure
any. And there is no need to perform a search operation on it (but it is required to display it)
4. Although according to information security laws passwords should be encrypted, this obligation does not apply
You must in this exercise.
5. The log file is a simple text file that can be read using a typewriter
6. The employee file and the details file can be regular files or binaries (3 points)
Bonus)
7. The program must be submitted with a complete item file, containing at least 20 different items
Guidelines and Comments:
Each section must have a separate function.
● Auxiliary functions should be written if necessary.
● Significant variables and functions must be given names.
● Submission only in pairs (exceptional cases only with prior approval by email), with one of the couple submitting
The ZIP file and the other TXT file with the ID of the two team members.
● The following files will be submitted in a ZIP file (please make sure the file is opened):
הקוד Code files (c. And h (.
■ In all the code files in the first lines, the names and ID numbers of the authors of the exercise will appear.
○ exe file created after compiling the code