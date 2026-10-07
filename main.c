#include <stdio.h>

/* Cau truc tai khoan dang ky */
struct UserAccount {
    int account_id;
    int plan_type;       /* 0: Free, 1: Standard, 2: Premium */
    int monthly_fee;
    int remaining_days;
    int active_devices;
};

int main(void) {
    struct UserAccount accounts[100];
    struct UserAccount key;          /* bien tam cho insertion sort */
    int n = 0;
    int i, j, c;
    int mrr_before = 0;
    int mrr_after = 0;
    int downgraded_count = 0;
    int capped_count = 0;
    int max_devices;
    int expired;

    /* ===== BUOC 1: NHAP N, bat buoc 1 <= N <= 100 ===== */
    while (n < 1 || n > 100) {
        printf("Nhap so luong tai khoan N (1-100): ");
        if (scanf("%d", &n) != 1) {
            printf("Loi: N phai la so nguyen!\n");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
            n = 0;
        } else if (n < 1 || n > 100) {
            printf("Loi: N phai nam trong khoang [1, 100]!\n");
        }
    }

    /* ===== BUOC 2: NHAP DU LIEU TUNG TAI KHOAN =====
       plan_type bat buoc thuoc [0, 2]. Cac truong con lai chi can la so nguyen,
       vi remaining_days am hoac active_devices rac la du lieu can kiem toan. */
    for (i = 0; i < n; i++) {
        printf("\n--- Tai khoan thu %d ---\n", i + 1);

        printf("account_id: ");
        while (scanf("%d", &accounts[i].account_id) != 1) {
            printf("Loi: phai la so nguyen! Nhap lai: ");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
        }

        printf("plan_type (0: Free, 1: Standard, 2: Premium): ");
        while (scanf("%d", &accounts[i].plan_type) != 1 ||
               accounts[i].plan_type < 0 || accounts[i].plan_type > 2) {
            printf("Loi: plan_type phai thuoc [0, 2]! Nhap lai: ");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
        }

        printf("monthly_fee (VND): ");
        while (scanf("%d", &accounts[i].monthly_fee) != 1) {
            printf("Loi: phai la so nguyen! Nhap lai: ");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
        }

        printf("remaining_days (co the am): ");
        while (scanf("%d", &accounts[i].remaining_days) != 1) {
            printf("Loi: phai la so nguyen! Nhap lai: ");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
        }

        printf("active_devices: ");
        while (scanf("%d", &accounts[i].active_devices) != 1) {
            printf("Loi: phai la so nguyen! Nhap lai: ");
            while ((c = getchar()) != '\n' && c != EOF) {
            }
            if (c == EOF) {
                return 1;
            }
        }
    }

    /* ===== BUOC 3: KIEM TOAN TUNG TAI KHOAN ===== */
    for (i = 0; i < n; i++) {
        /* MRR truoc kiem toan: tinh theo phi chuan cua goi dang khai bao,
           khong tin monthly_fee nhap vao vi co the sai lech */
        if (accounts[i].plan_type == 1) {
            mrr_before += 120000;
        } else if (accounts[i].plan_type == 2) {
            mrr_before += 300000;
        }

        /* Quy tac het han: remaining_days <= 0 (ke ca so am) thi ha ve Free.
           Chi dem ha cap khi goi thay doi that su (tu tra phi xuong Free) */
        expired = accounts[i].remaining_days <= 0;
        if (expired) {
            if (accounts[i].plan_type > 0) {
                accounts[i].plan_type = 0;
                downgraded_count++;
            }
            accounts[i].remaining_days = 0;
        }

        /* Chuan hoa monthly_fee va gioi han thiet bi theo plan_type SAU ha cap */
        if (accounts[i].plan_type == 2) {
            accounts[i].monthly_fee = 300000;
            max_devices = 5;
        } else if (accounts[i].plan_type == 1) {
            accounts[i].monthly_fee = 120000;
            max_devices = 2;
        } else {
            accounts[i].monthly_fee = 0;
            max_devices = 1;
        }

        /* Du lieu rac: so thiet bi <= 0 thi gan toi thieu la 1 */
        if (accounts[i].active_devices <= 0) {
            accounts[i].active_devices = 1;
        }

        /* Quy tac vuot han thiet bi: chi ap dung cho tai khoan CHUA het han */
        if (!expired && accounts[i].active_devices > max_devices) {
            accounts[i].active_devices = max_devices;
            capped_count++;
        }

        mrr_after += accounts[i].monthly_fee;
    }

    /* ===== BUOC 4: SAP XEP TAI CHO (INSERTION SORT, ON DINH) =====
       Sap monthly_fee giam dan: tra phi (phi > 0) len dau, Free (phi = 0) xuong cuoi.
       So sanh strict "<" nen hai phan tu cung phi khong bi hoan doi -> giu thu tu ban dau.
       Dieu kien j >= 0 dat truoc de khong truy cap accounts[-1].
       Neu moi phi bang nhau (toan Free hoac toan cung goi) vong while khong chay. */
    for (i = 1; i < n; i++) {
        key = accounts[i];
        j = i - 1;
        while (j >= 0 && accounts[j].monthly_fee < key.monthly_fee) {
            accounts[j + 1] = accounts[j];
            j--;
        }
        accounts[j + 1] = key;
    }

    /* ===== BUOC 5: IN BANG KET QUA VA BAO CAO MRR ===== */
    printf("\n=== KET QUA KIEM TOAN TAI KHOAN ===\n");
    printf("%-12s %-10s %-14s %-16s %-14s\n",
           "ACCOUNT_ID", "PLAN", "PHI THANG", "NGAY CON LAI", "SO THIET BI");
    printf("--------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%-12d %-10d %-14d %-16d %-14d\n",
               accounts[i].account_id,
               accounts[i].plan_type,
               accounts[i].monthly_fee,
               accounts[i].remaining_days,
               accounts[i].active_devices);
    }
    printf("--------------------------------------------------------------------\n");
    printf("MRR truoc kiem toan : %d VND\n", mrr_before);
    printf("MRR sau kiem toan   : %d VND\n", mrr_after);
    printf("Chenh lech MRR      : %d VND\n", mrr_after - mrr_before);
    printf("So tai khoan bi ha cap ve Free      : %d\n", downgraded_count);
    printf("So tai khoan bi cat giam thiet bi   : %d\n", capped_count);

    return 0;
}