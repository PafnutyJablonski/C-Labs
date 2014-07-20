#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

int main()
{
    int m, n, i, j, Prime;
    scanf("%i", &m);

    for (i = 2, n = 0; n < m; ++i)
    {
        Prime = TRUE;
        for (j = i / 2; j >= 2; --j)
        {
            if (i % j == 0)
            {
                Prime = FALSE;
                break;
            }
        }

        if (Prime == TRUE)
        {
            printf("%i ", i);
            ++n;
        }
    }

    return 0;
}
