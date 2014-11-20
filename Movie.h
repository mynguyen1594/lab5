//
//  Movie.h
//  lab5
//
//  Created by My Nguyen on 11/12/14.
//  Copyright (c) 2014 MyNguyen. All rights reserved.
//

#ifndef lab5_Movie_h
#define lab5_Movie_h

class Movie {
private:
    int Year;
    string Title;
    Movie * Next;
    
public:
    Movie() {Year = -1; Title = ""; Next = NULL;}
    
    void setInfo(int year, string title) {Year = year; Title = title;}
    void setNext(Movie * next) {Next = next;}
    
    int getYear() const {return Year;}
    string getTitle() const {return Title;}
    Movie * getNext() const {return Next;}
};
#endif
