
# Makefile for TTT_auto.c
INC = -I../../Logic -I../.. -I.
FC = frama-c -wp -cpp-command 'gcc -C -E $(INC)' -cpp-frama-c-compliant \
     -wp-skip-fct main -wp-skip-fct bot_input -wp-skip-fct human_input -wp-skip-fct bot_smart_move -wp-skip-fct bot_sub_move -wp-skip-fct display -wp-skip-fct check_winner -wp-skip-fct game_init -wp-rte


all: verify test

verify: TTT_auto.c
	$(FC) TTT_auto.c

test: TTT_auto.c
		gcc -o TTT TTT_auto.c
		./TTT