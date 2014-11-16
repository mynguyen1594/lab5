//
//  Movie.h
//  lab4
//
//  Created by My Nguyen on 11/6/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//
#include <iostream>
#include <string>

using namespace std;

#ifndef lab4_Movie_h
#define lab4_Movie_h

class Movie {
private:
    int Year;
    string Title;
    Movie * Next;
    
public:
    Movie() {Year = -1; Title = ""; Next = NULL;}
    
    void setYear(int year) {Year = year;}
    void setTitle(string title) {Title = title;}
    void setInfo(int year, string title) {Year = year; Title = title;}
    void setNext(Movie * next) {Next = next;}
    
    int getYear() const {return Year;}
    string getTitle() const {return Title;}
    Movie * getNext() const {return Next;}
};
#endif
