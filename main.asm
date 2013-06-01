/*.arm
.text
.global main

b main_ARM

.org 0xC0
main_ARM:
	mov r0, #0x08000000
	add r0, r0, #0xE1	@r0 = 0x080000E1
	bx r0			@When bx (address) @ ARM
				@When bx (address + 1) @ THUMB
/*
.thumb
.thumb_func
.align 2

/*.org 0xE0*/
main:
							@r0,r1,r2 = dynamic variables for loading and storing
							@r3 = current ball, r4 is key press timer, r5 is dirtomove, and r6 is circlevisible, r7 is timer
	push {r0-r7,lr}
	mov r3, #0x1					@Set current ball to center
	mov r5, #0x3					@Don't start accepting input until A press from yes/no is done
graphics_load:
	push {r3}
	@Load IO flags
	ldr r0, bgcnt
	ldrh r1, =0x1c40
	strh r1, [r0]

		ldr r0, bg2cnt 					@Set BG2 map loading offsets to load the tilemap from 0x06003800
	ldrh r1, bg2offsets				@Load half word
	bl writetoIO					@Store half word at bg2cnt


	ldr r0, bg3cnt 					@Set BG3 map loading offsets to load the tilemap from 0x06003000
	ldrh r1, bg3offsets				@Load half word
	bl writetoIO 					@Store half word at bg3cnt
	add r0, #0xA
	mov r1, #0x0
	bl writetoIO
	add r0, #0x2
	bl writetoIO
	add r0, #0x2
	bl writetoIO
	add r0, #0x2
	bl writetoIO

	@!!!!!!!!!!!!!@
	@Copy Graphics@					@BIG LONG GRAPHICS LOADING SECTION!
	@!!!!!!!!!!!!!@
	ldr r0, =ballpal
	/*mov r1, #0x90
	lsl r1, #0x14*/
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objpal_buffer
	mov r2, #8
	swi #0xC

	ldr r0, =grasspal
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgpal_buffer
	swi #0xC

	ldr r0, =bagpal
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgpal_buffer
	add r1, #0x20
	swi #0xC

	ldr r0, =grassraw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgdata
	swi #0x12

	ldr r0, =grasstm
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bg2tiles
	ldr r2, =0x180
	add r1, r2
	swi #0x12

	ldr r0, =bagraw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgdata
	ldr r2, =0xc00
	add r1, r2, r1
	swi #0x12

	ldr r0, =bagtm
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bg3tiles
	swi #0x12

	ldr r0, =ball1raw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objdata
	swi #0x12

	ldr r0, =ball2raw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objdata
	mov r3, #0x20
	lsl r3, #0x4
	add r1, r3, r1
	swi #0x12

	ldr r0, =ball3raw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objdata
	mov r3, #0x40
	lsl r3, #0x4
	add r1, r3, r1
	swi #0x12

	ldr r0, =ball3raw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objdata
	mov r3, #0x60
	lsl r3, #0x4
	add r1, r3, r1
	swi #0x12

	ldr r0, =pointerraw
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objdata
	mov r3, #0x80
	lsl r3, #0x4
	add r1, r3, r1
	swi #0x12

	ldr r0, oam_buffer
	ldrh r1, ball_lr_1
	strh r1, [r0]
	add r0, #0x2
	ldrh r1, ball_l_2
	strh r1, [r0]	
	add r0, #0x6

	ldrh r1, ball_c_1
	strh r1, [r0]
	add r0, #0x2
	ldrh r1, ball_c_2
	strh r1, [r0]	
	add r0, #0x6

	ldrh r1, ball_lr_1
	strh r1, [r0]
	add r0, #0x2
	ldrh r1, ball_r_2
	strh r1, [r0]	
	add r0, #0x6

	ldrh r1, ptr_c_1
	strh r1, [r0]
	add r0, #0x2
	ldrh r1, ptr_2
	strh r1, [r0]	
	add r0, #0x2
	ldrh r1, ptr_3
	strh r1, [r0]
	@!!!!!!!!!!!!!!!!!@
	@End Copy Graphics@				@END OF BIG LONG GRAPHICS LOADING SECTION!
	@!!!!!!!!!!!!!!!!!@
	pop {r3}
loop:	
	ldr r1, =0x1a0					@ASM iz too Fast. Needz limitationz
	cmp r7, r1
	blt halftimer
	mov r7, #0x0
	ldr r1, timer					@Load timer location
	ldrb r0, [r1] 					@Add to timer, wrap back if nececary.
	add r0, #0x1
	cmp r0, #155
	bge wipehalfway					@If timer is over 155 cycles, reset to 0
	strb r0, [r1]					@Otherwise, store added value
push_pallets:
	push {r3}
	@Load IO flags
	ldr r0, bgcnt
	ldrh r1, =0x1c40
	strh r1, [r0]

	ldr r0, bg2cnt 					@Set BG2 map loading offsets to load the tilemap from 0x06003800
	ldrh r1, bg2offsets				@Load half word
	bl writetoIO					@Store half word at bg2cnt


	ldr r0, bg3cnt 					@Set BG3 map loading offsets to load the tilemap from 0x06003000
	ldrh r1, bg3offsets				@Load half word
	bl writetoIO 					@Store half word at bg3cnt
	add r0, #0xA
	mov r1, #0x0
	bl writetoIO
	add r0, #0x2
	bl writetoIO
	add r0, #0x2
	bl writetoIO
	add r0, #0x2
	bl writetoIO

	

	pop {r3}

	@!!!!!!!!!!!!!@
	@Copy Graphics@					@BIG LONG GRAPHICS LOADING SECTION!
	@!!!!!!!!!!!!!@
	ldr r0, =ballpal
	/*mov r1, #0x90
	lsl r1, #0x14*/
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, objpal_buffer
	mov r2, #8
	@swi #0xC

	ldr r0, =grasspal
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgpal_buffer
	@swi #0xC

	ldr r0, =bagpal
	ldr r1, offsetyouinsertedthisat
	add r0, r1, r0
	ldr r1, bgpal_buffer
	add r1, #0x20
	@swi #0xC
	b resumeloop
wipehalfway:
	b wipetimer
writetoIO:
	@ldr r5, writeIO
	@bx r5
	bx lr
halftimer:
	add r7, #0x1
resumeloop:
	@bl waitvblank   					
	bl getinput    					@Get input
	bl updateballs					@Update ball animations
	bl addpointertimer
	bl updatepointerypos
	bl updatepointer				@Update pointer
checkexit:						@Update balls' sprite and pointer X position
	ldr r1, exitram					@See if it's time to exit...
	ldrb r0, [r1]
	cmp r0, #0x1
	beq exithalf					@If true, exit.
	b loop					@Otherwise, loop back.
updatepointerypos:
	ldr r0, pointerup
	ldrb r0, [r0]
	cmp r0, #0x1
	beq updatepointerypos_up

	ldr r0, pointertimer
	ldrh r1, [r0]
	ldr r2, pointerwait
	cmp r1, r2
	bne exitfunc

	ldr r0, pointerypos
	ldrb r1, [r0]
	add r1, #0x1
	cmp r1, #20
	bge setpointerdown
	strb r1, [r0]
	bx lr
setpointerdown:
	ldr r0, pointerup
	mov r1, #0x1
	strb r1, [r0]
	bx lr
updatepointerypos_up:
	ldr r0, pointertimer
	ldrh r1, [r0]
	ldr r2, pointerwait
	cmp r1, r2
	bne exitfunc

	ldr r0, pointerypos
	ldrb r1, [r0]
	sub r1, #0x1
	cmp r1, #0
	beq setpointerup
	strb r1, [r0]
	bx lr
setpointerup:
	ldr r0, pointerup
	mov r1, #0x0
	strb r1, [r0]
	bx lr
exitfunc:
	bx lr
addpointertimer:
	ldr r0, pointertimer
	ldrh r1, [r0]
	add r1, #0x1
	ldr r2, pointerwait
	cmp r1, r2
	bgt resetpointertimer
	strh r1, [r0]
	bx lr 
resetpointertimer:
	ldr r0, pointertimer
	mov r1, #0x0
	strh r1, [r0] 
updatepointer:	
	ldr r1, oam_buffer				@Pointer X pos = current ball X pos
	add r0, r3, #0x0
	mov r2, #0x8
	mul r0, r2
	add r0, #0x2
	add r1, r0, r1
	ldrh r0, [r1]
	ldr r1, oam_buffer
	mov r2, #27					@24 (pointer oam pos) + 3 for x pos
	add r1, r2, r1
	strh r0, [r1]
	sub r1, #0x2

	ldr r2, pointerypos				@Load pointer y difference
	ldrb r2, [r2]

	cmp r3, #0x1
	beq updatepointer_center			@Load different Y pos based on pokeball. Center is lower

	ldr r0, ptr_lr_1
	add r0, r2, r0
	strh r0, [r1]
	bx lr
updatepointer_center:
	ldr r0, ptr_c_1
	add r0, r2, r0
	strh r0, [r1]
	bx lr
wipetimer:
	mov r0, #0x0
	ldr r1, timer
	strb r0, [r1]
	b resumeloop
updateiobuffer:
	@ldr r0, copyio
	@bx r0
writeiobuffer:
	ldr r0, writeio
	bx r0
exithalf:					@Exit is too far from loop... wow.
	b exit
getinput:
	ldr r1, keys					@Check for key presses
	ldr r0, [r1]
	mvn r0, r0
	ldr r2, btn_a

	cmp r5, #0x3
	beq return_right

	mov r1, r0
	and r1, r2
	cmp r1, #0x0
	bgt a_press
return_a:						@A select ball, locks left+right input
	ldr r2, btn_b
	mov r1, r0
	and r1, r2
	cmp r1, #0x0
	bgt b_press
return_b:						@B cancels decision

	cmp r6, #0x1
	beq return_right

	ldr r2, btn_left
	mov r1, r0
	and r1, r2
	cmp r1, #0x0
	bgt left_press

	ldr r2, btn_right
	mov r1, r0
	and r1, r2
	cmp r1, #0x0
	bgt right_press
return_right:
	ldr r2, btn_allreading
	mov r1, r0
	and r1, r2
	cmp r1, #0x0
	beq wipebtntimer
	bx lr
wipebtntimer:
	mov r4, #0x0
	mov r5, #0x0
	bx lr
a_press:
	cmp r6, #0x1					@ If we already pressed it once (and it wasn't cancelled)
	beq a_press_confirm				@ Confirm our decision.
	beq return_a
	mov r5, #0x3
	mov r6, #0x1
	@TODO
	@Make Circle OEM show
	b return_a
a_press_confirm:
	ldr r1, exitram
	mov r2, #0x1
	strb r2, [r1]
	b return_a
b_press:
	mov r6, #0x0					@Cancel A press
	b return_b
left_press:
	cmp r3, #0x0					@We don't want r3 to wrap around to 0xFFFFFFFF.
	beq return_right

	ldr r1, oam_buffer				@Reset ball to normal position before moving.
	add r0, r3, #0x0
	mov r2, #0x8
	mul r0, r2
	add r0, #0x4
	add r1, r0, r1

	mov r0, #0x0
	strh r0, [r1]

	ldr r1, timer
	mov r0, #0x10					@Set timer to 0x10 to make it move immediately
	strb r0, [r1]

	sub r3, #0x1
	mov r5, #0x3
	b return_right
right_press:						@We only haz 3 balls. No more!
	cmp r3, #0x2
	beq return_right

	ldr r1, oam_buffer				@Reset ball to normal position before moving
	add r0, r3, #0x0
	mov r2, #0x8
	mul r0, r2
	add r0, #0x4
	add r1, r0, r1

	mov r0, #0x0
	strh r0, [r1]

	ldr r1, timer
	mov r0, #0x10					@Set timer to 0x10 to make it move immediately
	strb r0, [r1]

	add r3, #0x1
	mov r5, #0x3
	b return_right

@!!!!!!!!!!!@
@ BALL ANIM @
@!!!!!!!!!!!@
updateballs:					@Ball animation based on timer
	ldr r1, timer
	ldrb r0, [r1]
	cmp r0, #0
	beq bcenter
	cmp r0, #10
	beq bright
	cmp r0, #20
	beq bcenter
	cmp r0, #30
	beq bleft
	cmp r0, #40
	beq bcenter
	cmp r0, #50
	beq bright
	cmp r0, #60
	beq bcenter
	cmp r0, #70
	beq bleft
	cmp r0, #80
	beq bcenter
	cmp r0, #90
	beq bright
	cmp r0, #95
	beq bcenter
	cmp r0, #100
	beq bleft
	cmp r0, #105
	beq bcenter
	cmp r0, #110
	beq bright
	cmp r0, #116
	bge bcenter
	bx lr
bcenter:				@Set ball to upright image
	ldr r1, oam_buffer
	mov r0, r3
	mov r2, #0x8
	mul r0, r2
	add r0, #0x4
	add r1, r0, r1

	mov r0, #0x0
	strh r0, [r1]
	bx lr
bright:					@Make ball lean right
	ldr r1, oam_buffer
	mov r0, r3
	mov r2, #0x8
	mul r0, r2
	add r0, #0x4
	add r1, r0, r1

	mov r0, #0x10
	strh r0, [r1]
	bx lr
bleft:					@Make ball lean left
	ldr r1, oam_buffer
	mov r0, r3
	mov r2, #0x8
	mul r0, r2
	add r0, #0x4
	add r1, r0, r1

	mov r0, #0x20
	strh r0, [r1]
	bx lr
	
@!!!!!!!!!!!@
@ END ANIM @
@!!!!!!!!!!!@

exit:
	pop {r0-r7,pc}
	b exit

.align 2
offsetyouinsertedthisat: .word 0x09005000
@offsetyouinsertedthisat: .word 0x08000000
timer:      	.word 0x03000601 	@Something here...
exitram:    	.word 0x03000602 	@Need to find free RAM...
pointerup:    	.word 0x03000603 	@Need to find free RAM...
pointerypos:	.word 0x03000604	@Need to find free RAM...
pointertimer:	.word 0x03000606
writeIO:	.word 0x08000A39

pointerwait:	.word 0x00000190

bg2offsets: 	.word 0x00001c42	@IO Flags
bg3offsets: 	.word 0x00001e40

ball_lr_1:	.word 0x00000037	@I wish I commented these better. 0x37 is X pos
ball_l_2:	.word 0x0000802d	@0x2d is y pos. Ditto for other *_*_[1,2]

ball_c_1:	.word 0x0000004b
ball_c_2:	.word 0x00008067

ball_r_2:	.word 0x000080a0

ptr_c_1:	.word 0x0000001e
ptr_lr_1:	.word 0x0000000a
ptr_2:		.word 0x00008000
ptr_3:		.word 0x00000040

keys:		.word 0x04000130
btn_a:		.word 0x00000001
btn_b:		.word 0x00000002
btn_left:	.word 0x00000020
btn_right:	.word 0x00000010
btn_allreading:	.word 0x00000033

bgcnt:		.word 0x04000000	@Buffer is at 0x03000000, IO is at 0x04000000
bg2cnt: 	.word 0x0000000C
bg3cnt: 	.word 0x0000000E
bgpal:		.word 0x05000000
bgpal_buffer:	.word 0x020375F8
bgdata:		.word 0x06000000
bg2tiles:	.word 0x0600E000
bg3tiles:	.word 0x0600F000	@BG3 Tilemap location
copyio:		.word 0x080009C1
@copyio:		.word 0x08000AC5
writeio:	.word 0x080009c1

objpal:		.word 0x05000200	@OBJ pallet memory
objpal_buffer:	.word 0x020375F8 + (0x200) @Fire Red palette buffer
objdata:	.word 0x06010000	@OBJ tile data
oam:		.word 0x07000000	@OAM memory
oam_buffer:	.word 0x03003128	@Fire Red OAM buffer

.ltorg @This is where we start needing ldr rx, =xxx

ball1raw: 	.incbin "ball1.img.bin"	@All 3 ball images, and one shared palette (also used by pointer and circle).
ball2raw: 	.incbin "ball2.img.bin"
ball3raw: 	.incbin "ball3.img.bin"
ballpal: 	.incbin "ball1.pal.bin"

bagraw:		.incbin "bag.img.bin"	@Bag raw and palette, and tilemap
bagpal:		.incbin "bag.pal.bin"
bagtm:		.incbin "bagtm.lz.bin"

grassraw:	.incbin "grass.img.bin"	@Grass raw, palette, and tilemap
grasspal:	.incbin "bag.pal.bin"
grasstm:	.incbin "grasstm.lz.bin"

circleraw:	.incbin "circle.img.bin"	@Circle raw
pointerraw:	.incbin "pointer.img.bin"	@Pointer raw

