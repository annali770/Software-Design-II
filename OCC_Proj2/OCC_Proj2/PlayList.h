//
//  Playlist.hpp
//  CSCI 235, Fall 2018, Project 2
//
//  Created by Anna Li on 9/13/18.
//  Copyright © 2018 Anna Li. All rights reserved.
//

#pragma once

#include "Set.h"
#include "Song.h"

class PlayList
{
public:
    PlayList();

    PlayList(const Song& a_song);
    int getNumberOfSongs() const;

    bool isEmpty() const;

    bool addSong(const Song& new_song);

    bool removeSong(const Song& a_song);

    void clearPlayList();

    void displayPlayList() const;
private:
    Set<Song> playlist_;
};

