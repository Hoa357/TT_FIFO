#include "stdio.h"
#include "conio.h"
#include "math.h"
#include "string.h"
#include "stdlib.h"

// NHAP CHUOI THAM CHIEU
// Nhap so phan tu cua chuoi tham bien
int NhapSoPhanTu()
{
	int n;
	do
	{
		printf("\nNhap so phan tu cua chuoi tham chieu: ");
		scanf("%d", &n);
	} while (n <= 0);
	return n;
}

// Nhap Thu Cong
int NhapChuoiThamChieu(int ctc[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("Nhap phan tu thu %d: ", i + 1);
		scanf("%d", &ctc[i]);
	}
	return 0;
}

// Nhap Ngau Nhien
int NhapRandom(int ctc[], int n)
{
	for (int i = 0; i < n; i++)
	{
		ctc[i] = rand() % 10;  // Gioi han gia tri từ 0-9
	}
	return 0;
}

// Doc File
int DocFile(int ctc[], int& n)
{
	char filename[30];
	printf("\nBan muon mo file nao: ");
	scanf("%s", &filename);
	FILE* f = fopen(filename, "rt");
	if (f == NULL)
	{
		printf("\nKHONG MO DUOC FILE!");
		return 0;
	}
	fscanf(f, "%d\n", &n);
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%d#", &ctc[i]);
	}
	fclose(f);
	return 0;
}

// XUAT CHUOI THAM CHIEU
int XuatChuoi(int tc[], int n)
{
	printf("\nChuoi tham chieu: ");
	for (int i = 0; i < n; i++)
		printf("%3d", tc[i]);
	printf("\n");
	return 0;
}

// THUAT TOAN FIFO
int FIFO(int ctc[], int n, int f)
{
	int pagefault[100];
	int kq[100][100];
	int i, j, k, pf = 0, count = 0, a[10];
	// Cho cac gia tri ban dau cua mang la -1
	for (i = 0; i < f; i++)
	{
		a[i] = -1;
	}


	// In ket qua theo danh sach
	printf("\n\tQUA TRINH THAY THE TRANG THEO THUAT TOAN FIFO \n\n");
	printf(" STT |\t CTC\t|\tTrang Thai Frame\t| Page-Fault\n");
	printf(" ----|\t ---\t|\t----------------\t| ----------\n");

	// Xu ly va In KQ
	for (i = 0; i < n; i++)
	{
		// Kiem tra tham chieu da co trong bo nho chua
		for (k = 0; k < f; k++)
		{
			if (a[k] == ctc[i])
				break;
		}

		// Neu k = f tuc la tham so chua co trong bo nho
		if (k == f)
		{
			a[count++] = ctc[i];
			pf++;
		}


		// In STT và Tham Chieu
		printf("\n %2d  |%6d\t|\t", i + 1, ctc[i]);

		// In Trang Thai Frames
		for (j = 0; j < f; j++)
		{
			printf("%2d\t", a[j]);
			kq[j][i] = a[j];
		}

		// In Page-fault
		if (k == f)
		{
			printf("| PF so %d", pf);
			pagefault[i] = pf;
		}
		else
		{
			pagefault[i] = 0;
		}

		// Neu count bang so khung trang thi quay tro lai trang 0 dau tien
		if (count == f)
			count = 0;
	}
	printf("\n\nSo loi trang su dung thuat toan FIFO la %d\n\n", pf);

	// In ket qua theo bang
	printf("\n\t\t\tBANG QUA TRINH THAY THE TRANG THEO THUAT TOAN FIFO \n\n");

	// In chuoi tham chieu
	printf("|");
	for (i = 0; i < n; i++)
	{
		printf(" %2d |", ctc[i]);
	}
	printf("\n\n");

	// In bang FIFO
	for (i = 0; i < f; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("-----");
		}
		printf("-\n");
		printf("|");
		for (j = 0; j < n; j++)
		{
			if ((kq[i][j] == -1)||(pagefault[j] == 0))
				printf("    |");
			else
				printf(" %2d |", kq[i][j]);

		}
		printf("\n");
	}
	for (j = 0; j < n; j++)
	{
		printf("-----");
	}
	printf("-\n\n");

	// In Page-fault
	printf("|");
	for (i = 0; i < n; i++)
	{
		if (pagefault[i] == 0)
			printf("    |");
		else
			printf(" %2d |", pagefault[i]);
	}
	return 0;
}


// MENU
int menu()
{
	printf("\n\n===================================");
	printf("\n\t  CHUONG TRINH");
	printf("\n===================================");
	printf("\n 1. Nhap gia tri tu ban phim.");
	printf("\n 2. Lay gia tri ngau nhien.");
	printf("\n 3. Doc gia tri tu file.");
	printf("\n 4. Thuat toan FIFO.");
	printf("\n 0. Thoat.");
	printf("\n==================================\n");
	return 0;
}

// CHUONG TRINH CHINH
int main()
{
	int ctc[100]; // Chuoi tham chieu
	int n; // So phan tu cua chuoi tham chieu
	//int kq[100][100];
	int selection;
	int f; // Frames
	while (true)
	{
		menu();
		printf("Nhap lua chon cua ban: ");
		scanf("%d", &selection);
		switch (selection)
		{
		case 1:
			n = NhapSoPhanTu();
			NhapChuoiThamChieu(ctc, n);
			XuatChuoi(ctc, n);
			break;
		case 2:
			n = NhapSoPhanTu();
			NhapRandom(ctc, n);
			XuatChuoi(ctc, n);
			break;
		case 3:
			DocFile(ctc, n);
			XuatChuoi(ctc, n);
			break;
		case 4:
			do
			{
				printf("\nNhap so frame: ");
				scanf("%d", &f);
			} while (f <= 0);
			FIFO(ctc, n, f);
			break;
		default:
			return 0;
		}
	}
}



