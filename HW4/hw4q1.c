
/*=========================================================================
  Constants and definitions:
==========================================================================*/
#include <stdio.h>
#include <math.h>

#define N 50
#define M 50



/* put your #defines and typedefs here*/
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);
int sum_rect(int integral_image[][M], int rect[4]);
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);
void print_array(int a[N][M], int n, int m);


/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
 -------------------------------------------------------------------------*/


int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void compute_integral_image(int image[][M], int n, int m, int integral_image[][M])
{

    int above, left, remove;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            above = left = remove = 0;
            if (row > 0)
                above = integral_image[row - 1][col];
            if (col > 0)
                left = integral_image[row][col - 1];
            if (col > 0 && row > 0)
                remove = integral_image[row - 1][col - 1];

            integral_image[row][col] = image[row][col] + above + left - remove;
        }
    }
}
int sum_rect(int integral_image[][M], int rect[4])
{
    int sum = 0;
    sum += integral_image[rect[2]][rect[3]];

    if (rect[0] > 0)
        sum -= integral_image[rect[0] - 1][rect[3]];

    if (rect[1] > 0)
        sum -= integral_image[rect[2]][rect[1] - 1];

    if (rect[1] > 0 && rect[0] > 0)
        sum += integral_image[rect[0] - 1][rect[1] - 1];

    return sum;
}

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M])
{
    int rect[4];
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < m; col++)
        {
            rect[0] = row - h / 2;
            rect[1] = col - w / 2;

            rect[2] = row + (row < n - (h / 2)) * (h / 2);
            rect[3] = col + (col < m - (w / 2)) * (w / 2);
            average[row][col] = round(sum_rect(integral_image, rect) / (double)(h * w));
        }
    }
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m-1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}
