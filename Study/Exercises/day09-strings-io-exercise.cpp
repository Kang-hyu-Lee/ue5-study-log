// Day 9 -- Exercises: C++ Strings & Basic I/O
// Attempt each part yourself before checking the Solutions file.
// Type your answers below each numbered comment (or in a separate .cpp you compile).
#include <iostream>
#include <string>

int main() {
// 1. Declare a std::string holding your first name. Print it, then print its
//    length on the next line using .length() or .size().
    std::string firstName = "Kang";
    std::cout << "First name is: " << firstName << '\n' << "Length of first name: " << firstName.length() << '\n';

// 2. Prompt the user with std::cout, then read a SINGLE word (no spaces) into
//    a std::string using std::cin >>. Print "Hello, " followed by what they typed.
    std::cout << "Please enter you first name: " << '\n';
    std::cin >> firstName;
    std::string greeting = "Hello, " + firstName;
    std::cout << greeting << '\n';

// 3. Prompt the user for their favorite quote (a full sentence, with spaces).
//    Read it correctly using std::getline -- think about whether you need
//    std::cin.ignore() first depending on what you did in #2.
    std::cin.ignore(); //because the last input I read was using std::cin meaning the '\n' is still in the buffer to be read
    std::string favQuote;
    std::cout << "What is your favorite quote?: " << '\n';
    std::getline(std::cin, favQuote);
    std::cout << "Favorite quote: " << favQuote << '\n';

// 4. Declare two separate strings, e.g. a first name and a last name.
//    Concatenate them into one string with a space in between and print it.
    std::string fName = "Kang";
    std::string lName = "Lee";
    std::string fullName = fName + " " + lName;
    std::cout << "First name is: " << fName << '\n' << "Last name is: " << lName << '\n' << "Full name is: " << fullName << '\n'; //don't forget to add newlines or spacing in between statements 

// 5. Using .substr(), extract and print just the first 3 characters of a
//    string of your choice.
    std::string word = "coding";
    std::cout << "First 3 characters of the word coding is: " << word.substr(0, 3) << '\n'; //.substr(start, length) so .substr(3) will take start=3 and show until the end of the string (so 3rd char onwards)

// 6. Using .find(), search for a substring inside a longer string. Print a
//    different message depending on whether it was found or not -- remember
//    the pitfall about what .find() returns when nothing matches
//    (see Study/Concepts/strings-io.md if you need a reminder).
    std::string longString;
    std::string searchWord;
    std::cout << "Please input a word to search through: " << '\n';
    std::cin >> longString;
    std::cout << "Please input the substring you want to search: " << '\n';
    std::cin >> searchWord;
    if (longString.find(searchWord) == std::string::npos){
        std::cout << "Substring not found" << '\n';
    }else {
        std::cout << "Substring found!" << '\n';
    }

// 7. Declare two strings that are different. Print the result of comparing
//    them with == and then with < . Briefly comment on why the < result is
//    what it is.
    std::string firstWord = "Apple";
    std::string secondWord = "Orange";
    std::cout << "First word: " << firstWord << '\n' << "Second word: " << secondWord << '\n';
    if(firstWord == secondWord){
        std::cout << "Exact same word (char-sensitive)" << '\n';
    }else if(firstWord < secondWord){
        std::cout << "First word comes first lexicographically (dictionnary order)" << '\n';
    }else {
        std::cout << "Second word comes first lexicographically (dictionnary order)" << '\n';
    }
return 0;
}