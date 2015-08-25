.include "STM32F4_P24v04_definitions03.inc"


@; --- characterize target syntax, processor
	.syntax unified				@; ARM Unified Assembler Language (UAL). 
								@; Code written using UAL can be assembled 
								@; for ARM, Thumb-2, or pre-Thumb-2 Thumb
	.thumb						@; Use thmb instructions only
	
	
	.equ ST_Up,0
	.equ ST_A,1
	.equ ST_B,2
	.equ ST_Down,3
	.equ ST_C,4
	.equ ST_D,5


@;     Time to go
@;
@;     ||	|     //| ||\  //
@;     ||	|    // | || \//|
@;     ||===|   //==| ||    |
@;     ||	|  //   | ||    |
@;     ||	| //    | ||    |

	.bss
.comm outarray, 4
.lcomm mux, 1
.lcomm asmticks, 1
.lcomm sw_states, 52

	@;.align 3

	.text

	.global P24_init
	.thumb_func
P24_init:
	@; DISPLAY PINS OUT
	PORTBIT_init 0,GPIOA_BASE,1		
	PORTBIT_init 0,GPIOB_BASE,0
	PORTBIT_init 0,GPIOB_BASE,1
	PORTBIT_init 0,GPIOB_BASE,5
	PORTBIT_init 0,GPIOB_BASE,11
	PORTBIT_init 0,GPIOC_BASE,2
	PORTBIT_init 0,GPIOC_BASE,4
	PORTBIT_init 0,GPIOC_BASE,5
	
	@; EN/CLK OUT
	PORTBIT_init 0,GPIOD_BASE,2
	PORTBIT_init 0,GPIOC_BASE,11
	PORTBIT_init 0,GPIOC_BASE,1
	PORTBIT_init 0,GPIOB_BASE,4
	
	@; SWITCH OUT
	PORTBIT_init 2,GPIOA_BASE,15
	PORTBIT_init 2,GPIOC_BASE,8
	
	@; SWITCH IN
	@;PORTBIT_init 1,GPIOA_BASE,1
	@;PORTBIT_init 1,GPIOB_BASE,0
	@;PORTBIT_init 1,GPIOB_BASE,1
	@;PORTBIT_init 1,GPIOB_BASE,5
	@;PORTBIT_init 1,GPIOB_BASE,11
	@;PORTBIT_init 1,GPIOC_BASE,4
	@;PORTBIT_init 1,GPIOC_BASE,5
	@;PORTBIT_init 1,GPIOD_BASE,2
	
	@;PORTBIT_write GPIOC_BASE,8,1
	@;PORTBIT_write GPIOA_BASE,15,1
	
	bx lr

	.global asm_print_digit
	.thumb_func
asm_print_digit:
	push {r1}
	
	PORTBIT_write GPIOB_BASE,4,1			@;	01_PB4	AN_EN	-- disable anode   (active-low)
	PORTBIT_write GPIOC_BASE,1,1			@;	01_PC1	CA_EN	-- disable cathode (active-low)

	tbh [pc,r0]
TBB_CATHODE_table:	@;table where offsets to code entry points are stored
	.hword ((cathode_0 - TBB_CATHODE_table)/2)
	.hword ((cathode_1 - TBB_CATHODE_table)/2)
	.hword ((cathode_2 - TBB_CATHODE_table)/2)
	.hword ((cathode_3 - TBB_CATHODE_table)/2)
	.hword ((cathode_4 - TBB_CATHODE_table)/2)
	.hword ((cathode_5 - TBB_CATHODE_table)/2)
	.hword ((cathode_6 - TBB_CATHODE_table)/2)
	.hword ((cathode_7 - TBB_CATHODE_table)/2)
	.hword ((cathode_8 - TBB_CATHODE_table)/2)
	.hword ((cathode_9 - TBB_CATHODE_table)/2)
	.hword ((cathode_A - TBB_CATHODE_table)/2)
	.hword ((cathode_B - TBB_CATHODE_table)/2)
	.hword ((cathode_C - TBB_CATHODE_table)/2)
	.hword ((cathode_D - TBB_CATHODE_table)/2)
	.hword ((cathode_E - TBB_CATHODE_table)/2)
	.hword ((cathode_F - TBB_CATHODE_table)/2)

	.thumb_func
cathode_0:
	CATHODE_write 0,0,0,0,0,0,1,1
	b continue

	.thumb_func
cathode_1:
	CATHODE_write 1,0,0,1,1,1,1,1
	b continue
	
	.thumb_func
cathode_2:
	CATHODE_write 0,0,1,0,0,1,0,1
	b continue
	
	.thumb_func
cathode_3:
	CATHODE_write 0,0,0,0,1,1,0,1
	b continue
	
	.thumb_func
cathode_4:
	CATHODE_write 1,0,0,1,1,0,0,1
	b continue
	
	.thumb_func
cathode_5:
	CATHODE_write 0,1,0,0,1,0,0,1
	b continue

	.thumb_func
cathode_6:
	CATHODE_write 0,1,0,0,0,0,0,1
	b continue
	
	.thumb_func
cathode_7:
	CATHODE_write 0,0,0,1,1,1,1,1
	b continue
	
	.thumb_func
cathode_8:
	CATHODE_write 0,0,0,0,0,0,0,1
	b continue
	
	.thumb_func
cathode_9:
	CATHODE_write 0,0,0,1,1,0,0,1
	b continue
	
	.thumb_func
cathode_A:
	CATHODE_write 0,0,0,1,0,0,0,1
	b continue

	.thumb_func
cathode_B:
	CATHODE_write 1,1,0,0,0,0,0,1
	b continue
	
	.thumb_func
cathode_C:
	CATHODE_write 0,1,1,0,0,0,1,1
	b continue
	
	.thumb_func
cathode_D:
	CATHODE_write 1,0,0,0,0,1,0,1
	b continue
	
	.thumb_func
cathode_E:
	CATHODE_write 0,1,1,0,0,0,0,1
	b continue
	
	.thumb_func
cathode_F:
	CATHODE_write 0,1,1,1,0,0,0,1
	b continue
	

continue:
	pop {r1}
	tbh [pc,r1]
TBB_ANODE_table:	@;table where offsets to code entry points are stored
	.hword ((anode_COLON  - TBB_ANODE_table)/2)
	.hword ((anode_DIGIT1 - TBB_ANODE_table)/2)
	.hword ((anode_DIGIT2 - TBB_ANODE_table)/2)
	.hword ((anode_DIGIT3 - TBB_ANODE_table)/2)
	.hword ((anode_DIGIT4 - TBB_ANODE_table)/2)

	.thumb_func
anode_COLON:
	ANODE_write 1,1,1,1,1,1,1,0
	b prt_end
	
	.thumb_func
anode_DIGIT1:
	ANODE_write 1,1,1,1,1,1,0,1
	b prt_end
	
	.thumb_func
anode_DIGIT2:
	ANODE_write 1,1,1,1,1,0,1,1
	b prt_end
	
	.thumb_func
anode_DIGIT3:
	ANODE_write 1,1,1,1,0,1,1,1
	b prt_end
	
	.thumb_func
anode_DIGIT4:
	ANODE_write 1,1,1,0,1,1,1,1
	b prt_end

prt_end: 
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	PORTBIT_write GPIOB_BASE,4,0			@;	01_PB4	AN_EN	-- enable anode   (active-low)
	@;b get_switch_pcont
	bx lr
	
	
	@;.global asm_set_switch
	@;.thumb_func
asm_set_switch:

	@;push {r0}

	PORTBIT_write GPIOC_BASE,1,1			@;	01_PC1	CA_EN	-- disable cathode (active-low)
	PORTBIT_write GPIOB_BASE,4,1			@;	01_PB4	AN_EN	-- disable anode   (active-low)

	@;pop {r0}
	tbh [pc,r0]
TBB_SWITCH_table:	@;table where offsets to code entry points are stored
	.hword ((switch_1 - TBB_SWITCH_table)/2)
	.hword ((switch_2 - TBB_SWITCH_table)/2)
	.hword ((switch_3 - TBB_SWITCH_table)/2)
	.hword ((switch_4 - TBB_SWITCH_table)/2)
	.hword ((switch_5 - TBB_SWITCH_table)/2)
	.hword ((switch_6 - TBB_SWITCH_table)/2)
	.hword ((switch_7 - TBB_SWITCH_table)/2)
	.hword ((switch_8 - TBB_SWITCH_table)/2)
	.hword ((switch_9 - TBB_SWITCH_table)/2)
	.hword ((switch_A - TBB_SWITCH_table)/2)
	.hword ((switch_B - TBB_SWITCH_table)/2)
	.hword ((switch_C - TBB_SWITCH_table)/2)
	.hword ((switch_D - TBB_SWITCH_table)/2)
	
	.thumb_func
switch_1:
	CATHODE_write 1,1,1,0,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,5,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_2:
	CATHODE_write 1,1,1,0,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,5,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_3:
	CATHODE_write 1,1,1,1,0,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,11,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_4:
	CATHODE_write 1,1,1,1,0,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,11,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_5:
	CATHODE_write 1,1,1,1,1,1,1,0
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,0,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_6:
	CATHODE_write 1,1,1,1,1,1,1,0
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,0,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_7:
	CATHODE_write 1,0,1,1,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,1,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_8:
	CATHODE_write 1,0,1,1,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOB_BASE,1,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_9:
	CATHODE_write 1,1,1,1,1,1,0,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOC_BASE,4,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_A:
	CATHODE_write 1,1,1,1,1,1,0,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOC_BASE,4,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_B:
	CATHODE_write 0,1,1,1,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOC_BASE,5,GPIOA_BASE,15
	b sw_end
	
	.thumb_func
switch_C:
	CATHODE_write 0,1,1,1,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOC_BASE,5,GPIOC_BASE,8
	b sw_end
	
	.thumb_func
switch_D:
	CATHODE_write 1,1,0,1,1,1,1,1
	PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	SWITCH_read GPIOA_BASE,1,GPIOA_BASE,15
	b sw_end
	
sw_end: 
	@;PORTBIT_write GPIOC_BASE,1,0			@;	01_PC1	CA_EN	-- enable cathode (active-low)
	@;PORTBIT_write GPIOB_BASE,4,0			@;	01_PB4	AN_EN	-- enable anode   (active-low)
	@;bx lr
	@;b cont
	push {r0,r1,r2,r3,lr}
	bl asm_vdisplay
	pop {r0,r1,r2,r3,lr}
	b cont
	
	.global asm_vdisplay
	.thumb_func
asm_vdisplay:
	ldr r0,=vdisplay
	ldr r3,=mux
	ldrh r1,[r3]
	
	ldr r2, [r0, r1, lsl #2]
	add r1,r1,#1
	
	cmp r1,#4
	ite ge
	movwge r0,#0
	movlt r0,r1
	str r0,[r3]
	
	@;mov r1,r0
	mov r0,r2
	
	b asm_print_digit
	
	
update_state:
	@; r0 - Switch #
	@; r1 - Raw Press: 0/1 (0 IS PRESSED)
	@; r2 - 
	@; r3 - 

	ldr r3,=sw_states
	ldr r2, [r3, r0, lsl #2]
	
	tbb [pc,r2]
STATE_table:
	.byte ((state_START - STATE_table)/2)
	.byte ((state_A - STATE_table)/2)
	.byte ((state_B - STATE_table)/2)
	.byte ((state_PRESS - STATE_table)/2)
	.byte ((state_C - STATE_table)/2)
	.byte ((state_D - STATE_table)/2)
	
	.thumb_func
state_START:
	cmp r1,#0
	bne loop_cont
	movw r2,ST_A	@; advance to state A
	str r2, [r3, r0, lsl #2]
	b loop_cont
	
	
	.thumb_func
state_A:
	cmp r1,#0
	bne a_ne
	movw r2,ST_B	@; advance to state B
	str r2, [r3, r0, lsl #2]
	b loop_cont
a_ne:
	@;push {r4,r5}
	movw r2,ST_Up	@; retreat to state START
	str r2, [r3, r0, lsl #2]
	@;pop {r4,r5}
	b loop_cont
	
	.thumb_func
state_B:
	cmp r1,#0
	bne b_ne
	movw r2,ST_Down	@; advance to state PRESS
	str r2, [r3, r0, lsl #2]
	b get_switch_save
b_ne:
	movw r2,ST_Up	@; retreat to state START
	str r2, [r3, r0, lsl #2]
	b loop_cont
	
	.thumb_func
state_PRESS:
	cmp r1,#0
	beq loop_cont
	movw r2,ST_C	@; advance to state C
	str r2, [r3, r0, lsl #2]
	b loop_cont
	
	.thumb_func
state_C:
	cmp r1,#0
	bne c_ne
	movw r2,ST_Down	@; retreat to state PRESS
	str r2, [r3, r0, lsl #2]
	b loop_cont
c_ne:
	movw r2,ST_D	@; advance to state D
	str r2, [r3, r0, lsl #2]
	b loop_cont
	
	.thumb_func
state_D:
	cmp r1,#0
	bne d_ne
	movw r2,ST_Down	@; retreat to state PRESS
	str r2, [r3, r0, lsl #2]
	b loop_cont
d_ne:
	movw r2,ST_Up	@; advance to state START
	str r2, [r3, r0, lsl #2]
	b get_switch_save
	
get_switch_save:
	@; r0 - Switch number
	@; r1 - Raw Press: 0/1 (0 IS PRESSED)
	
	eor r1,r1,#1
	
	movw r2,#0
	orr r2,r2,r1
	
	pop {r0}
	add r1,r0,#1	@; r0 is technically sw# - 1
	push {r0}
	lsl r1,r1,#1
	orr r2,r2,r1
	
	@;push {r1}
	ldr r0,=outarray
	str r2, [r0]
	
	@;pop {r0}
	@;add r1,r0,#1	@; r0 is technically sw# - 1
	@;push {r0}
	@;str r1, [r3, #4]@;r2, lsl #2]
	
	@;mov r2,#2
	@;ldrh r1,=asmticks
	@;ldr r0,[r1]
	@;str r0, [r3, r2, lsl #2]

	@;mov r0,r3	@; return outarray
	
	@;pop {r1}
	@;ldr r0,=vdisplay
	@;mov r2,#1
	@;str r1, [r0, r2, lsl #2]
	
	push {lr}
	bl queue
	pop {lr}
	
	b loop_cont
	
	
	.global asm_get_switch
	.thumb_func
asm_get_switch:
	push {lr}
	
	@;ldrh r1,=asmticks
	@;ldr r2,[r1]
	@;add r2,r2,#1
	@;str r2,[r1]
	
	movw r0, #0
	
get_switch_loop:
	push {r0}
	b asm_set_switch  @; makes it dim
cont:
	@;DEBUG_cmp 0
	mov r1,r0
	pop {r0}
	push {r0}
	b update_state
loop_cont:
	pop {r0}
	add r0,r0,#1
	cmp r0,#13
	blt get_switch_loop

get_switch_end:
	pop {lr}
	bx lr
	
	
	
	.global screw_it
	.thumb_func
screw_it:
	push {lr}
	
	ldr r2,=fifo
	ldm r2,{r0,r1}
	ldr r3,=vdisplay
	
	cmp r0,#0
	beq ayyy
	mov r2,#2
	str r1, [r3, r2, lsl #2]
	b screw_end
	
ayyy:
	mov r2,#0
	str r1, [r3, r2, lsl #2]

screw_end:
	pop {lr}
	bx lr



	.global asm_hw8_stuff
	.thumb_func
asm_hw8_stuff:
	push {lr}
	
	ldr r2,=fifo
	ldm r2,{r0,r1}
	ldr r3,=vdisplay
	
	cmp r0,#0
	beq hw8_release
	
@;press
	cmp r1,#1
	itt eq
	moveq r2,#0
	beq hw8_press_cont
	
	cmp r1,#3
	itt eq
	moveq r2,#1
	beq hw8_press_cont

	cmp r1,#5
	itt eq
	moveq r2,#2
	beq hw8_press_cont
	
	cmp r1,#7
	itt eq
	moveq r2,#3
	beq hw8_press_cont
	
	b hw8_end

hw8_press_cont:
	ldr r1, [r3, r2, lsl #2]
	cmp r1,#15
	it lt
	addlt r1,r1,#1
	str r1, [r3, r2, lsl #2]
	b hw8_end
	
hw8_release:
	cmp r1,#2
	itt eq
	moveq r2,#0
	beq hw8_release_cont
	
	cmp r1,#4
	itt eq
	moveq r2,#1
	beq hw8_release_cont

	cmp r1,#6
	itt eq
	moveq r2,#2
	beq hw8_release_cont
	
	cmp r1,#8
	itt eq
	moveq r2,#3
	beq hw8_release_cont
	
	b hw8_end
hw8_release_cont:
	ldr r1, [r3, r2, lsl #2]
	cmp r1,#0
	it gt
	subgt r1,r1,#1
	str r1, [r3, r2, lsl #2]

hw8_end:
	pop {lr}
	bx lr
