#include <memory>
#include <concepts>
#include <optional>
#include <generator>
#include <stack>
using std::unique_ptr;

template <std::totally_ordered T>
struct Node {
    T data_;
    unique_ptr<Node<T>> left_;
    unique_ptr<Node<T>> right_;

    explicit Node(const T& val): data_{val} {};
    explicit Node(T&& val): data_{std::move(val)} {}; 
};

template <std::totally_ordered T>
class BinarySearchTree {
public:
    bool insert(const T& val);
    bool insert(T&& val);
    bool remove(const T& val);
    std::optional<T> find(const T& val) const;
    bool empty() const { return root_ == nullptr; }
    std::generator<const T&> inorder() const;
private:
    unique_ptr<Node<T>> root_;
    bool insertImpl(unique_ptr<Node<T>>& node, const T& val);
    bool insertImpl(unique_ptr<Node<T>>& ndoe, T&& val);
    bool removeImpl(unique_ptr<Node<T>>& node);
};

template<std::totally_ordered T>
bool BinarySearchTree<T>::insert(const T& val){
    return insertImpl(root_, val);
}

template<std::totally_ordered T>
bool BinarySearchTree<T>::insert(T&& val) {
    return insertImpl(root_, std::move(val));
}

template<std::totally_ordered T>
bool BinarySearchTree<T>::insertImpl(unique_ptr<Node<T>>& node,  const T& val) {
    if (!node) {
        node = std::make_unique<Node<T>>(val);
        return true;
    }
    
    if (val < node->data_){
        return insertImpl(node->left_, val);
    }
    else if (val > node->data_) {
        return insertImpl(node->right_, val);
    }

    return false;
}

template<std::totally_ordered T>
bool BinarySearchTree<T>::insertImpl(unique_ptr<Node<T>>& node, T&& val){
    if (!node) {
        node = std::make_unique<Node<T>>(std::move(val));
        return true;
    }

    if (val < node->data_){
        return insertImpl(node->left_, std::move(val));
    }
    else if (val > node->data_){
        return insertImpl(node->right_, std::move(val));
    }

    return false;
}

template<std::totally_ordered T>
std::optional<T> BinarySearchTree<T>::find(const T& val) const {
    for(const auto* cur=root_.get(); cur != nullptr;){
        if (val < cur->data_){
            cur = cur->left_.get();
        }
        else if (val > cur->data_){
            cur = cur->right_.get();
        }
        else {
            return cur->data_;
        }
    }

    return std::nullopt;
}

template<std::totally_ordered T>
bool BinarySearchTree<T>::remove(const T& val) {
    std::unique_ptr<Node<T>>* target = &root_;
    while (*target) {
        auto& cur = **target;
        if (cur.data_ > val) {
            target = &cur.right_;
        }
        else if (cur.data_ < val) {
            target = &cur.left_;
        }
        else {
            return removeImpl(*target);
        }
    }

    return false;
}

template<std::totally_ordered T>
bool BinarySearchTree<T>::removeImpl(unique_ptr<Node<T>>& node) {
    if (!node->left_ and !node->right_){
        node.reset();
    }
    else if (node->left_ && !node->right_){
        node = std::move(node->left_);
    }
    else if (!node->left_ && node->right_){
        node = std::move(node->right_);
    }
    else {
        unique_ptr<Node<T>>* target = &node->right_;
        while ((*target)->left_){
            target = &(*target)->left_;
        }

        node->data_ = std::move((*target)->data_);
        *target = std::move((*target)->right_);
    }
    return true;
}

template<std::totally_ordered T>
std::generator<const T&> BinarySearchTree<T>::inorder() const {
    std::stack<Node<T>*> stack;
    auto* cur = root_.get();
    while (cur || !stack.empty()) {
        while (cur) {
            stack.push(cur);
            cur = cur->left_.get();
        }

        cur = stack.top();
        stack.pop();
        co_yield cur->data_;
        cur = cur->right_.get();
    }
}