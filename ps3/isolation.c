#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct tree_node {
    int val;
    struct tree_node* left;
    struct tree_node* right;
};


struct tree_node* create(int val) {
    struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node));

    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool compare(struct tree_node* p, struct tree_node* q);
int find_struct(struct tree_node** trees, int n, int k);
void add(struct tree_node** root, int val);

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    struct tree_node** trees = (struct tree_node**)malloc(n * sizeof(struct tree_node*));
    for (int i = 0; i < n; i++) {
        trees[i] = NULL;
        for (int j = 0; j < k; j++) {
            int val;
            scanf("%d", &val);
            add(&trees[i], val);
        }
    }

    int count = find_struct(trees, n, k);
    printf("%d\n", count);

    for (int i = 0; i < n; i++) {
        free(trees[i]);
    }
    free(trees);

    return 0;
}




bool compare(struct tree_node* p, struct tree_node* q) {
    if (p == NULL && q == NULL) {
        return true;
    } else if (p == NULL || q == NULL) {
        return false;
    } else {
        return compare(p->left, q->left) && compare(p->right, q->right);
    }
}


int find_struct(struct tree_node** trees, int n, int k) {
    int count = 0;
    bool* visited = (bool*)calloc(n, sizeof(bool));

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = true;
            count++;
            for (int j = i + 1; j < n; j++) {
                if (!visited[j] && compare(trees[i], trees[j])) {
                    visited[j] = true;
                }
            }
        }
    }

    free(visited);
    return count;
}

void add(struct tree_node** root, int val) {
    if (*root == NULL) {
        *root = create(val);
        return;
    }
    if (val < (*root)->val) {
        add(&(*root)->left, val);
    } else {
        add(&(*root)->right, val);
    }
}



