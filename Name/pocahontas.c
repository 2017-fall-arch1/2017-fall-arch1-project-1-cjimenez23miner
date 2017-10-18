/*
 * pocahontas.c
 *
 *  Created on: Oct 16, 2017
 *      Author: 1
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "pocahontas.h"
#define EOL '\n'

/* Main method where initial calls are made */
int main(){
  Node *root; // Pointer for tree to be created
  root = NULL; // create empty tree
  int input = 0; // used for user input
  char first[50]; // pointer for name to be inserted
  int forScan; // used to store scanf value, no real usage, except for avoiding warnings
  root = makeTree(); // add names from the existing file into current tree

  printf("Current list of names: \n"); // print current names in the file
  printTree(root);

  // user interface
  while (input != 4) {
    printf("Type 1 to add names, 2 to remove names, 3 to print the current tree or 4 to exit\n");
    forScan = scanf("%d", &input); // user input for what they want to do
    if (input == 1) { // add a name
      printf("Type name: ");
       forScan = scanf("%s", first); // user inputs name to be added
      // scanf("%s",first);
      // fgets(first,50,stdin);
      root = add(root, first); // add name to tree
    }
    if (input == 2) { // remove a name
      printf("Type name you want to delete: ");
      scanf("%s", first); // user inputs name to delete
      root = removeName(root, first); // remove the name
    }
    if (input == 3) { // print current tree inorder
     printTree(root);
    }
    printf("\n Current list on file: \n");
    printFile();
  }
  return 0;
}

  //Copy of the string is made and put into a node, need to add to tree from here
  Node *add(Node *tp, char *s) {
// the copying and memory allocation was given by the professor in his llist.c file
       	if(tp == NULL) { //Base Case
	  Node *np; // pointer for node going to be added
	  char *scopy; // copy of the string to be added
       	  int size; // used to traverse char array and get the size
	  for (size = 0; s[size]; size++);
	  scopy = (char *)malloc(size + 1); // + 1 for the null character
	  for (size = 0; s[size]; size++)
	    scopy[size] = s[size];
	  scopy[size+1] = 0; // set null character
          np = (Node *)malloc(sizeof(scopy)); // allocate memory
	  np->string = scopy; // set pointer to correct string
	  np->left = np->right = NULL;
	  // printf("String added: %s\n", scopy); //used for debugging
          return np; // return the newly inserted node
      	}

	int cmp;// used to store strcmp value
	cmp = strcmp(s, tp->string); // compare strings
	if (cmp < 0) { // go to left child
	  tp->left =  add(tp->left, s); // add to left if less
	}
	if (cmp > 0) {
	  tp->right = add(tp->right, s); // add to right
	}
	remove("employees.txt");
	writeFile(tp);
	return tp;
  }

/* Prints tree inorder */
void printTree(Node *tp) {
  if (tp != NULL) {
    printTree(tp->left); //recursively call left child
    printf("%s\n",tp->string); // print current name
    printTree(tp->right); // recursivley call right child

  }
}

Node *removeName(Node *tp, char *s) {
  if (tp == NULL)
    return tp;

  int cmp;
  Node *temp; // temp variable
  cmp = strcmp(s, tp->string); // check to see if the string is smaller or larger

  if (cmp < 0) { // go to left child
    tp->left = removeName(tp->left, s);// recursive call to left child
    return tp;
  }
  if (cmp > 0) { // go to right child
    tp->right = removeName(tp->right, s); // recursive call to right child
    return tp;
  }
  // strings are equal, so delete this node
  if (tp->left == NULL) { //has right child, but no left
    temp = tp->right;
    free(tp); // free the memory
    tp = temp;
  } else if (tp->right == NULL) { //has left child, but no right child
    temp = tp->left;
    free(tp); // free memory
    tp = temp;
  } else{
    // has two children
    temp = smallestChild(tp->right); // calls auxiliary method
    tp->string = temp->string; // set the char *
    tp->right = removeName(tp->right, temp->string); // remove the Node
  }
  remove("employees.txt");
  writeFile(tp);
  return tp;
}

/* finds node to replace the root being deleted */
Node *smallestChild(Node  *tp) {
  Node *np = tp;
  while (np->left != NULL)
    np = np->left;
  return np;

}

/* reads from the file and adds all the names to the binary tree before modification */
Node *makeTree() {
  FILE *file;
  file = fopen("employees.txt", "r"); // only to read names
  char data[100];
  Node *tp = NULL;
  while(fgets(data,50,file)!=NULL) {
    tp = add(tp, data); // add the names to the binary tree
  }
  fclose(file);
  return tp;
}

/* writes the names to the text file in preorder */
void writeFile(Node *tp) {
  FILE *file;
  //  remove("employees.txt");
  file = fopen("employees.txt", "w"); // write mode

  if (tp) {
    fprintf(file, "\n", tp->string); // rights current name
    // fputs(strcat(tp->string,\n), file);
    fseek(file, 0, SEEK_SET);  // points to end of file
    writeFile(tp->left); // recusive call to go to the left subtree
    fseek(file, 0, SEEK_SET); // points to end of file
    writeFile(tp->right); // recursive call to right subtree
  }
  fclose(file); 
}

void printFile(){
  FILE *file;
  file = fopen("employees.txt", "r");
  char data[50];
  Node *tp = NULL;
  printf("\n");
  while(fgets(data, 50, file)!=NULL){
    printf("\n", data);
  }
  fclose(file);
}
