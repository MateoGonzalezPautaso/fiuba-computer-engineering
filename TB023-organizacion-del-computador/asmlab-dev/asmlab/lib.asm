%define ARRAY_OFFSET_type 0
%define ARRAY_OFFSET_size 4
%define ARRAY_OFFSET_capacity 5
%define ARRAY_OFFSET_data 8
%define ARRAY_SIZE 16

%define TAMAÑO_PUNTERO 8

%define CARD_OFFSET_suit 0
%define CARD_OFFSET_number 8
%define CARD_OFFSET_stacked 16
%define CARD_SIZE 24

%define TYPE_CARD 3

global strClone
global strPrint
global strCmp
global strLen
global strDelete

global arrayNew
global arrayDelete
global arrayPrint
global arrayGetSize
global arrayAddLast
global arrayGet
global arrayRemove
global arraySwap

global cardCmp
global cardClone
global cardAddStacked
global cardDelete
global cardGetSuit
global cardGetNumber
global cardGetStacked
global cardPrint
global cardNew

extern malloc
extern fprintf
extern free
extern getCloneFunction
extern getDeleteFunction
extern getPrintFunction
extern intClone
extern listNew
extern listDelete
extern intPrint
extern listPrint
extern intCmp
extern listClone
extern listAddFirst
extern intDelete

section .data

FORMATO_STRING: db "%s", 0
FORMATO_NULL: db "NULL", 0
CORCHETE_ABRIENDO: db "[", 0
CORCHETE_CERRANDO: db "]", 0
COMA db ",", 0
LLAVE_ABRIENDO: db "{",0
LLAVE_CERRANDO: db "}",0
GUION: db "-",0

section .text

; ** String **
;char* strClone(char* a);
strClone:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; El puntero al string se guarda en r12 para pasarlo a strLen
    call strLen     ;Longitud del string en rax

    mov r13, rax   ; Guarda Len en r13
    inc r13        ; Agrega un espacio para copiar '\0'
    mov rdi, r13   ; Guarda Len en rdi para pasarlo a malloc
    call malloc    ; Puntero a memoria reservada en rax

    mov r8, 0   ; Desplazamiento sobre el puntero
    .while:
        mov r9b, BYTE [r12 + r8] ; operamos de a 1 byte para evitar problemas de tamaños incompatibles
        mov [rax + r8] , r9b
        inc r8
        
        cmp r8, r13     ; Si el desplazamiento es igual a la longitud del string, hay que dejar de copiar
        jne .while

    .fin:
        pop r13
        pop r12
        pop rbp
        ret

;void strPrint(char* a, FILE* pFile)
strPrint:
    ; rdi = char* a
    ; rsi = FILE* pFile
    ; fprintf(pFile, "%s", *a)
    ; rdi = FILE* pFile     rsi = "%s"      rdx = char* a
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; r12 = char* a
    mov r13, rsi ; r13 = FILE* pFile 
    
    call strLen
    
    mov rdi, r13
    mov rsi, FORMATO_NULL
    cmp eax, 0
    je .fin
    
    mov rdi, r13
    mov rsi, FORMATO_STRING     ; rsi = "%s"
    mov rdx,  r12   ; rdx = *a

    
    .fin:
        call fprintf
        pop r13
        pop r12
        pop rbp
        ret

;uint32_t strLen(char* a);
strLen:
    push rbp
    mov rbp, rsp

    mov rax, 0 ; Limpiamos rax para usarlo como contador
    .while:
        cmp BYTE [rdi + rax], 0
        je .fin ; si el caracter es igual a 0, llego al fin
        inc rax
        jmp .while

    .fin:
        pop rbp
        ret

;int32_t strCmp(char* a, char* b);
strCmp:
    push rbp
    mov rbp, rsp

    mov r8, 0 ; Limpiamos r8 para usarlo como contador

    .while:
        mov r9b, [rdi + r8]
        mov r10b, [rsi + r8]
        cmp r9b, 0 ; Se verifica si a tiene más carateres
        je .equal
        inc r8b
        cmp r9b, r10b
        jg .a ; Si a > b, se hace un jump a .a
        jl .b ; Si a < b, se hace un jump a .b
        je .while ; Si son iguales, como no llegaron al final, se sigue comparando

    .equal:
        cmp r10b, 0 ; Se verifica si b tiene más carateres
        jne .b ; Si el a llegó al final, pero b no, b > a 
        mov eax, 0
        jmp .fin

    .a: ; a > b
        mov eax, -1
        jmp .fin

    .b: ; b > a
        mov eax, 1
        jmp .fin

    .fin:
        pop rbp
        ret

;void strDelete(char* a);
strDelete:
    push rbp
    mov rbp, rsp
    
    call free   ; Ya tengo el puntero al string en rdi

    .fin:
        pop rbp
        ret

; ** Array **

; uint8_t arrayGetSize(array_t* a)
arrayGetSize:
    push rbp
    mov rbp, rsp

    mov rax, 0
    mov al, BYTE [rdi + ARRAY_OFFSET_size] ; guardo en el registro al el size

    .fin:
        pop rbp
        ret

; void arrayAddLast(array_t* a, void* data)
arrayAddLast:
    push rbp
    mov rbp, rsp
    push r12 ; r12 = array_t *a
    push r13 ; r13 = void *data
    push r14 ; rbx = a->size
    push r15 ; r15 = a->data

    mov r12, rdi ; Puntero a array guardado en r12
    mov r13, rsi ; data guardado en r13

    mov r14, 0 
    mov r14b, BYTE [rdi + ARRAY_OFFSET_size] ; Guardamos el tamaño actual del array en r14
    cmp r14b, BYTE [rdi + ARRAY_OFFSET_capacity]
    je .fin ; Si el array está lleno, no se hace nada

    mov r15, [r12 + ARRAY_OFFSET_data] ; Vector de void* data guardado en r15

    mov rdi,  [r12 + ARRAY_OFFSET_type]
    call getCloneFunction ; La función clonadora queda guardada en rax
    mov rdi, r13 
    call rax ; Se llama a la función clonadora. Queda guardada la data copiada en rax

    mov [r15 + r14 * TAMAÑO_PUNTERO], rax ; Guardamos la data copiada en la última posición disponible del array
    inc BYTE [r12 + ARRAY_OFFSET_size]   ; Aumentamos el tamaño del array

    .fin:
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; void* arrayGet(array_t* a, uint8_t i)
arrayGet:
    push rbp
    mov rbp,rsp
    mov r8, [rdi + ARRAY_OFFSET_size] ; Tamaño actual del array en r8
    mov r9, [rdi + ARRAY_OFFSET_data] ; a->data en r9
    mov r10, rsi ; índice i

    mov rax, 0  ;Limpia el registro de retorno 

    cmp r10b, 0
    jl .fin
    
    cmp r10b, r8b
    jge .fin ; Si el tamaño actual es menor que la posición recibida, se devuelve rax en 0
    
    mov rax, [r9 + rsi * TAMAÑO_PUNTERO]

    .fin:
        pop rbp
        ret

; array_t* arrayNew(type_t t, uint8_t capacity)
arrayNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push rbx
    sub rsp, 8

    mov r12, rdi    ;Guarda type_t en r12
    mov r13, rsi    ;Guarda capacity en r13

    mov rdi, ARRAY_SIZE ;Tamaño del array en rdi
    call malloc     
    mov rbx, rax        ;Guarda el puntero al array en rbx

    mov [rbx + ARRAY_OFFSET_type],r12
    mov [rbx + ARRAY_OFFSET_capacity], r13

    shl r13, 3 ; multiplica *8 (tamaño puntero)
    mov rdi, r13  ; Guarda en rdi el tamaño del vector 'data'
    call malloc

    mov [rbx + ARRAY_OFFSET_data], rax
    mov [rbx + ARRAY_OFFSET_size], BYTE 0

    .fin:
        mov rax, rbx
        add rsp, 8
        pop rbx
        pop r13
        pop r12
        pop rbp
        ret

; void* arrayRemove(array_t* a, uint8_t i)
arrayRemove:
    ; rdi = array_t* a
    ; rsi = uint8_t i
    push rbp
    mov rbp, rsp
    push rbx ; void *quitado
    push r12 ; r12 = array_t* a
    push r13 ; r13 = a->data
    push r14 ; r14 = a->size
    push r15 ; r15 = uint8_t i
    sub rsp,8

    mov r12, rdi
    mov r13, [rdi + ARRAY_OFFSET_data]
    mov r14b, [rdi + ARRAY_OFFSET_size]
    mov r15, rsi

    mov rbx, 0 ; Limpio void *quitado
    cmp r15b, r14b
    jge .fin    ; Salto al fin devolviendo 0 cuando i esta fuera de rango

    mov rbx, [r13 + r15 * TAMAÑO_PUNTERO] ; Guarda el elemento a eliminar

    dec r14b ; size - 1 como condicion de corte
    
    .while:
        cmp r15b, r14b
        je .fin

        mov rdi, r12 ; 1° parametro de swap, array_t
        mov rsi, r15 ; 2° parametro de swap, posicion i
        inc r15b
        mov rdx, r15 ; 3° parametro de swap, posicion i + 1
        dec r15b

        call arraySwap ; swap(array, i, i+1)

        inc r15b
        jmp .while

    .fin:
        mov rax, rbx
        mov [r12 + ARRAY_OFFSET_size], r14b
        add rsp,8
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbx
        pop rbp
        ret

; void arraySwap(array_t* a, uint8_t i, uint8_t j)
arraySwap:
    push rbp
    mov rbp,rsp
    mov r8, [rdi + ARRAY_OFFSET_size] ; Tamaño actual del array en r8
    mov r9, rsi ; índice i
    mov r10, rdx ; indice j
    ;   rdi = array_t *a
    ;   rsi = i
    ;   rdx = j

    cmp r9b, r10b ; Si quiero hacer un swap entre los mismos elementos, ya termine
    je .fin
    
    cmp r10b, r8b
    jge .fin ; Si j esta fuera de rango, no hace nada

    cmp r9b, r8b
    jge .fin ; Si i esta fuera de rango, no hace nada
    
    mov rax, [rdi + ARRAY_OFFSET_data] 
    mov r11, [rax + r9 * TAMAÑO_PUNTERO] ; Guardo el dato que esta en data[i]
    mov r8, [rax + r10 * TAMAÑO_PUNTERO]  ; Guardo el dato que esta en data[j]

    mov [rax + r10 * TAMAÑO_PUNTERO], r11
    mov [rax + r9 * TAMAÑO_PUNTERO], r8

    .fin:
        pop rbp
        ret

; void arrayDelete(array_t* a) 
arrayDelete:
    ; rdi = array_t* a
    ; free(a->data[i]) funcion destructora para esto
    ; free(a->data)
    ; free(a)
    push rbp
    mov rbp, rsp
    push r12 ; contador
    push r13 ; puntero al array
    push r14 ; puntero al data
    push r15 ; funcion destructora

    mov r12, 0
    mov r13, rdi
    mov r14, [r13 + ARRAY_OFFSET_data] 

    mov rdi, [r13 + ARRAY_OFFSET_type]
    call getDeleteFunction
    mov r15, rax

    .while:
        cmp r12b, [r13 + ARRAY_OFFSET_size] ; para iterar sobre data[i]
        je .fin
        mov rdi, [r14 + r12 * TAMAÑO_PUNTERO]
        call r15 ; free(data[i])
        inc r12
        jmp .while

    .fin:
        mov rdi, r14
        call free ; free(data)
        mov rdi, r13
        call free ; free(array)
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

;void arrayPrint(array_t* a, FILE* pFile)
arrayPrint:
    push rbp
    mov rbp, rsp
    push r12 ; r12 = a->data
    push r13 ; r13 = a->size
    push r14 ; r14 = i
    push r15 ; r15 = FILE *pFile 
    push rbx ; rbx = a->type
    sub rsp, 8

    mov r12, [rdi + ARRAY_OFFSET_data]
    mov r13b, [rdi + ARRAY_OFFSET_size]
    mov rbx, [rdi + ARRAY_OFFSET_type]
    mov r14, 0  
    mov r15, rsi

    mov rdi, r15        ; rdi = FILE* pFile
    mov rsi, CORCHETE_ABRIENDO     ; rsi = "["
    call fprintf

    mov rdi, rbx
    call getPrintFunction
    mov rbx, rax ;  rbx = funcion impresora

    .while:
        cmp r14b, r13b
        jge .fin

        mov rdi, [r12 + r14 * TAMAÑO_PUNTERO]
        mov rsi, r15
        call rbx    ; Imprime el numero actual

        inc r14b
        cmp r14b, r13b
        je .fin ;Si se acaba de imprimir el ultimo elemento, no imprime la coma

        mov rdi, r15
        mov rsi, COMA
        call fprintf
        
        jmp .while

    .fin:
        mov rdi, r15        ; rdi = FILE* pFile
        mov rsi, CORCHETE_CERRANDO     ; rsi = "]"
        call fprintf

        add rsp,8
        pop rbx
        pop r15
        pop r14
        pop r13
        pop r12
        pop rbp
        ret

; ** Card **

; card_t* cardNew(char* suit, int32_t* number)
cardNew:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push rbx
    sub rsp, 8
    
    mov r12, rdi ; r12 = suit
    mov r13, rsi ; r13 = number

    mov rdi, CARD_SIZE
    call malloc
    mov rbx, rax    ; rbx = card_t*

    mov rdi, r12
    call strClone
    mov r12, rax ; r12 = copia suit
    
    mov rdi, r13
    call intClone
    mov r13, rax ; r13 = copia number
    
    mov rdi, TYPE_CARD  
    call listNew

    mov [rbx + CARD_OFFSET_suit], r12       ; Asigna el suit
    mov [rbx + CARD_OFFSET_number], r13     ; Asigna el number
    mov [rbx + CARD_OFFSET_stacked], rax    ; Asigna el stacked

    .fin:
        mov rax, rbx
        add rsp, 8
        pop rbx
        pop r13
        pop r12
        pop rbp
        ret

;char* cardGetSuit(card_t* c)
cardGetSuit:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFFSET_suit] ; Guardo en rax el suit

    .fin:
        pop rbp
        ret

;int32_t* cardGetNumber(card_t* c)
cardGetNumber:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFFSET_number] ; Guardo en rax el number

    .fin:
        pop rbp
        ret

;list_t* cardGetStacked(card_t* c)
cardGetStacked:
    push rbp
    mov rbp, rsp

    mov rax, [rdi + CARD_OFFSET_stacked] ; Guardo en rax el stacked

    .fin:
        pop rbp
        ret

;void cardPrint(card_t* c, FILE* pFile)
cardPrint:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; r12 = card_t *c
    mov r13, rsi ; r13 = FILE *pFile

    mov rdi, r13
    mov rsi, LLAVE_ABRIENDO
    call fprintf

    mov rdi, [r12 + CARD_OFFSET_suit]
    mov rsi, r13
    call strPrint

    mov rdi, r13
    mov rsi, GUION
    call fprintf
    
    mov rdi, [r12 + CARD_OFFSET_number]
    mov rsi, r13
    call intPrint

    mov rdi, r13
    mov rsi, GUION
    call fprintf

    mov rdi, [r12 + CARD_OFFSET_stacked]
    mov rsi, r13
    call listPrint

    mov rdi, r13
    mov rsi, LLAVE_CERRANDO
    call fprintf
    
    .fin:
        pop r13
        pop r12
        pop rbp
        ret


;int32_t cardCmp(card_t* a, card_t* b)
cardCmp:
    push rbp
    mov rbp, rsp
    push r12
    push r13

    mov r12, rdi ; r12 = card_t *a
    mov r13, rsi ; r13 = card_t *b

    mov rdi, [r12 + CARD_OFFSET_suit]
    mov rsi, [r13 + CARD_OFFSET_suit]
    call strCmp

    cmp eax, 0
    je .equal ; a->suit == b->suit
    jl .b     ; eax = -1    a->suit > b->suit
    jg .a     ; eax = 1     a->suit < b->suit
    
    .equal:
        mov rdi, [r12 + CARD_OFFSET_number]
        mov rsi, [r13 + CARD_OFFSET_number]
        call intCmp

        cmp eax, 0
        jl .b
        jg .a
            
        mov eax, 0
        jmp .fin
        
    .a:
        mov eax, 1
        jmp .fin

    .b: 
        mov eax, -1
        jmp .fin
    
    .fin:
        pop r13
        pop r12
        pop rbp
        ret

;card_t* cardClone(card_t* c)
cardClone:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push rbx
    
    mov r12, [rdi + CARD_OFFSET_suit] ; r12 = suit
    mov r13, [rdi + CARD_OFFSET_number] ; r13 = number
    mov r14, [rdi + CARD_OFFSET_stacked] ; r14 = stacked

    mov rdi, CARD_SIZE
    call malloc
    mov rbx, rax    ; rbx = card_t* copia

    mov rdi, r12
    call strClone
    mov r12, rax ; r12 = copia suit
    
    mov rdi, r13
    call intClone
    mov r13, rax ; r13 = copia number

    mov rdi, r14
    call listClone
    mov r14, rax ; r14 = lista clonada

    mov [rbx + CARD_OFFSET_suit], r12       ; Asigna el suit
    mov [rbx + CARD_OFFSET_number], r13     ; Asigna el number
    mov [rbx + CARD_OFFSET_stacked], r14    ; Asigna el stacked
    
    .fin:
        mov rax, rbx
        pop rbx
        pop r14
        pop r13
        pop r12
        pop rbp
        ret
        
;void cardAddStacked(card_t* c, card_t* card)
cardAddStacked:
    push rbp 
    mov rbp, rsp
    
    mov rdi, [rdi + CARD_OFFSET_stacked] ; rdi = c->stacked
    ; rsi = card_t* card
    call listAddFirst   ; Agrega la COPIA de card al principio de c->stacked

    .fin:
        pop rbp
        ret

;void cardDelete(card_t* c)
cardDelete:
    push rbp
    mov rbp, rsp
    push rbx
    sub rsp, 8
    
    mov rbx, rdi ; rbx = card_t *c
    
    mov rdi, [rbx + CARD_OFFSET_suit]
    call strDelete
    
    mov rdi, [rbx + CARD_OFFSET_number]
    call intDelete
    
    mov rdi, [rbx + CARD_OFFSET_stacked]
    call listDelete
    
    mov rdi, rbx
    call free

    .fin:
        add rsp, 8
        pop rbx
        pop rbp
        ret

