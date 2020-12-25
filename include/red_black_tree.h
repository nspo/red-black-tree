#ifndef RED_BLACK_TREE_RED_BLACK_TREE_H
#define RED_BLACK_TREE_RED_BLACK_TREE_H


#include <optional>
#include <utility>
#include <vector>
#include <memory>
#include <sstream>
#include <cassert>


/**
 * Left-leaning red-black tree (Sedgewick 2008)
 */
template<typename Key, typename Value>
class red_black_tree {
public:
    [[nodiscard]] std::optional<Value> get(const Key &key) const {
        const Node *node = root.get();
        while (node != nullptr) {
            if (key < node->key) {
                node = node->left.get();
            } else if (key > node->key) {
                node = node->right.get();
            } else {
                // keys are equal -> found
                return {node->val};
            }
        }
        return {};
    }

    void put(const Key &key, const Value &val) {
        root = put(root, key, val);
        root->color = Color::BLACK; // root is always black
    }

    [[nodiscard]] std::optional<Key> min() const {
        if (root == nullptr) {
            return {};
        }

        const Node *node = root.get();
        while (node->left != nullptr) {
            node = node->left.get();
        }

        return {node->key};
    }


    [[nodiscard]] std::optional<Key> max() const {
        if (root == nullptr) {
            return {};
        }

        const Node *node = root.get();
        while (node->right != nullptr) {
            node = node->right.get();
        }

        return {node->key};
    }

    [[nodiscard]] int size() const {
        return size(root.get());
    }

    [[nodiscard]] std::vector<Key> keys() const {
        std::vector<Key> keys{};
        keys.reserve(size());
        inorder(root.get(), keys);
        return keys;
    }

    [[nodiscard]] std::string toString() const {
        if (root != nullptr) {
            return root->toString();
        } else {
            return "";
        }
    }

private:
    enum class Color {
        RED, BLACK
    };

    class Node {
    public:
        Node(Key key1, Value val1, Color color1) : key(std::move(key1)), val(std::move(val1)),
                                                   color(std::move(color1)) {}

        Key key;
        Value val;
        int count = 1;
        Color color;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        [[nodiscard]] std::string toString() const {
            std::stringstream ss;
            print(ss, "", "");
            return ss.str();
        }

        /// helper function to check color of valid and null nodes
        static bool isRed(const Node *node) {
            if (node == nullptr) {
                // null links are black
                return false;
            }
            return node->color == Color::RED;
        }


    private:
        void print(std::stringstream &ss, const std::string &prefix, const std::string &childrenPrefix) const {
            ss << prefix << key << "\n";
            const char *strRED = "(red)";
            const char *strBLK = "(blk)";
            if (right != nullptr) {
                std::string newPrefix = childrenPrefix + "├r" + (isRed(right.get()) ? strRED : strBLK) + "── ";
                std::string newChildrenPrefix = childrenPrefix + "|     ";
                if (left == nullptr) {
                    newPrefix = childrenPrefix + "└r" + (isRed(right.get()) ? strRED : strBLK) + "── ";
                    newChildrenPrefix = childrenPrefix + "     ";
                }
                right->print(ss, newPrefix, newChildrenPrefix);
            }
            if (left != nullptr) {
                left->print(ss, childrenPrefix + "└l" + (isRed(left.get()) ? strRED : strBLK) + "── ",
                            childrenPrefix + "     ");
            }
        }
    };

    /// helper function to check color of valid and null nodes
    static bool isRed(const Node *node) {
        return Node::isRed(node);
    }

    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> &h) {
        assert(isRed(h->right.get()));
        std::unique_ptr<Node> x = std::move(h->right);
        h->right = std::move(x->left);
        x->left = std::move(h);
        x->color = x->left->color;
        x->left->color = Color::RED;
        // update sizes
        x->left->count = 1 + size(x->left->left.get()) + size(x->left->right.get());
        x->count = 1 + size(x->left.get()) + size(x->right.get());
        return x;
    }

    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> &h) {
        assert(isRed(h->left.get()));
        std::unique_ptr<Node> x = std::move(h->left);
        h->left = std::move(x->right);
        x->right = std::move(h);
        x->color = x->right->color;
        x->right->color = Color::RED;
        // update sizes
        x->right->count = 1 + size(x->right->left.get()) + size(x->right->right.get());
        x->count = 1 + size(x->left.get()) + size(x->right.get());
        return x;
    }

    void flipColors(Node *h) {
        assert(!isRed(h));
        assert(isRed(h->left.get()));
        assert(isRed(h->right.get()));
        h->color = Color::RED;
        h->left->color = Color::BLACK;
        h->right->color = Color::BLACK;
    }


    std::unique_ptr<Node> root;

    std::unique_ptr<Node> put(std::unique_ptr<Node> &node, const Key &key, const Value &val) {
        if (node == nullptr) {
            return std::make_unique<Node>(key, val, Color::RED);
        }

        if (key < node->key) {
            // go left
            node->left = put(node->left, key, val);
        } else if (key > node->key) {
            // go right
            node->right = put(node->right, key, val);
        } else {
            // keys are equal
            node->val = val;
        }

        if (isRed(node->right.get()) && !isRed(node->left.get())) {
            node = rotateLeft(node);
        }
        if (isRed(node->left.get()) && isRed(node->left->left.get())) {
            node = rotateRight(node);
        }
        if (isRed(node->left.get()) && isRed(node->right.get())) {
            flipColors(node.get());
        }

        node->count = 1 + size(node->left.get()) + size(node->right.get());
        return std::move(node);
    }

    [[nodiscard]] int size(const Node *node) const {
        if (node == nullptr) {
            return 0;
        }
        return node->count;
    }

    void inorder(const Node *node, std::vector<Key> &keys) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left.get(), keys);
        keys.push_back(node->key);
        inorder(node->right.get(), keys);
    }

};

template<typename Key, typename Val>
std::ostream &operator<<(std::ostream &os, const red_black_tree<Key, Val> &bst) {
    return os << "RedBlackTree (r=right child, l=left child)\n" << bst.toString() << "\n";
}


#endif //RED_BLACK_TREE_RED_BLACK_TREE_H
