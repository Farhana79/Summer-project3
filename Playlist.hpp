#ifndef PLAYLIST_HPP 
#define PLAYLIST_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>

/**
 * @brief A struct representing a node in a binary tree storing songs and artists.
 */
struct SongNode {
    /**
     * @brief Constructor for a SongNode object.
     * @param song The name of the song.
     * @param artist The name of the artist.
     */
    SongNode(const std::string& song, const std::string& artist) : 
        song_(song), artist_(artist), left_(nullptr), right_(nullptr) {}
    
    /**
     * @brief Checks if the node is a leaf node.
     * @return True if the node is a leaf, false otherwise.
     */
    bool isLeaf() const {
        return (left_ == nullptr) && (right_ == nullptr);
    }
    
    std::string song_; /** Name of the song */
    std::string artist_; /** Artist for the corresponding song */
    std::shared_ptr<SongNode> left_; /** Pointer to the left sub tree of the Playlist */
    std::shared_ptr<SongNode> right_; /** Pointer to the right sub tree of the Playlist */
};

/**
 * @brief Class representing a playlist of songs
 */
class Playlist {
    public:
        /**
         * @brief Default constructor for Playlist
         */
        Playlist();
        
        /**
         * @brief Copy constructor for Playlist
         * @param other The Playlist object to be copied
         */
        Playlist(const Playlist& other);
        
        /**
         * @brief Move constructor for Playlist
         * @param other The Playlist object to be moved
         */
        Playlist(Playlist&& other);
        
        /**
         * @brief Destructor for Playlist
         */
        ~Playlist();
        
        /**
         * @brief Copy assignment operator for Playlist
         * @param other The Playlist object to be assigned
         * @return Reference to the assigned Playlist object
         */
        Playlist& operator=(const Playlist& other);
        
        /**
         * @brief Move assignment operator for Playlist
         * @param other The Playlist object to be moved
         * @return Reference to the moved Playlist object
         */
        Playlist& operator=(Playlist&& other);
        
        /**
         * @brief Check if the Playlist is empty
         * @return True if Playlist is empty, otherwise false
         */
        bool isEmpty() const;
        
        /**
         * @brief Get the height of the Playlist
         * @return Height of the Playlist tree
         */
        size_t getHeight() const;
        
        /**
         * @brief Get the number of songs in the Playlist
         * @return Number of songs in the Playlist
         */
        size_t getNumberOfSongs() const;
        
        /**
         * @brief Add a song to the Playlist if the given song and artist is not empty string
         * @param song The name of the song to be added
         * @param artist The name of the artist of the song
         * @return True if the song was successfully added, otherwise false
         */
        bool add(const std::string& song, const std::string& artist);
        
        /**
         * @brief Remove a song from the Playlist if the song exists in the Playlist
         * @param song The name of the song to be removed
         * @param artist The name of the artist of the song
         * @return True if the song was successfully removed, otherwise false
         */
        bool remove(const std::string& song, const std::string& artist);
        
        /**
         * @brief Search for a song in the Playlist
         * @param name The name of the song to search for
         * @param artist The name of the artist of the song
         * @return True if the song was found, otherwise false
         */
        bool search(const std::string& name, const std::string& artist) const;
        
        /**
         * @brief Clear the Playlist of all songs
         */
        void clear();
        
        /**
         * @brief Perform a preorder traversal of the Playlist
         * @return Vector containing the nodes in preorder traversal order
         */
        std::vector<SongNode> preorderTraverse() const;
        
        /**
         * @brief Perform an inorder traversal of the Playlist
         * @return Vector containing the nodes in inorder traversal order
         */
        std::vector<SongNode> inorderTraverse() const;
        
        /**
         * @brief Perform a postorder traversal of the Playlist
         * @return Vector containing the nodes in postorder traversal order
         */
        std::vector<SongNode> postorderTraverse() const;
        
    private:
        std::shared_ptr<SongNode> root_ptr_; /** Pointer to the root node of the Playlist */
        
        /**
         * @brief Remove a value from a subtree of the Playlist
         * @param sub_tree The subtree to remove the value from
         * @param song The name of the song to be removed
         * @param artist The name of the artist of the song
         * @param success Flag to indicate successful removal
         * @return Pointer to the subtree after value removal
         * @post Flag success is updated to true or false depending on if removal was successful
         */
        std::shared_ptr<SongNode> removeValue(std::shared_ptr<SongNode> sub_tree, const std::string& song, const std::string& artist, bool& success);
        
        /**
         * @brief Remove a node from the Playlist
         * @param node_ptr The node to be removed
         * @return Pointer to the node after removal
         */
        std::shared_ptr<SongNode> removeNode(std::shared_ptr<SongNode> node_ptr);
        
        /**
         * @brief Remove the leftmost node from a subtree
         * @param node_ptr The root of the subtree
         * @param song The name of the song in the inorder successor
         * @param artist The name of the artist of the inorder successor
         * @return Pointer to the subtree after leftmost node removal
         * @post Parameters song and artist updated with the song and artist in the inorder successor of the left node
         */
        std::shared_ptr<SongNode> removeLeftmostNode(std::shared_ptr<SongNode> node_ptr, std::string& song, std::string& artist);
        
        /**
         * @brief Helper function for inorder traversal
         * @param node_ptr The current node being processed
         * @param result Vector to store traversal result in
         */
        void inorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const;

        /**
         * @brief Helper function for preorder traversal
         * @param node_ptr The current node being processed
         * @param result Vector to store traversal result in
         */
        void preorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const;
        
        /**
         * @brief Helper function for postorder traversal
         * @param node_ptr The current node being processed
         * @param result Vector to store traversal result in
         */
        void postorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const;
        
        /**
         * @brief Get the key for a song and artist
         * @param song The name of the song
         * @param artist The name of the artist of the song
         * @return Key formed from song and artist names by adding the strings
         */
        std::string getKey(const std::string& song, const std::string& artist) const;
        
        /**
         * @brief Get the key for a SongNode
         * @param song The SongNode to get key from
         * @return Key formed from the song and artist in the SongNode by adding the strings
         */
        std::string getKey(const SongNode& song) const;
};

#endif // PLAYLIST_HPP
