[GLOBAL gdt_flush]

gdt_flush:
          mov eax,[esp+4]
          lgdt [eax]

          ;load data segment descriptor
          mov ax,0x10
          mov ds,ax
          mov ss,ax
          mov es,ax
          mov fs,ax,
          mov gs,ax
          jmp 0x08:.flush   ;far jmp, 0x08 represent code segment descriptor
                            ;jmp for clear pipeline
.flush:
          ret
