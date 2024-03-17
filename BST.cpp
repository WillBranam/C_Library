#include "BST.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

BST::BST() {
    root = nullptr;
}

BST::BST(string title, string author, int yr, string pub, long long isbn, float rate) {
    root = new BSTNode(title, author, yr, pub, isbn, rate);
}

BST::~BST() {
    clearTree();
}

void BST::insert(string title, string author, int yr, string pub, long long isbn, float rate) {
    BSTNode *node = new BSTNode(title, author, yr, pub, isbn, rate);
    if (root == nullptr) {
        root = node;
        return;
    }
    BSTNode *current = root;

    while (true) {
        // Compare books by author first
        if (*(node->book) < *(current->book)) {
            if (!current->left) {
                current->left = node;
                node->parent = current;
                setHeight(current);
                return;
            } else {
                current = current->left;
            }
        } else if (*(node->book) >= *(current->book)) {
            if (!current->right) {
                current->right = node;
                node->parent = current;
                setHeight(current);
                return;
            } else {
                current = current->right;
            }
        }
    }
}


BSTNode *BST::find(string title, string author) {
    return find(title, author, root);
}

BSTNode *BST::find(string title, string author, BSTNode *start) {
    if (!start) {
        return nullptr;
    }
    if (author == start->book->author && title == start->book->title) {
        return start;
    } else if (author < start->book->author || (author == start->book->author && title < start->book->title)) {
        return find(title, author, start->left);
    } else if (author > start->book->author || (author == start->book->author && title > start->book->title)) {
        return find(title, author, start->right);
    }
    return nullptr;
}

// starts the in-order print traversal at the root
void BST::printTreeIO() {
    if (root == nullptr) {
        cout << "Empty Tree" << endl;
    } else {
        cout << endl << "Printing In-Order:" << endl;
        printTreeIO(root);
    }
}

void BST::printTreeIO(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    // Recursively print left subtree
    printTreeIO(node->left);
    // Print the current node's data
    node->printNode(false);
    // Recursively print right subtree
    printTreeIO(node->right);
}

void BST::printTreePre() {
    if (root == nullptr) {
        cout << "Empty Tree" << endl;
    } else {
        cout << endl << "Printing Pre-Order:" << endl;
        printTreePre(root);
    }
}

void BST::printTreePre(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    node->printNode(false);
    printTreePre(node->left);
    printTreePre(node->right);
}

void BST::printTreePost() {
    if (root == nullptr) {
        cout << "Empty Tree" << endl;
    } else {
        cout << endl << "Printing Post-Order:" << endl;
        printTreePost(root);
    }
}

void BST::printTreePost(BSTNode *node) {
    if (node == nullptr) {
        return;
    }
    printTreePost(node->left);
    printTreePost(node->right);
    node->printNode(false);
}

void BST::clearTree() {
    if (root == nullptr) {
        cout << "Tree already empty" << endl;
    } else {
        cout << endl << "Clearing Tree:" << endl;
        clearTree(root);
        root = nullptr;
    }
}

void BST::clearTree(BSTNode *node) {
    if (node == nullptr) {
        return;
    } else {
        clearTree(node->left);
        node->left = nullptr;
        clearTree(node->right);
        node->right = nullptr;
        node->printNode(true);
        delete node;
    }
}

bool BST::checkOut(string title, string author) {
    BSTNode *target = find(title, author);

    if (target) {
        while (target && target->book->checked_out) {
            target = find(title, author, target->right);
        }
        if (target) {
            target->book->checked_out = true;
            return true;
        }
        return false;
    }
    return false;
}

bool BST::checkIn(string title, string author) {
    BSTNode *target = find(title, author);
    bool found = false;

    while (!found) {
        if (target == nullptr) {
            break;
        } else if (target->book->checked_out) {
            target->book->checked_out = false;
            found = true;
        }
        target = find(title, author, target->right);
    }
    return found;
}

void BST::updateRating(string title, string author, float newRating) {
    BSTNode *target = find(title, author);

    while (target) {
        target->book->rating = newRating;
        target = find(title, author, target->right);
    }
}

BSTNode *BST::removeNoKids(BSTNode *node) {
    if (node->parent == nullptr) {
        root = nullptr;
    } else if (node->parent->right == node) {
        node->parent->right = nullptr;
    } else {
        node->parent->left = nullptr;
    }
    setHeight(node->parent);
    return node;
}

BSTNode *BST::removeOneKid(BSTNode *node, bool leftFlag) {
    if (node == root) {
        if (leftFlag) {
            root = node->left;
            root->parent = nullptr;
            node->left = nullptr;
            setHeight(root);
            return node;
        } else {
            root = node->right;
            root->parent = nullptr;
            node->right = nullptr;
            setHeight(nullptr);
            return node;
        }
    } else if (leftFlag) {
        node->left->parent = node->parent;
        node->parent->left = node->left;
        setHeight(node->parent);
        node->parent = nullptr;
        node->left = nullptr;
        return node;
    } else {
        node->right->parent = node->parent;
        node->parent->right = node->right;
        setHeight(node->parent);
        node->parent = nullptr;
        node->right = nullptr;
        return node;
    }
}

BSTNode *BST::remove(string title, string author) {
    BSTNode *target = find(title, author);

    if (target == nullptr) {
        return nullptr;
    }

    BSTNode *parent = target->parent;

    if (!target->right && !target->left) {
        return removeNoKids(target);
    } else if (target->right == nullptr && target->left != nullptr) {
        return removeOneKid(target, true);
    } else if (target->right != nullptr && target->left == nullptr) {
        return removeOneKid(target, false);
    } else {
        BSTNode *right = find(title, author, target->right);

        if (!right) {
            right = target->right;
            while (right->left != nullptr) {
                right = right->left;
            }
        }

        if (right->right) {
            removeOneKid(right, false);
        } else {
            removeNoKids(right);
        }

        if (!parent) {
            // If we are removing the root node, set the new root
            root = right;
        } else if (parent->left == target) {
            parent->left = right;
        } else {
            parent->right = right;
        }

        right->parent = parent;
        right->left = target->left;
        right->right = target->right;

        if (target->left) {
            target->left->parent = right;
        }

        if (target->right) {
            target->right->parent = right;
        }

        setHeight(right);

        target->right = nullptr;
        target->left = nullptr;
        target->parent = nullptr;

        return target;
    }
}


void BST::setHeight(BSTNode *node) {
    while (node) {
        int newHeight = 1;
        if (node->right) {
            newHeight = max(newHeight, node->right->height + 1);
        }
        if (node->left) {
            newHeight = max(newHeight, node->left->height + 1);
        }
        if (node->height == newHeight) {
            break;
        }
        node->height = newHeight;
        node = node->parent;
    }
}