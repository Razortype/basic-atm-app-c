/*

* 2 Tane kullanıcısı olan bir banka
* Kullanıcılar Structure formatında ve list of Class şeklinde tutulacak
* Kullanıcı arayüzü olacak (while console print)

1) bakiye sorgulama
2) para yatırma
3) para çekme
4) havale
5) yazdır
0) çıkış

*/
#include <stdio.h>
#include "helpers.h"

const char* screen = "\n1) Bakiye Sorgulama\n2) Para Yatırma\n3) Para Çekme\n4) Havale\n5) Kullanıcılar\n0) Çıkış\n";

void display_screen() {
    printf("-----------------------------");
    printf("%s",screen);
    printf("-----------------------------\n");
}

int eval_option(int islem) {
    switch (islem)
    {
    case 1:
        get_credit();
        break;
    case 2:
        deposit();
        deploy_data();
        break;
    case 3:
        withdraw();
        deploy_data();
        break;
    case 4:
        transfer();
        deploy_data();
        break;
    case 5:
        show_users();
        break;
    case 0:
        return 1;
    default:
        printf("Yanlış opsiyon girildi : %d\n",islem);
        break;
    }
    return 0;
}

int main() {
    
    int islem;
    int flag = 1;
    int user_id;

    if (check_data_exists("data")) {
        load_data();
        printf("Veriler başarıyla yüklendi.\n");
    } else {
        printf("Veri dosyası bulunamadı!\n");
        return 0;
    }   

    user_id = login_check();
    if(user_id==-1){ 
        printf("Kullanıcı adı ve(ya) paralosı yanlış.");
        return 0; 
    } else {
        printf("Başarı ile giriş yapıldı.\n");
    }
    
    while (flag)
    {
        display_screen();
        printf("Yapmak istediginiz islemi seciniz : ");
        scanf("%d" ,&islem);
        if (eval_option(islem)) { flag=0; }
    }

    return 0;
}
