/* Simple command-line calculator */
#include <stdio.h>

int main(void)
{
    double first, second;
    char operator;

    printf("Enter an expression (e.g. 12.5 * 4): ");
    if (scanf("%lf %c %lf", &first, &operator, &second) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    switch (operator) {
    case '+':
        printf("Result: %.2f\n", first + second);
        break;
    case '-':
        printf("Result: %.2f\n", first - second);
        break;
    case '*':
        printf("Result: %.2f\n", first * second);
        break;
    case '/':
        if (second == 0.0) {
            fprintf(stderr, "Error: division by zero.\n");
            return 1;
        }
        printf("Result: %.2f\n", first / second);
        break;
    default:
        fprintf(stderr, "Invalid operator. Use +, -, *, or /.\n");
        return 1;
    }

    return 0;
}
