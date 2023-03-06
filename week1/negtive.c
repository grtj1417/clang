#include <stdio.h>
// int main()
// {
//     unsigned int list[10] = {1,5,5,7,1,4,7,6,8,9};
//     for(int i = 0; i < 9; i++){
//         unsigned int count = 0, a = 0;
//         a = list[i];
//         for(int j = 0; j < 9; j++){
//             unsigned int b;
//             b = list[j];
//             if(a == b){
//                 count++;
//                 if(count == 2)
//                 printf("%d",a);
//                 continue;
//             }
//         }
//     }
//     return 0;
// }
int main()
{
    unsigned int list[3] = {1,5,5};
    for(int i = 0; i < 2; i++){
        unsigned int count = 0, temp = 0;
        for(int j = 0; j < 2; j++){
            temp = list[i];
            temp ^= list[j];
            if(temp == 0)
                count++;
                if(count == 2)
                printf("%d",list[i]);
        }
    }
}