#include "Philosophers.h"
//./philo 5 800 200 200 (5) 引数は、何人寿命、食事時間、睡眠時間、最大食事回数(ないなら無限ループ、あるなら制限付きループ)
void chech_argument(int ac, char **av)
{
    int i = 1;

    while (i < ac)
    {
        if (ft_atoi(av[i]) <= 0)
        {
            printf("Error: Argument %d is not a positive integer.\n", i);
            exit(1);
        }
        i++;
    }
}

int main(int ac, char **av)
{
    t_philo *z;

    if(ac == 5 || ac == 6)
    {
        chech_argument(ac, av);
        
    }
}