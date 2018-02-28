#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;
unsigned check = 0;

struct node {
    int value;
    int size;
    node *childL;
    node *childR;
};
node *root = NULL;

void insertion(node *node, int x) {
    if (node->value < x) {
        if (node->childR == NULL) {
            node->size += 1;
            node->childR = new struct node;
            node->childR->value = x;
            node->childR->size = 0;
            node->childR->childR = NULL;
            node->childR->childL = NULL;
        } else {
            node->size+=1;
            insertion(node->childR, x);
        }
    } else {
        if (node->childL == NULL) {
            node->size += 1;
            node->childL = new struct node;
            node->childL->value = x;
            node->childL->size = 0;
            node->childL->childR = NULL;
            node->childL->childL = NULL;
        } else {
            node->size+=1;
            insertion(node->childL, x);
        }
    }
}

void insert(int x) {
    if (root == NULL) {
        root = new node;
        root->value = x;
        root->size = 0;
        root->childR = NULL;
        root->childL = NULL;
    } else {
        insertion(root, x);
    }
}

int findNode(node *node, int x) {
    check++;
    if (node->value == x) {
        return 1;
    } else {
        check++;
        if (node->value < x) {
            check++;
            if (node->childR == NULL) {
                return 0;
            } else {
                return findNode(node->childR, x);
            }
        } else {
            check++;
            if (node->childL == NULL) {
                return 0;
            } else {
                return findNode(node->childL, x);
            }
        }
    }
}

int find(int x) {
    check++;
    if (root == NULL) {
        return 0;
    } else {
        return findNode(root, x);
    }
}

int osRankNode(node *node, int x) {
    check++;
    if (node->value == x) {
        if (node->childL == NULL) {
            return 0;
        } else {
            return node->childL->size+1;
        }
    } else {
        check++;
        if (node->value < x) {
            check++;
            if (node->childR == NULL) {
                return -1;
            } else {
                return osRankNode(node->childR, x);
            }
        } else {
            check++;
            if (node->childL == NULL) {
                return -1;
            } else {
                return osRankNode(node->childL, x);
            }
        }
    }
}

int osRank(int x) {
    check++;
    if (root == NULL) {
        return -1;
    } else {
        return osRankNode(root, x);
    }
}

int osSelectNode(node *node, int x) {
    check++;
    if(node->childR==NULL){
        check++;
        if(node->size==x){
            return node->value;
        }else{
            check++;
            if(node->size<x){
                return -1;
            }else{
                check++;
                if(node->childL!=NULL) {
                    osSelectNode(node->childL, x);
                }else{
                    return -1;
                }
            }
        }
    }else{
        check++;
        if(node->size-node->childR->size==x){
            return node->value;
        }else{
            check++;
            if(node->size-node->childR->size<x){
                osSelectNode(node->childR,x-(node->size-node->childR->size));
            }else{
                check++;
                if(node->childL!=NULL) {
                    osSelectNode(node->childL, x);
                }else{
                    return -1;
                }
            }
        }
    }
}

int osSelect(int x) {
    check++;
    if (root == NULL) {
        return -1;
    } else {
        return osSelectNode(root, x);
    }
}

void deleteNode(node *node, int x) {
    if (node->value < x) {
        if (node->childR != NULL) {
            if (node->childR->value == x) {
                struct node *newNode = node->childR;
                if (newNode->childR == NULL) {
                    node->childR = newNode->childL;
                    node->size-=1;
                    delete newNode;
                } else {
                    struct node *newNode1 = newNode;
                    newNode->size-=1;
                    newNode = newNode->childR;
                    while (newNode->childL != NULL) {
                        newNode1 = newNode;
                        newNode = newNode->childL;
                        newNode->size-=1;
                    }
                    newNode->childL = node->childR->childL;
                    newNode1->childL = newNode->childR;
                    newNode->childR = node->childR->childR->childR;
                    delete node->childR;
                    node->childR = newNode;
                    node->size-=1;
                }
            } else {
                node->size-=1;
                deleteNode(node->childR, x);
            }
        }
    } else {
        if (node->childL != NULL) {
            if (node->childL->value == x) {
                struct node *newNode = node->childL;
                if (newNode->childR == NULL) {
                    node->childL = newNode->childL;
                    node->size-=1;
                    delete newNode;
                } else {
                    struct node *newNode1 = newNode;
                    newNode->size-=1;
                    newNode = newNode1->childR;
                    while (newNode->childL != NULL) {
                        newNode1 = newNode;
                        newNode = newNode->childL;
                        newNode->size-=1;
                    }

                    newNode->childL = node->childL->childL;
                    newNode1->childL = newNode->childR;
                    newNode->childR = node->childL->childR->childR;
                    delete node->childL;
                    node->childL = newNode;
                    node->size-=1;
                }
            } else {
                node->size-=1;
                deleteNode(node->childR, x);
            }
        }
    }

}


void deleteN(int x) {
    if (root != NULL) {
        if (root->value == x) {
            if (root->childR == NULL && root->childL == NULL) {
                delete root;
                root = NULL;
            } else {
                struct node *newNode = root;
                if (newNode->childR == NULL) {
                    root = newNode->childL;
                    root->size=newNode->size-1;
                    delete newNode;
                } else {
                    struct node *newNode1 = newNode;
                    newNode = newNode->childR;
                    newNode->size-=1;

                    while (newNode->childL != NULL) {
                        newNode1 = newNode;
                        newNode = newNode->childL;
                        newNode->size-=1;
                    }
                    newNode->childL = root->childL;
                    newNode1->childL = newNode->childR;
                    newNode->childR = root->childR;
                    newNode->size=root->size-1;
                    delete root;
                    root = newNode;
                }
            }
        } else {
            deleteNode(root, x);
        }
    }
}

void inOrderNode(node *node) {
    if (node->childL != NULL) {
        inOrderNode(node->childL);
    }
    cout << node->value << " - "<<node->size <<"; ";
    if (node->childR != NULL) {
        inOrderNode(node->childR);
    }
}

void inorder() {
    if (root != NULL) {
        if (root->childL != NULL) {
            inOrderNode(root->childL);
        }
        cout << root->value << " - "<<root->size <<"; ";
        if (root->childR != NULL) {
            inOrderNode(root->childR);
        }
    }
    cout << endl;
}

void deleteBSTNode(node *node) {
    if (node->childL != NULL) {
        deleteBSTNode(node->childL);
    }
    if (node->childR != NULL) {
        deleteBSTNode(node->childR);
    }
    delete node;
}

void deleteBST() {
    if (root != NULL) {
        if (root->childL != NULL) {
            deleteBSTNode(root->childL);
        }
        if (root->childR != NULL) {
            deleteBSTNode(root->childR);
        }
        root = NULL;
    }
}

void min() {
    if (root != NULL) {
        struct node *node1 = root;
        while (node1->childL != NULL) {
            node1 = node1->childL;
        }
        cout << node1->value;
    }
    cout << endl;
}

void max() {
    if (root != NULL) {
        struct node *node1 = root;
        while (node1->childR != NULL) {
            node1 = node1->childR;
        }
        cout << node1->value;
    }
    cout << endl;
}

void insertEven(int i, int l, int j, int k) {
    insert(l);
    if (k < j) {
        insertEven(i / 2, l - i / 2, j, k + 1);
        insertEven(i / 2, l + i / 2, j, k + 1);
    }
}

int main() {

    int n, b, c, test;

    string a;
    cout << "Test BST? 1-Yes 2-No 3-Select Test" << endl;
    cin >> test;
    if (test == 2) {
        fstream file;
        file.open("input1.txt");
        file >> n;
        cout << "Show more information? 1-Yes 2-No" << endl;
        cin >> c;
        cout << "Result:" << endl;
        for (int i = 0; i < n; i++) {
            file >> a;
            if (!a.compare("insert")) {
                file >> b;
                insert(b);
                if (c == 1) {
                    cout << "Element " << b << " successfully added" << endl;
                }
            } else if (!a.compare("find")) {
                if (c == 1) {
                    cout << "Find: ";
                }
                file >> b;
                cout << find(b) << endl;
            } else if (!a.compare("delete")) {
                file >> b;
                deleteN(b);
                if (c == 1) {
                    cout << "Element " << b << " successfully removed" << endl;
                }
            } else if (!a.compare("min")) {
                if (c == 1) {
                    cout << "Min: ";
                }
                min();
            } else if (!a.compare("max")) {
                if (c == 1) {
                    cout << "Max: ";
                }
                max();
            } else if (!a.compare("inorder")) {
                if (c == 1) {
                    cout << "In Order: " << endl;
                }
                inorder();
            } else if (!a.compare("rank")) {
                file >> b;
                if (c == 1) {
                    cout << "OS-Rank ("<<b<<") : ";
                }
                cout << osRank(b)<<endl;
            }else if (!a.compare("select")) {
                file >> b;
                if (c == 1) {
                    cout << "OS-Select ("<<b<<") : ";
                }
                cout << osSelect(b)<<endl;
            }
            a = "";
        }
    }else if(test == 3){
        ofstream file;
        cout << "Tests" << endl;
        srand(time(NULL));
        file.open("output1.txt");
        unsigned max, min, avgSum;
        for (int j = 0; j < 100; j++) {
            insert(rand() % 1000);
        }
        file << "" << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg" << endl;
        for (int i = 100; i <= 100000; i+=100) {
            avgSum = 0;
            min = 4294967295;
            max = 0;
            for (int j = 0; j < 50; ++j) {
                check = 0;
                osSelect(rand() % i);
                avgSum += check;
                if (check > max) {
                    max = check;
                }
                if (check < min) {
                    min = check;
                }
                for (int k = 0; k < 100; ++k) {
                    insert(rand()%1000);
                }
                cout<<i<<endl;
            }
            file << i<< "\t" << min << "\t" << max << "\t" << (double) avgSum / 50 << "\t" << endl;
        }
        deleteBST();
        file << "------------------------------------------------" << endl;
        for (int j = 0; j < 100; j++) {
            insert(j + 1);
        }
        file << "" << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg" << endl;
        for (int i = 100; i <= 100000; i+=100) {
            avgSum = 0;
            min = 4294967295;
            max = 0;
            for (int j = 0; j < 50; ++j) {
                check = 0;
                osSelect(rand() % i);
                avgSum += check;
                if (check > max) {
                    max = check;
                }
                if (check < min) {
                    min = check;
                }
                for (int k = i; k < i+100; k++) {
                    insert(k + 1);
                }
            }
            cout<<i<<endl;
            file << i << "\t" << min << "\t" << max << "\t" << (double) avgSum / 50 << "\t" << endl;
        }
        deleteBST();
        file.close();
    } else {

        ofstream file;
        cout << "Tests" << endl;
        srand(time(NULL));
        file.open("output.txt");
        unsigned max, min, avgSum;
        for (int j = 0; j < 1000; j++) {
            insert(rand() % 1000);
        }
        file << "" << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg" << endl;
        for (int i = 0; i < 1000; ++i) {
            avgSum = 0;
            min = 4294967295;
            max = 0;
            for (int j = 0; j < 10000; ++j) {
                check = 0;
                find(rand() % 1000);
                avgSum += check;
                if (check > max) {
                    max = check;
                }
                if (check < min) {
                    min = check;
                }
            }
            file << (i + 1) << "\t" << min << "\t" << max << "\t" << (double) avgSum / 10000 << "\t" << endl;
        }
        deleteBST();
        file << "------------------------------------------------" << endl;
        for (int j = 0; j < 1000; j++) {
            insert(j + 1);
        }
        file << "" << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg" << endl;
        for (int i = 0; i < 1000; ++i) {
            avgSum = 0;
            min = 4294967295;
            max = 0;
            for (int j = 0; j < 10000; ++j) {
                check = 0;
                find(rand() % 1000);
                avgSum += check;
                if (check > max) {
                    max = check;
                }
                if (check < min) {
                    min = check;
                }
            }
            file << (i + 1) << "\t" << min << "\t" << max << "\t" << (double) avgSum / 10000 << "\t" << endl;
        }
        deleteBST();
        file << "------------------------------------------------" << endl;
        insertEven(500, 500, 9, 0);
        file << "" << "\t" << "Min" << "\t" << "Max" << "\t" << "Avg" << endl;
        for (int i = 0; i < 1000; ++i) {
            avgSum = 0;
            min = 4294967295;
            max = 0;
            for (int j = 0; j < 10000; ++j) {
                check = 0;
                find(rand() % 1000);
                avgSum += check;
                if (check > max) {
                    max = check;
                }
                if (check < min) {
                    min = check;
                }
            }
            file << (i + 1) << "\t" << min << "\t" << max << "\t" << (double) avgSum / 10000 << "\t" << endl;
        }
        file.close();
    }
    deleteBST();
    return 0;
}