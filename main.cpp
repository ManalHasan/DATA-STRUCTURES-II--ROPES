#include "Rope.hpp"
#include <iostream>

// int main()
// {
//     Rope rope;

//      // Insert a string in the middle
//     rope.insert("Hello World", 0);
//     std::cout << "Initial insert: ";
//     rope.print();

//     // Insert a string " beautiful" at index 5
//     rope.insert(" beautiful", 5);
//     std::cout << "After insert: ";
//     rope.print();

//     // Insert at the beginning
//     rope.insert("Start: ", 0);
//     std::cout << "After insert at start: ";
//     rope.print();

//     // Insert at the end
//     rope.insert("!hyng ", 15); // Make sure to adjust index appropriately
//     std::cout << "After insert at end: ";
//     rope.print();

//     rope.Delete(6,7);
//     std::cout << "After Deletion: ";
//     rope.print();

//     // Undo the last insert
//     rope.undo();
//     std::cout << "After undo: ";
//     rope.print();

//     // Undo the next last insert
//     rope.undo();
//     std::cout << "After another undo: ";
//     rope.print();
// //     std::cout<<std::endl;
// //    std::vector<int> s= rope.Searchbyword("ello");
// //    for(const int& i : s){
// //     std::cout<<i<<" ";
// //    }
//     // std::string s="C:/Users/A450L/Downloads/eshalversionds2/eshalversionds2/final/text.txt";
//     // rope.insertFileIntoRope(s);
//     // rope.print();

//     // // Insert at the beginning
//     // rope.insert("Start: ", 0);
//     // std::cout << "After insert at start: ";
//     // rope.print();

//     // // Insert in between
//     // rope.insert("!hyng ", 15); // Make sure to adjust index appropriately
//     // std::cout << "After insert in between : ";
//     // rope.print();
//     // rope.Delete(6,7);
//     // std::cout << "After Deletion: ";
//     // rope.print();

//     // rope.getWeight();
//     return 0;
// }
int main()
{
    Rope rope;

    int choice;
    do
    {
        std::cout << "\n-----------------------------------Rope Editor Menu------------------------------------------------\n";

        // std::cout << "\nRope Editor Menu:\n";
        std::cout << "1. Insert a string\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Search by Index\n";
        std::cout << "4. Search by word\n";
        std::cout << "5. Undo\n";
        std::cout << "6. Print current rope\n";
        std::cout << "7. Get weight of the rope\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::string s;
            int index;
            std::cout << "Enter the string to insert: ";
            std::cin.ignore(); // Ignore previous newline character
            std::getline(std::cin, s);
            std::cout << "Enter the index to insert at: ";
            std::cin >> index;
            rope.insert(s, index);
            break;
        }
        case 2:
        {
            int low, high;
            std::cout << "Enter the index to delete from: ";
            std::cin >> low;
            std::cout << "Till what index: ";
            std::cin >> high;
            rope.Delete(low, high);
            break;
        }
        case 3:
        {
            int ind, len;
            std::cout << "Enter index to start search from: ";
            std::cin >> ind;
            std::cout << "Enter Length of string: ";
            std::cin >> len;
            rope.Searchbyindex(ind, len);
            break;
        }
        case 4:
        {
            std::string s;
            std::cout << "Enter the string to search for: ";
            std::cin.ignore();
            std::getline(std::cin, s);
            std::vector<int> ss = rope.Searchbyword(s);
            if (ss.empty()){
                std::cout <<"==> String not found in the text";
                break;
            }
            else{
            for (const int &i : ss)
            {
                std::cout << i << " ";
            }
            break;
            }
            break;
        }

        case 5:
            rope.undo();
            break;
        case 6:
            std::cout << "\n";
            std::cout << "-->> Current rope: ";
            rope.print();
            break;

        case 8:
        {
            std::string filename;
            std::cout << "Enter the filename to open (.txt file): ";
            std::cin >> filename;
            rope.insertFileIntoRope(filename);
            break;
        }

        case 0:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}