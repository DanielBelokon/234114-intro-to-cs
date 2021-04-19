#include <stdio.h>
#include <math.h>

#define EPSILON 0.000001 // the threashold for considering a number as equel to 0 (when distance from 0 smaller than the value)
#define ISZERO(a) ((a < EPSILON) && (a > -EPSILON))

int main()
{
    double a, b, c; // Coeficients
    double rootone = 0, roottwo = 0;
    double discriminant;

    // loop until break (print the request until valid input)
    while (1)
    {
        printf("Enter the coefficients of a polynomial:\n");

        // check for valid input
        if ((scanf(" %lf %lf %lf", &a, &b, &c) != 3))
            return 1;

        // a must be != 0, if it is loop again
        if (!ISZERO(a))
        {
            // if no solutions over R (root of a negative dscrm), print no roots
            if ((discriminant = b * b - 4 * a * c) <= -EPSILON)
                printf("There are no roots\n");

            // if discriminant is effectively 0, print one solution
            else if (ISZERO(discriminant))
            {
                rootone = (0 - b) / (2 * a);
                if (ISZERO(rootone))
                    rootone = 0;

                printf("The root is %.2lf\n", rootone);
            }
            // if neither -> dscrm is positive, print both solutions
            else
            {
                double dscrmroot = sqrt(discriminant);
                rootone = (-b - dscrmroot) / (2 * a); // the smaller root goes into rootone
                roottwo = (-b + dscrmroot) / (2 * a);

                if (ISZERO(rootone))
                    rootone = 0;
                if (ISZERO(roottwo))
                    roottwo = 0;

                printf("The roots are %.2lf, %.2lf\n", rootone, roottwo);
            }

            break; // if we got this far, exit the loop
        }
    }

    return 0;
}