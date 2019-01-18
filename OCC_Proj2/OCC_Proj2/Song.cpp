//
//  Song.cpp
//  CSCI 235, Fall 2018, Project 2
//
//  Created by Anna Li on 9/13/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//

#include "Song.h"

//default constructor
Song::Song() {
    title_ = "";
    author_ = "";
    album_ = "";
}

//parametized constructor
Song::Song(const std::string& title, const std::string& author, const std::string& album) {
    title_ = title;
    author_ = author;
    album_ = album;
}

void Song::setTitle(std::string title) {
    title_ = title;
}

void Song::setAuthor(std::string author) {
    author_ = author;
}

void Song::setAlbum(std::string album) {
    album_ = album;
}

std::string Song::getTitle() const {
    return title_;
}

std::string Song::getAuthor() const {
    return author_;
}

std::string Song::getAlbum() const {
    return album_;
}

//ovverides "==" operator to return true if author, title, and album of two songs are equal
bool operator==(const Song& lhs, const Song& rhs)
{
    return ((lhs.author_==rhs.author_ && lhs.title_==rhs.title_ && lhs.album_==rhs.album_));
}




