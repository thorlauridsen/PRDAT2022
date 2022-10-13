// micro-C 7.2.(iii)

void main() {

  int arr[6];
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 1;
  arr[3] = 1;
  arr[4] = 1;
  arr[5] = 2;
  arr[6] = 0;

  int freq[3];
  
  int max; 
  max = 3;

  histogram(7, arr, max, freq);
  printarr(max, freq);
}

void histogram(int n, int ns[], int max, int freq[]) {
  int i;
  i = 0;
  while(i < max)
  {
    freq[i] = 0;
    i = i + 1;
  }

  i = 0;
  while(i < n)
  {
    freq[ns[i]] = freq[ns[i]] + 1;
    i = i + 1;
  }
}


void printarr(int len, int a[]) {
  int i; 
  i = 0; 
  while (i < len) { 
    print a[i]; 
    i=i+1; 
  } 
}