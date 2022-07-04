#include <stdio.h>


int main(){

    int array[] = {1,2,4,8,16,32};
    int n = 6;

    int ans = sum(array, n);
    printf("%d", ans);

}

int sum(int arr[], int n){
    
    int s = 0;
    for(int i=0; i<n; i++){
        s = s + arr[i];
    }
    return s;
}