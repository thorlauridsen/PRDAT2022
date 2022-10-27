// micro-C 7.2.(iii)

void main() {

  int arr[7];
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 1;
  arr[3] = 1;
  arr[4] = 1;
  arr[5] = 2;
  arr[6] = 0;

  int freq[4];

  int n;
  n = 7;
  int max;
  max = 3;

  histogram(n, arr, max, freq);

  printarr(max+1, freq);
}

void histogram(int n, int ns[], int max, int freq[]){
  int i;
  for(i = 0; i <= max; i = i + 1) {
    freq[i] = 0;
  }
  for(i = 0; i < n; i = i + 1) {
    freq[ns[i]] = freq[ns[i]] + 1;
  }
}



void printarr(int size, int arr[]) {
  int i;
  for(i = 0; i < size; i = i + 1) {
    print arr[i];
  }
}