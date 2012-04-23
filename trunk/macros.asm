%macro syscall 1
		mov 	eax,%1
        int 	0x80	;call kernel
%endmacro

%macro syscall 2
		mov 	ebx,%2
		mov 	eax,%1
        int 	0x80	;call kernel
%endmacro

%macro syscall 3
		mov 	ecx,%3
		mov 	ebx,%2
		mov 	eax,%1
        int 	0x80	;call kernel
%endmacro

%macro syscall 4
		mov 	edx,%4
		mov 	ecx,%3
		mov 	ebx,%2
		mov 	eax,%1
        int 	0x80	;call kernel
%endmacro

%macro exit 0
		syscall	1,0
%endmacro

%macro flushargs 0
		add	esp,byte 8      ; `byte' saves space
%endmacro

%macro ccall 1
		call	%1
%endmacro

%macro ccall 2
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 3
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 4
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 5
		push	%5
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro

%macro ccall 6
		push	%6
		push	%5
		push	%4
		push	%3
		push	%2
		call	%1
		flushargs
%endmacro
