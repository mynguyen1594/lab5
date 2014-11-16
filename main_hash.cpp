//
//  main.cpp
//  lab5
//
//  Created by My Nguyen on 11/10/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>

#include "HashTable.h"
#include "Movie.h"

using namespace std;

// Functions Prototype
bool readFile(HashTable<Movie> * movie);
void menu(HashTable<Movie> * movie);
void display(Movie & movie);
void showMenu();

int main() {
    HashTable<Movie> * movie = new HashTable<Movie>();
    
    readFile(movie);
   
    menu(movie);
    
    return 0;
}

// **************************************
//  readFile function
// **************************************
bool readFile(HashTable<Movie> * movie) {
    ifstream inputFile;
    string line, title;
    int year;
    Movie newMovie;
    
    inputFile.open("/Users/mynguyen5194/Desktop/running_test/running_test/academy_award_films.txt");
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            // Insert sth here to the hash table
            while (getline(inputFile, line, '\r')) {
                year = atoi(line.substr(0, 4).c_str());
                title = line.substr(5, line.length()-5);
                newMovie.setInfo(year, title);
                movie->insert(newMovie);
            }
        }
    }
    else {
        cout << "Error opening file 'academy_award_films.txt'" << endl;
        return false;
    }
    
    inputFile.close();
    
    return true;
}

// **************************************
//  display function
// **************************************
void display(Movie & movie) {
    if (movie.getYear() != -1 && movie.getTitle() != "")
        cout << movie.getYear() << " " << movie.getTitle() << endl;
    return;
}

// **************************************
//  menu function
// **************************************
void menu(HashTable<Movie> * movie) {
    string option;
    string line, title, aYear = "";
    int year = 0;
    Movie * moviePtr = new Movie();
    
    do {
        cout << "Please enter your option: ";
        getline(cin, option);
        
        if (isalpha(option[0]) && option.length() == 1) {
            
            switch (toupper(option[0])) {
                case 'S':
                    cout << "\n\t\t ~*~ Search Movie ~*~\n";
                    cout << "Please enter the movie title: ";
                    getline(cin, title);
                    
                    moviePtr->setInfo(year, title);

                    if (movie->search(*moviePtr, *moviePtr)) {
                        cout << "Year: " << moviePtr->getYear() << endl;
                    }
                    else
                        cout << "The title is not in the hash table\n";
                    break;
                    
                case 'D':
                    cout << "\n\t\t ~*~ Display List ~*~ \n";
                    movie->displayList(display);
                    break;
                    
                case 'P':
                    cout << "\n\t\t ~*~ Print the Hashed Table ~*~\n";
                    movie->printHashTable(display);
                    break;
                    
                case 'T':
                    cout << "\n\t\t ~*~ Show Statictics ~*~ \n";
                    movie->statistics();
                    break;
                    
                case 'M':
                    cout << "\n\t\t ~*~ Help ~*~ \n";
                    showMenu();
                    break;
                    
                default:
                    break;
            }
        }
        
    } while (toupper(option[0]) != 'Q');
    return;
}

// **************************************
//  menu function
// **************************************
void showMenu() {
    cout << "S - Search by a unique key\n"
        << "D - Display the content of the hash table\n"
        << "P - Print the hashed table\n"
        << "T - Show statistics\n"
        << "M - Show menu\n"
        << "Q - Quit\n";
    return;
}