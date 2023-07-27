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
//This function is used during the process of building the decision trees in the Random Forest to find the best feature and threshold to split the data at each node.
//The goal is to find the split that minimizes the Gini impurity in the resulting child nodes, thereby improving the overall quality of the decision tree and the Random Forest
double calculate_gini_impurity(int* class_counts, int num_classes) {
    double impurity = 1.0;
    int total_samples = 0;
    
    for (int i = 0; i < num_classes; i++) {
        total_samples += class_counts[i];    //Sum of class_counts
    }
    
    for (int i = 0; i < num_classes; i++) {
        double p_i = (double)class_counts[i] / total_samples; // Compute the probability of an element belonging to class `i`
        impurity -= p_i * p_i;  //subtract the square of the probability from the impurity.
    }
    
    return impurity;
}

// Function to split the data based on a feature index and threshold value
// This function is used during the construction of decision trees when determining the best split at each node.
void split_data(DataPoint* data, int num_data, int feature_index, double threshold, DataPoint** left_data, int* left_count, DataPoint** right_data, int* right_count) {
    *left_data = (DataPoint*)malloc(num_data * sizeof(DataPoint));  //The left data points after the split
    *right_data = (DataPoint*)malloc(num_data * sizeof(DataPoint));  //The right data points after the split
    *left_count = 0;
    *right_count = 0;
    
    for (int i = 0; i < num_data; i++) {
        DataPoint dp = data[i];
        //All data points with feature values less than or equal to the threshold will be placed in the left data group, and all data points with feature values greater than the threshold will be placed in the right data group
        if(dp.features[feature_index] <= threshold) {
            (*left_data)[(*left_count)++] = dp;
        } else {
            (*right_data)[(*right_count)++] = dp;
        }
    }
    //`left_data`, `left_count`, `right_data`, and `right_count` pointers have been updated to hold the split data.
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
