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
 Agora, podemos forçar a sincronização dos threads usando o construtor #pragma omp barrier
 em uma determinada linha do código.  Por exemplo, podemos fazer todos os threads esperarem
 pelo thread 5 no código acima. Veja a seguir o código modificado. Teste!
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

    cout << "\n\n Tecle uma tecla e apos Enter para finalizar...\n";
    cin >> caracter;

    return 0;
}

