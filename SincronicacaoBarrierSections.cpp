/* 2.2.3 Sincronização
 * A sincronização dos threads deve ser evitada sempre que possível, devido a perda de performance
 * em códigos paralelos. Atenção, ela ocorre implicitamente no término da região paralela!
 * No seguinte código, o thread 1 é atrasado em 1 segundo,
 * de forma que ele é o último a imprimir. Verifique!
 */
#include <ctime>
#include <omp.h>
#include <iostream>

using namespace std;

// Variáveis Globais(shared)
char caracter;

int tid = 0;
int nt;
time_t now;
struct tm ts;
char buf[80];

int main(int argc, char *argv[]) {


    // Obtem o tempo corrente
    now = time(NULL);

    // Formata e imprime o tempo, "ddd yyyy-mm-dd hh:mm:ss zzz"
    ts = *localtime(&now);
    strftime(buf, sizeof(buf), "%a %d-%m-%Y %H:%M:%S %Z", &ts);
    printf("\n%s", buf);


#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

        if (tid == nt - 1) {
            // Obtem o tempo corrente
            time_t t1 = time(NULL);
            //Espera 0,1 segundo
            while (difftime(time(NULL), t1) < 0.1) {
            }
        }

        printf("\n Processo %d/%d.", tid, nt);
    }

    cout << "\n";
/*
 * Agora, podemos forçar a sincronização dos threads usando o construtor #pragma omp barrier
 * em uma determinada linha do código.  Por exemplo, podemos fazer todos os threads esperarem
 * pelo thread 5 no código acima. Veja a seguir o código modificado. Teste!
*/
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

        if (tid == 5) {
            // delay 1s
            time_t t0 = time(NULL);
            while (time(NULL) - t0 < 0.1) {
            }
        }

#pragma omp barrier

        printf("\n Processo %d/%d.", tid, nt);
    }

/*
 * Seção
 * O construtor sections pode ser usado para determinar seções do código que deve ser executada
 * de forma serial apenas uma vez por um único thread. Verifique o seguinte código.
*/
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

#pragma omp sections
        {
            // seção 1
#pragma omp section
            {
                printf("%d/%d exec secao 1\n", \
                tid, nt);
            }

            // seção 2
#pragma omp section
            {
                // delay 1s
                time_t t0 = time(NULL);
                while (time(NULL) - t0 < 1) {
                }
                printf("%d/%d exec a secao 2\n", \
                tid, nt);
            }
        }

        printf("%d/%d terminou\n", tid, nt);
    }


/*
 * Seção
 * O construtor sections pode ser usado para determinar seções do código que deve ser executada
 * de forma serial apenas uma vez por um único thread. Verifique o seguinte código.
*/
    cout << "\n";
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

#pragma omp sections
        {
            // seção 1
#pragma omp section
            {
                printf("\n %d/%d executou a secao 1", \
                tid, nt);
            }

            // seção 2
#pragma omp section
            {
                // delay 1s
                time_t t0 = time(NULL);
                while (time(NULL) - t0 < 1) {
                }
                printf("\n %d/%d executou a secao 2", \
                tid, nt);
            }
        }

        printf("\n %d/%d terminou", tid, nt);
    }

/*
 * No código acima, o primeiro thread que alcançar a linha 19 é o único a executar a seção 1 e,
 * o primeiro que alcançar a linha 25 é o único a executar a seção 2.
 * Observe que ocorre a sincronização implícita de todos os threads ao final do escopo sections.
 * Isso pode ser evitado usando a cláusula nowait, i.e. alterando a linha 16 para
 * # pragma omp sections nowait
 * Teste!
 * Observação 2.2.5.
 * A clausula nowait também pode ser usada com o construtor for, i.e. #pragma omp for nowait
 * Para uma região contendo apenas uma seção, pode-se usar o construtor
 * #pragma omp single
 * Isto é equivalente a escrever

#pragma omp sections
  #pragma omp section
*/
    cout << "\n";
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        nt = omp_get_num_threads();

#pragma omp sections
        {
            // seção 1
#pragma omp section
            {
                printf("\n %d/%d executou a secao 1", \
                tid, nt);
            }

            // seção 2
#pragma omp section
            {
                // delay 1s
                time_t t0 = time(NULL);
                while (time(NULL) - t0 < 1) {
                }
                printf("\n %d/%d executou a secao 2", \
                tid, nt);
            }
        }

        printf("\n %d/%d terminou", tid, nt);
    }



    cout << "\n\n Tecle uma tecla e apos Enter para finalizar...\n";
    cin >> caracter;

    return 0;
}
