fibonacci_bu:
        cmp     edi, 2
        jae     .LBB0_1
        mov     eax, edi
        ret
.LBB0_1:
        inc     edi
        cmp     edi, 4
        mov     eax, 3
        cmovae  eax, edi
        lea     esi, [rax - 2]
        add     eax, -3
        mov     ecx, esi
        and     ecx, 7
        cmp     eax, 7
        jae     .LBB0_4
        mov     eax, 1
        xor     edx, edx
        jmp     .LBB0_6
.LBB0_4:
        and     esi, -8
        mov     eax, 1
        xor     edx, edx
.LBB0_5:
        add     rdx, rax
        add     rax, rdx
        add     rdx, rax
        add     rax, rdx
        add     rdx, rax
        add     rax, rdx
        add     rdx, rax
        add     rax, rdx
        add     esi, -8
        jne     .LBB0_5
.LBB0_6:
        test    ecx, ecx
        je      .LBB0_8
.LBB0_7:
        mov     rsi, rax
        mov     rax, rdx
        add     rax, rsi
        mov     rdx, rsi
        dec     ecx
        jne     .LBB0_7
.LBB0_8:
        ret