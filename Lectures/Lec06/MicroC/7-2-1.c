int main() {
    int arr[4];
    arr[0] = 7;
    arr[1] = 13;
    arr[2] = 9;
    arr[3] = 8;
    int *sump;
    arrsum(4, arr, &sump);
    print *sump; 
}

void arrsum(int n, int arr[], int *sump) {
    if(n > 0){
        *sump = arr[n];
        arrsum(n-1, arr, &sump);
    }
}
