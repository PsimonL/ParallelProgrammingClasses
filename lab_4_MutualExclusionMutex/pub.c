#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define ILE_MUSZE_WYPIC 3

pthread_mutex_t *mutexKufle;
int l_kl, l_kr, l_kf;

void *watek_klient(void *arg_wsk)
{

    int moj_id = *((int *)arg_wsk);

    int i, result, k = 0;
    int ile_musze_wypic = ILE_MUSZE_WYPIC;

    printf("\nKlient %d, wchodzê do pubu\n", moj_id);

    for (i = 0; i < ile_musze_wypic; i++)
    {
        result = 0;
        while (result == 0)
        {
            if (pthread_mutex_trylock(&mutexKufle[k]) == 0) {
                printf("\nKlient %d, wybieram kufel\n", moj_id);
                printf("\nKlient %d, pije\n", moj_id);
                printf("\nKlient %d, odkladam kufel\n", moj_id);
                nanosleep((struct timespec[]) {{0, 50000000L}}, NULL);
                result = 1;
            }
            else
            {
                if (k == l_kf - 1)
                    k = 0;
                else
                    k++;
            }
        }
        k = 0;
        pthread_mutex_unlock(&mutexKufle[k]);
    }
    printf("\nKlient %d, wychodzê z pubu\n", moj_id);
    return (NULL);
}

int main(void)
{
    pthread_t *tab_klient;
    int *tab_klient_id;

    printf("\nLiczba klientow: ");
    scanf("%d", &l_kl);
    printf("\nLiczba kufli: ");
    scanf("%d", &l_kf);

    mutexKufle = calloc(l_kf, sizeof(pthread_mutex_t));

    for (int i = 0; i < l_kf; i++)
    {

        pthread_mutex_init(&mutexKufle[i], NULL);
    }

    tab_klient = (pthread_t *)malloc(l_kl * sizeof(pthread_t));
    tab_klient_id = (int *)malloc(l_kl * sizeof(int));
    for (int i = 0; i < l_kl; i++)
        tab_klient_id[i] = i;

    printf("\nOtwieramy pub (simple)!\n");
    printf("\nLiczba wolnych kufli przed %d\n", l_kf);

    for (int i = 0; i < l_kl; i++)
    {
        pthread_create(&tab_klient[i], NULL, watek_klient, &tab_klient_id[i]);
    }
    for (int i = 0; i < l_kl; i++)
    {
        pthread_join(tab_klient[i], NULL);
    }
    printf("\nLiczba wolnych kufli po %d\n", l_kf);
    printf("\nZamykamy pub!\n");
}

