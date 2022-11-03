void main(int n) {
	if (n > 20) {
		n = 20; 
	}
	int arr[20];
	int sump;
	sump = 0;
	arrsum(n, squares(n, arr), &sump);
	print sump;
}

void arrsum(int n, int arr[], int *sump) {
    if(n > 0){
        *sump = (*sump + arr[n-1]);
        arrsum(n-1, arr, sump);
    }
}

void squares(int n, int arr[]) {
	if (n < 1) {
		return arr;
	} else {
		arr[n] = n * n;
		squares(n - 1, arr);
	}
}