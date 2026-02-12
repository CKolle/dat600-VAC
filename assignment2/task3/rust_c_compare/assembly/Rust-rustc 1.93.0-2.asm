fibonacci_bu:
        cmp     edi, 2
        jae     .LBB0_1
        mov     eax, edi
        ret
.LBB0_1:
        lea     edx, [rdi - 2]
        mov     eax, 1
        cmp     edx, -4
        ja      .LBB0_8
        dec     edi
        mov     ecx, edi
        and     ecx, 7
        cmp     edx, 7
        jae     .LBB0_4
        mov     edx, 1
        xor     esi, esi
        jmp     .LBB0_6
.LBB0_4:
        and     edi, -8
        mov     edx, 1
        xor     esi, esi
.LBB0_5:
        add     rsi, rdx
        add     rdx, rsi
        add     rsi, rdx
        add     rdx, rsi
        add     rsi, rdx
        add     rdx, rsi
        add     rsi, rdx
        add     rdx, rsi
        add     edi, -8
        jne     .LBB0_5
.LBB0_6:
        mov     rax, rdx
        test    ecx, ecx
        je      .LBB0_8
.LBB0_7:
        mov     rax, rsi
        add     rax, rdx
        mov     rsi, rdx
        mov     rdx, rax
        dec     ecx
        jne     .LBB0_7
.LBB0_8:
        ret