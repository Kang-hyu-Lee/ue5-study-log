// Day 9 -- Solutions: C++ Strings & Basic I/O

#include <iostream>
#include <string>

int main() {
// 1.
    std::string firstName = "Kang";
    std::cout << firstName << '\n';
    std::cout << firstName.length() << '\n';
    // .length() and .size() are interchangeable -- both return the character count.

// 2.
    std::cout << "Enter your first name: ";
    std::cin >> firstName;                     // cin >> stops at the first whitespace
    std::cout << "Hello, " << firstName << '\n';

// 3.
    std::cin.ignore();                          // discards leftover '\n' left in the buffer by cin >> above
                                                 // without this, getline() below would read an empty line
    std::string favQuote;
    std::cout << "What is your favorite quote?: " << '\n';
    std::getline(std::cin, favQuote);           // reads the full line, spaces included
    std::cout << "Favorite quote: " << favQuote << '\n';

// 4.
    std::string fName = "Kang";
    std::string lName = "Lee";
    std::string fullName = fName + " " + lName; // '+' concatenates; explicit " " needed for the space
    std::cout << fullName << '\n';

// 5.
    std::string word = "coding";
    std::cout << word.substr(0, 3) << '\n';
    // .substr(start, length) -- start=0, length=3 -> characters at index 0,1,2 -> "cod"
    // .substr(3) alone would mean start=3 with NO length limit -> everything from index 3 to
    // the end -> "ing". Same call, one missing argument, completely different result --
    // this is exactly the pitfall the concept file flagged.

// 6.
    std::string longString = "hello world";
    std::string searchWord = "world";
    if (longString.find(searchWord) == std::string::npos) {
        std::cout << "Not found\n";
    } else {
        std::cout << "Found\n";
    }
    // .find() returns the starting index if found, or std::string::npos if not.
    // npos is unsigned -- comparing to -1 instead of std::string::npos is the classic bug here.

// 7.
    std::string firstWord = "Apple";
    std::string secondWord = "Orange";
    std::cout << "First word: " << firstWord << '\n' << "Second word: " << secondWord << '\n';
    std::cout << (firstWord == secondWord) << '\n';  // 0 (false) -- different strings, exact match required
    std::cout << (firstWord < secondWord) << '\n';   // 1 (true)  -- lexicographic: 'A' < 'O' in ASCII order,
                                                       // so "Apple" is considered "less than" "Orange",
                                                       // the same way it'd come first in a dictionary.

    return 0;
}
