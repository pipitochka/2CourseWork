int main(){
    int x = 10;
    while (x > 7){
        x -= 1;
    }
    for (int t = 0; t < 3; t += 1){
                x -= 1;
    }
    
    if (x < 5){
        x = 8;
    }
}