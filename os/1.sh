echo "Assignment 1"
echo "Address Book"

echo "1.Create"
echo "2.Insert"
echo "3.Display"
echo "4.Update"
echo "5.Delete"
echo "6.Exit"

echo "Enter the choice:"
read choice

case $choice in

1)
    if [ ! -f Database.txt ]
    then
        touch Database.txt
        echo "File created successfully"
    else
        echo "File already exists"
    fi
;;

2)
    read -p "Enter Employee ID: " empid

    if grep -q "^$empid " Database.txt
    then
        echo "Employee ID already exists!"
    else
        read -p "Enter Name: " name
        read -p "Enter City: " city
        read -p "Enter Mobile: " mobile

        echo "$empid $name $city $mobile" >> Database.txt
        echo "Data inserted successfully"
    fi
;;

3)
    cat Database.txt
;;

4)
    read -p "Enter Employee ID to update: " empid

    if grep -q "^$empid " Database.txt
    then
        grep -v "^$empid " Database.txt > temp

        read -p "Enter New Name: " name
        read -p "Enter New City: " city
        read -p "Enter New Mobile: " mobile

        echo "$empid $name $city $mobile" >> temp
        mv temp Database.txt

        echo "Data updated successfully"
    else
        echo "Employee ID not found!"
    fi
;;

5)
    read -p "Enter Employee ID to delete: " empid

    if grep -q "^$empid " Database.txt
    then
        grep -v "^$empid " Database.txt > temp
        mv temp Database.txt

        echo "Data deleted successfully"
    else
        echo "Employee ID not found!"
    fi
;;

6)
    exit
;;

*)
    echo "Invalid choice"
;;

esac