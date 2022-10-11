#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "form.h"

User user;
int users_length();
int find_by_iban(char* IBAN);
int find_by_id(int id);

int check_data_exists(char* fname) {
    if (access(fname, F_OK) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void load_data() {
    
    
    FILE *file;
    file = fopen("data", "rb");
    User read_user;
    int i=0;
    while(fread(&read_user, sizeof(read_user), 1, file)) {
        users[i] = read_user;
        i++;
    }
    fclose(file);
}

int deploy_data() {
    int length = users_length();
    FILE *file;
    file = fopen("data", "wb");
    if (file == NULL) return -1;
    for (int i=0;i<users_length();i++) {
        fwrite(&users[i], sizeof(users[i]), 1, file);
    }
    fclose(file);
    return 1;
}

void show_users() {
    
    for (int i=0;i<2;i++) {
        printf("--------------------\n");
        printf("Username : %s\n", users[i].name);
        printf("IBAN     : %s\n", users[i].IBAN);
        printf("Money    : %d\n", users[i].money);
        printf("--------------------\n");
    }

}

int login_check() {
    char username[20],
        password[20];

    printf("Username : ");
    scanf("%s",username);
    printf("Password : ");
    scanf("%s",password);

    for (int i=0; i<2; i++) {
        if ((strcmp(users[i].name,username) || strcmp(users[i].password,password))==0) {
            user = users[i];
            return users[i].id;
        }
    }
    return -1;
} 

int valid_password(){
    return 1;
}


void get_credit(){
    printf("Bakiyeniz %d\n",user.money);
}

void deposit(){
    int deposit_money;
    printf("Yatırmak istediğiniz miktarı giriniz >> ");
    scanf("%d", &deposit_money);
    user.money += deposit_money;
    users[find_by_id(user.id)].money += deposit_money;
    printf("%d miktar türk lirası hesabınıza yatırıldı.\n ",deposit_money);
    printf("Yeni bakiyeniz %d\n",user.money);
}

void withdraw(){
    int withdraw_money;
    printf("Çekmek istediğiniz miktarı giriniz >> ");
    scanf("%d", &withdraw_money);
    if(withdraw_money<=user.money){
        user.money -= withdraw_money;
        users[find_by_id(user.id)].money -= withdraw_money;
        printf("Hesabınızdan %d miktar para çektiniz.\n", withdraw_money);
    } else {
        printf("Hesap bakiyeniz yetersiz, Ana menüye yönlendirliyorsunuz...\n");
    }
}

int transfer(){
    char cur_iban[11];
    int transfer_money;
    printf("Para transferi yapmak istediğiniz hesabın IBAN ini giriniz >> ");
    scanf("%s",cur_iban);
    if (strcmp(cur_iban, user.IBAN)==0) { printf("Kendi IBAN numaranıza para göndermezsiniz.\n"); return -1; } 
    int transfer_id=find_by_iban(cur_iban);
    if (transfer_id==-1) {
        printf("Var olmayan bir iban girdiniz!! \n");
        return -1;
    }
    
    printf(" Göndermek istediğiniz miktarı giriniz >> ");
    scanf("%d",&transfer_money);
    if(transfer_money<=user.money){
        user.money -= transfer_money;
        users[find_by_id(user.id)].money -= transfer_money;
        users[transfer_id].money += transfer_money;
        printf("'%s' kullanıcının hesabından '%s' adlı kullanıcının hesabına '%d' miktarda para aktrılmıştır. \n", user.name, users[transfer_id].name, transfer_money);
        return 1;
    }
    else{
        printf("Hesap bakiyeniz yetersiz, Ana menüye yönlendirliyorsunuz...\n");
        return -1;
    }
    
}

int users_length() {
    int length = sizeof(users) / sizeof(users[0]);
    return length; 
}


int find_by_iban(char* IBAN){
    for(int i=0;i<users_length();i++){
        if(strcmp(users[i].IBAN,IBAN) == 0){
            return i;
        }
    }
    return -1;    

}

int find_by_id(int id) {
    for (int i=0;i<users_length();i++) {
        if (users[i].id == id) {
            return i;
        }
    }
    return -1;
}