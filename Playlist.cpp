/**
 * @file Playlist.cpp
 * @Farhana Sultana (farhana.sultana79@myhunter.cuny.edu)
 * @brief This file for the Playlist class
 *
 */
#include "Playlist.hpp"
#include <functional>

// Constructor
Playlist::Playlist() : root_ptr_(nullptr) {}

// Copy constructor
Playlist::Playlist(const Playlist& other) : root_ptr_(nullptr) {
    // Implement deep copy
    if (other.root_ptr_) {
        root_ptr_ = std::make_shared<SongNode>(*other.root_ptr_);
        if (other.root_ptr_->left_) root_ptr_->left_ = std::make_shared<SongNode>(*other.root_ptr_->left_);
        if (other.root_ptr_->right_) root_ptr_->right_ = std::make_shared<SongNode>(*other.root_ptr_->right_);
    }
}

// Move constructor
Playlist::Playlist(Playlist&& other) : root_ptr_(std::move(other.root_ptr_)) {
    other.root_ptr_ = nullptr;
}

// Destructor
Playlist::~Playlist() {
    clear();
}

// Copy assignment operator
Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        clear();
        // Implement deep copy
        if (other.root_ptr_) {
            root_ptr_ = std::make_shared<SongNode>(*other.root_ptr_);
            if (other.root_ptr_->left_) root_ptr_->left_ = std::make_shared<SongNode>(*other.root_ptr_->left_);
            if (other.root_ptr_->right_) root_ptr_->right_ = std::make_shared<SongNode>(*other.root_ptr_->right_);
        }
    }
    return *this;
}

// Move assignment operator
Playlist& Playlist::operator=(Playlist&& other) {
    if (this != &other) {
        root_ptr_ = std::move(other.root_ptr_);
        other.root_ptr_ = nullptr;
    }
    return *this;
}

// Check if the Playlist is empty
bool Playlist::isEmpty() const {
    return root_ptr_ == nullptr;
}

// Get the height of the Playlist
size_t Playlist::getHeight() const {
    std::function<size_t(std::shared_ptr<SongNode>)> getHeightHelper = [&](std::shared_ptr<SongNode> node) {
        if (!node) return size_t(0);
        return 1 + std::max(getHeightHelper(node->left_), getHeightHelper(node->right_));
    };
    return getHeightHelper(root_ptr_);
}

// Get the number of songs in the Playlist
size_t Playlist::getNumberOfSongs() const {
    std::function<size_t(std::shared_ptr<SongNode>)> getNumberOfSongsHelper = [&](std::shared_ptr<SongNode> node) {
        if (!node) return size_t(0);
        return 1 + getNumberOfSongsHelper(node->left_) + getNumberOfSongsHelper(node->right_);
    };
    return getNumberOfSongsHelper(root_ptr_);
}

// Add a song to the Playlist
bool Playlist::add(const std::string& song, const std::string& artist) {
    if (song.empty() || artist.empty()) return false;

    auto newNode = std::make_shared<SongNode>(song, artist);

    if (!root_ptr_) {
        root_ptr_ = newNode;
        return true;
    }

    std::shared_ptr<SongNode> current = root_ptr_;
    std::shared_ptr<SongNode> parent = nullptr;

    while (current) {
        parent = current;
        if (getKey(song, artist) < getKey(*current)) {
            current = current->left_;
        } else if (getKey(song, artist) > getKey(*current)) {
            current = current->right_;
        } else {
            return false; // Duplicate song
        }
    }

    if (getKey(song, artist) < getKey(*parent)) {
        parent->left_ = newNode;
    } else {
        parent->right_ = newNode;
    }

    return true;
}

// Remove a song from the Playlist
bool Playlist::remove(const std::string& song, const std::string& artist) {
    bool is_successful = false;
    root_ptr_ = removeValue(root_ptr_, song, artist, is_successful);
    return is_successful;
}

// Search for a song in the Playlist
bool Playlist::search(const std::string& song, const std::string& artist) const {
    std::shared_ptr<SongNode> current = root_ptr_;
    std::string key = getKey(song, artist);

    while (current) {
        if (key < getKey(*current)) {
            current = current->left_;
        } else if (key > getKey(*current)) {
            current = current->right_;
        } else {
            return true;
        }
    }
    return false;
}

// Clear the Playlist of all songs
void Playlist::clear() {
    root_ptr_.reset();
}

// Perform a preorder traversal of the Playlist
std::vector<SongNode> Playlist::preorderTraverse() const {
    std::vector<SongNode> result;
    preorderHelper(root_ptr_, result);
    return result;
}

// Perform an inorder traversal of the Playlist
std::vector<SongNode> Playlist::inorderTraverse() const {
    std::vector<SongNode> result;
    inorderHelper(root_ptr_, result);
    return result;
}

// Perform a postorder traversal of the Playlist
std::vector<SongNode> Playlist::postorderTraverse() const {
    std::vector<SongNode> result;
    postorderHelper(root_ptr_, result);
    return result;
}

// Remove a value from a subtree of the Playlist
std::shared_ptr<SongNode> Playlist::removeValue(std::shared_ptr<SongNode> sub_tree, const std::string& song, const std::string& artist, bool& success) {
    // If subtree is empty, set success flag to false and return nullptr
    if (sub_tree == nullptr) {
        success = false;
        return sub_tree;
    }
    // If the current node matches the song and artist, remove the node and set success flag to true
    if (getKey(*sub_tree) == getKey(song, artist)) {
        sub_tree = removeNode(sub_tree);
        success = true;
        return sub_tree;
    }
    // Recursively search in the left subtree if the current node key is greater than the target song and artist
    if (getKey(*sub_tree) > getKey(song, artist)) {
        sub_tree->left_ = removeValue(sub_tree->left_, song, artist, success);
    }
    // Recursively search in the right subtree if the current node key is less than the target song and artist
    else {
        sub_tree->right_ = removeValue(sub_tree->right_, song, artist, success);
    }
    return sub_tree;
}

// Remove a node from the Playlist
std::shared_ptr<SongNode> Playlist::removeNode(std::shared_ptr<SongNode> node_ptr) {
    // If the node is a leaf node, reset it and return nullptr
    if (node_ptr->isLeaf()) {
        node_ptr.reset();
        return node_ptr;
    }
    // If the left child is nullptr, return the right child
    else if (node_ptr->left_ == nullptr) {
        return node_ptr->right_;
    }
    // If the right child is nullptr, return the left child
    else if (node_ptr->right_ == nullptr) {
        return node_ptr->left_;
    }
    // If there are two children, find the leftmost node in the right subtree and replace the current node
    std::string inorder_song;
    std::string inorder_artist;
    node_ptr->right_ = removeLeftmostNode(node_ptr->right_, inorder_song, inorder_artist);
    node_ptr->song_ = inorder_song;
    node_ptr->artist_ = inorder_artist;
    return node_ptr;
}

// Remove the leftmost node from a subtree
std::shared_ptr<SongNode> Playlist::removeLeftmostNode(std::shared_ptr<SongNode> node_ptr, std::string& inorder_song, std::string& inorder_artist) {
    // If the left child is nullptr, store the song and artist, remove the current node
    if (node_ptr->left_ == nullptr) {
        inorder_song = node_ptr->song_;
        inorder_artist = node_ptr->artist_;
        return removeNode(node_ptr);
    }
    // Recursively search for the leftmost node
    node_ptr->left_ = removeLeftmostNode(node_ptr->left_, inorder_song, inorder_artist);
    return node_ptr;
}

// Helper function for preorder traversal
void Playlist::preorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    if (node_ptr) {
        result.push_back(*node_ptr);
        preorderHelper(node_ptr->left_, result);
        preorderHelper(node_ptr->right_, result);
    }
}

// Helper function for inorder traversal
void Playlist::inorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    if (node_ptr) {
        inorderHelper(node_ptr->left_, result);
        result.push_back(*node_ptr);
        inorderHelper(node_ptr->right_, result);
    }
}

// Helper function for postorder traversal
void Playlist::postorderHelper(std::shared_ptr<SongNode> node_ptr, std::vector<SongNode>& result) const {
    if (node_ptr) {
        postorderHelper(node_ptr->left_, result);
        postorderHelper(node_ptr->right_, result);
        result.push_back(*node_ptr);
    }
}

// Get the key for a song and artist
std::string Playlist::getKey(const std::string& song, const std::string& artist) const {
    return song + artist;
}

// Get the key for a SongNode
std::string Playlist::getKey(const SongNode& song) const {
    return song.song_ + song.artist_;
}

