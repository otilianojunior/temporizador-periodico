// Inclui a biblioteca padrão do Pico
#include "pico/stdlib.h"
// Inclui a biblioteca padrão de entrada e saída
#include <stdio.h>

// Define os pinos dos LEDs
#define RED_LED 11
#define GREEN_LED 12
#define BLUE_LED 13

// Função de callback para o timer recorrente
bool repeating_timer_callback(struct repeating_timer *t)
{
    // Variável estática para armazenar o estado atual
    static int state = 0;

    // Desliga todos os LEDs
    gpio_put(RED_LED, 0);
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);

    // Atualiza o estado
    state = (state + 1) % 3;

    // Liga o LED correspondente ao estado atual
    switch (state)
    {
    case 0: // Vermelho
        gpio_put(RED_LED, 1);
        printf("| - - - - - - - - - - - - - - - - |\n");
        printf("|                                 |\n");
        printf("|             [🔴] - VERMELHO     |\n"); // LED vermelho aceso
        printf("|             [⚫]                |\n"); // LED amarelo apagado
        printf("|             [⚫]                |\n"); // LED verde apagado
        printf("|                                 |\n");
        break;
    case 1: // Amarelo
        gpio_put(GREEN_LED, 1);
        printf("| - - - - - - - - - - - - - - - - |\n");
        printf("|                                 |\n");
        printf("|             [⚫]                |\n"); // LED vermelho apagdo
        printf("|             [🟡] - AMARELO      |\n"); // LED amarelo aceso
        printf("|             [⚫]                |\n"); // LED verde apagado
        printf("|                                 |\n");
        break;
    case 2: // Verde
        gpio_put(BLUE_LED, 1);
        printf("| - - - - - - - - - - - - - - - - |\n");
        printf("|                                 |\n");
        printf("|             [⚫]                |\n"); // LED vermelho apagdo
        printf("|             [⚫]                |\n"); // LED amarelo apagado
        printf("|             [🟢] - VERDE        |\n"); // LED verde aceso
        printf("|                                 |\n");
        break;
    }

    // Retorna verdadeiro para continuar o timer
    return true;
}

int main()
{
    // Inicializa todas as funcionalidades de entrada e saída padrão
    stdio_init_all();

    // Inicializa os GPIOs dos LEDs
    gpio_init(RED_LED);
    gpio_init(GREEN_LED);
    gpio_init(BLUE_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    // Configuração inicial: Vermelho ligado
    gpio_put(RED_LED, 1);
    gpio_put(GREEN_LED, 0);
    gpio_put(BLUE_LED, 0);
    printf("| - - - - - - - - - - - - - - - - |\n");
    printf("|            SEMÁFORO             |\n");
    printf("| - - - - - - - - - - - - - - - - |\n");
    printf("|                                 |\n");
    printf("|             [🔴] - Vermelho     |\n"); // LED vermelho aceso
    printf("|             [⚫]                |\n"); // LED amarelo apagado
    printf("|             [⚫]                |\n"); // LED verde apagado
    printf("|                                 |\n");

    // Configura o timer recorrente de 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Variável para contar o tempo decorrido
    uint32_t contador = 1;

    // Variáveis para o relógio
    uint32_t horas = 0;
    uint32_t minutos = 0;
    uint32_t segundos = 0;

    while (1)
    {
        // Atualiza o relógio
        segundos++;
        if (segundos >= 60)
        {
            segundos = 0;
            minutos++;
            if (minutos >= 60)
            {
                minutos = 0;
                horas++;
                if (horas >= 24)
                {
                    horas = 0;
                }
            }
        }
        // Imprime o relógio
        printf("| - - - - - - - - - - - - - - - - |\n");
        printf("| Relógio: %02lu:%02lu:%02lu               |\n", horas, minutos, segundos);

        contador++;
        // Aguarda 1 segundo
        sleep_ms(1000);
    }

    // Retorna 0 para indicar que o programa terminou corretamente
    return 0;
}