/*
 Help found at https://gist.github.com/ArnonEilat/4611213 for implementation.
 Author: Arnmon Eilat
 Adapted by: Matt Drew
*/

#include "bst.h"

Tree * add(Tree* node, int key, int number) {
    if (node == NULL) {
        node = (Tree*) malloc(sizeof (Tree));
        if (node == NULL) {
            return NULL;
        }
        node->info.value = number;
        node->info.key = 0;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    if (node->info.value > number) {
        node->left = add(node->left, key, number);
    } else {
        node->right = add(node->right, key, number);
    }
    return node;
}

int rank(Tree* root) {
    int left, right;
    if (root == NULL) {
        return -1;
    }
    left = rank(root->left);
    right = rank(root->right);
    return 1 + (left > right ? left : right);
}

void printInorder(Tree* node) {
    if (node == NULL) {
        return;
    }
    printInorder(node->left);
    printf(" %d ", node->info.value);
    printInorder(node->right);
}

Tree * findMinimum(Tree *t) {
    if (t == NULL) {
        return t;
    }
    if (t->left == NULL) {
        return t;
    }
    return findMinimum(t->left);
}

Tree * deletenode(Tree *t, Data x){
  Tree * tmp;
      if (t == NULL) {
          return t;
      }
      if (x.value < t->info.value) {
          t->left = deletenode(t->left, x);
      } else {
          if (x.value > t->info.value) {
              t->right = deletenode(t->right, x);
          } else {
              if (t->left && t->right) {
                  tmp = findMinimum(t->right);
                  t->info.value = tmp->info.value;
                  t->right = deletenode(t->right, t->info);
              } else {
                  tmp = t;
                  if (t->left == NULL) {
                      t = t->right;
                  } else {
                      if (t->right == NULL) {
                          t = t->left;
                      }
                      free(tmp);
                  }
              }
          }
      }
      return t;
}

void freeTree(Tree *root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}




Tree * find(Tree * node, int val) {
    if (node == NULL) {
        return NULL;
    }
    if (node->info.value == val) {
        return node;
    }
    if (node->info.value > val) {
        return find(node->left, val);
    }
    return find(node->right, val);
}

int main() {
    Tree* t = NULL;
    int i;
    Data itm;
    int arr[] = {5, 7, 6, 9, 8, 11, 10, 12, 3, 4, 1, 2, 0};

    //initialize the tree
    for (i = 0; i < length(arr); i++) {
        t = add(t, i, arr[i]);
    }
    int keyCount = length(arr);

    printf("=====================\nWelcome to the binary search tree program.\n\nEnter 1 to add a node.\nEnter 2 to search a node.\nEnter 3 to update a node.\nEnter 4 to print the tree.\nEnter 5 to delete a node.\nEnter 9 to exit.\n=======================\n\nPlease enter your command: ");

      int integer;
    while (scanf("%d", &integer)) {
      //we've entered a vaild number
      switch (integer) {
        //add node
        case 1:
          {
            int xi;
            printf("Enter the number node you want to add: ");
            scanf("%d", &xi);
            if (find(t, xi) == NULL) {
              t = add(t, i++, xi);
              printf("\nSuccessfully added.\n====================\n\nPlease enter a number: ");
              break;
            } else {
              printf("\nnode already exists in the tree. Would you like to update it? (y/n): ");
              char yOrN;
              while(scanf("%c", &yOrN)){
                if(yOrN == 'y'){
                  int a = find(t, xi)->info.value;
                  printf("\n%d is the number you are updating.\nEnter your new number: ", a);
                  int newNumber;
                  scanf("%d", &newNumber);
                  find(t, xi)->info.value = newNumber;
                  printf("%d is updated to %d", a, newNumber);
                  printf("\n==================\n\nPlease enter a number: ");
                  break;
                }
                else if(yOrN == 'n'){
                  printf("\n==================\n\nPlease enter a number: ");
                  break;
                }
              } break;

            }
          }
        //search a node
        case 2:
          {
            int yi;
            printf("Enter the number node you want to search: ");
            scanf("%d", &yi);
            if (find(t, yi) == NULL) {
                printf("\nCannot find %d.\n=======================\n\nPlease enter a number: ", yi);
                break;
            } else {
              printf("\nWe found %d!\n====================\n\nPlease enter a number: ", yi);
              break;
            }

          }
        //update a node
        case 3:
        {
          int zi;
          printf("Enter the number node you want to update: ");
          scanf("%d", &zi);
          if (find(t, zi) == NULL) {
            printf("\nnode does not exist in the tree. Would you like to make it? (y/n): ");
            char yOrN;
            while(scanf("%c", &yOrN)){
              if(yOrN == 'y'){
                t = add(t, i++, zi);
                printf("Successfully added to the tree.");
              }
              else if(yOrN == 'n'){
                printf("\n==================\n\nPlease enter a number: ");
                break;
              }
            } break;
          } else {
                int a = find(t, zi)->info.value;
                printf("\n%d is the number you are updating.\nEnter your new number: ", a);
                int newNumber;
                scanf("%d", &newNumber);
                find(t, zi)->info.value = newNumber;
                printf("%d is updated to %d", a, newNumber);
                printf("\n==================\n\nPlease enter a number: ");
                break;
              }

        }
        //print the tree
        case 4:
          {
            printInorder(t);
            printf("\nSuccessfully printed.\n===================\n\nPlease enter a number: ");
            break;
          }
        //delete a node
        case 5:
          {
            printf("\nEnter the node that you want to delete: ");
            int deletingnode;
            scanf("%d", &deletingnode);
            if(find(t, deletingnode) == NULL){
              printf("\nThe number doesn't exist in the tree.");
              break;
            } else{
              printf("\nDeleting...");
              deletenode(t, find(t, deletingnode)->info);
              printf("\nSuccessful deletion.\n==================\n\nPlease enter a number: ");
              break;
            }
          }
        //exit the program
        case 9:
          {
            printf("\nExiting...\n\n");
            return 0;
          }
        default:
          {
            printf("\nPlease try entering another number. That one didn't match a command.\n=====================\n\nPlease enter a number: ");
            break;
          }
      }
    }

    return (EXIT_SUCCESS);
}
