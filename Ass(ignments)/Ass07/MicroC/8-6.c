void main(int month, int year) {
    int days;
    switch (month) {
        case 1:
            { days = 31; }
        case 2:
            { days = (year%4==0 ? 29 : 28); }
        case 3:
            { days = 31; } 
    }
    print days;
}