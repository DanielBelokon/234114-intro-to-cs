#include <stdio.h>
#include <math.h>

#define EPSILON 0.000001 // the threashold for considering a number as equel to 0 (when distance from 0 smaller than the value)

int main()
{
    double a, b, c; // Coeficients
    double rootone = 0, roottwo = 0;
    double discriminant;

    // loop until break (print the request until valid input)
    while (1)
    {
        printf("Enter the coefficients of a polynomial:\n");

        // true when scanned all 3 input doubles AND 'a' (coeficient of x^2) is not defined 0.
        if ((scanf(" %lf %lf %lf", &a, &b, &c) == 3) && (a > EPSILON || a < -EPSILON))
        {
            // if no solutions over R (root of a negative dscrm), print no roots
            if ((discriminant = b * b - 4 * a * c) < -EPSILON)
                printf("There are no roots\n");

            // if discriminant is effectively 0, print one solution
            else if (discriminant >= -EPSILON && discriminant <= EPSILON)
            {
                rootone = (0 - b) / (2 * a);
                printf("The root is %.2lf\n", rootone);
            }
            // if neither -> dscrm is positive, print both solutions
            else
            {
                double dscrmroot = sqrt(discriminant);
                rootone = (-b - dscrmroot) / (2 * a); // the smaller root goes into rootone
                roottwo = (-b + dscrmroot) / (2 * a);
                printf("The roots are %.2lf, %.2lf\n", rootone, roottwo);
            }
            break;
        }
    }

    return 0;
}