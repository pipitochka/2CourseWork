int add(int* x, int y){
    *x = y;
    return 0;
}

int main(){
    int x = 5;
    add(&x, 12);
}