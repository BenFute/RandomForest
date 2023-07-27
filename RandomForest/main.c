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
void split_data(DataPoint* data, int num_data, int feature_index, double threshold, DataPoint** left_data, int* left_count, DataPoint** right_data, int* right_count) {
    *left_data = (DataPoint*)malloc(num_data * sizeof(DataPoint));
    *right_data = (DataPoint*)malloc(num_data * sizeof(DataPoint));
    *left_count = 0;
    *right_count = 0;
    
    for (int i = 0; i < num_data; i++) {
        DataPoint dp = data[i];
        if(dp.features[feature_index] <= threshold) {
            (*left_data)[(*left_count)++] = dp;
        } else {
            (*right_data)[(*right_count)++] = dp;
        }
    }
    //`left_data`, `left_count`, `right_data`, and `right_count` pointers have been updated to hold the split data.
}

// Function to create a decision tree
Node* create_decision_tree(DataPoint* data, int num_data, int depth) {
    //Stop recursion if we reach the maximum depth or all the data belongs to the same class
    int class_counts[2] = {0}; // Binary classification, assuming classes 0 and 1
    for (int i = 0; i < num_data; i++) {
        class_counts[data[i].label]++;
    }
    
    if (depth >= MAX_DEPTH || class_counts[0] == 0 || class_counts[1] == 0) {
        Node* leaf = (Node*)malloc(sizeof(Node));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->left_label = (class_counts[0] >= class_counts[1]) ? 0 : 1;
        leaf->right_label = leaf->left_label;
        return leaf;
    }
    
    double best_gini = INFINITY;
    int best_feature_index = -1;
    double best_threshold = 0.0;
    DataPoint* best_left_data = NULL;
    int best_left_count = 0;
    DataPoint* best_right_data = NULL;
    int best_right_count = 0;
    
    for (int i = 0; i < 2; i++) { // Assume 2 features for simplicity
        for(int j = 0; j < num_data; j++){
            double threshold = data[j].features[i];
            
            int left_count, right_count;
            DataPoint* left_data;
            DataPoint* right_data;
            
            split_data(data, num_data, i, threshold, &left_data, &left_count, &right_data, &right_count);
            
            if (left_count > 0 && right_count > 0) {
                int left_class_counts[2] = {0};
                int right_class_counts[2] = {0};
                
                for (int k = 0; k < left_count; k++) {
                    left_class_counts[left_data[k].label]++;
                }
                
                for (int k = 0; k < right_count; k++) {
                    right_class_counts[right_data[k].label]++;
                }
                
                double gini_left = calculate_gini_impurity(left_class_counts, 2);
                double gini_right = calculate_gini_impurity(right_class_counts, 2);
                double gini = ((double)left_count / num_data) * gini_left + ((double)right_count / num_data) * gini_right;
                
                if (gini < best_gini) {
                    best_gini = gini;
                    best_feature_index = i;
                    best_threshold = threshold;
                    if (best_left_data) free(best_left_data);
                    best_left_data = left_data;
                    best_left_count = left_count;
                    if (best_right_data) free(best_right_data);
                    best_right_data = right_data;
                    best_right_count = right_count;
                } else {
                    free(left_data);
                    free(right_data);
                }
            }
        }
    }
    
    if (best_feature_index == -1) { // Unable to split further
        Node* leaf = (Node*)malloc(sizeof(Node));
        leaf->left = NULL;
        leaf->right = NULL;
        leaf->left_label = (class_counts[0] >= class_counts[1]) ? 0 : 1;
        leaf->right_label = leaf->left_label;
        return leaf;
    }
    
    Node* root = (Node*)malloc(sizeof(Node));
    root->feature_index = best_feature_index;
    root->threshold = best_threshold;
    root->left = create_decision_tree(best_left_data, best_left_count, depth);
    root->right = create_decision_tree(best_right_data, best_left_count, depth);
    return root;

}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
