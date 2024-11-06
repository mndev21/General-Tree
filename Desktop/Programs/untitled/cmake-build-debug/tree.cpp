#include <vector>
#include <iostream>
#include <queue>

class Tree {
public:
    struct Node {
        int value;
        std::vector<Node*> children;

        Node(const int& val) : value(val) {}

        void addChild(const int& val) {
            children.push_back(new Node(val));
        }

        ~Node() {
            for (Node* child : children) {
                delete child;
            }
        }
    };

    Node* root;

    Tree(const int& val) : root(new Node(val)) {}

    void print() {
        if (!root) {
            return;
        }
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node* node = q.front();
                q.pop();
                std::cout << node->value << " ";
                for (Node* child: node->children) {
                    q.push(child);
                }
            }
            std::cout << "\n";
        }
    }

    ~Tree() {
        delete root;
    }
};

int main() {
    Tree tree(1);

    tree.root->addChild(21);
    tree.root->addChild(3);
    tree.root->addChild(4);

    tree.root->children[0]->addChild(5);
    tree.root->children[0]->addChild(6);

    tree.root->children[1]->addChild(7);

    tree.print();

    return 0;
}
