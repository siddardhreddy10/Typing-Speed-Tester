section .data
    tick_start dd 0
    flag_done  dd 0

section .text
global _start_timer
global _get_timer_flag
global _my_strcmp
global _my_strlen
global _wpm

extern _GetTickCount@0
extern Sleep

_start_timer:
    push ebp
    mov  ebp, esp
    mov  dword [flag_done], 0
    call _GetTickCount@0
    mov  [tick_start], eax
    pop  ebp
    ret

_get_timer_flag:
    push ebp
    mov  ebp, esp
    call _GetTickCount@0
    sub  eax, [tick_start]
    cmp  eax, 60000
    jl   .not_yet
    mov  dword [flag_done], 1
.not_yet:
    mov  eax, [flag_done]
    pop  ebp
    ret

_my_strlen:
    push ebp
    mov  ebp, esp
    mov  esi, [ebp+8]
    xor  eax, eax
.loop:
    mov  bl, [esi+eax]
    cmp  bl, 0
    je   .done
    inc  eax
    jmp  .loop
.done:
    pop  ebp
    ret

_my_strcmp:
    push ebp
    mov  ebp, esp
    mov  esi, [ebp+8]
    mov  edi, [ebp+12]
.check:
    mov  al, [esi]
    mov  bl, [edi]
    cmp  al, bl
    jne  .differ
    cmp  al, 0
    je   .same
    inc  esi
    inc  edi
    jmp  .check
.same:
    xor  eax, eax
    pop  ebp
    ret
.differ:
    mov  eax, 1
    pop  ebp
    ret
.zero:
    xor  eax, eax
    pop  ebp
    ret
            