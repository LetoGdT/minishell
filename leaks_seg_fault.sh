#!/bin/bash

ASAN=1 make
echo $1 | ./minishell
ASAN=0 make re
echo $1 |  leaks -atExit -- ./minishell