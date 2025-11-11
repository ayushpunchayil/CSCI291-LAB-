#include <stdio.h>
#include <stdbool.h>
#define SIZE 24
#define nRows 8
#define nCols 3

// PROTOTYPES
void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
void set_array(int arr[], int length);
void rem_align(int arr[], int *length, int pos);
void insert_align(int arr[], int *length, int pos, int value);
void reshape(int arr[], int length, int arr2d[][nCols]);
void print_trans_matrix(int arr2d[][nCols]);
bool found_duplicate(int arr[], int length);
void flip_array(int arr[], int length);

int main() {
    int arr[SIZE];
    int arr2d[nRows][nCols];
    int length = 10; // starting length

    set_array(arr, length); // fills array with values 0–9
    printf("Initial array:\n");
    print_array(arr, length);

    rem_align(arr, &length, 2); // removes value at index 2
    printf("\nArray after removing index 2:\n");
    print_array(arr, length);

    insert_align(arr, &length, 2, 80); // inserts 80 at index 2
    printf("\nArray after inserting 80 at index 2:\n");
    print_array(arr, length);

    reshape(arr, nRows * nCols, arr2d); // reshape into 2D
    printf("\n2D reshaped array:\n");
    print_matrix(arr2d, nRows);

    printf("\nTranspose of 2D array:\n");
    print_trans_matrix(arr2d); // print transpose

    if (found_duplicate(arr, length))
        printf("\nDuplicate found!\n");
    else
        printf("\nNo duplicates found.\n");

    flip_array(arr, length); // reverse array
    printf("\nArray after flipping:\n");
    print_array(arr, length);

    return 0;
}

// prints 1D array
void print_array(int array[], int length) {
    for (int i = 0; i < length; i++)
        printf("array[%d] = %d\n", i, array[i]);
}

// prints 2D matrix
void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++)
            printf("mat[%d][%d] = %d\n", i, j, mat[i][j]);
    }
}

// fills array with its indices
void set_array(int arr[], int length) {
    for (int i = 0; i < length; i++)
        arr[i] = i;
}

// removes element and shifts others up
void rem_align(int arr[], int *length, int pos) {
    if (pos < 0 || pos >= *length) {
        printf("Invalid position, please try again.\n");
        return;
    }
    for (int i = pos; i < *length - 1; i++)
        arr[i] = arr[i + 1];
    (*length)--;
}

// inserts element and shifts others down
void insert_align(int arr[], int *length, int pos, int value) {
    if (pos < 0 || pos > *length) {
        printf("Invalid position, cannot insert.\n");
        return;
    }
    for (int i = *length; i > pos; i--)
        arr[i] = arr[i - 1];
    arr[pos] = value;
    (*length)++;
}

// converts 1D to 2D array
void reshape(int arr[], int length, int arr2d[][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: length not matching | expected %d elements.\n", nRows * nCols);
        return;
    }
    int index = 0;
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = arr[index++];
        }
    }
}

// prints transpose of matrix
void print_trans_matrix(int arr2d[][nCols]) {
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++)
            printf("%4d ", arr2d[i][j]);
        printf("\n");
    }
}

// checks for duplicates
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j])
                return true;
        }
    }
    return false;
}

// reverses array
void flip_array(int arr[], int length) {
    for (int i = 0, j = length - 1; i < j; i++, j--) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
