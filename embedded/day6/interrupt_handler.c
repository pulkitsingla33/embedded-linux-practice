#include <stdio.h>

#define MAX_INTERRUPTS 16

#define IRQ_UART 0
#define IRQ_TIMER 1
#define IRQ_GPIO 2

typedef void (*irq_handler_t)(void);

static irq_handler_t interrupt_vector_table[MAX_INTERRUPTS] = {NULL};

int register_interrupt(int irq_num, irq_handler_t irq_function)
{
    if(irq_num < 0 || irq_num > MAX_INTERRUPTS)
    {
        printf("Invalid IRQ number %d\n", irq_num);
        return 1;
    }

    interrupt_vector_table[irq_num] = irq_function;
    printf("Successfully registered handler for IRQ %d\n", irq_num);
    return 0;
}

int trigger_interrupt(int irq_num)
{
    if(irq_num < 0 || irq_num > MAX_INTERRUPTS)
    {
        printf("Invalid IRQ number %d\n", irq_num);
        return 1;
    }

    irq_handler_t handler = interrupt_vector_table[irq_num];

    if(handler != NULL)
    {
        handler();
    }
    else
    {
        printf("No ISR registered for IRQ %d\n", irq_num);
        return 1;
    }

    return 0;
}

void uart_handler(void)
{
    printf("Executing inside UART\n");
}

void timer_handler(void)
{
    printf("Executing inside Timer\n");
}

int main()
{
    register_interrupt(IRQ_UART, uart_handler);
    register_interrupt(IRQ_TIMER, timer_handler);

    trigger_interrupt(IRQ_GPIO);
    trigger_interrupt(IRQ_UART);
    trigger_interrupt(IRQ_TIMER);
    
    return 0;
}