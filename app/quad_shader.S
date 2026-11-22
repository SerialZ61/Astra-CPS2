.section .rodata.quad_shader,"a",%progbits
.balign 4
.global astra_quad_shader, astra_quad_shader_end
astra_quad_shader:
.incbin ASTRA_QUAD_SHADER
astra_quad_shader_end:
.section .note.GNU-stack,"",%progbits
