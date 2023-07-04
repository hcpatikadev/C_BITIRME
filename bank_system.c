#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME_LENGTH 50

// Kullanıcı yapısı
struct User {
    int accountNumber;
    char name[MAX_NAME_LENGTH];
    double balance;
};

// Kullanıcılar dizisi
struct User users[MAX_USERS];
int numUsers = 0;

// Kullanıcı kayıt işlemi
void createUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maksimum kullanıcı sayısına ulaşıldı!\n");
        return;
    }

    struct User newUser;

    printf("Adınız: ");
    scanf("%s", newUser.name);

    printf("Hesap numaranız: ");
    scanf("%d", &newUser.accountNumber);

    printf("Başlangıç bakiyeniz: ");
    scanf("%lf", &newUser.balance);

    users[numUsers++] = newUser;

    printf("Kullanıcı oluşturuldu.\n");
}

// Kullanıcıyı bulma
struct User* findUser(int accountNumber) {
    for (int i = 0; i < numUsers; i++) {
        if (users[i].accountNumber == accountNumber) {
            return &users[i];
        }
    }
    return NULL;
}

// Hesap bakiyesini görüntüleme
void viewBalance() {
    int accountNumber;
    printf("Hesap numaranızı girin: ");
    scanf("%d", &accountNumber);

    struct User* user = findUser(accountNumber);
    if (user != NULL) {
        printf("Hesap bakiyeniz: %.2lf\n", user->balance);
    } else {
        printf("Kullanıcı bulunamadı.\n");
    }
}

// Hesaba para yatırma
void deposit() {
    int accountNumber;
    double amount;
    printf("Hesap numaranızı girin: ");
    scanf("%d", &accountNumber);

    struct User* user = findUser(accountNumber);
    if (user != NULL) {
        printf("Yatırmak istediğiniz tutarı girin: ");
        scanf("%lf", &amount);

        user->balance += amount;

        printf("%.2lf TL hesabınıza yatırıldı. Yeni bakiyeniz: %.2lf TL\n", amount, user->balance);
    } else {
        printf("Kullanıcı bulunamadı.\n");
    }
}

// Hesaptan para çekme
void withdraw() {
    int accountNumber;
    double amount;
    printf("Hesap numaranızı girin: ");
    scanf("%d", &accountNumber);

    struct User* user = findUser(accountNumber);
    if (user != NULL) {
        printf("Çekmek istediğiniz tutarı girin: ");
        scanf("%lf", &amount);

        if (amount <= user->balance) {
            user->balance -= amount;
            printf("%.2lf TL hesabınızdan çekildi. Yeni bakiyeniz: %.2lf TL\n", amount, user->balance);
        } else {
            printf("Yetersiz bakiye. İşlem gerçekleştirilemedi.\n");
        }
    } else {
        printf("Kullanıcı bulunamadı.\n");
    }
}

// Kullanıcıları dosyaya kaydetme
void saveUsersToFile() {
    FILE* file = fopen("users.txt", "w");
    if (file == NULL) {
        printf("Dosya oluşturulamadı.\n");
        return;
    }

    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %d %.2lf\n", users[i].name, users[i].accountNumber, users[i].balance);
    }

    fclose(file);
    printf("Kullanıcılar dosyaya kaydedildi.\n");
}

// Kullanıcıları dosyadan yükleme
void loadUsersFromFile() {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadı.\n");
        return;
    }

    numUsers = 0;
    while (fscanf(file, "%s %d %lf\n", users[numUsers].name, &users[numUsers].accountNumber, &users[numUsers].balance) != EOF) {
        numUsers++;
    }

    fclose(file);
    printf("Kullanıcılar dosyadan yüklendi.\n");
}

// Kullanıcı arayüzü
void displayMenu() {
    printf("\n-- Banka Hesap Yönetimi Sistemi --\n");
    printf("1. Kullanıcı Kaydı Oluştur\n");
    printf("2. Bakiye Görüntüle\n");
    printf("3. Para Yatırma\n");
    printf("4. Para Çekme\n");
    printf("5. Kullanıcıları Dosyaya Kaydet\n");
    printf("6. Kullanıcıları Dosyadan Yükle\n");
    printf("0. Çıkış\n");
    printf("İşlem seçin: ");
}

int main() {
    int choice;

    loadUsersFromFile(); // Kullanıcıları dosyadan yükleme

    do {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createUser();
                break;
            case 2:
                viewBalance();
                break;
            case 3:
                deposit();
                break;
            case 4:
                withdraw();
                break;
            case 5:
                saveUsersToFile();
                break;
            case 6:
                loadUsersFromFile();
                break;
            case 0:
                printf("Çıkış yapılıyor.\n");
                break;
            default:
                printf("Geçersiz işlem. Tekrar deneyin.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
