
#!/bin/bash

file="addressbook.txt"

while true
do
    echo "-----------------------------"
    echo "       ADDRESS BOOK"
    echo "-----------------------------"
    echo "1. Create Address Book"
    echo "2. View Address Book"
    echo "3. Insert Record"
    echo "4. Delete Record"
    echo "5. Modify Record"
    echo "6. Exit"
    echo "-----------------------------"

    read -p "Enter your choice: " ch

    case $ch in

    1)
        touch "$file"
        echo "Address book created successfully."
        ;;

    2)
        echo "----- Address Book -----"

        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        elif [ -s "$file" ]; then
            cat "$file"
        else
            echo "Address book is empty."
        fi
        ;;

    3)
        if [ ! -f "$file" ]; then
            echo "Create address book first!"
        else
            read -p "Enter Name: " name
            read -p "Enter Phone: " phone
            read -p "Enter Email: " email

            echo "$name | $phone | $email" >> "$file"

            echo "Record inserted successfully."
        fi
        ;;

    4)
        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        else
            read -p "Enter Name to delete: " name

            if grep -Fq "$name |" "$file"; then
                grep -Fv "$name |" "$file" > temp.txt
                mv temp.txt "$file"
                echo "Record deleted successfully."
            else
                echo "Record not found."
            fi
        fi
        ;;

    5)
        if [ ! -f "$file" ]; then
            echo "Address book does not exist."
        else
            read -p "Enter Name to modify: " oldname

            if grep -Fq "$oldname |" "$file"; then
                read -p "Enter New Name: " newname
                read -p "Enter New Phone: " newphone
                read -p "Enter New Email: " newemail

                grep -Fv "$oldname |" "$file" > temp.txt
                echo "$newname | $newphone | $newemail" >> temp.txt
                mv temp.txt "$file"

                echo "Record modified successfully."
            else
                echo "Record not found."
            fi
        fi
        ;;

    6)
        echo "Exiting..."
        exit 0
        ;;

    *)
        echo "Invalid choice!"
        ;;

    esac

    echo
done




























# ================================================================
# ASSIGNMENT 1: ADDRESS BOOK MANAGEMENT SYSTEM USING SHELL SCRIPT
# ================================================================
#
# AIM:
# To write a menu-driven shell script that performs basic
# address book operations such as creating, viewing, inserting,
# deleting and modifying records using Bash shell commands.
#
# ---------------------------------------------------------------
# 1. INTRODUCTION
# ---------------------------------------------------------------
#
# This program is an Address Book Management System developed
# using Bash Shell Scripting.
#
# It allows users to store and manage contact information.
# Each contact contains three fields:
#   1. Name
#   2. Phone Number
#   3. Email Address
#
# All contact records are stored permanently in a text file
# named "addressbook.txt".
#
# The program provides a menu with six options:
#   1. Create Address Book
#   2. View Address Book
#   3. Insert Record
#   4. Delete Record
#   5. Modify Record
#   6. Exit
#
# The program continuously displays the menu until the user
# selects the Exit option.
#
# ---------------------------------------------------------------
# 2. SHELL SCRIPTING BASICS
# ---------------------------------------------------------------
#
# #!/bin/bash
#
# This is called the Shebang line.
# It specifies that the script should be executed using the
# Bash shell interpreter.
#
# A shell is a command-line interface that allows users to
# interact with the operating system.
#
# Bash stands for Bourne Again Shell.
# It is commonly used for automation, file management and
# executing system commands.
#
# ---------------------------------------------------------------
# 3. FILE VARIABLE
# ---------------------------------------------------------------
#
# file="addressbook.txt"
#
# Here, a variable named 'file' is declared and initialized
# with the filename addressbook.txt.
#
# Variables are used to store values that can be reused
# throughout the program.
#
# Instead of writing "addressbook.txt" repeatedly, we use
# "$file" wherever the filename is required.
#
# The $ symbol is used to access the value stored in a variable.
#
# ---------------------------------------------------------------
# 4. INFINITE WHILE LOOP
# ---------------------------------------------------------------
#
# while true
# do
#     ...
# done
#
# The while loop is used to execute a block of statements
# repeatedly as long as its condition is true.
#
# Here, 'true' always returns a successful status, so the loop
# continues indefinitely.
#
# This is necessary because the menu should appear again after
# completing an operation.
#
# The loop terminates only when the user selects option 6,
# which executes the exit command.
#
# ---------------------------------------------------------------
# 5. DISPLAYING THE MENU
# ---------------------------------------------------------------
#
# The echo command is used to display messages and menu options
# on the terminal.
#
# Example:
# echo "1. Create Address Book"
#
# The program displays six available operations so that the
# user can select the required operation.
#
# ---------------------------------------------------------------
# 6. TAKING USER INPUT
# ---------------------------------------------------------------
#
# read -p "Enter your choice: " ch
#
# The read command accepts input from the keyboard.
#
# -p is an option that displays a prompt before accepting input.
#
# The entered value is stored in the variable 'ch'.
#
# Example:
# If the user enters 3, the variable ch stores the value 3.
#
# ---------------------------------------------------------------
# 7. CASE STATEMENT
# ---------------------------------------------------------------
#
# case $ch in
#     1) ... ;;
#     2) ... ;;
#     3) ... ;;
# esac
#
# The case statement is used for decision-making.
#
# It compares the value of the variable 'ch' with different
# patterns and executes the corresponding block.
#
# It is similar to the switch-case statement in C or C++.
#
# The double semicolon (;;) indicates the end of a case block.
#
# esac marks the end of the case statement.
#
# ---------------------------------------------------------------
# 8. OPTION 1: CREATE ADDRESS BOOK
# ---------------------------------------------------------------
#
# touch "$file"
#
# The touch command creates an empty file if the specified
# file does not already exist.
#
# If addressbook.txt already exists, touch does not erase
# its existing contents.
#
# After creating the file, the program displays a success
# message.
#
# PURPOSE:
# To initialize the address book before inserting records.
#
# ---------------------------------------------------------------
# 9. OPTION 2: VIEW ADDRESS BOOK
# ---------------------------------------------------------------
#
# if [ ! -f "$file" ]; then
#     ...
# elif [ -s "$file" ]; then
#     cat "$file"
# else
#     ...
# fi
#
# This option displays all the contact records stored in
# addressbook.txt.
#
# IMPORTANT COMMANDS AND OPERATORS:
#
# [ ]:
# Used to evaluate conditions in shell scripting.
#
# -f:
# Checks whether the specified path exists and is a regular file.
#
# !:
# Logical NOT operator. It reverses the result of a condition.
#
# -s:
# Checks whether a file exists and has a size greater than zero.
#
# cat:
# Displays the contents of a file on the terminal.
#
# The program performs three checks:
#
# 1. If the file does not exist, it displays:
#    "Address book does not exist."
#
# 2. If the file exists and contains data, it displays all
#    records using the cat command.
#
# 3. If the file exists but is empty, it displays:
#    "Address book is empty."
#
# PURPOSE:
# To display all stored contact information.
#
# ---------------------------------------------------------------
# 10. OPTION 3: INSERT RECORD
# ---------------------------------------------------------------
#
# First, the program checks whether the address book file exists.
#
# If the file does not exist, the user is asked to create
# the address book first.
#
# Otherwise, the read command is used to accept:
#   1. Name
#   2. Phone Number
#   3. Email Address
#
# Example:
# read -p "Enter Name: " name
# read -p "Enter Phone: " phone
# read -p "Enter Email: " email
#
# After accepting the information, the following command
# stores the record:
#
# echo "$name | $phone | $email" >> "$file"
#
# IMPORTANT:
#
# echo:
# Displays or outputs the specified text.
#
# >>:
# This is the append redirection operator.
# It adds new data at the end of a file without deleting
# the existing contents.
#
# >:
# This is the overwrite redirection operator.
# It replaces the existing contents of a file.
#
# Example record:
# Prince | 9876543210 | prince@gmail.com
#
# Each record is stored on a separate line.
# The vertical bar (|) is used as a separator between fields.
#
# PURPOSE:
# To add a new contact record to the address book.
#
# ---------------------------------------------------------------
# 11. OPTION 4: DELETE RECORD
# ---------------------------------------------------------------
#
# First, the program checks whether the address book exists.
#
# If it exists, the user is asked to enter the name of the
# contact that needs to be deleted.
#
# The following command checks whether the record exists:
#
# grep -Fq "$name |" "$file"
#
# UNDERSTANDING GREP:
#
# grep is a Linux command used to search for text or patterns
# inside files.
#
# -F:
# Searches for a fixed string instead of interpreting the
# search text as a regular expression.
#
# -q:
# Quiet mode. It does not display matching lines.
# It only returns a status indicating whether a match exists.
#
# If the record is found, the following command executes:
#
# grep -Fv "$name |" "$file" > temp.txt
#
# -v:
# Inverts the search result and displays lines that do not
# contain the specified string.
#
# temp.txt:
# A temporary file used to store all records except the
# matching record.
#
# >:
# Redirects the output into temp.txt, overwriting its contents.
#
# Next:
#
# mv temp.txt "$file"
#
# mv is the move command.
# Here, it replaces the original addressbook.txt with the
# temporary file containing the remaining records.
#
# Thus, the matching record is removed from the address book.
#
# If no matching record is found, an appropriate message
# is displayed.
#
# IMPORTANT:
# If multiple records have the same name, this implementation
# removes all matching records, not just the first one.
#
# PURPOSE:
# To remove a contact from the address book.
#
# ---------------------------------------------------------------
# 12. OPTION 5: MODIFY RECORD
# ---------------------------------------------------------------
#
# First, the program checks whether the address book exists.
#
# The user is asked to enter the name of the contact that
# needs to be modified.
#
# The grep command checks whether the old name exists:
#
# grep -Fq "$oldname |" "$file"
#
# If the record is found, the program asks for:
#   1. New Name
#   2. New Phone Number
#   3. New Email Address
#
# These values are stored in:
#   newname
#   newphone
#   newemail
#
# The following command removes the old matching record:
#
# grep -Fv "$oldname |" "$file" > temp.txt
#
# All records except those matching the old name are
# copied into temp.txt.
#
# Next, the updated record is added:
#
# echo "$newname | $newphone | $newemail" >> temp.txt
#
# The append operator (>>) adds the new record at the end
# of the temporary file.
#
# Finally:
#
# mv temp.txt "$file"
#
# The temporary file replaces the original address book.
#
# This completes the modification operation.
#
# IMPORTANT:
# This implementation removes all records matching the old
# name and inserts one new record. Therefore, if multiple
# contacts have the same name, they will all be removed.
#
# PURPOSE:
# To update the information of an existing contact.
#
# ---------------------------------------------------------------
# 13. OPTION 6: EXIT
# ---------------------------------------------------------------
#
# echo "Exiting..."
# exit 0
#
# The echo command displays an exit message.
#
# The exit command terminates the shell script.
#
# 0 indicates successful program termination.
#
# Since the script terminates, the infinite while loop also
# stops executing.
#
# ---------------------------------------------------------------
# 14. DEFAULT CASE
# ---------------------------------------------------------------
#
# *)
#     echo "Invalid choice!"
#     ;;
#
# The asterisk (*) acts as a wildcard pattern in the case
# statement.
#
# It executes when the user's input does not match any of
# the available menu options.
#
# It prevents the program from silently ignoring invalid input.
#
# ---------------------------------------------------------------
# 15. IMPORTANT LINUX COMMANDS USED
# ---------------------------------------------------------------
#
# 1. touch:
#    Creates an empty file if it does not exist.
#
# 2. echo:
#    Displays text or outputs data.
#
# 3. read:
#    Accepts input from the user.
#
# 4. cat:
#    Displays the contents of a file.
#
# 5. grep:
#    Searches for text inside a file.
#
# 6. mv:
#    Moves or renames a file. In this program, it replaces
#    the original file with the temporary file.
#
# 7. exit:
#    Terminates the shell script.
#
# ---------------------------------------------------------------
# 16. IMPORTANT SHELL OPERATORS
# ---------------------------------------------------------------
#
# $:
# Accesses the value of a variable.
#
# !:
# Logical NOT operator.
#
# >>:
# Appends output to an existing file.
#
# >:
# Redirects output and overwrites the destination file.
#
# |:
# Pipe operator in Linux commands. However, the vertical bar
# inside the address book records is simply a text separator,
# not a pipe operation.
#
# &&:
# Logical AND operator (not used in this program).
#
# ---------------------------------------------------------------
# 17. OVERALL WORKING OF THE PROGRAM
# ---------------------------------------------------------------
#
# 1. The program starts by initializing the filename variable.
#
# 2. An infinite while loop displays the main menu.
#
# 3. The user enters a choice.
#
# 4. The case statement identifies the selected operation.
#
# 5. The corresponding operation is executed.
#
# 6. After completing the operation, the menu is displayed again.
#
# 7. This process continues until the user selects option 6.
#
# 8. The exit command terminates the program.
#
# ---------------------------------------------------------------
# 18. ADVANTAGES
# ---------------------------------------------------------------
#
# 1. Simple and easy-to-use menu-driven interface.
# 2. Stores contact information in a permanent text file.
# 3. Supports basic CRUD operations.
# 4. Uses standard Linux commands.
# 5. Does not require a database management system.
# 6. Demonstrates file handling, loops and decision-making
#    in Bash scripting.
#
# CRUD stands for:
# C - Create
# R - Read
# U - Update
# D - Delete
#
# ---------------------------------------------------------------
# 19. LIMITATIONS
# ---------------------------------------------------------------
#
# 1. No validation is performed on phone numbers or email IDs.
# 2. Duplicate contact names are allowed.
# 3. Deletion and modification operate on all matching names.
# 4. Data is stored in a plain text file rather than a database.
# 5. No password protection or authentication is implemented.
# 6. The program does not provide separate fields for searching
#    by phone number or email address.
#
# ================================================================
# END OF EXPLANATION
# ================================================================
