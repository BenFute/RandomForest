//A simplified decision tree that can handle binary classificiation tasks.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUM_TREES 100
#define MAX_DEPTH 10

// Structure to hold the dataset
typedef struct {
    double features[2]; // Assume we have two features for simplicity
    int label;  // Binary classification label (0 or 1)
} DataPoint;

// Decision tree node
typedef struct Node {
    int feature_index; //Index of the feature to split on
    double threshold; // Value to split the feature on
    int left_label; // Label if left child is a leaf node
    int right_label; //Label if right child is a leaf node
    struct Node* left;
    struct Node* right;
} Node;

//Gini impurity is one the measures used to evaluate how "impure" a node is in a decision tree.  In the context of Random Forests, it is used to access the quality of a split during the tree-building process.
//This funciton is used during hte process of building the deciision trees in the Random Forest to find the best feature and threshold to split the data at each node.
//The goal is to find the split that minimizes the Gini impurity in the resulting child nodes, thereby improving the overall quality of the decision tree and the Random Forest
double calculate_gini_impurity(int* class_counts, int num_classes) {
    double impurity = 1.0;
    int total_samples = 0;
    
    //Sum of class_counts
    for (int i = 0; i < num_classes; i++) {
        total_samples += class_counts[i];
    }
    
    for (int i = 0; i < num_classes; i++) {
        double p_i = (double)class_counts[i] / total_samples; // Compute the probability of an element belonging to class `i`
        impurity -= p_i * p_i;  //subtract the square of the probability from the impurity.
    }
    
    return impurity;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
