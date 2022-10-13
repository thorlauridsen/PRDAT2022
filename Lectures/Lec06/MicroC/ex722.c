void main(int n) {
  int arr[20];
  print n;
}

void squares(int n, int arr[]) {
	if (n < 1) {
		return arr;
	} else {
		arr[n] = n * n;
		squares(n - 1, arr);
	}
}