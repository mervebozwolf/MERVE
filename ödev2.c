#include<stdio.h>
#include<stdlib.h>

#define FILE_NAME "outputs.dat"

typedef struct {
    int id;
    char name[20];
    float price;
    int stock;
} Product;

void showMenu();

void addProduct();

void updateProduct();

void getProducts();

void deleteProduct();

int main() {
    showMenu();
    return 0;
}

void showMenu() {
    int choice;
    while (1) {
        printf("\n--- Menu ---\n");
        printf("1 - urun ekle\n");
        printf("2 - urun stogunu güncelle\n");
        printf("3 - urunleri listele\n");
        printf("4 - urun sil\n");
        printf("5 - cikis\n");

        printf("seciminizi girin: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                getProducts();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("gecersiz secim. tekrar deneyin.\n");
        }
    }
}

void addProduct() {
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file) {
        printf("Dosya açılamadı!");
        return;
    }

    Product p;

    printf("ürün ID girin: ");
    scanf("%d", &p.id);
    printf("ürün adi girin: ");
    scanf("%s", p.name);
    printf("ürün fiyati girin: ");
    scanf("%f", &p.price);
    printf("ürün stok adedini: ");
    scanf("%d", &p.stock);

    if (fwrite(&p, sizeof(Product), 1, file) == 1) {
        printf("Ürün eklendi!\n");
    } else {
        printf("Ürün eklenirken hata oluştu.\n");
    }

    fclose(file);
}

void updateProduct() {
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file) {
        printf("Dosya açılamadı!");
        return;
    }

    Product p;
    int id, found = 0;

    printf("güncellemek için ürün ID girin: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id == id) {
            found = 1;

            printf("yeni stok degerini girin: ");
            scanf("%d", &p.stock);

            fseek(file, -sizeof(Product), SEEK_CUR);

            if (fwrite(&p, sizeof(Product), 1, file) == 1) {
                printf("ürün stogu güncellendi!\n");
            } else {
                printf("ürün güncellenirken hata olustu.\n");
            }

            break;
        }
    }

    if (!found) {
        printf("urun bulunamadı.\n");
    }

    fclose(file);
}

void getProducts() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file) {
        printf("Dosya açilamadi!");
        return;
    }

    Product p;
    int id, found = 0;

    printf("aramak için urun kimligini girin: ");
    scanf("%d", &id);

    if (id == 0) {
        while (fread(&p, sizeof(Product), 1, file)) {
            printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", p.id, p.name, p.price, p.stock);
            found++;
        }
    } else {
        while (fread(&p, sizeof(Product), 1, file)) {
            if (p.id == id) {
                printf("ID: %d | Name: %s | Price: %.2f | Stock: %d\n", p.id, p.name, p.price, p.stock);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("ürün bulunamadi\n");
    }

    fclose(file);
}

void deleteProduct() {
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (!file || !temp) {
        printf("Failed to open files!");
        if (file) fclose(file);
        if (temp) fclose(temp);
        return;
    }

    Product p;
    int id, found = 0;
    printf("silinecek urun ID girin: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(Product), 1, file)) {
        if (p.id == id) {
            found = 1;
            continue;
        }

        fwrite(&p, sizeof(Product), 1, temp);
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("ürün silindi.\n");
    } else {
        remove("temp.dat");
        printf("ürün bulunamadi.\n");
    }
}
