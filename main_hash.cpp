//
//  main.cpp
//  lab5
//
//  Created by My Nguyen on 11/10/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//

// Name: MY NGUYEN

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
    
    delete movie;
    
    return 0;
}

// **************************************************
//  readFile functions
//  This function reads the file academy_award_films.
//  txt and inserts each line into the movie pointer
//  Return: true if file can be opened
//          false if not
// **************************************************
bool readFile(HashTable<Movie> * movie) {
    ifstream inputFile;
    string line;
    Movie newMovie;
    bool empty = true;
    
    inputFile.open("/Users/mynguyen5194/Desktop/lab5/lab5/academy_award_films.txt");
    if (!inputFile) {
        cout << "Error opening file 'academy_award_files.txt'" << endl;
        return false;
    }
    while (getline(inputFile, line)) {
        int year = atoi(line.substr(0, 4).c_str());
        string title = line.substr(5, line.length()-5);
        newMovie.setInfo(year, title);
        movie->insert(newMovie);
        empty = false;
    }

    inputFile.close();
    
    if (empty) {
        return false;
    }
    
    return true;
}

// **********************************************
//  display function
//  This function displays the content of a movie
//  Return: none
// **********************************************
void display(Movie & movie) {
    if (movie.getYear() != -1 && movie.getTitle() != "")
        cout << movie.getYear() << " " << movie.getTitle() << endl;
    return;
}

// **************************************
//  menu function
//  This function gets the users' inputs and runs
//  the appropriate options with the correct syntax
//  It keeps getting the users' input until Q is entered
//  Return: none
// **************************************
void menu(HashTable<Movie> * movie) {
    string option;
    string line, title, aYear = "";
    int year = 0;
    Movie * moviePtr = new Movie();
    
    do {
        cout << "Please enter your option: ";
        getline(cin, option);
    
        if (isalpha(option[0]) && option.length() == 1 && !movie->isEmpty()) {
            
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
    } while (toupper(option[0]) != 'Q' && !movie->isEmpty());
    return;
}

// **************************************
//  showMenu function
//  This function displays the menu
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