int main() {
    int arr[4];
    arr[0] = 7;
    arr[1] = 13;
    arr[2] = 9;
    arr[3] = 8;
    int sump;
    sump = 0;
    arrsum(4, arr, &sump);
    print sump;
}

//Using recursion
void arrsum(int n, int arr[], int *sump) {
    if(n > 0){
        *sump = (*sump + arr[n-1]);
        arrsum(n-1, arr, sump);
    }
}

/*void arrsum(int n, int arr[], int *sump) {
    int i;
    i = 0;
    while (i < n) {
        *sump = (*sump + arr[i]);
        i = i + 1;
    }
}*/