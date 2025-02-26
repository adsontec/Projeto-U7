#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "Projeto-U7.pio.h"

#define GPIO_R_LED 13
#define GPIO_B_LED 12
#define GPIO_G_LED 11
#define BUTTON_A 5
#define BUTTON_B 6

#define NUM_PIXELS 25
#define OUT_PIN 7

const uint8_t GPIOs[] = {GPIO_R_LED, GPIO_B_LED, GPIO_G_LED, BUTTON_A, BUTTON_B};

volatile bool red_led_state = false;
volatile int cont = 0;
volatile absolute_time_t last_press_time = 0;

PIO pio;
uint sm;

double numeros[11][5][5] = {
    {
        // Desligar todos os LEDs
        {0.0, 0.0, 0.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0},{0.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 0
        {1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 1
        {1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 2
        {1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 3
        {1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 4
        {1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 5
        {1.0, 1.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
    },
    {
        // Número 6
        {1.0, 1.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 1.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
    },{
        // Número 7
        {1.0, 1.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 1.0, 1.0},
		{1.0, 0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0, 1.0},
		{1.0, 1.0, 1.0, 0.0, 0.0},
    },{
        // Número 8
        {0.0, 1.0, 1.0, 1.0, 0.0},{0.0, 1.0, 0.0, 1.0, 0.0},{0.0, 1.0, 1.0, 1.0, 0.0},{0.0, 1.0, 0.0, 1.0, 0.0},{0.0, 1.0, 1.0, 1.0, 0.0},
    },{
        // Número 9
        {0.0, 1.0, 1.0, 1.0, 0.0},{0.0, 0.0, 0.0, 1.0, 0.0},{0.0, 1.0, 1.0, 1.0, 0.0},{0.0, 1.0, 0.0, 1.0, 0.0},{0.0, 1.0, 1.0, 1.0, 0.0},
    },
};

// Protótipo de Função
void inicializar_GPIOs();
uint32_t matriz_rgb(double r, double g, double b);
void atualizar_matriz_leds(PIO pio, uint sm, int current_pattern);
void gpio_irq_handler(uint gpio, uint32_t events);

int main(){
    stdio_init_all();
    inicializar_GPIOs();
    void numero(PIO pio, uint sm);

    pio = pio0;
    
    uint offset = pio_add_program(pio, &pio_matrix_program);
    sm = pio_claim_unused_sm(pio, true);
    pio_matriz_program_init(pio, sm, offset, OUT_PIN);

    // Configuração da interrupção com callback
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

    atualizar_matriz_leds(pio, sm, cont);

    gpio_put(GPIO_R_LED, !gpio_get(GPIO_R_LED));

    while (true){
        // Piscar LED vermelho continuamente 5 vezes por segundo
       
    }
}

// Função para inicializar saídas dos LEDs e as entradas dos Buttons
void inicializar_GPIOs(){
    for(int i = 0; i < 5; i++){
        gpio_init(GPIOs[i]);
        if( i < 3){
            gpio_set_dir(GPIOs[i], GPIO_OUT);
        }else{
            gpio_set_dir(GPIOs[i], GPIO_IN);
            // Habilita o resistor pull-up interno
            gpio_pull_up(GPIOs[i]);
        }
    }
}

// Função que returna a cor com base nos parâmetros fornecidos
uint32_t matriz_rgb(double r, double g, double b){
    return ((uint8_t)(g * 255) << 24) | ((uint8_t)(r * 255) << 16) | ((uint8_t)(b * 255) << 8);
}

// Função para atualizar a matriz de LEDs
void atualizar_matriz_leds(PIO pio, uint sm, int current_pattern){
    for (int j = 0; j < 5; j++){
        for (int k = 0; k < 5; k++){
            uint32_t cor = matriz_rgb(0, numeros[current_pattern][j][k], 0);
            pio_sm_put_blocking(pio, sm, cor);
        }
    }
}

// Função de interrupção com debouncing
void gpio_irq_handler(uint gpio, uint32_t events){
    bool btn_last_state = 0;

    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    bool btn_pressed = !gpio_get(gpio);

    // Verifica se passou tempo suficiente desde o último evento
    if (btn_pressed && !btn_last_state && (absolute_time_diff_us(last_press_time, get_absolute_time()) > 200000)){
        last_press_time = get_absolute_time();
        btn_last_state = 1;
        if ((gpio == BUTTON_A) && (cont > 0)){
            cont--; // Decrementar
            atualizar_matriz_leds(pio, sm, cont);
        }else if ((gpio == BUTTON_B) && (cont < 10)){
            cont++; // Incrementar
            atualizar_matriz_leds(pio, sm, cont);
        }
    }else if (!btn_pressed){
        btn_last_state = 0;
    }
    if(gpio_get(GPIO_R_LED) == 1){
        gpio_put(GPIO_R_LED, !gpio_get(GPIO_R_LED));
    }
    
}