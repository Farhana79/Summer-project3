#include "Playlist.hpp"
#include <iostream>

int main() {
    // Creating a Playlist object
    Playlist playlist;

    // Adding songs to the playlist
    playlist.add("Song A", "Artist A");
    playlist.add("Song B", "Artist B");
    playlist.add("Song C", "Artist C");
    playlist.add("Song D", "Artist D");
    playlist.add("Song E", "Artist E");

    // Displaying the number of songs in the playlist
    std::cout << "Number of songs in the playlist: " << playlist.getNumberOfSongs() << std::endl;

    // Displaying the height of the playlist
    std::cout << "Height of the playlist: " << playlist.getHeight() << std::endl;

    // Performing an inorder traversal and displaying the songs
    std::cout << "Inorder traversal:" << std::endl;
    auto inorder_result = playlist.inorderTraverse();
    for (const auto& song : inorder_result) {
        std::cout << song.song_ << " by " << song.artist_ << std::endl;
    }

    // Searching for a song in the playlist
    std::string search_song = "Song B";
    std::string search_artist = "Artist B";
    if (playlist.search(search_song, search_artist)) {
        std::cout << search_song << " by " << search_artist << " found in the playlist." << std::endl;
    } else {
        std::cout << search_song << " by " << search_artist << " not found in the playlist." << std::endl;
    }

    // Removing a song from the playlist
    std::string remove_song = "Song C";
    std::string remove_artist = "Artist C";
    if (playlist.remove(remove_song, remove_artist)) {
        std::cout << remove_song << " by " << remove_artist << " removed from the playlist." << std::endl;
    } else {
        std::cout << remove_song << " by " << remove_artist << " not found in the playlist. Removal failed." << std::endl;
    }

    // Displaying the number of songs in the playlist after removal
    std::cout << "Number of songs in the playlist after removal: " << playlist.getNumberOfSongs() << std::endl;

    return 0;
}

