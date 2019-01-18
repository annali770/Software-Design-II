//
//  Playlist.cpp
//  CSCI 235, Fall 2018, Project 2
//
//  Created by Anna Li on 9/13/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//
#include <iostream>

#include "PlayList.h"
#include "Song.h"
#include "Set.cpp"

using namespace std;

//default constructor
PlayList::PlayList() {
}

//parametized constructor for PlayList, adds first song to playlist
PlayList::PlayList(const Song& a_song) {
    playlist_.Set<Song>::add(a_song);
}

//returns: current number of songs
int PlayList::getNumberOfSongs() const {
    return playlist_.Set<Song>::getCurrentSize();
}

//returns: true if playlist is empty
bool PlayList::isEmpty() const {
    return playlist_.Set<Song>::isEmpty();
}

//adds song to end of playlist only if it is not a repeat
bool PlayList::addSong(const Song& new_song) {
    std::vector<Song> temp = playlist_.Set<Song>::toVector();
    if (playlist_.getCurrentSize() > 1) {
        for (unsigned i = 0; i<temp.size();i++) {
            if (temp[i] == new_song) {
                return false;
            }
        }
    }
    return playlist_.Set<Song>::add(new_song);
}

bool PlayList::removeSong(const Song& a_song) {
    return playlist_.Set<Song>::remove(a_song);
}

void PlayList::clearPlayList() {
    playlist_.Set<Song>::clear();
}

//outputs title, author, and album of current songs in playlist
void PlayList::displayPlayList() const {
    std::vector<Song> temp = playlist_.Set<Song>::toVector();
    
    for (unsigned i = 0; i<temp.size(); i++)
    {
        std::cout << "* Title: " << temp[i].getTitle() << "* Author: " << temp[i].getAuthor() << "* Album: " << temp[i].getAlbum() << " *" << std::endl;
    }
    
    std::cout << "End of playlist" << std::endl;
}

