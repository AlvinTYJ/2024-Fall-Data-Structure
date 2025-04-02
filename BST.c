#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
  int key;
  struct node *left, *right;
};

struct node *newNode(int item) {
  struct node *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

void inorder(struct node *root) {
  if (root != NULL) {
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
  }
}

void levelOrder(struct node* root) {
    if (root == NULL) return;

    struct node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct node* current = queue[front++];
        printf("%d ", current->key);
        
        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
    printf("\n");
}

struct node *insert(struct node *node, int key) {
  // Return a new node if the tree is empty
  if (node == NULL) return newNode(key);

  // Traverse to the right place and insert the node
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);

  return node;
}

// Find the inorder successor
struct node *minValueNode(struct node *node) {
  struct node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

struct node *deleteNode(struct node *root, int key) {
  // Return if the tree is empty
  if (root == NULL) return root;

  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      struct node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      struct node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    struct node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
}

struct node *search(struct node *root, int key) {
  if (root == NULL || root->key == key)
    return root;

  if (key > root->key)
    return search(root->right, key);

  return search(root->left, key);
}

int main() {
  struct node *root = NULL;
  char input[100];
  int value;
  struct node *searchResult;

  while (scanf("%s", input) == 1) {
    if (strcmp(input, "exit") == 0) break;

    if (strcmp(input, "insert") == 0) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    if (strcmp(input, "delete") == 0) { 
        scanf("%d", &value);
        root = deleteNode(root, value);
    }

    if (strcmp(input, "search") == 0) { 
        scanf("%d", &value);
        searchResult = search(root, value);
        if (searchResult != NULL)
            printf("%d\n", searchResult->key);
        else
            printf("NULL\n");
    }
  }
  inorder(root);
  printf("\n");

  return 0;
}
